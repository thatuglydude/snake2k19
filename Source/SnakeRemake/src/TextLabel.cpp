
#include "TextLabel.h"
#include "TextPallette.h"

namespace tbd {


TextLabel::TextLabel(const EntityId& entityId, EntityManager& entityManager, const int x, const int y, const TextureId bitmapFontTexture, const std::string& text)
	: Entity{entityId, CType::COMPONENT_TYPE_NONE}, m_entityManager{entityManager}, m_x{x}, m_y{y}, BITMAP_FONT_TEXTURE{bitmapFontTexture}, m_text{text}
{
	setText(text);
}

void TextLabel::setText(const std::string& text)
{
	for (auto& characterEId : m_characterEIDs)
	{
		m_entityManager.remove(characterEId);
	}
	m_characterEIDs.clear();

	m_text = text;

	for (size_t i = 0; i < text.length(); ++i)
	{
		m_characterEIDs.emplace_back(m_entityManager.create<TextCharacter>(
			BITMAP_FONT_TEXTURE,
			characterTextureRect(text[i]),
			SDL_Rect{m_x + static_cast<int>(i) * 20, m_y, 20, 20}));
	}
}

} // namespace tbd {
