#pragma once

#include <SDL_image.h>
#include <algorithm>

namespace tbd {

// Simple RAII wrapper around SDL_Texture
struct Texture
{
	explicit Texture()
		: m_texture{nullptr}
	{}

	explicit Texture(SDL_Texture* texture)
		: m_texture{texture}
	{}

	Texture(const Texture& rhs) = delete;
	Texture& operator=(const Texture& rhs) = delete;

	Texture(Texture&& rhs)
	{
		std::swap(m_texture, rhs.m_texture);
	}

	Texture& operator=(Texture&& rhs)
	{
		std::swap(m_texture, rhs.m_texture);
		return *this;
	}

	virtual ~Texture()
	{
		SDL_DestroyTexture(m_texture);
	}

	operator bool() const
	{
		return m_texture != nullptr;
	}

	operator SDL_Texture*() const
	{
		return m_texture;
	}

	SDL_Texture* m_texture = nullptr;
};

} // namespace tbd {
