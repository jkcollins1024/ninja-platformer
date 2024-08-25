#pragma once

#include "Actor.h"

#include <glm/glm.hpp>
#include <JCEngine/SpriteBatch.h>
#include <JCEngine/GLTexture.h>
#include <JCEngine/InputManager.h>
#include <JCEngine\Camera2D.h>
#include <JCEngine/TileSheet.h>

class Enemy : public Actor
{
public:
	Enemy(glm::vec2 position);
	~Enemy();

	//depends on actors around it - will need some processing in main game
	//virtual void move(const std::vector<std::string>& levelData, std::vector<Enemy*>& actors, Player* player, float deltaTime) {};

	//returns true if dead
	bool applyDamage(int damage);
};