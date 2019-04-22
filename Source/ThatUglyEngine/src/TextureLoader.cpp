
#include "TextureLoader.h"

#include "Logging.h"
#include "Surface.h"
#include "Texture.h"
#include "SDLRenderer.h"
#include <SDL.h>
#include <SDL_image.h>

namespace tbd {

Texture loadTexture(SDLRenderer& renderer, const std::string& path)
{
	// Load image at specified path
	Surface loadedSurface{IMG_Load(path.c_str())};
	if (!loadedSurface)
	{
		LOG_ERR << "Unable to load image: " << path << ", SDL_image Error: " << IMG_GetError();
		return Texture{};
	}

	// Create texture from surface pixels
	if (Texture newTexture{SDL_CreateTextureFromSurface(renderer.get(), loadedSurface)})
	{
		return newTexture;
	}

	LOG_ERR << "Unable to create texture from: " << path << ", SDL_image Error : " << IMG_GetError();
	return Texture{};
}

} // namespace tbd {
