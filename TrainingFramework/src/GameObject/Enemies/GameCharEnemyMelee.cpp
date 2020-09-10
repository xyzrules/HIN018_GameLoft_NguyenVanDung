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

void GameCharEnemyMelee::Update(GLfloat deltaTime)
{
	AnimationSprite::Update(deltaTime);
	GLfloat xMove = 0.0, yMove = 0.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_UP) yMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_DOWN) yMove = 1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_LEFT) xMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_RIGHT) xMove = 1.0;


	Vector2 oldPos = this->Get2DPosition();

	this->Set2DPosition(oldPos.x + xMove * deltaTime * m_moveSpeedHorizontal, oldPos.y + yMove * deltaTime * m_moveSpeedVertical);
}
