#include "GameProjectile.h"

extern GLint screenWidth;
extern GLint screenHeight;

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: AnimationSprite(model, shader, texture, numFrames, frameTime), m_projectileType(0), m_projectileChar (0)
{
}

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, float loopPoint)
	: AnimationSprite(model, shader, texture, numFrames, frameTime, loopPoint), m_projectileType(0), m_projectileChar(0)
{
}

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int projectileType, int projectileChar)
	: AnimationSprite(model, shader, texture, numFrames, frameTime), m_projectileType(projectileType), m_projectileChar(projectileChar)
{
}

GameProjectile::~GameProjectile()
{
}

void GameProjectile::Update(GLfloat deltaTime)
{
	// Default projectile flying right
	GLfloat xMove = 1.0;
	Vector2 oldPos = this->Get2DPosition();
	if (m_projectileType == 0)
	{
		// Projectile flying left
		xMove = -1.0;
	}

	this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_SPEED, oldPos.y);
}

bool GameProjectile::CheckProjectileOutOfBounds()
{
	Vector2 pos = Get2DPosition();
	if (pos.x > screenWidth || pos.x < 0)	return true;
	return false;
}
