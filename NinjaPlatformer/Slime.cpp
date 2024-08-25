#include "Slime.h"

Slime::Slime(glm::vec2 position): Enemy(position) {
	_position = position;
	//_size = size;
	_type = ActorType::ENEMY;
	_uv = glm::vec4(0.0f, 0.0f, 1.0f, 1.0f); //uv should just be standard for now

	/*_texture = JCEngine::ResourceManager::getTexture("Textures/zombie.png");

	JCEngine::GLTexture walkTexture = JCEngine::ResourceManager::getTexture("Textures/ZombieWalkAnimation.png");

	m_walkTileSheet.init(walkTexture, glm::ivec2(4, 1));

	static std::mt19937 randomEngine;
	randomEngine.seed(time(nullptr));
	static std::uniform_real_distribution<float> randomDirection(-1.0f, 1.0f);*/

	//get a random direction for movement
	//_direction = glm::vec2(randomDirection(randomEngine), randomDirection(randomEngine));
	//_direction = glm::normalize(_direction);

	//zombies are red
	_color = JCEngine::ColorRGBA8();
	_color.r = 255;
	_color.g = 255;
	_color.b = 255;
	_color.a = 255;

	//zombies faster than humans, but slower than player
	_speed = 3.0f;
	_frames = 0;
	_health = 60;
}

Slime::~Slime() {

}

void Slime::draw(JCEngine::SpriteBatch& spriteBatch) {
	float animationSpeed = 0.2f;
	glm::vec4 uvRect;
	int tileIndex, numTiles = 4;
	glm::vec4 positionRect(_position.x, _position.y, _size.x, _size.y);
	GLuint textureID;

	m_animTime += animationSpeed;

	//get animation frame
	numTiles = 4;

	tileIndex = (int)m_animTime % numTiles;

	if (m_animTime > numTiles) {
		m_animTime = 0.0f;
	}

	textureID = m_walkTileSheet.texture.id;
	uvRect = m_walkTileSheet.getUV(tileIndex);

	spriteBatch.draw(positionRect, uvRect, textureID, 0.0f, _color, _directionFacing);
}

void Slime::move(const std::vector<std::string>& levelData, float deltaTime) {
	//Actor* nearestHuman = getNearestHuman(actors, player);

	/*if (nearestHuman != nullptr) {
		_direction = glm::normalize(nearestHuman->getPosition() - _position);
		_directionFacing = _direction;

		setPosition(_position + (_direction * _speed * deltaTime));
	}*/


	collideWithLevel(levelData);
}