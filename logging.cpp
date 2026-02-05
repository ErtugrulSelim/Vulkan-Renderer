#include "logging.h"

VKAPI_ATTR vk::Bool32 VKAPI_CALL vkInit::debugCallback(
	vk::DebugUtilsMessageSeverityFlagBitsEXT messageSeverity,
	vk::DebugUtilsMessageTypeFlagsEXT messageType,
	const vk::DebugUtilsMessengerCallbackDataEXT* pCallbackData,
	void* pUserData
) {
	// std::cerr Vulkan-HPP tarafından tanımlanmaz, <iostream>'ı dahil ettiğinizden emin olun.
	std::cerr << "validation layer: " << pCallbackData->pMessage << std::endl;

	return vk::False; // vk::Bool32 için vk::False kullanılır
}

// 2. Debug Messenger Oluşturma Fonksiyonu Tanımı
vk::DebugUtilsMessengerEXT vkInit::make_debug_messenger(vk::Instance& instance, vk::detail::DispatchLoaderDynamic& dldi) {

	// Deprecated (C4996) uyarısını ve eski flag uyarılarını çözen modern oluşturucu (constructor) kullanımı:
	vk::DebugUtilsMessengerCreateInfoEXT createInfo = vk::DebugUtilsMessengerCreateInfoEXT(
		{}, // flags (vk::DebugUtilsMessengerCreateFlagsEXT{} veya {})
		vk::DebugUtilsMessageSeverityFlagBitsEXT::eVerbose
		| vk::DebugUtilsMessageSeverityFlagBitsEXT::eWarning
		| vk::DebugUtilsMessageSeverityFlagBitsEXT::eError, // messageSeverity
		vk::DebugUtilsMessageTypeFlagBitsEXT::eGeneral
		| vk::DebugUtilsMessageTypeFlagBitsEXT::eValidation
		| vk::DebugUtilsMessageTypeFlagBitsEXT::ePerformance, // messageType
		vkInit::debugCallback, // pfnUserCallback (Yeni imzalı fonksiyon işaretçisi)
		nullptr // pUserData
	);

	// createDebugUtilsMessengerEXT, vk::DispatchLoaderDynamic ile çağrılır.
	return instance.createDebugUtilsMessengerEXT(createInfo, nullptr, dldi);
}