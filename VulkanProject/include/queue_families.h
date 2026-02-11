#pragma once
#include "config.h"

namespace vkUtil {

	struct QueueFamilyIndices {
		std::optional<uint32_t> graphicsFamily;
		std::optional<uint32_t> presentFamily;

		/**
			\returns whether all of the Queue family indices have been set.
		*/
		bool isComplete() {
			return graphicsFamily.has_value() && presentFamily.has_value();
		}
	};

	/**
		Find suitable queue family indices on the given physical device.

		\param device the physical device to check
		\param debug whether the system is running in debug mode
		\returns a struct holding the queue family indices
	*/
	inline QueueFamilyIndices findQueueFamilies(vk::PhysicalDevice device, vk::SurfaceKHR surface, bool debug) {
		QueueFamilyIndices indices;

		// Get the list of queue families supported by the device example 0 is graphics, 1 is compute, etc.
		std::vector<vk::QueueFamilyProperties> queueFamilies = device.getQueueFamilyProperties();

		if (debug) {
			std::cout << "There are " << queueFamilies.size() << " queue families available on the system.\n";
		}

		int i = 0;
		for (vk::QueueFamilyProperties queueFamily : queueFamilies) {


			if (queueFamily.queueFlags & vk::QueueFlagBits::eGraphics) {
				indices.graphicsFamily = i;

				if (debug) {
					std::cout << "Queue Family " << i << " is suitable for graphics\n";
				}
			}

			if (device.getSurfaceSupportKHR(i, surface)) {
				indices.presentFamily = i;

				if (debug) {
					std::cout << "Queue Family " << i << " is suitable for presenting\n";
				}
			}

			if (indices.isComplete()) {
				break;
			}

			i++;
		}

		return indices;
	}
}