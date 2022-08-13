#pragma once

#include <vector>
#include <functional>

#include "logger.h"
#include "../imgui/imgui.h"
#include "../imgui/imgui_internal.h"
#include "../imgui/imgui_impl_android.h"
#include "../imgui/imgui_impl_opengl3.h"

static bool g_initialized = false;

namespace menu{
    void menu_style();
    void setup_menu();
    void draw_menu(int width, int height);
}
