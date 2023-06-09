#define HACK
#include "gui.hpp"

namespace engine {
    gui::gui(GLFWwindow* m_window)
    : m_window(m_window) {
        onAttach();
    }

    gui::~gui() {
        onDetach();
    }

    void gui::onAttach() {
        this->m_window = m_window;
        // Setup Dear ImGui context
        // Setup Dear ImGui context
        IMGUI_CHECKVERSION();
        ImGui::CreateContext();
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
        io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
        io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
        io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
        //io.ConfigViewportsNoAutoMerge = true;
        //io.ConfigViewportsNoTaskBarIcon = true;
        //io.ConfigViewportsNoDefaultParent = true;
        //io.ConfigDockingAlwaysTabBar = true;
        //io.ConfigDockingTransparentPayload = true;
        //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleFonts;     // FIXME-DPI: Experimental. THIS CURRENTLY DOESN'T WORK AS EXPECTED. DON'T USE IN USER APP!
        //io.ConfigFlags |= ImGuiConfigFlags_DpiEnableScaleViewports; // FIXME-DPI: Experimental.

        // Setup Dear ImGui style
        ImGui::StyleColorsDark();
        //ImGui::StyleColorsLight();

        // When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
        ImGuiStyle& style = ImGui::GetStyle();
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            style.WindowRounding = 0.0f;
            style.Colors[ImGuiCol_WindowBg].w = 1.0f;
        }

        // Setup ImGui context
        ImGui_ImplGlfw_InitForOpenGL(m_window, true);
        ImGui_ImplOpenGL3_Init("#version 330 core");

        initialised = true;
        EN_CORE_INFO("initialised imgui");

    }
    
    void gui::onDetach() {
        ImGui_ImplOpenGL3_Shutdown();
        ImGui_ImplGlfw_Shutdown();
        ImGui::DestroyPlatformWindows(); // destroy all platform windows
        ImGui::DestroyContext();
    }

    /*
    void gui::windowResizeEvent() {
        float xscale, yscale;
        glfwGetWindowContentScale(m_window, &xscale, &yscale);
        ImGui::GetIO().FontGlobalScale = xscale;
        ImGui::GetIO().DisplayFramebufferScale = ImVec2(xscale, yscale);
    }
    */

    /*void gui::onResize(windowResizeEvent& e) {

    }*/

    void gui::onEvent(event& e) {
        eventDispatcher dispatcher(e);
        //dispatcher.dispatch<windowResizeEvent>(BIND_EVENT_FN(gui::onResize));


    }


    void dock(gui* e) {                                                                                                                                                                         

        //opengl::WindowData& data = *(opengl::WindowData*)glfwGetWindowUserPointer(e->m_window);
        //ImGui::SetNextWindowSize(ImVec2((float)data.Width, (float)data.Height));

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoBringToFrontOnFocus;
        if (ImGui::GetIO().ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            //dockspace_flags |= ImGuiDockNodeFlags_PassthruCentralNode;
            window_flags |= ImGuiWindowFlags_NoBackground;
        }
        
        ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
        ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
        ImGui::Begin("Dockspace", nullptr, window_flags);

        ImGui::End();

    }

    bool HAKOR = false;

    bool open_ui = true;
    void gui::ui() {

        ImGuiWindowFlags window_flags = ImGuiWindowFlags_NoBringToFrontOnFocus;
        // Set up the viewport for each window
        //ImGuiViewport* viewport = ImGui::GetMainViewport();
        //ImGui::SetNextWindowSize(ImGui::GetMainViewport()->Size);
        //ImGui::SetNextWindowPos(ImGui::GetMainViewport()->Pos);
        ImGui::Begin("yoo", &open_ui, window_flags);
        
        ImGui::ColorEdit3("clear color", (float*)&this->clear_color);
        ImGui::Text("sup");
        if (HAKOR == false) {
            HAKOR = true;
            hack = new hack::hackor();
        }

        ImGui::End();
    }

    void gui::onUpdate() { 
        //// Start ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        //dock(this);

        ui();
        if (HAKOR == true) hack->onUpdate();

        ImGui::ShowDemoWindow();

        ImGui::Render();

        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
        ImGuiIO& io = ImGui::GetIO(); (void)io;
        if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
            GLFWwindow* backup_current_context = glfwGetCurrentContext();
            ImGui::UpdatePlatformWindows();
            ImGui::RenderPlatformWindowsDefault();
            glfwMakeContextCurrent(backup_current_context); 
        }
        /*
        glfwGetFramebufferSize(this->m_window, &this->display_w, &this->display_h);
        glClearColor(this->clear_color.x * this->clear_color.w, this->clear_color.y * this->clear_color.w, this->clear_color.z * this->clear_color.w, this->clear_color.w);
        glClear(GL_COLOR_BUFFER_BIT); // clear color buffer with the specified color
        glViewport(0, 0, this->display_w, this->display_h);
        */
    }

}
/* // old test at adding a gui from sandbox
    void gui::addui(void(*ui)(gui& g)) {
        onRender = ui;
    }*/
