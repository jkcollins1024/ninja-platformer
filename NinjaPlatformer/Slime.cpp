#include "Slime.h"
#include <JCEngine/ResourceManager.h>

Slime::Slime(glm::vec2 position, int currentFrame): Enemy(position, currentFrame) {
	m_type = ActorType::ENEMY;
	m_uv = glm::vec4(1.0f, 1.0f, -1.0f, -1.0f);

	m_textures.push_back(JCEngine::ResourceManager::getTexture("Assets/slimeWalk1.png"));
	m_textures.push_back(JCEngine::ResourceManager::getTexture("Assets/slimeWalk2.png"));
	m_directionFacing = glm::vec2(-1.0f, 0.0f);

	m_color = JCEngine::ColorRGBA8();
	m_color.r = 255;
	m_color.g = 255;
	m_color.b = 255;
	m_color.a = 255;

	m_speed = 3.0f;
	m_health = 2;
	m_size = glm::vec2(2.0f, 1.0f);

	m_position = position + m_size / 2.0f;
}

Slime::~Slime() {

}
//
//void Slime::draw(JCEngine::SpriteBatch& spriteBatch) {
//	int animationSpeed = 8;
//	//glm::vec4 uvRect = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f);
//	int tileIndex = (m_frameCount / animationSpeed) % m_textures.size();
//	glm::vec4 positionRect(m_position.x - m_size.x / 2.0f, m_position.y - m_size.y / 2.0f, m_size.x, m_size.y);
//	GLuint textureID;
//
//	textureID = m_textures[tileIndex].id;
//
//	spriteBatch.draw(positionRect, getUV(), textureID, 0.0f, m_color, m_directionFacing);
//}

//void Slime::move(const std::vector<std::string>& levelData, float deltaTime) {
//	if (m_frameCount == 100) {
//		m_directionFacing = -m_directionFacing;
//		m_frameCount = 0;
//	}
//	else {
//		m_frameCount++;
//	}
//
//	m_position += m_directionFacing * m_speed * deltaTime;
//
//	//collideWithLevel(levelData);
//}

glm::vec4 Slime::getUV() {
	float xFacing = m_directionFacing.x;

	return glm::vec4(1.0f, 0.5f + 0.5f * xFacing, -1.0f, xFacing);
}