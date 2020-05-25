#include "ZLpch.h"
#include "VulkanDevice.h"

namespace Zorlock
{
	void VulkanDevice::EnumerateDevices(VkPhysicalDevice& m_device, VkInstance m_instance)
	{
		// Enumerate all devices
		auto m_numDevices = uint32_t{0};
		vkEnumeratePhysicalDevices(m_instance, &m_numDevices, nullptr);

		auto physDevices =std::vector<VkPhysicalDevice>(m_numDevices);
		vkEnumeratePhysicalDevices(m_instance, &m_numDevices, physDevices.data());
		

		for (const auto& device : physDevices)
		{
			auto props = VkPhysicalDeviceProperties{};
			vkGetPhysicalDeviceProperties(device, &props);

			if (props.deviceType == VkPhysicalDeviceType::VK_PHYSICAL_DEVICE_TYPE_DISCRETE_GPU)
			{
				m_device = device;
			}
			else
			{
				m_device = VK_NULL_HANDLE;
			}
		}

		if (m_device == VK_NULL_HANDLE)
		{
			throw std::runtime_error("failed to find a suitable GPU");
		}
		
	}
}