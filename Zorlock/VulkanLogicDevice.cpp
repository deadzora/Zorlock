#include "ZLpch.h"
#include "VulkanLogicDevice.h"
#include <set>

#if ZL_DEBUG
const char* layers[] =
{
    "VK_LAYER_LUNARG_standard_validation"
};

const char* extensions[] =
{
    VK_KHR_SURFACE_EXTENSION_NAME,
    nullptr, /** Surface extension */
    nullptr, /** OS specific surface extension */
    VK_EXT_DEBUG_REPORT_EXTENSION_NAME
};

uint32_t numLayers = sizeof(layers) / sizeof(layers[0]);
#else
const char** layers = nullptr;
const char* extensions[] =
{
    nullptr, /** Surface extension */
    nullptr, /** OS specific surface extension */
};

uint32_t numLayers = 0;
#endif

namespace Zorlock
{
    struct QueueFamilyIndices {
        std::optional<uint32_t> graphicsFamily;
        std::optional<uint32_t> presentFamily;

        bool isComplete() {
            return graphicsFamily.has_value() && presentFamily.has_value();
        }
    };

    QueueFamilyIndices findQueueFamilies(VkPhysicalDevice device, VkSurfaceKHR m_surface) {
        QueueFamilyIndices indices;

        uint32_t queueFamilyCount = 0;
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, nullptr);

        std::vector<VkQueueFamilyProperties> queueFamilies(queueFamilyCount);
        vkGetPhysicalDeviceQueueFamilyProperties(device, &queueFamilyCount, queueFamilies.data());

        int i = 0;
        for (const auto& queueFamily : queueFamilies) {
            if (queueFamily.queueFlags & VK_QUEUE_GRAPHICS_BIT) {
                indices.graphicsFamily = i;
            }

            VkBool32 presentSupport = false;
            vkGetPhysicalDeviceSurfaceSupportKHR(device, i, m_surface, &presentSupport);

            if (presentSupport)
            {
                indices.presentFamily = i;
            }

            if (indices.isComplete()) {
                break;
            }

            i++;
        }

        return indices;
    }

	void VulkanLogicDevice::CreateLogicDevice(VkDevice m_logDevice, VkPhysicalDevice m_physDevice, VkQueue m_gQueue, VkQueue m_pQueue, VkSurfaceKHR m_surface)
	{
        QueueFamilyIndices indices = findQueueFamilies(m_physDevice, m_surface);

        std::vector<VkDeviceQueueCreateInfo> queueCreateInfos;
        std::set<uint32_t> uniqueQueueFamilies = { indices.graphicsFamily.value(), indices.presentFamily.value() };

        float queuePriority = 1.0f;
        for (uint32_t queueFamily : uniqueQueueFamilies)
        {
            VkDeviceQueueCreateInfo queueCreateInfo{};
            queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
            queueCreateInfo.queueFamilyIndex = indices.graphicsFamily.value();
            queueCreateInfo.queueCount = 1;
            queueCreateInfo.pQueuePriorities = &queuePriority;
            queueCreateInfos.push_back(queueCreateInfo);
        }

        VkPhysicalDeviceFeatures deviceFeatures{};

        VkDeviceCreateInfo createInfo{};
        createInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        createInfo.queueCreateInfoCount = static_cast<uint32_t>(queueCreateInfos.size());
        createInfo.pQueueCreateInfos = queueCreateInfos.data();

        createInfo.pEnabledFeatures = &deviceFeatures;

        createInfo.enabledLayerCount = numLayers;
        createInfo.ppEnabledLayerNames = layers;

        if (vkCreateDevice(m_physDevice, &createInfo, nullptr, &m_logDevice) != VK_SUCCESS) {
            throw std::runtime_error("failed to create logical device!");
        }

        vkGetDeviceQueue(m_logDevice, indices.graphicsFamily.value(), 0, &m_gQueue);
        vkGetDeviceQueue(m_logDevice, indices.presentFamily.value(), 0, &m_pQueue);
	}

    
}
