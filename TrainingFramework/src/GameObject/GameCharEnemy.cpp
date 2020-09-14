#include "GameCharEnemy.h"

GameCharEnemy::GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharacter (model, shader, texture, numFrames, frameTime)
{
	m_moveSpeedMultiplyer = GameManager::GetInstance()->GetEnemySpeedMultiplyer();
}

GameCharEnemy::~GameCharEnemy()
{
}

void GameCharEnemy::Update(GLfloat deltaTime)
{
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

	this->Set2DPosition(newPos);
}

bool GameCharEnemy::CheckEnemyHitAncient()
{
	Vector2 pos = Get2DPosition();
	if (pos.x < ANCIENT_HITBOX_RANGE) return true;
	return false;
}

bool GameCharEnemy::EnemySpecial()
{
	return false;
}
