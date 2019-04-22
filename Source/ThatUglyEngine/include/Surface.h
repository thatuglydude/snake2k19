#pragma once

#include <SDL_image.h>
#include <algorithm>

namespace tbd {

// Simple RAII wrapper around SDL_Surface
struct Surface
{
	explicit Surface()
		: m_surface{nullptr}
	{}

	explicit Surface(SDL_Surface* surface)
		: m_surface{surface}
	{}

	Surface(const Surface& rhs) = delete;
	Surface& operator=(const Surface& rhs) = delete;

	Surface(Surface&& rhs)
	{
		std::swap(m_surface, rhs.m_surface);
	}

	Surface& operator=(Surface&& rhs)
	{
		std::swap(m_surface, rhs.m_surface);
		return *this;
	}

	virtual ~Surface()
	{
		SDL_FreeSurface(m_surface);
	}

	operator bool() const
	{
		return m_surface != nullptr;
	}

	operator SDL_Surface*() const
	{
		return m_surface;
	}

	SDL_Surface* m_surface = nullptr;
};

} // namespace tbd {
