#include "GameplayScreen.h"
#include "Slime.h"
#include "Fly.h"
#include <iostream>
#include <fstream>
#include <SDL\SDL_events.h>
#include <JCEngine/IMainGame.h>
#include<JCEngine/ResourceManager.h>
#include <JCEngine/GameErrors.h>
#include <NinjaPlatformer\Box.h>
#include <random>

const float TILE_WIDTH = 1.5f;

GameplayScreen::GameplayScreen(JCEngine::Window* window) {
	m_window = window;
}

GameplayScreen::~GameplayScreen() {

}

int GameplayScreen::getNextScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

int GameplayScreen::getPreviousScreenIndex() const
{
	return SCREEN_INDEX_NO_SCREEN;
}

void GameplayScreen::build()
{
}

void GameplayScreen::destroy()
{
}

void GameplayScreen::onEntry()
{
	//create world with normal gravity
	const b2Vec2 gravity(0.0f, -9.8f);
	game_world = new b2World(gravity);

	//make the ground
	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -20.0f);
	b2Body* groundBody = game_world->CreateBody(&groundBodyDef);

	//make the ground fixture
	b2PolygonShape groundBox;
	groundBox.SetAsBox(50.0f, 10.0f);
	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.0f;
	groundBody->CreateFixture(&fixtureDef);

	//load texture
	JCEngine::GLTexture boxTexture = JCEngine::ResourceManager::getTexture("Assets/bricks_top.png");

	std::mt19937 randGenerator;
	/*std::uniform_real_distribution<float> xDist(-10.0f, 10.0f);
	std::uniform_real_distribution<float> yDist(-15.0f, 15.0f);
	std::uniform_real_distribution<float> size(0.5f, 2.5f);*/
	std::uniform_int_distribution<int> colorValue(0, 255);

	std::ifstream file;

	file.open("Levels/level3.txt");
	if (file.fail()) {
		JCEngine::fatalError("Failed to load level from level1.txt");
	}

	std::string temp;
	file >> temp;

	std::string firstLine;
	std::getline(file, firstLine);

	//std::vector<std::string> _levelData;

	while (std::getline(file, temp)) {
		m_levelData.push_back(temp);
	}

	glm::vec4 uvRect(0.0f, 0.0f, 1.0f, 1.0f);
	JCEngine::ColorRGBA8 tileColor{ 255, 255, 255, 255 };
	glm::vec2 startPlayerPosition;

	for (int y = 0; y < m_levelData.size(); y++) {
		for (int x = 0; x < m_levelData[y].size(); x++) {
			glm::vec4 positionRect(x * TILE_WIDTH, y * TILE_WIDTH, TILE_WIDTH, TILE_WIDTH);

			JCEngine::ColorRGBA8 randColor(colorValue(randGenerator), colorValue(randGenerator), colorValue(randGenerator), 255);

			switch (m_levelData[y][x]) {
			case 'B':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/boxAlt.png"), tileColor, TileType::GROUND);
				break;
			case 'T':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/grassHillRight2.png"), tileColor, TileType::GROUND);
				break;
			case 'G':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/grassMid.png"), tileColor, TileType::GROUND);
				break;
			case 'K':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/grassHillLeft2.png"), tileColor, TileType::GROUND);
				break;
			case 'D':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/grassCenter.png"), tileColor, TileType::GROUND);
				break;
			case 'L':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/grassCliffLeft.png"), tileColor, TileType::GROUND);
				break;
			case 'R':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/grassCliffRight.png"), tileColor, TileType::GROUND);
				break;
			case 'W':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH, TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/liquidWaterTop_mid.png"), tileColor, TileType::WATER);
				break;
			case 'P':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH, TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/liquidWater.png"), tileColor, TileType::GROUND);
				break;
			case 'E':
				m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH, TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/signExit.png"), tileColor, TileType::GROUND);
				break;
			case '@':
				startPlayerPosition.x = x * TILE_WIDTH + TILE_WIDTH / 2.0f;
				startPlayerPosition.y = y * TILE_WIDTH + TILE_WIDTH / 2.0f;
				m_levelData[y][x] = '.';
				break;
			case 'S':
				//slime enemies - make these actors
				m_enemies.push_back(new Slime(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH), x * 5 % 20 * 5));// (game_world, glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH), glm::vec2(TILE_WIDTH, TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/slimeWalk1.png"), tileColor, TileType::GROUND);
				m_levelData[y][x] = '.';
				break;
			case 'F':
				//fly enemies - make these actors
				m_enemies.push_back(new Fly(glm::vec2(x * TILE_WIDTH, y * TILE_WIDTH), x % 20 * 5)); //m_boxes.emplace_back(game_world, glm::vec2(x * TILE_WIDTH + TILE_WIDTH / 2.0f, y * TILE_WIDTH + TILE_WIDTH / 2.0f), glm::vec2(TILE_WIDTH, TILE_WIDTH), JCEngine::ResourceManager::getTexture("Assets/flyFly1.png"), tileColor, TileType::GROUND);
				m_levelData[y][x] = '.';
				break;
			case '.':
				break;
			default:
				std::printf("unexpected symbol tile %c at (%d,%d)", m_levelData[y][x], x, y);
				break;
			}
		}
	}

	m_spriteBatch.init();

	//shaders init
	m_textureProgram.compileShaders("Shaders/ColorShading.vert.txt", "Shaders/ColorShading.frag.txt");
	m_textureProgram.addAttribute("vertexPosition");
	m_textureProgram.addAttribute("vertexColor");
	m_textureProgram.addAttribute("vertexUV");
	m_textureProgram.linkShaders();

	m_debugRenderer.init();

	//init camera
	m_camera.Init(m_window->GetScreenWidth(), m_window->GetScreenHeight());
	m_camera.SetScale(40.0f);

	//font for debug
	_spriteFont = new JCEngine::SpriteFont("Fonts/chintzy.ttf", 8);

	m_player = Player(game_world, startPlayerPosition, glm::vec2(0.8f, 1.8f), glm::vec2(2.0f), JCEngine::ColorRGBA8(255, 255, 255, 255), &m_camera, 12.8f, m_levelData[0].length() * TILE_WIDTH - 12.8f);
}

