#include "GameCharEnemyMelee.h"

GameCharEnemyMelee::GameCharEnemyMelee(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	:GameCharEnemy(model, shader, texture, numFrames, frameTime)
{
	m_healthPoints = ENEMY_MELEE_STARTING_HEALTH_POINTS;
	m_damagePoints = ENEMY_MELEE_DAMAGE;
	m_hitboxVertical = ENEMY_MELEE_VERTICAL_HITBOX;
	m_hitboxHorizontal = ENEMY_MELEE_HORIZONTAL_HITBOX;
	m_moveSpeedVertical = ENEMY_MELEE_STARTING_VERTICAL_SPEED;
	m_moveSpeedHorizontal = ENEMY_MELEE_STARTING_HORIZONTAL_SPEED;

	
	m_moveDirection = 0 | CHAR_MOVE_DIRECTION_LEFT;
	m_spriteName = "sprite_enemy_melee";
	SetSize(ENEMY_MELEE_HORIZONTAL_SIZE, ENEMY_MELEE_VERTICAL_SIZE);
}

GameCharEnemyMelee::~GameCharEnemyMelee()
{
}
