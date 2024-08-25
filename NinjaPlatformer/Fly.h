#pragma once

#include "Enemy.h"

class Fly : public Enemy
{
public:
	Fly(glm::vec2 position);
	~Fly();

	virtual void draw(JCEngine::SpriteBatch& spriteBatch) override;
	virtual void move(const std::vector<std::string>& levelData, float deltaTime) override;
};