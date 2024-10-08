#pragma once
#include <NinjaPlatformer\Box.h>

#include <JCEngine/SpriteBatch.h>
#include <JCEngine/GLTexture.h>
#include <JCEngine\InputManager.h>
#include <JCEngine\DebugRenderer.h>

#include "Capsule.h"
#include "Projectile.h"
#include "Actor.h"
#include <JCEngine\TileSheet.h>
#include <JCEngine/Camera2D.h>

class Projectile;

enum class PlayerMoveState { STANDING, RUNNING, PUNCHING, IN_AIR };

class Player : public Actor
{
public:
	Player() {}
	Player(b2World* world, const glm::vec2& position, const glm::vec2& collisionDimensions, const glm::vec2& drawDimensions,
		JCEngine::ColorRGBA8 color, JCEngine::Camera2D* camera, float minCameraX, float maxCameraX);
	~Player();

	void draw(JCEngine::SpriteBatch& spriteBatch);
	void drawDebug(JCEngine::DebugRenderer& renderer);
	bool update(JCEngine::InputManager& inputManager, std::vector<Projectile*>& bullets, float deltaTime);
	void fire(const glm::vec2& direction, const glm::vec2& position, std::vector<Projectile*>& bullets);

	const Capsule& getCapsule() const { return m_collisionCapsule; }
private:
	Capsule m_collisionCapsule;
	JCEngine::TileSheet m_textureSheet;
	glm::vec2 m_drawDimensions;
	bool m_onGround = false;
	bool m_punching = false;
	//1 for right, -1 for left
	int m_direction = 1;
	PlayerMoveState m_moveState = PlayerMoveState::STANDING;
	JCEngine::Camera2D* m_camera;
	int m_fireRate = 30;
	int m_frameCount;

	float m_minCameraX = 0.0f;
	float m_maxCameraX = 0.0f;
};

