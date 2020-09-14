#include "GameCharEnemyTank.h"

GameCharEnemyTank::GameCharEnemyTank(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	:GameCharEnemy(model, shader, texture, numFrames, frameTime)
{
	m_healthPoints = ENEMY_TANK_STARTING_HEALTH_POINTS;
	m_damagePoints = ENEMY_TANK_DAMAGE;
	m_hitboxVertical = ENEMY_TANK_VERTICAL_HITBOX;
	m_hitboxHorizontal = ENEMY_TANK_HORIZONTAL_HITBOX;
	m_moveSpeedVertical = ENEMY_TANK_STARTING_VERTICAL_SPEED;
	m_moveSpeedHorizontal = ENEMY_TANK_STARTING_HORIZONTAL_SPEED;

	m_moveDirection = 0 | CHAR_MOVE_DIRECTION_LEFT;
	m_spriteName = "sprite_enemy_tank";
	SetSize(ENEMY_TANK_HORIZONTAL_SIZE, ENEMY_TANK_VERTICAL_SIZE);
}
GameCharEnemyTank::~GameCharEnemyTank()
{
}

