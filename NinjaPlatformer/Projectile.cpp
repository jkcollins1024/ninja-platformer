#include "Projectile.h"

#include <glm/glm.hpp>
#include <JCEngine/GLTexture.h>
#include <JCEngine/ResourceManager.h>

Projectile::Projectile(float speed, glm::vec2 direction, glm::vec2 position, int lifetime, GLuint textureId, int damage) {
	m_speed = speed;
	m_direction = direction;
	m_position = position;
	m_lifetime = lifetime;
	m_textureId = textureId;
	m_damage = damage;

	m_radius = 0.5f;
}

Projectile::~Projectile() {

}

void Projectile::draw(JCEngine::SpriteBatch& spriteBatch) {
	JCEngine::ColorRGBA8 color;
	color.r = 255;
	color.b = 255;
	color.g = 255;
	color.a = 255;

	glm::vec4 positionForSprite = glm::vec4(m_position.x - 0.5f, m_position.y - 0.5f, 1, 1);
	glm::vec4 uv(0.0f, 0.0f, 1.0f, 1.0f);

	spriteBatch.draw(positionForSprite, uv, m_textureId, 0, color);
}

bool Projectile::collideWithLevel(const std::vector<std::string>& levelData) {
	std::vector<glm::vec2> collideTilePositions;

	//check four corners
	glm::vec2 cornerPosition1 = glm::vec2(floor((m_position.x - 0.5f) / 1.5f), floor((m_position.y - 0.5f) / 1.5f));
	glm::vec2 cornerPosition2 = glm::vec2(floor((m_position.x + 0.5f) / 1.5f), floor((m_position.y - 0.5f) / 1.5f));
	glm::vec2 cornerPosition3 = glm::vec2(floor((m_position.x - 0.5f) / 1.5f), floor((m_position.y + 0.5f) / 1.5f));
	glm::vec2 cornerPosition4 = glm::vec2(floor((m_position.x + 0.5f) / 1.5f), floor((m_position.y + 0.5f) / 1.5f));

	if (levelData[cornerPosition1.y][cornerPosition1.x] != '.') {
		//glm::vec2 cornerPosition = glm::vec2(cornerPosition1.x * 1.5f + 0.75f, cornerPosition1.y * 1.5f + 0.75f);
		glm::vec2 cornerPosition = (cornerPosition1 * 1.5f) + glm::vec2(0.75f);
		collideTilePositions.push_back(cornerPosition);
	}

	if (levelData[cornerPosition2.y][cornerPosition2.x] != '.') {
		//glm::vec2 cornerPosition = glm::vec2(cornerPosition2.x * 1.5f + 0.75f, cornerPosition2.y * 1.5f + 0.75f);
		glm::vec2 cornerPosition = (cornerPosition2 * 1.5f) + glm::vec2(0.75f);
		collideTilePositions.push_back(cornerPosition);
	}

	if (levelData[cornerPosition3.y][cornerPosition3.x] != '.') {
		//glm::vec2 cornerPosition = glm::vec2(cornerPosition3.x * 1.5f + 0.75f, cornerPosition3.y * 1.5f + 0.75f);
		glm::vec2 cornerPosition = (cornerPosition3 * 1.5f) + glm::vec2(0.75f);
		collideTilePositions.push_back(cornerPosition);
	}

	if (levelData[cornerPosition4.y][cornerPosition4.x] != '.') {
		//glm::vec2 cornerPosition = glm::vec2(cornerPosition4.x * 1.5f + 0.75f, cornerPosition4.y * 1.5f + 0.75f);
		glm::vec2 cornerPosition = (cornerPosition4 * 1.5f) + glm::vec2(0.75f);
		collideTilePositions.push_back(cornerPosition);
	}

	for (int i = 0; i < collideTilePositions.size(); i++) {
		if (collideWithTile(collideTilePositions[i]))
			return true;
	}

	return false;
}

bool Projectile::collideWithTile(glm::vec2 tilePosition) {
	const float TILE_HALF = 0.75f;
	const float MIN_DISTANCE = 1.25f;

	glm::vec2 centerPlayerPosition = m_position;
	glm::vec2 distVec = centerPlayerPosition - tilePosition;

	float xdist = abs(distVec.x);
	float ydist = abs(distVec.y);

	if (xdist > MIN_DISTANCE) { return false; }
	if (ydist > MIN_DISTANCE) { return false; }

	if (xdist <= TILE_HALF) { return true; }
	if (ydist <= TILE_HALF) { return true; }

	double corner_dist_squared = pow(xdist - TILE_HALF, 2) +
		pow(ydist - TILE_HALF, 2);

	return corner_dist_squared <= 0.0625;

	/*float xdepth = MIN_DISTANCE - abs(distVec.x);
	float ydepth = MIN_DISTANCE - abs(distVec.y);

	if (xdepth > 0 || ydepth > 0) {
		return true;
	}*/
}

bool Projectile::collideWithEnemy(Enemy* enemy) {
	glm::vec2 currentCenter = m_position;
	glm::vec2 otherCenter = enemy->getPosition();

	glm::vec2 distVec = currentCenter - otherCenter;

	float depth = glm::length(distVec);

	if (depth <= m_radius + enemy->getHitboxRadius()) {
		return true;
	}
	return false;
}

//returns position to determine collision when bullet should be destroyed
glm::vec2 Projectile::update(float deltaTime) {
	m_position += m_direction * m_speed * deltaTime;
	m_lifetime--;

	return m_position;
}