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

	virtual void draw(JCEngine::SpriteBatch& spriteBatch);

	//depends on actors around it - will need some processing in main game
	virtual void move(const std::vector<std::string>& levelData, float deltaTime) {};

	//returns true if dead
	bool applyDamage(int damage);

	bool collideWithLevel(const std::vector<std::string>& levelData);
	bool collideWithActor(Actor* actor);
	bool isEnemy() { return _type == ActorType::ENEMY; };
	bool isPlayer() { return _type == ActorType::PLAYER; };

	//getters
	glm::vec2 getPosition() { return _position; };

	//setters
	void setPosition(glm::vec2 position) { _position = position; };
	void setDirection(glm::vec2 direction) { _direction = direction; _directionFacing = direction; };

protected:
	float _speed = 20;
	float m_animTime = 0.0f;
	glm::vec2 _position;
	glm::vec2 _size;
	glm::vec4 _uv;
	JCEngine::ColorRGBA8 _color;
	JCEngine::GLTexture _texture;
	JCEngine::TileSheet m_walkTileSheet;
	ActorType _type;
	glm::vec2 _direction;
	glm::vec2 _directionFacing;
	int _frames;
	int _health;

	void collideWithTile(glm::vec2 tilePosition);
};