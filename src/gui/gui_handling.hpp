#pragma once

#include "imgui.h"
#if defined(IMGUI_IMPL_OPENGL_ES2)
#endif
#undef GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "code_hardware/EngineRunner.hpp"

static void glfw_error_callback(int error, const char* description);
void handle_keyboard_inputs(Engine& engine);
void clean_window(GLFWwindow* window);
void render_window(GLFWwindow* window, const ImGuiIO& io, ImVec4 clear_color);
void handle_frame_creation();
void loop_iteration(GLFWwindow* window, const ImGuiIO& io, ImVec4 clear_color, EngineRunner& engine_runner);
bool setup_glfw(const char*& glsl_version, GLFWwindow*& window, int& exit_code);
void setup_imgui(const char* glsl_version, GLFWwindow* window, ImGuiIO& io_copy);
bool start_window(GLFWwindow*& window, ImGuiIO& io, int& exit_code);
void execute_loop(GLFWwindow* window, const ImGuiIO& io, EngineRunner& engine_runner);
int create_window(EngineRunner& engine_runner);
