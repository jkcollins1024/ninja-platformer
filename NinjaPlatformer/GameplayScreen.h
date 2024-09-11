#pragma once

#include<JCEngine/IGameScreen.h>
#include<JCEngine/SpriteBatch.h>
#include<JCEngine/Camera2D.h>
#include<JCEngine/GLSLProgram.h>
#include<JCEngine/Window.h>
#include<JCEngine/GLTexture.h>
#include<box2d/box2d.h>

#include "Box.h"
#include <NinjaPlatformer\Player.h>
#include <JCEngine\DebugRenderer.h>
#include <JCEngine\SpriteFont.h>

class GameplayScreen : public JCEngine::IGameScreen
{
public:
	GameplayScreen(JCEngine::Window* window);
	~GameplayScreen();
	// Inherited via IGameScreen
	virtual int getNextScreenIndex() const override;

	virtual int getPreviousScreenIndex() const override;

	virtual void build() override;

	virtual void destroy() override;

	virtual void onEntry() override;

	virtual void onExit() override;

	virtual void update() override;

	virtual void draw() override;

private:
	void checkInput();

	void drawHUD();

	b2World* game_world;
	std::vector<Box> m_boxes;
	Player m_player;
	std::vector<Enemy*> m_enemies;
	bool m_renderDebug = false;
	std::vector<std::string> m_levelData;
	std::vector<Projectile*> m_projectiles;
	float endLevel = 0.0f;

	JCEngine::GLSLProgram m_textureProgram;
	JCEngine::Camera2D m_camera;
	JCEngine::SpriteBatch m_spriteBatch;
	//JCEngine::GLTexture m_texture;
	JCEngine::Window* m_window;
	JCEngine::DebugRenderer m_debugRenderer;

	JCEngine::SpriteFont* _spriteFont;
	JCEngine::SpriteBatch _hudSpriteBatch;
	JCEngine::Camera2D _hudCamera;

};

