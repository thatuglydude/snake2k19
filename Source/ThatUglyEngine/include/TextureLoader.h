#pragma once

#include "Texture.h"
#include "SDLRenderer.h"
#include <string>
#include "ThatUglyEngine.h"

struct SDL_Renderer;

namespace tbd {

// TODO: this is obviously SDLTextureLoader: define ITextureLoader interface, implement it here oncefold, reimplement in other engines (least make it possibru)

// Load texture from the given path using the renderer.
// Returns empty Texture on error.
Texture DLLEXPORT loadTexture(SDLRenderer& renderer, const std::string& path);

} // namespace tbd {
