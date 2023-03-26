#pragma once
#include <core.h>
#include <enpch.hpp>

// ---- ---- ---- ---- ---- 
#ifdef PLATFORM_WINDOWS
	#include <platform/windows/WindowsWindow.hpp>
#endif

#include <app/app.hpp>
#include <log/log.hpp>

#include <events/event.hpp>
#include <events/AppEvent.hpp>
#include <events/KeyEvent.hpp>
#include <events/MouseEvent.hpp>

