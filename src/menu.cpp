#include "includes/menu.h"

namespace menu{
    void menu_style(){
        //setup your menu style here
    }

    void setup_menu(){
        if(g_initialized) return;

        auto ctx = ImGui::CreateContext();
        if(!ctx) {
            LOGI("Failed to create context");
            return;
        }

        ImGuiIO& io = ImGui::GetIO();
        io.IniFilename = NULL;

        menu_style();

        // Setup Platform/Renderer backends
        ImGui_ImplAndroid_Init(nullptr);
        ImGui_ImplOpenGL3_Init();

        ImFontConfig font_cfg;
        font_cfg.SizePixels = 20.0f;
        io.Fonts->AddFontDefault(&font_cfg);
        ImGui::GetStyle().ScaleAllSizes(2.5f);

        g_initialized = true;
        LOGI("setup done.");
    }

    void draw_menu(int width, int height){
        if(!g_initialized) return;

        ImGuiIO &io = ImGui::GetIO();

        ImGui_ImplOpenGL3_NewFrame();

        ImGui_ImplAndroid_NewFrame(width, height);

        ImGui::NewFrame();
        ImGui::Begin("Hello, world!"); // Create a window called "Hello, world!" and append into it.


        ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
        ImGui::End();

        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        ImGui::EndFrame();
    }
}
