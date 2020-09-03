#include "GameCharPlayer.h"




GameCharPlayer::GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharacter(model, shader, texture, numFrames, frameTime),
	m_playerId(1), m_playerCharacter(0), m_playerProjectileReady(false), m_playerTimer(0), m_playerAlive(true)
{
}

GameCharPlayer::GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, GLfloat moveSpeedVertical, GLfloat moveSpeedHorizontal)
	: GameCharacter(model, shader, texture, numFrames, frameTime, moveSpeedVertical, moveSpeedHorizontal),
	m_playerId(1), m_playerCharacter(0), m_playerProjectileReady(false), m_playerTimer(0), m_playerAlive(true)
{
}

GameCharPlayer::~GameCharPlayer()
{
}

void GameCharPlayer::HandleKeyEvent(int key, bool bIsPressed)
{
	if (bIsPressed) {
		switch (key){
		case KEY_MOVE_LEFT:
			if (!(m_moveDirection & CHAR_MOVE_DIRECTION_RIGHT))
				m_charFacingRight = true;
			m_moveDirection |= CHAR_MOVE_DIRECTION_LEFT;
			break;
		case KEY_MOVE_RIGHT:
			if (!(m_moveDirection & CHAR_MOVE_DIRECTION_LEFT))
				m_charFacingRight = false;
			m_moveDirection |= CHAR_MOVE_DIRECTION_RIGHT;
			break;
		case KEY_MOVE_FORWARD:
			m_moveDirection |= CHAR_MOVE_DIRECTION_UP;
			break;
		case KEY_MOVE_BACKWARD:
			m_moveDirection |= CHAR_MOVE_DIRECTION_DOWN;
			break;
		};
	}

	else {
		switch (key) {
		case KEY_MOVE_LEFT:
			if (m_moveDirection & CHAR_MOVE_DIRECTION_RIGHT)
				m_charFacingRight = true;
			m_moveDirection &= ~CHAR_MOVE_DIRECTION_LEFT;
			break;
		case KEY_MOVE_RIGHT:
			if (m_moveDirection & CHAR_MOVE_DIRECTION_LEFT)
				m_charFacingRight = false;
			m_moveDirection &= ~CHAR_MOVE_DIRECTION_RIGHT;
			break;
		case KEY_MOVE_FORWARD:
			m_moveDirection &= ~CHAR_MOVE_DIRECTION_UP;
			break;
		case KEY_MOVE_BACKWARD:
			m_moveDirection &= ~CHAR_MOVE_DIRECTION_DOWN;
			break;
		};
	}

	//std::cout << key << " " << bIsPressed << " " << m_moveDirection << std::endl;
}

void GameCharPlayer::Update(GLfloat deltaTime)
{
	m_playerTimer += deltaTime;
	if (m_playerTimer > PLAYER_CHARACTER_ATTACK_SPEED) {
		m_playerTimer -= PLAYER_CHARACTER_ATTACK_SPEED;
		SetPlayerProjectileReady(true);
	}

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

GLint GameCharPlayer::GetPlayerCharacter()
{
	return m_playerCharacter;
}

void GameCharPlayer::SetPlayerCharacter(GLint playerCharacter)
{
	m_playerCharacter = playerCharacter;
}

GLint GameCharPlayer::GetPlayerId()
{
	return m_playerId;
}

void GameCharPlayer::SetPlayerId(GLint playerId)
{
	m_playerId = playerId;
}

bool GameCharPlayer::GetPlayerProjectileReady()
{
	return m_playerProjectileReady;
}

void GameCharPlayer::SetPlayerProjectileReady(bool ready)
{
	m_playerProjectileReady = ready;
}
