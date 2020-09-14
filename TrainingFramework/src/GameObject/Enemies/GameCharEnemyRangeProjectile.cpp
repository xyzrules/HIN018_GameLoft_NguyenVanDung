#include "GameCharEnemyRangeProjectile.h"

GameCharEnemyRangeProjectile::GameCharEnemyRangeProjectile(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	:GameCharEnemy(model, shader, texture, numFrames, frameTime)
{
	m_healthPoints = ENEMY_RANGE_PROJECTILE_HEALTH_POINTS;
	m_damagePoints = ENEMY_RANGE_PROJECTILE_DAMAGE;
	m_hitboxVertical = PROJECTILE_VERTICAL_HITBOX;
	m_hitboxHorizontal = PROJECTILE_HORIZONTAL_HITBOX;
	m_moveSpeedVertical = ENEMY_RANGE_PROJECTILE_VERTICAL_SPEED;
	m_moveSpeedHorizontal = ENEMY_RANGE_PROJECTILE_HORIZONTAL_SPEED;

	m_moveDirection = 0 | CHAR_MOVE_DIRECTION_LEFT;
	//m_spriteName = "sprite_enemy_melee";
	SetSize(PROJECTILE_HORIZONTAL_SIZE, PROJECTILE_VERTICAL_SIZE);
}

GameCharEnemyRangeProjectile::~GameCharEnemyRangeProjectile()
{
}
