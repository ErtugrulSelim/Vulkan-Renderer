#pragma once
#include "config.h"
#include "queue_families.h"

namespace vkInit {

	struct commandBufferInputChunk {
		vk::Device device;
		vk::CommandPool commandPool;
		std::vector<vkUtil::FrameData>& frames;
	}; 

	vk::CommandPool make_command_pool(vk::Device device, vk::PhysicalDevice physicalDevice, vk::SurfaceKHR surface, bool debug) {
		
		// Find the queue family indices for the physical device
		vkUtil::QueueFamilyIndices queueFamilyIndices = vkUtil::findQueueFamilies(physicalDevice, surface, debug); 

		vk::CommandPoolCreateInfo poolInfo{};\
		// Specify the command pool creation parameters
		poolInfo.flags = vk::CommandPoolCreateFlags() | vk::CommandPoolCreateFlagBits::eResetCommandBuffer;
		// Set the queue family index for the command pool. eResetCommandBuffer flag allows command buffers to be reset individually rather than resetting the entire pool.
		poolInfo.queueFamilyIndex = queueFamilyIndices.graphicsFamily.value();

		try {
			return device.createCommandPool(poolInfo);
		}
		catch (vk::SystemError err) {
			std::cout << "Failed to create Command Pool" << std::endl;
		}

		return nullptr;
	}

	std::vector<vk::CommandBuffer> make_command_buffer(commandBufferInputChunk inputChunk, int count, bool debug) {
		 
		inputChunk.frames.resize(2);
		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.commandPool = inputChunk.commandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = (uint32_t)inputChunk.frames.size();

	
		try {
			std::vector<vk::CommandBuffer> commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo);

			if (debug) {
				std::cout << "Allocated main command buffer" << std::endl;
			}

			return commandBuffer;
		}
		catch (vk::SystemError err) {

			if (debug) {
				std::cout << "Failed to allocate main command buffer" << std::endl;
			}
			return {};
		}
	}
	void make_frame_command_buffers(commandBufferInputChunk inputChunk, bool debug) {

		vk::CommandBufferAllocateInfo allocInfo = {};
		allocInfo.commandPool = inputChunk.commandPool;
		allocInfo.level = vk::CommandBufferLevel::ePrimary;
		allocInfo.commandBufferCount = 1;

		//Make a command buffer for each frame
		for (int i = 0; i < inputChunk.frames.size(); ++i) {
			try {
				inputChunk.frames[i].commandBuffer = inputChunk.device.allocateCommandBuffers(allocInfo)[0];

				if (debug) {
					std::cout << "Allocated command buffer for frame " << i << std::endl;
				}
			}
			catch (vk::SystemError err) {

				if (debug) {
					std::cout << "Failed to allocate command buffer for frame " << i << std::endl;
				}
			}
		}
	}
}