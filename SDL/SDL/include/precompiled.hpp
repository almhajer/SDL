#pragma once
#include <map>
#include <SDL3/SDL.h>

inline  std::unordered_map<std::string, std::string> language = {
    {"languages", "ar"},
    {"version", "1.0.0"},
    {"description", " اللغة العربية"},
    {"ERROR_SDL_initialize", "لايمكن تهيئة SDL"},
    {"ERROR_window_renderer", "لايمكن انشاء النافذة  والريندر"},
    {"ERROR_create_surface", "لايمكن انشاء سسطح لرسم الصورة"},
    {"ERROR_create_from_surface", "لايمكن انشاء تخطيط للصورة"}
};
inline  std::unordered_map<std::string, std::string> languageEn = {
    {"languages", "ar"},
    {"version", "1.0.0"},
    {"description", "Language ENGLISH"},
    {"ERROR_SDL_initialize", "Couldn't initialize SDL"},
    {"ERROR_window_renderer", "Couldn't create window and renderer"},
    {"ERROR_create_surface", "Couldn't create surface from image"},
    {"ERROR_create_from_surface", "Couldn't create texture from surface"}
};
