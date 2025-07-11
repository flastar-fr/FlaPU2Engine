#include "gui_handling.hpp"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#include "config_gui.hpp"
#include "windows_creation.hpp"

static void glfw_error_callback(const int error, const char* description) {
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void execute_instructions(EngineRunner& engine_runner) {
    const float fps = ImGui::GetIO().Framerate;
    const int ops = engine_runner.getEngineStatus().op_per_second;
    float& instruction_accumulator = engine_runner.getEngineStatus().instruction_accumulator;

    if (fps <= 0.0f || ops <= 0) return;

    const float instructions_per_frame = static_cast<float>(ops) / fps;
    instruction_accumulator += instructions_per_frame;

    while (instruction_accumulator >= 1.0f) {
        engine_runner.executeNextInstruction();
        instruction_accumulator -= 1.0f;
    }
}

void handle_keyboard_inputs(Engine& engine) {
    for (auto& [key, val] : PRESSABLE_KEYCODES) {
        if (ImGui::IsKeyPressed(key)) {
            engine.getPorts().keyboard.pushKeyCode(val);
        }
    }
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

void loop_iteration(GLFWwindow* window, const ImGuiIO& io, const ImVec4 clear_color, EngineRunner& engine_runner) {
    const auto &engineStatus = engine_runner.getEngineStatus();

    handle_frame_creation();

    handle_keyboard_inputs(engine_runner.getEngine());

    const bool engine_running = !engine_runner.isProgramFinished() && engineStatus.running_status == EngineRunningStatus::RUNNING;
    if (engine_running) execute_instructions(engine_runner);

    if constexpr (SHOW_DEBUG) display_debug_windows(engine_runner);

    display_controls(engine_runner);
    display_text_n_number(engine_runner.getEngine());

    render_main_window_content(engine_runner.getEngine().getPorts().screen);

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

    window = glfwCreateWindow(SCREEN_SIZE.x, SCREEN_SIZE.y, "FlaPU2Engine", nullptr, nullptr);
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

void execute_loop(GLFWwindow* window, const ImGuiIO& io, EngineRunner& engine_runner) {
    constexpr auto clear_color = ImVec4(0.f, 0.f, 0.f, 1.f);

    while (!glfwWindowShouldClose(window)) {
        loop_iteration(window, io, clear_color, engine_runner);
    }
}

int create_window(EngineRunner& engine_runner) {
    GLFWwindow* window;
    ImGuiIO io;

    if (int exit_code; start_window(window, io, exit_code)) return exit_code;

    execute_loop(window, io, engine_runner);

    clean_window(window);

    return 0;
}
