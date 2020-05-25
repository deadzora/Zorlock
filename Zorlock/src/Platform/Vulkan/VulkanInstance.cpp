#include "ZLpch.h"
#include "VulkanInstance.h"
#include "glfw3.h"

#include <sstream>
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

VkBool32 debugMsgCallback(VkDebugReportFlagsEXT flags, VkDebugReportObjectTypeEXT objType, uint64_t srcObject,
    size_t location, int32_t msgCode, const char* pLayerPrefix, const char* pMsg, void* pUserData)
{
    std::stringstream message;

    // Determine prefix
    if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
        message << "ERROR";

    if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT)
        message << "WARNING";

    if (flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
        message << "PERFORMANCE";

    if (flags & VK_DEBUG_REPORT_INFORMATION_BIT_EXT)
        message << "INFO";

    if (flags & VK_DEBUG_REPORT_DEBUG_BIT_EXT)
        message << "DEBUG";

    message << ": [" << pLayerPrefix << "] Code " << msgCode << ": " << pMsg << std::endl;

    if (flags & VK_DEBUG_REPORT_ERROR_BIT_EXT)
        ZL_CORE_ERROR(message.str());
    else if (flags & VK_DEBUG_REPORT_WARNING_BIT_EXT || flags & VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT)
        ZL_CORE_WARN(message.str());
    else
        ZL_CORE_INFO(message.str());

    // Don't abort calls that caused a validation message
    return VK_FALSE;
}

namespace Zorlock
{
	VulkanInstance::VulkanInstance()
	{
	}

	void VulkanInstance::CreateInstance(VkInstance& m_Instance, VkDebugReportCallbackEXT& m_debugMessenger)
	{
        extensions[0] = VK_KHR_SURFACE_EXTENSION_NAME;
        uint32_t numExtensions = sizeof(extensions) / sizeof(extensions[0]);

        VkApplicationInfo appInfo{};
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.pApplicationName = " ";
        appInfo.applicationVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.pEngineName = "Zorlock Engine";
        appInfo.engineVersion = VK_MAKE_VERSION(1, 0, 0);
        appInfo.apiVersion = VK_API_VERSION_1_2;

        VkInstanceCreateInfo InstanceData{};
        InstanceData.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        InstanceData.pNext = nullptr;
        InstanceData.flags = 0;
        InstanceData.pApplicationInfo = &appInfo;
        InstanceData.enabledLayerCount = numLayers;
        InstanceData.ppEnabledLayerNames = layers;
        InstanceData.enabledExtensionCount = numExtensions;
        InstanceData.ppEnabledExtensionNames = extensions;


        vkCreateInstance(&InstanceData, nullptr, &m_Instance);
        
#if ZL_DEBUG
        VkDebugReportFlagsEXT debugFlags = VK_DEBUG_REPORT_ERROR_BIT_EXT | VK_DEBUG_REPORT_WARNING_BIT_EXT |
            VK_DEBUG_REPORT_PERFORMANCE_WARNING_BIT_EXT;

        vkGetInstanceProcAddr(m_Instance, "vkCreateDebugUtilsMessengerEXT");
        vkGetInstanceProcAddr(m_Instance, "vkDestroyDebugUtilsMessengerEXT");

        VkDebugReportCallbackCreateInfoEXT debugInfo;
        debugInfo.sType = VK_STRUCTURE_TYPE_DEBUG_REPORT_CREATE_INFO_EXT;
        debugInfo.pNext = nullptr;
        debugInfo.flags = 0;
        debugInfo.pfnCallback = (PFN_vkDebugReportCallbackEXT)debugMsgCallback;
        debugInfo.flags = debugFlags;

        vkCreateDebugReportCallbackEXT(m_Instance, &debugInfo, nullptr, &m_debugMessenger);
#endif
	}
}