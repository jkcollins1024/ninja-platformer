#include "Enemy.h"

#include <iostream>
#include <random>
#include <ctime>
#include <glm/gtx/rotate_vector.hpp>
#include <SDL/SDL.h>
#include <JCEngine\ResourceManager.h>

Enemy::Enemy(glm::vec2 position) {
	_position = position;
}

Enemy::~Enemy() {

}

bool Enemy::applyDamage(int damage) {
	_health -= damage;

	return _health <= 0;
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