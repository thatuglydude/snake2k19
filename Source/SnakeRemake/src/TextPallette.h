#pragma once

#include <SDL_image.h>

namespace tbd {

SDL_Rect characterTextureRect(const uint8_t character, const int textureWidth = 500, const int textureHeight = 220, const int characterTextureWidth = 20, const int characterTextureHeight = 20)
{
	const int charactersInRow = textureWidth / characterTextureWidth;
	const int row = character / charactersInRow;
	const int col = character % charactersInRow;

	return SDL_Rect{col * characterTextureWidth, row * characterTextureHeight, characterTextureWidth, characterTextureHeight};
}

} // namespace tbd {
