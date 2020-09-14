#include "GameCharEnemyRange.h"

GameCharEnemyRange::GameCharEnemyRange(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	:GameCharEnemy(model, shader, texture, numFrames, frameTime), m_enemyAttackTimer(0), m_enemyProjectileReady(false)
{
	m_healthPoints = ENEMY_RANGE_STARTING_HEALTH_POINTS;
	m_damagePoints = ENEMY_RANGE_DAMAGE;
	m_hitboxVertical = ENEMY_RANGE_VERTICAL_HITBOX;
	m_hitboxHorizontal = ENEMY_RANGE_HORIZONTAL_HITBOX;
	m_moveSpeedVertical = ENEMY_RANGE_STARTING_VERTICAL_SPEED;
	m_moveSpeedHorizontal = ENEMY_RANGE_STARTING_HORIZONTAL_SPEED;

	m_moveDirection = 0 | CHAR_MOVE_DIRECTION_LEFT;
	m_spriteName = "sprite_enemy_range";
	SetSize(ENEMY_RANGE_HORIZONTAL_SIZE, ENEMY_RANGE_VERTICAL_SIZE);
}

GameCharEnemyRange::~GameCharEnemyRange()
{
}

void GameCharEnemyRange::Update(GLfloat deltaTime)
{
	m_enemyAttackTimer += deltaTime;
	
	if (m_enemyAttackTimer > ENEMY_RANGE_ATTACK_SPEED)
	{
		//std::cout << m_enemyAttackTimer << std::endl;
		m_enemyAttackTimer = 0;
		m_enemyProjectileReady = true;
	}

	AnimationSprite::Update(deltaTime);
	GLfloat xMove = 0.0, yMove = 0.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_UP) yMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_DOWN) yMove = 1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_LEFT) xMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_RIGHT) xMove = 1.0;


	Vector2 oldPos = this->Get2DPosition();
	Vector2 newPos;
	newPos.x = oldPos.x + xMove * deltaTime * m_moveSpeedHorizontal * m_moveSpeedMultiplyer;
	newPos.y = oldPos.y + yMove * deltaTime * m_moveSpeedVertical * m_moveSpeedMultiplyer;

	if (newPos.x < FIELD_RIGHT_BOUND) {
		newPos.x = FIELD_RIGHT_BOUND;
	}

	this->Set2DPosition(newPos);
}

bool GameCharEnemyRange::EnemySpecial()
{
	if (m_enemyProjectileReady) {
		m_enemyProjectileReady = false;
		return true;
	}
	return false;
}
