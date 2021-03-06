#pragma once

#include "../Core/application.h"
#include "../GraphicsAPI/vk_engine.h"
#include "../Utils/defines.h"
#include "../Utils/logger.h"


#ifdef PLATFORM_WINDOWS

extern kuvlan::application* kuvlan::create_application();

int main(int argc, char** argv)
{
	kuvlan::logger::init();
	KV_CORE_INFO("Test sandbox app initialized");

	auto app = kuvlan::create_application();
	// kuvlan::vk_engine engine = kuvlan::vk_engine();
	app->run();
	//engine.cleanup();
	delete app;
}
#endif