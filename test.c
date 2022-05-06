#include <vulkan/vulkan.h>
#include <stdint.h>

int main(void) {
        VkApplicationInfo appInfo = { 0 };
        appInfo.sType = VK_STRUCTURE_TYPE_APPLICATION_INFO;
        appInfo.apiVersion = VK_API_VERSION_1_0;

        VkInstanceCreateInfo instanceCreateInfo = { 0 };
        instanceCreateInfo.sType = VK_STRUCTURE_TYPE_INSTANCE_CREATE_INFO;
        instanceCreateInfo.pApplicationInfo = &appInfo;

        VkInstance instance;
        vkCreateInstance(&instanceCreateInfo, NULL, &instance);

        uint32_t deviceCount = 1;
        VkPhysicalDevice physicalDevice;
        vkEnumeratePhysicalDevices(instance, &deviceCount, &physicalDevice);

        float queuePriority = 1.0f;

        VkDeviceQueueCreateInfo queueCreateInfo = { 0 };
        queueCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_QUEUE_CREATE_INFO;
        queueCreateInfo.queueFamilyIndex = 0;
        queueCreateInfo.queueCount = 1;
        queueCreateInfo.pQueuePriorities = &queuePriority;

        VkDeviceCreateInfo deviceCreateInfo = { 0 };
        deviceCreateInfo.sType = VK_STRUCTURE_TYPE_DEVICE_CREATE_INFO;
        deviceCreateInfo.pQueueCreateInfos = &queueCreateInfo;
        deviceCreateInfo.queueCreateInfoCount = 1;

        VkDevice device;
        vkCreateDevice(physicalDevice, &deviceCreateInfo, NULL, &device);

        VkQueue queue;
        vkGetDeviceQueue(device, 0, 0, &queue);

        VkCommandPoolCreateInfo info = { 0 };
        info.queueFamilyIndex = 0;

        VkCommandPool pool;
        vkCreateCommandPool(device, &info, NULL, &pool);

        VkCommandBufferAllocateInfo allocateInfo = { 0 };
        allocateInfo.commandPool = pool;
        allocateInfo.commandBufferCount = 1;

        VkCommandBuffer buffer;
        vkAllocateCommandBuffers(device, &allocateInfo, &buffer);

        VkSubmitInfo submitInfo = { 0 };
        submitInfo.pCommandBuffers = &buffer;
        submitInfo.commandBufferCount = 1;

        vkQueueSubmit(queue, 1, &submitInfo, VK_NULL_HANDLE);
}
