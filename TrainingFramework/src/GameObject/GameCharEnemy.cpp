#include "GameCharEnemy.h"

GameCharEnemy::GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharacter (model, shader, texture, numFrames, frameTime), m_enemyId(0), m_enemyCharacter(0)
{
}

GameCharEnemy::GameCharEnemy(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, GLfloat moveSpeedVertical, GLfloat moveSpeedHorizontal)
	: GameCharacter(model, shader, texture, numFrames, frameTime, moveSpeedVertical, moveSpeedHorizontal), m_enemyId(0), m_enemyCharacter(0)
{
}

GameCharEnemy::~GameCharEnemy()
{
}

void GameCharEnemy:: ChasePlayer(GameCharPlayer &player) {
	Vector2 playerPos, currentPos;

	playerPos = player.Get2DPosition();
	currentPos = Get2DPosition();

	m_moveDirection = 0;

	if (currentPos.y > playerPos.y)
	{
		m_moveDirection |= CHAR_MOVE_DIRECTION_UP;
	}
	else if (currentPos.y < playerPos.y)
	{
		m_moveDirection |= CHAR_MOVE_DIRECTION_DOWN;
	}

	if (currentPos.x > playerPos.x)
	{
		m_moveDirection |= CHAR_MOVE_DIRECTION_LEFT;
		m_charFacingRight = false;
	}
	else if (currentPos.x < playerPos.x)
	{
		m_moveDirection |= CHAR_MOVE_DIRECTION_RIGHT;
		m_charFacingRight = true;
	}
}

void GameCharEnemy::Update(GLfloat deltaTime, GameCharPlayer &player)
{
	ChasePlayer(player);

	AnimationSprite::Update(deltaTime);
	GLfloat xMove = 0.0, yMove = 0.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_UP) yMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_DOWN) yMove = 1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_LEFT) xMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_RIGHT) xMove = 1.0;


	Vector2 oldPos = this->Get2DPosition();

	//std::cout << "old" << m_moveDirection << " " << oldPos.x << " " << oldPos.y << std::endl;
	//std::cout << "new" << oldPos.x + xMove * deltaTime << " " << oldPos.y + yMove * deltaTime << std::endl;

	this->Set2DPosition(oldPos.x + xMove * deltaTime * m_moveSpeedHorizontal, oldPos.y + yMove * deltaTime * m_moveSpeedVertical);
}

GLint GameCharEnemy::GetEnemyId()
{
	return m_enemyId;
}

void GameCharEnemy::SetEnemyId(GLint enemyId)
{
	m_enemyId = enemyId;
}

GLint GameCharEnemy::GetEnemyCharacter()
{
	return m_enemyCharacter;
}

void GameCharEnemy::SetEnemyCharacter(GLint enemyCharacter)
{
	m_enemyCharacter = enemyCharacter;
}
