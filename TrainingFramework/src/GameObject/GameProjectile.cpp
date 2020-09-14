#include "GameProjectile.h"

extern GLint screenWidth;
extern GLint screenHeight;

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharacter(model, shader, texture, numFrames, frameTime),
	m_projectileType(0), m_projectileTimer(0)
{
	m_hitboxVertical = PROJECTILE_VERTICAL_HITBOX;
	m_hitboxHorizontal = PROJECTILE_HORIZONTAL_HITBOX;
}

GameProjectile::GameProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int projectileType)
	: GameCharacter(model, shader, texture, numFrames, frameTime),
	m_projectileType(projectileType), m_projectileTimer(0)
{
	switch (projectileType) {
		case PROJECTILE_NORMAL:
		case PROJECTILE_DROW_1:
		case PROJECTILE_DROW_2:
		case PROJECTILE_DROW_3:
		case PROJECTILE_DROW_4:
		{
			m_damagePoints = PROJECTILE_PLAYER_NORMAL_DAMAGE;
			m_hitboxVertical = PROJECTILE_VERTICAL_HITBOX;
			m_hitboxHorizontal = PROJECTILE_HORIZONTAL_HITBOX;
			break;
		}
		case PROJECTILE_CM_SKILL:
		{
			m_damagePoints = PROJECTILE_SKILL_CM_DAMAGE;
			m_healthPoints = PROJECTILE_SKILL_CM_HEALTH;
			m_hitboxVertical = PROJECTILE_SKILL_CM_VERTICAL_HITBOX;
			m_hitboxHorizontal = PROJECTILE_SKILL_CM_HORIZONTAL_HITBOX;
			break;
		}
		case PROJECTILE_LINA_SKILL:
		{
			m_damagePoints = PROJECTILE_SKILL_LINA_DAMAGE;
			m_healthPoints = PROJECTILE_SKILL_LINA_HEALTH;
			m_hitboxVertical = PROJECTILE_SKILL_LINA_VERTICAL_HITBOX;
			m_hitboxHorizontal = PROJECTILE_SKILL_LINA_HORIZONTAL_HITBOX;
			break;
		}
	}
}

GameProjectile::~GameProjectile()
{
}

void GameProjectile::Update(GLfloat deltaTime)
{
	// Default projectile flying right
	AnimationSprite::Update(deltaTime);

	switch (m_projectileType)
	{
		case PROJECTILE_NORMAL:
		{
			GLfloat xMove = 1.0;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_PLAYER_SPEED, oldPos.y);
			break;
		}
		
		case PROJECTILE_DROW_1:
		{
			GLfloat xMove = 1.0, yMove = -0.25;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_PLAYER_SPEED,
				oldPos.y + yMove * deltaTime * PROJECTILE_PLAYER_SPEED);
			break;
		}
		case PROJECTILE_DROW_2:
		{
			GLfloat xMove = 1.0, yMove = -0.5;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_PLAYER_SPEED,
				oldPos.y + yMove * deltaTime * PROJECTILE_PLAYER_SPEED);
			break;
		}
		case PROJECTILE_DROW_3:
		{
			GLfloat xMove = 1.0, yMove = 0.25;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_PLAYER_SPEED,
				oldPos.y + yMove * deltaTime * PROJECTILE_PLAYER_SPEED);
			break;
		}
		case PROJECTILE_DROW_4:
		{
			GLfloat xMove = 1.0, yMove = 0.5;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_PLAYER_SPEED,
				oldPos.y + yMove * deltaTime * PROJECTILE_PLAYER_SPEED);
			break;
		}
		case PROJECTILE_CM_SKILL:
		{
			m_projectileTimer += deltaTime;
			//std::cout << m_projectileTimer << std::endl;
			if (m_projectileTimer > PROJECTILE_SKILL_CM_TIME) {
				this->Set2DPosition(-100.0f, -100.0f);
			}
			break;
		}
		case PROJECTILE_LINA_SKILL:
		{
			GLfloat xMove = 1.0;
			Vector2 oldPos = this->Get2DPosition();
			this->Set2DPosition(oldPos.x + xMove * deltaTime * PROJECTILE_SKILL_LINA_SPEED, oldPos.y);
			break;
		}
	}
	
}

bool GameProjectile::CheckProjectileOutOfBounds()
{
	Vector2 pos = Get2DPosition();
	if (pos.x > screenWidth || pos.x < 0 || pos.y > screenHeight || pos.y < 0)	return true;
	return false;
}
