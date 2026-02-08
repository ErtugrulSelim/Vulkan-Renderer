#pragma once
#include "config.h"
#include "frame.h"

class Engine {

public:

	Engine(int width, int height, GLFWwindow* window, bool debug);

	~Engine();

	void render();

private:

	//whether to print debug messages in functions
	bool debugMode = true;

	//glfw window parameters
	int width{ 1080 };
	int height{ 1080 };
	GLFWwindow* window{ nullptr };

	vk::Instance instance{ nullptr };
	vk::DebugUtilsMessengerEXT debugMessenger{ nullptr };
	vk::detail::DispatchLoaderDynamic dldi;
	vk::SurfaceKHR surface;

	//device-related variables
	vk::PhysicalDevice physicalDevice{ nullptr };
	vk::Device device{ nullptr };
	vk::Queue graphicsQueue{ nullptr };
	vk::Queue presentQueue{ nullptr };
	vk::SwapchainKHR swapchain{ nullptr };
	std::vector<vkUtil::SwapChainFrame> swapchainFrames;
	std::vector<vkUtil::FrameData> frameData;
	vk::Format swapchainFormat;
	vk::Extent2D swapchainExtent;

	//pipeline-related variables
	vk::PipelineLayout pipelineLayout;
	vk::RenderPass renderpass;
	vk::Pipeline pipeline;

	//command-related variables
	vk::CommandPool commandPool;
	vk::CommandBuffer mainCommandBuffer;

	//synchronization-related variables
	int maxFramesInFlight, frameNumber;


	//glfw setup
	void build_glfw_window();

	//instance setup
	void make_instance();

	void make_device();

	//pipeline setup
	void make_pipeline();

	void finalize_setup();

	void record_draw_commands(vk::CommandBuffer commandBuffer, uint32_t imageIndex);
};	