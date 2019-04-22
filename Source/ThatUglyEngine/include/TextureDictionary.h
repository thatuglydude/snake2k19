#pragma once

#include "TextureId.h"
#include "Texture.h"
#include "SDLRenderer.h"

#include "ThatUglyEngine.h"
#include <memory>
#include <string>

struct SDL_Renderer;

namespace tbd
{

class TextureDictionaryImpl;

class DLLEXPORT TextureDictionary
{
public:
	TextureDictionary();
	virtual ~TextureDictionary();

	void load(SDLRenderer& renderer, const std::string& path);

	const TextureId& getId(const std::string& path) const;
	const Texture& getTexture(const std::string& path) const;
	const Texture& getTexture(const TextureId& id) const;

private:
	std::unique_ptr<TextureDictionaryImpl> m_textureDictionaryImpl;
};

} // namespace tbd {
