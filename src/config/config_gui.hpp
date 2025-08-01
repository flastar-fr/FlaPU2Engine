#pragma once

#include "config_hardware.hpp"
#include <imgui.h>

constexpr long MAX_SPEED_EXECUTION = 100000000;
constexpr int MAX_INSTRUCTION_TO_DISPLAY = 100;

const std::unordered_map<ImGuiKey, Keycode> PRESSABLE_KEYCODES = {
    {ImGuiKey_1, Keycode::ONE},
    {ImGuiKey_2, Keycode::TWO},
    {ImGuiKey_3, Keycode::THREE},
    {ImGuiKey_4, Keycode::FOUR},
    {ImGuiKey_5, Keycode::FIVE},
    {ImGuiKey_6, Keycode::SIX},
    {ImGuiKey_7, Keycode::SEVEN},
    {ImGuiKey_8, Keycode::EIGHT},
    {ImGuiKey_9, Keycode::NINE},
    {ImGuiKey_A, Keycode::A},
    {ImGuiKey_B, Keycode::B},
    {ImGuiKey_C, Keycode::C},
    {ImGuiKey_D, Keycode::D},
    {ImGuiKey_E, Keycode::E},
    {ImGuiKey_F, Keycode::F},
    {ImGuiKey_G, Keycode::G},
    {ImGuiKey_H, Keycode::H},
    {ImGuiKey_I, Keycode::I},
    {ImGuiKey_J, Keycode::J},
    {ImGuiKey_K, Keycode::K},
    {ImGuiKey_M, Keycode::M},
    {ImGuiKey_N, Keycode::N},
    {ImGuiKey_O, Keycode::O},
    {ImGuiKey_P, Keycode::P},
    {ImGuiKey_Q, Keycode::Q},
    {ImGuiKey_R, Keycode::R},
    {ImGuiKey_S, Keycode::S},
    {ImGuiKey_T, Keycode::T},
    {ImGuiKey_U, Keycode::U},
    {ImGuiKey_V, Keycode::V},
    {ImGuiKey_W, Keycode::W},
    {ImGuiKey_X, Keycode::X},
    {ImGuiKey_Y, Keycode::Y},
    {ImGuiKey_Z, Keycode::Z},
    {ImGuiKey_UpArrow, Keycode::UP},
    {ImGuiKey_DownArrow, Keycode::DOWN},
    {ImGuiKey_LeftArrow, Keycode::LEFT},
    {ImGuiKey_RightArrow, Keycode::RIGHT},
    {ImGuiKey_Space, Keycode::SPACE},
};