void GameplayScreen::onExit()
{
	m_debugRenderer.dispose();
}

void GameplayScreen::update()
{
	float timeStep = 1.0f / 60.0f;
	m_camera.Update();
	checkInput();
	if (m_player.update(m_game->inputManager, m_projectiles, timeStep)) {
		JCEngine::fatalError("");//dead
	}

	/*for (auto& enemy : m_enemies) {
		if (enemy->move(timeStep)) {

		}
	}*/

	for (int i = 0; i < m_enemies.size(); i++) {
		m_enemies[i]->move(timeStep);
		if (m_enemies[i]->isDead()) {
			delete m_enemies[i];
			m_enemies[i] = m_enemies.back();
			m_enemies.pop_back();
		}
	}

	for (int i = 0; i < m_projectiles.size(); i++) {
		Projectile* bullet = m_projectiles[i];

		bullet->update(timeStep);

		if (m_projectiles[i]->isDead() || m_projectiles[i]->collideWithLevel(m_levelData)) {
			m_projectiles[i] = m_projectiles.back();
			m_projectiles.pop_back();
			i--;
			continue;
		}

		for (int j = 0; j < m_enemies.size();) {
			Enemy* enemy = m_enemies[j];

			if (m_projectiles[i]->collideWithEnemy(enemy) && !enemy->applyDamage(m_projectiles[i]->getDamage())) {
				//addDebris(glm::vec2(asteroid->getBody()->GetPosition().x, asteroid->getBody()->GetPosition().y), 100);

				//destroy asteroid here
				/*delete enemy;
				m_enemies[j] = m_enemies.back();
				m_enemies.pop_back();*/
				//enemy->applyDamage(m_projectiles[i]->getDamage());

				m_projectiles[i] = m_projectiles.back();
				m_projectiles.pop_back();
				i--;

				//restart loop for bullet
				break;
			}
			else {
				j++;
			}
		}
	}

	//update physics simulation
	game_world->Step(1.0f / 60.0f, 6, 2);
}

void GameplayScreen::draw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.408, 0.706, 0.949f, 1.0f);

	m_textureProgram.use();

	//texture uniform
	GLint textureUniform = m_textureProgram.getUniformLocation("spriteTexture");
	glUniform1i(textureUniform, 0);
	glActiveTexture(GL_TEXTURE0);

	//camera matrix
	glm::mat4 projectionMatrix = m_camera.GetCameraMatrix();
	GLint pUniform = m_textureProgram.getUniformLocation("P");
	glUniformMatrix4fv(pUniform, 1, GL_FALSE, &projectionMatrix[0][0]);

	m_spriteBatch.begin();

	for (auto& box : m_boxes) {
		box.draw(m_spriteBatch);

		/*if (m_renderDebug) {
			box.drawPositions(m_spriteBatch, _spriteFont);
		}*/
	}

	//drawHUD();

	for (auto& projectile : m_projectiles) {
		projectile->draw(m_spriteBatch);
	}

	for (auto& enemy : m_enemies) {
		enemy->draw(m_spriteBatch);
	}

	m_player.draw(m_spriteBatch);

	m_spriteBatch.end();
	m_spriteBatch.renderBatch();

	m_textureProgram.unuse();

	//debug rendering
	if (m_renderDebug) {
		for (auto& box : m_boxes) {
			b2Body* boxBody = box.getBody();
			glm::vec4 destRect(boxBody->GetPosition().x - box.getDimensions().x / 2.0f,
								boxBody->GetPosition().y - box.getDimensions().y / 2.0f,
								box.getDimensions().x, box.getDimensions().y);

			m_debugRenderer.drawBox(destRect, JCEngine::ColorRGBA8(255, 255, 255, 255), boxBody->GetAngle());
		}

		//render player
		m_player.drawDebug(m_debugRenderer);

		for (auto& projectile : m_projectiles) {
			m_debugRenderer.drawCircle(projectile->getPosition(), JCEngine::ColorRGBA8(255, 255, 255, 255), 0.5f);
		}

		for (auto& enemy : m_enemies) {
			//m_debugRenderer.drawCircle(enemy->getPosition(), JCEngine::ColorRGBA8(255, 255, 255, 255), enemy->getHitboxRadius());
			m_debugRenderer.drawBox(glm::vec4(enemy->getPosition().x - 1.0f, enemy->getPosition().y - 0.5f, 2.0f, 1.0f), JCEngine::ColorRGBA8(255, 255, 255, 255), 0.0f);
		}

		m_debugRenderer.end();
		m_debugRenderer.render(projectionMatrix, 2.0f);
	}
}

void GameplayScreen::drawHUD() {
	char buffer[256];

	GLuint pLocation = m_textureProgram.getUniformLocation("P");
	glm::mat4 cameraMatrix = m_camera.GetCameraMatrix();
	glUniformMatrix4fv(pLocation, 1, GL_FALSE, &(cameraMatrix[0][0]));

	for (auto& box : m_boxes) {
		box.drawPositions(m_spriteBatch, _spriteFont);
	}
}

void GameplayScreen::checkInput() {
	SDL_Event event;
	while (SDL_PollEvent(&event)) {
		m_game->onSDLEvent(event);
	}
}
