#pragma once

#include <glm/glm.hpp>
#include <JCEngine/SpriteBatch.h>
#include <JCEngine/GLTexture.h>
#include <JCEngine/InputManager.h>
#include <JCEngine\Camera2D.h>
#include <JCEngine/TileSheet.h>
#include <string>

enum class ActorType { ENEMY, PLAYER };

class Actor
{
public:
	Actor();
	~Actor();

	virtual void draw(JCEngine::SpriteBatch& spriteBatch) {};
	virtual void move(float deltaTime) {};

	//returns true if dead
	bool applyDamage(int damage);

	/*bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithActor(Actor* actor);*/
	bool isEnemy() { return m_type == ActorType::ENEMY; };
	bool isPlayer() { return m_type == ActorType::PLAYER; };

protected:
	float m_speed = 20;
	float m_animTime = 0.0f;
	JCEngine::ColorRGBA8 m_color;
	ActorType m_type;
	glm::vec2 m_directionFacing;
	int m_frameCount;
	int m_health;

	void collideWithTile(glm::vec2 tilePosition);
};