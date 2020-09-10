#include "GameProjectile.h"

extern GLint screenWidth;
extern GLint screenHeight;

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharacter(model, shader, texture, numFrames, frameTime),
	m_projectileType(0)
{
	m_hitboxVertical = PROJECTILE_VERTICAL_HITBOX;
	m_hitboxHorizontal = PROJECTILE_HORIZONTAL_HITBOX;
}

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int projectileType)
	: GameCharacter(model, shader, texture, numFrames, frameTime),
	m_projectileType(projectileType)
{
	switch (projectileType) {
		case PROJECTILE_NORMAL:
		case PROJECTILE_DROW_1:
		case PROJECTILE_DROW_2:
		case PROJECTILE_DROW_3:
		case PROJECTILE_DROW_4:
		{
			m_damagePoints = PROJECTILE_PLAYER_NORMAL_DAMAGE;
			break;
		}
		case PROJECTILE_CM_SKILL:
		{
			m_damagePoints = PROJECTILE_SKILL_CM_DAMAGE;
			break;
		}
		case PROJECTILE_LINA_SKILL:
		{
			m_damagePoints = PROJECTILE_SKILL_LINA_DAMAGE;
			break;
		}
	}
	m_hitboxVertical = PROJECTILE_VERTICAL_HITBOX;
	m_hitboxHorizontal = PROJECTILE_HORIZONTAL_HITBOX;
}

GameProjectile::~GameProjectile()
{
}

void GameProjectile::Update(GLfloat deltaTime)
{
	// Default projectile flying right
	switch (m_projectileType)
	{
		case PROJECTILE_NORMAL:
		{
			GLfloat xMove = 1.0;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_PLAYER_SPEED, oldPos.y);
			break;
		}
		/*
		case PROJECTILE_ENEMY_RANGE:
		{
			GLfloat xMove = 1.0;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_ENEMY_RANGE_SPEED, oldPos.y);
			break;
		}
		*/
	}
	
}

bool GameProjectile::CheckProjectileOutOfBounds()
{
	Vector2 pos = Get2DPosition();
	if (pos.x > screenWidth || pos.x < 0 || pos.y > screenHeight || pos.y < 0)	return true;
	return false;
}
