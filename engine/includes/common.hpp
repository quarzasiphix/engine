#pragma once
#include <core.h>
#include <enpch.hpp>

// ---- ---- ---- ---- ---- 
#include <log/log.hpp>
#include <app/app.hpp>

#include <renderer/renderer.hpp>


#define DEF_ENGINE_API class ENGINE_API Event; \ 
						class ENGINE_API opengl; \
						class ENGINE_API WindowCloseEvent;
