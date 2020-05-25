#pragma once
#include "vulkan.h"
namespace Zorlock
{
	class VulkanInstance
	{
	public:
		VulkanInstance();
		~VulkanInstance() = default;
		void CreateInstance(VkInstance& m_instance, VkDebugReportCallbackEXT& m_debugMessenger);
	};
}