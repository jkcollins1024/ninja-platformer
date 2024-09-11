#include "Enemy.h"

#include <iostream>
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>
#include <SDL/SDL.h>
#include <JCEngine\ResourceManager.h>

Enemy::Enemy(glm::vec2 position, int currentFrame) {
	m_position = position;
	m_frameCount = currentFrame;
}

Enemy::~Enemy() {

}

void Enemy::move(float deltaTime) {
	//don't move while taking damage or dying
	if (m_deathFrames > 0) {
		m_deathFrames--;
		return;
	}

	if (m_takingDamage) {
		m_damageFrameCount++;
		if (m_damageFrameCount > 40) {
			m_damageFrameCount = 0;
			m_takingDamage = false;
		}
		return;
	}

	if (m_frameCount == 100) {
		m_directionFacing = -m_directionFacing;
		m_frameCount = 0;
	}
	else {
		m_frameCount++;
	}

	m_position += m_directionFacing * m_speed * deltaTime;

	//collideWithLevel(levelData);
}

void Enemy::draw(JCEngine::SpriteBatch& spriteBatch) {
	int animationSpeed = 8;
	int tileIndex = (m_frameCount / animationSpeed) % m_textures.size();
	glm::vec4 positionRect(m_position.x - m_size.x / 2.0f, m_position.y - m_size.y / 2.0f, m_size.x, m_size.y);
	GLuint textureID;

	JCEngine::ColorRGBA8 color = m_color;
	textureID = m_textures[tileIndex].id;

	if (m_deathFrames > 0) {
		//fade out alpha
		color.a = 255.0f * m_deathFrames / 60.0f;
		m_deathFrames--;
	}
	else if (m_takingDamage) {
		//damage animation
		/*int side = m_damageFrameCount / 20;
		int frame = m_damageFrameCount % 20;*/

		color = JCEngine::ColorRGBA8(255, 0, 0, 255.0f * m_damageFrameCount / 10.0f);

		//positionRect.a = side == 0 ? m_size.y - m_size.y * frame / 20.0f : m_size.y * frame / 20.0f;
	}

	spriteBatch.draw(positionRect, getUV(), textureID, 0.0f, color, m_directionFacing);
}

//bool Enemy::collideWithLevel(const std::vector<std::string>& levelData) {
//	std::vector<glm::vec2> collideTilePositions;
//	bool didCollide = false;
//
//	//check four corners
//	glm::vec2 cornerPosition1 = glm::vec2(floor(_position.x / 1.5f), floor(_position.y / 1.5f));
//	glm::vec2 cornerPosition2 = glm::vec2(floor((_position.x + _size.x) / 1.5f), floor(_position.y / 1.5f));
//	glm::vec2 cornerPosition3 = glm::vec2(floor(_position.x / 1.5f), floor((_position.y + _size.y) / 1.5f));
//	glm::vec2 cornerPosition4 = glm::vec2(floor((_position.x + _size.x) / 1.5f), floor((_position.y + _size.y) / 1.5f));
//
//	if (cornerPosition1.x < 0 || cornerPosition4.x >= levelData[0].size() ||
//		cornerPosition1.y < 0 || cornerPosition4.y >= levelData.size()) {
//		return false;
//	}
//
//	if (levelData[cornerPosition1.y][cornerPosition1.x] != '.') {
//		//glm::vec2 cornerPosition = glm::vec2(cornerPosition1.x * 1.5f + 0.75f, cornerPosition1.y * 1.5f + 0.75f);
//		glm::vec2 cornerPosition = (cornerPosition1 * 1.5f) + glm::vec2(0.75f);
//		collideTilePositions.push_back(cornerPosition);
//		didCollide = true;
//	}
//
//	if (levelData[cornerPosition2.y][cornerPosition2.x] != '.') {
//		//glm::vec2 cornerPosition = glm::vec2(cornerPosition2.x * 1.5f + 0.75f, cornerPosition2.y * 1.5f + 0.75f);
//		glm::vec2 cornerPosition = (cornerPosition2 * 1.5f) + glm::vec2(0.75f);
//		collideTilePositions.push_back(cornerPosition);
//		didCollide = true;
//	}
//
//	if (levelData[cornerPosition3.y][cornerPosition3.x] != '.') {
//		//glm::vec2 cornerPosition = glm::vec2(cornerPosition3.x * 1.5f + 0.75f, cornerPosition3.y * 1.5f + 0.75f);
//		glm::vec2 cornerPosition = (cornerPosition3 * 1.5f) + glm::vec2(0.75f);
//		collideTilePositions.push_back(cornerPosition);
//		didCollide = true;
//	}
//
//	if (levelData[cornerPosition4.y][cornerPosition4.x] != '.') {
//		//glm::vec2 cornerPosition = glm::vec2(cornerPosition4.x * 1.5f + 0.75f, cornerPosition4.y * 1.5f + 0.75f);
//		glm::vec2 cornerPosition = (cornerPosition4 * 1.5f) + glm::vec2(0.75f);
//		collideTilePositions.push_back(cornerPosition);
//		didCollide = true;
//	}
//
//	for (int i = 0; i < collideTilePositions.size(); i++) {
//		collideWithTile(collideTilePositions[i]);
//	}
//
//	return didCollide;
//}

//void Enemy::collideWithTile(glm::vec2 tilePosition) {
//	const float MIN_DISTANCE = 1.5f;
//
//	glm::vec2 centerPlayerPosition = _position + glm::vec2(0.75f);
//	glm::vec2 distVec = centerPlayerPosition - tilePosition;
//
//	float xdepth = MIN_DISTANCE - abs(distVec.x);
//	float ydepth = MIN_DISTANCE - abs(distVec.y);
//
//	if (xdepth > 0 || ydepth > 0) {
//		if (xdepth < ydepth) {
//			if (distVec.x > 0)
//				_position.x += xdepth;
//			else
//				_position.x -= xdepth;
//		}
//		else {
//			if (distVec.y > 0)
//				_position.y += ydepth;
//			else
//				_position.y -= ydepth;
//		}
//	}
//}

//bool Enemy::collideWithActor(Enemy* enemy) {
//	const float MIN_DISTANCE = 1.5f;
//
//	glm::vec2 currentCenter = _position + glm::vec2(0.75f);
//	glm::vec2 otherCenter = enemy->getPosition() + glm::vec2(0.75f);
//
//	glm::vec2 distVec = currentCenter - otherCenter;
//
//	float depth = glm::length(distVec);
//
//	glm::vec2 collisionDepthVec = glm::normalize(distVec);
//
//	if (depth == 0) {
//		collisionDepthVec = glm::normalize(glm::vec2(1.0f, 1.0f));
//	}
//
//	if (depth < MIN_DISTANCE) {
//		collisionDepthVec = collisionDepthVec * (MIN_DISTANCE - depth);
//		enemy->setPosition(enemy->getPosition() - (collisionDepthVec / 2.0f));
//		setPosition(_position + (collisionDepthVec / 2.0f));
//		return true;
//	}
//	return false;
//}