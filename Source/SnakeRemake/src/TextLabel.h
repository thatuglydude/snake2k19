#pragma once

#include "Entity.h"
#include "EntityManager.h"
#include "TextCharacter.h"
#include "TextureId.h"
#include <vector>
#include <memory>
#include <string>

namespace tbd {

class TextLabel : public Entity
{
public:
	TextLabel(const EntityId& entityId, EntityManager& entityManager, const int x, const int y, const TextureId bitmapFontTexture, const std::string& text);

	void setText(const std::string& text);

private:
	EntityManager& m_entityManager;
	int m_x;
	int m_y;
	TextureId BITMAP_FONT_TEXTURE;
	std::string m_text;

	std::vector<EntityId> m_characterEIDs;
};

} // namespace tbd {
