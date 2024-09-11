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
	Enemy(glm::vec2 position, int currentFrame);
	~Enemy();

	virtual void move(float deltaTime) override;
	virtual void draw(JCEngine::SpriteBatch& spriteBatch) override;

	//setters
	void setPosition(glm::vec2 position) { m_position = position; };
	void setDirection(glm::vec2 direction) { m_directionFacing = direction; };

	//getters
	glm::vec2 getPosition() { return m_position; };
	float getHitboxRadius() { return m_hitboxRadius; };
	glm::vec2 getSize() { return m_size; };

	bool isDead() { return m_deathFrames == 0; }

protected:
	std::vector<JCEngine::GLTexture> m_textures;
	glm::vec2 m_position;
	glm::vec2 m_size;
	glm::vec4 m_uv;
	float m_hitboxRadius = 1.0f;

	virtual glm::vec4 getUV() { return m_uv; };
};