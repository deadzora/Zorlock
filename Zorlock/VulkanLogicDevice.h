#pragma once
#include "vulkan.h"
#include <optional>

namespace Zorlock
{
	class VulkanLogicDevice
	{
	public:
		~VulkanLogicDevice() = default;

		void CreateLogicDevice(VkDevice m_logDevice, VkPhysicalDevice m_physDevice, VkQueue m_gQueue, VkQueue m_pQueue, VkSurfaceKHR m_surface);
	};
}