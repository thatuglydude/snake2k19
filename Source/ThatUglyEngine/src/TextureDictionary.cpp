#pragma once

#include "TextureDictionary.h"

#include "TextureLoader.h"
#include "TextureError.h"
#include "TextureIdProvider.h"

#include "Logging.h"
#include <map>

namespace tbd
{

// PIMPL idiom for the implementation
class TextureDictionaryImpl
{
public:
	void load(SDLRenderer& renderer, const std::string& path)
	{
		// first: find the corresponding texId in the path-to-id to check whether the path has already been loaded
		{
			auto texIdIter = m_pathIdentifierMap.find(path);
			if (texIdIter != m_pathIdentifierMap.end())
			{
				LOG_WRN << "Texture under path: " << path << " is already loaded in the TextureDictionary under ID: " << texIdIter->second;
				return;
			}
		}

		// otherwise: new texture, get a new texId and insert it into the path-to-id map
		const auto newTexId = m_idProvider.nextId();
		m_pathIdentifierMap.insert({path, newTexId});

		// insert texture into m_identifierTextureMap under the new texId
		if (auto texture = loadTexture(renderer, path))
		{
			m_identifierTextureMap.emplace(newTexId, std::move(texture));
		}
		else
		{
			throw TextureError{}; // << "Could not initialize the texture from path: " << path;	// TODO: add CRTP to the exception, use custom exceptions
		}
	}

	const TextureId& getId(const std::string& path) const
	{
		auto texIdIter = m_pathIdentifierMap.find(path);
		if (texIdIter != m_pathIdentifierMap.end())
		{
			return texIdIter->second;	// found, texture was already loaded
		}

		throw TextureError{}; // << "Could not find textureId for specified path: " << path;
	}

	const Texture& getTexture(const std::string& path) const
	{
		const auto texId = getId(path);
		return getTexture(texId);
	}

	const Texture& getTexture(const TextureId& id) const
	{
		auto texIter = m_identifierTextureMap.find(id);
		if (texIter != m_identifierTextureMap.end())
		{
			return texIter->second;	// found, texture was already loaded
		}

		throw TextureError{}; // << "Could not find texture for specified ID: " << id;
	}

private:
	std::map<std::string, TextureId>  m_pathIdentifierMap;
	std::map<TextureId, Texture> m_identifierTextureMap;

	TextureIdProvider m_idProvider;
};

// The external interface
TextureDictionary::TextureDictionary()
{
	m_textureDictionaryImpl = std::make_unique<TextureDictionaryImpl>();
}

TextureDictionary::~TextureDictionary() = default;

void TextureDictionary::load(SDLRenderer& renderer, const std::string& path)
{
	return m_textureDictionaryImpl->load(renderer, path);
}

const TextureId& TextureDictionary::getId(const std::string& path) const
{
	return m_textureDictionaryImpl->getId(path);
}

const Texture& TextureDictionary::getTexture(const std::string& path) const
{
	return m_textureDictionaryImpl->getTexture(path);
}

const Texture& TextureDictionary::getTexture(const TextureId& id) const
{
	return m_textureDictionaryImpl->getTexture(id);
}

} // namespace tbd {
