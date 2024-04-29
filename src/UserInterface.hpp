#pragma once
#include <array>

#include "Vulkan/Vulkan.hpp"
#include <memory>
#include <UserTelemetry.hpp>
#include <vector>

namespace Vulkan
{
	class CommandPool;
	class DepthBuffer;
	class DescriptorPool;
	class FrameBuffer;
	class RenderPass;
	class SwapChain;
}

struct UserSettings;

struct Statistics final
{
	VkExtent2D FramebufferSize;
	float FrameRate;
	float RayRate;
	uint32_t TotalSamples;
	uint32_t OccupancyAmountSubgroups;
	uint32_t OccupancyAmountActiveLanes;
	std::vector<float> OccupancyPercentage;
};

class UserInterface final
{
public:

	VULKAN_NON_COPIABLE(UserInterface)

	UserInterface(
		Vulkan::CommandPool& commandPool, 
		const Vulkan::SwapChain& swapChain, 
		const Vulkan::DepthBuffer& depthBuffer,
		UserSettings& userSettings,
		UserTelemetry& userTelemetry);
	~UserInterface();

	void Render(VkCommandBuffer commandBuffer, const Vulkan::FrameBuffer& frameBuffer, const Statistics& statistics);

	bool WantsToCaptureKeyboard() const;
	bool WantsToCaptureMouse() const;

	UserSettings& Settings() { return userSettings_; }
	UserTelemetry& Telemetry() { return userTelemetry_; }

private:

	void DrawSettings();
	void DrawOverlay(const Statistics& statistics);

	std::unique_ptr<Vulkan::DescriptorPool> descriptorPool_;
	std::unique_ptr<Vulkan::RenderPass> renderPass_;
	UserSettings& userSettings_;
	UserTelemetry& userTelemetry_;
};
