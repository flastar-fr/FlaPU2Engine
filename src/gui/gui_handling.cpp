#include "gui_handling.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"
#include <cstdio>

#include "windows_creation.hpp"

static void glfw_error_callback(const int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void clean_window(GLFWwindow* window) {
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(window);
    glfwTerminate();
}

void render_window(GLFWwindow* window, const ImGuiIO& io, const ImVec4 clear_color) {
    ImGui::Render();
    int display_w, display_h;
    glfwGetFramebufferSize(window, &display_w, &display_h);
    glViewport(0, 0, display_w, display_h);
    glClearColor(clear_color.x * clear_color.w, clear_color.y * clear_color.w, clear_color.z * clear_color.w,
                 clear_color.w);
    glClear(GL_COLOR_BUFFER_BIT);
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window);

    if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
        GLFWwindow* backup_current_context = glfwGetCurrentContext();
        ImGui::UpdatePlatformWindows();
        ImGui::RenderPlatformWindowsDefault();
        glfwMakeContextCurrent(backup_current_context);
    }
}

void handle_frame_creation() {
    glfwPollEvents();

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void loop_iteration(GLFWwindow* window, const ImGuiIO& io, const ImVec4 clear_color, Engine& engine) {
    handle_frame_creation();

    if (!engine.isProgramFinished()) engine.executeNextInstruction();

    display_registers(engine.getRegisters());
    display_memory(engine.getMemory());

    render_window(window, io, clear_color);
}

bool setup_glfw(const char*& glsl_version, GLFWwindow*& window, int& exit_code) {
    glfwSetErrorCallback(glfw_error_callback);
    if (!glfwInit()) {
        exit_code = 1;
        return true;
    }

#if defined(IMGUI_IMPL_OPENGL_ES2)
    const char* glsl_version = "#version 100";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
#elif defined(__APPLE__)
    const char* glsl_version = "#version 150";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);  // 3.2+ only
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);            // Required on Mac
#else
    glsl_version = "#version 130";
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
#endif

    window = glfwCreateWindow(1280, 720, "FlaPU2Engine", nullptr, nullptr);
    if (window == nullptr) {
        exit_code = 1;
        return true;
    }
    glfwMakeContextCurrent(window);
    glfwSwapInterval(1);
    return false;
}

void setup_imgui(const char* glsl_version, GLFWwindow* window, ImGuiIO& io_copy) {
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    (void)io;
    io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init(glsl_version);
    io_copy = io;
}

bool start_window(GLFWwindow*& window, ImGuiIO& io, int& exit_code) {
    const char* glsl_version;
    if (setup_glfw(glsl_version, window, exit_code)) {
        return true;
    }

    setup_imgui(glsl_version, window, io);
    return false;
}

void execute_loop(GLFWwindow* window, const ImGuiIO& io, Engine& engine) {
    constexpr auto clear_color = ImVec4(0.f, 0.f, 0.f, 1.f);

    while (!glfwWindowShouldClose(window)) {
        loop_iteration(window, io, clear_color, engine);
    }
}

int create_window(Engine& engine) {
    GLFWwindow* window;
    ImGuiIO io;

    if (int exit_code; start_window(window, io, exit_code)) return exit_code;

    execute_loop(window, io, engine);

    clean_window(window);

    return 0;
}
