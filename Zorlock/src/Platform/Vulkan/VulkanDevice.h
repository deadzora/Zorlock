#pragma once

#include "vulkan.h"
#include <iostream>

namespace Zorlock
{
	class VulkanDevice
	{
	public:
		~VulkanDevice() = default;

		void EnumerateDevices(VkPhysicalDevice& m_device, VkInstance m_instance);


	};
}