#pragma once

#include "SDLWindow.h"
#include "SDLError.h"

namespace tbd {

SDLWindow::SDLWindow(const int screenWidth, const int screenHeight)
	: m_screenWidth{screenWidth}, m_screenHeight{screenHeight}
{}

SDLWindow::~SDLWindow()
{
	// Destroy window	
	SDL_DestroyWindow(m_window);
}

void SDLWindow::init()
{
	// TODO: tmp on the second screen for demo purposes
	//m_window = SDL_CreateWindow("Snake2019", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
	m_window = SDL_CreateWindow("Snake2019", 2000, SDL_WINDOWPOS_UNDEFINED, m_screenWidth, m_screenHeight, SDL_WINDOW_SHOWN);
	if (m_window == nullptr)
	{
		throw SDLError{"Window could not be created! SDL Error: ", SDL_GetError()};
	}
}

SDL_Window* SDLWindow::get() const
{
	return m_window;
}

} // namespace tbd {
