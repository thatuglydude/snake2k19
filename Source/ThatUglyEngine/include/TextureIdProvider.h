#pragma once

#include "TextureId.h"

namespace tbd {

class TextureIdProvider
{
public:
	TextureId nextId()
	{
		return m_currentTextureEntityId++;
	}

private:
	TextureId m_currentTextureEntityId = {0};		// TODO: access to this var has to be protected from all threads! - atomic?
};

} // namespace tbd {
