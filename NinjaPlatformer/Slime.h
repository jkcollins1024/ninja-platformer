#pragma once

#include "Enemy.h"

class Slime : public Enemy 
{
public:
	Slime(glm::vec2 position, int currentFrame);
	~Slime();

	//virtual void draw(JCEngine::SpriteBatch& spriteBatch) override;
	//virtual void move(const std::vector<std::string>& levelData, float deltaTime) override;
protected:
	virtual glm::vec4 getUV() override;
};