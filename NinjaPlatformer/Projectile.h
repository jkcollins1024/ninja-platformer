#pragma once

#include <glm/glm.hpp>
#include <JCEngine/SpriteBatch.h>
#include <string>
#include <vector>
#include <NinjaPlatformer\Player.h>
#include <NinjaPlatformer/Enemy.h>

class Projectile
{
public:
	Projectile(float speed, glm::vec2 direction, glm::vec2 position, int _lifetime, GLuint textureId, int damage);
	~Projectile();

	void draw(JCEngine::SpriteBatch& spriteBatch);
	glm::vec2 update(float deltaTime);

	bool collideWithEnemy(Enemy* enemy);

	bool collideWithLevel(const std::vector<std::string>& levelData);

	bool isDead() { return m_lifetime <= 0; };
	int getDamage() { return m_damage; };
	glm::vec2 getPosition() { return m_position; };
	float getRadius() { return m_radius; };


private:
	float m_speed;
	int m_lifetime;
	glm::vec2 m_direction;
	glm::vec2 m_position;
	GLuint m_textureId;
	int m_damage;
	float m_radius;

	bool collideWithTile(glm::vec2 tilePosition);
};