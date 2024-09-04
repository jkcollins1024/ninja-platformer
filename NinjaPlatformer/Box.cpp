#include "Box.h"
#include <JCEngine/SpriteFont.h>

//fixedRotation defaults to false
Box::Box(b2World* world, const glm::vec2& position, const glm::vec2& dimensions, JCEngine::GLTexture texture, JCEngine::ColorRGBA8 color, TileType type,
		bool fixedRotation, glm::vec4 uvRect) {

	m_tileType = type;

	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.fixedRotation = fixedRotation;
	bodyDef.position.Set(position.x, position.y);
	//bodyDef.userData.pointer = (uintptr_t)&m_tileType;
	m_body = world->CreateBody(&bodyDef);

	b2PolygonShape boxShape;
	if (type == TileType::WATER) {
		boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 4.0f);
	}
	else {
		boxShape.SetAsBox(dimensions.x / 2.0f, dimensions.y / 2.0f);
	}

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &boxShape;
	fixtureDef.density = 0.0f;
	if (type == TileType::WATER) {
		fixtureDef.friction = 0.0f;
	}
	else {
		fixtureDef.friction = 0.3f;
	}

	m_fixture = m_body->CreateFixture(&fixtureDef);

	m_dimensions = dimensions;
	m_color = color;
	m_texture = texture;
	m_uvRect = uvRect;
}

Box::~Box() {

}

void Box::draw(JCEngine::SpriteBatch& spriteBatch) {
	glm::vec4 destRect(m_body->GetPosition().x - m_dimensions.x / 2.0f, m_body->GetPosition().y - m_dimensions.y / 2.0f, m_dimensions);
	spriteBatch.draw(destRect, m_uvRect, m_texture.id, 0.0f, m_color, m_body->GetAngle());
}

void Box::drawPositions(JCEngine::SpriteBatch& spriteBatch, JCEngine::SpriteFont* spriteFont) {
	char buffer[256];
	sprintf_s(buffer, "%.2f, %.2f", m_body->GetPosition().x, m_body->GetPosition().y);
	//sprintf_s(buffer, "%f, %f", );

	spriteFont->draw(spriteBatch, buffer, glm::vec2(m_body->GetPosition().x, m_body->GetPosition().y), glm::vec2(0.01f), 0, JCEngine::ColorRGBA8(0, 0, 0, 255));
}