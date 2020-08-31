#include "GameCharPlayer.h"

GameCharPlayer::GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	:GameCharacter(model, shader, texture)
{
	m_playerId = 0;
	m_playerCharacter = 0;
	
}

GameCharPlayer::~GameCharPlayer()
{
}

void GameCharPlayer::HandleKeyEvent(int key, bool bIsPressed)
{
	

	if (bIsPressed) {
		switch (key){
		case KEY_MOVE_LEFT:
			m_moveDirection |= CHAR_MOVE_DIRECTION_LEFT;
			break;
		case KEY_MOVE_RIGHT:
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
			m_moveDirection ^= CHAR_MOVE_DIRECTION_LEFT;
			break;
		case KEY_MOVE_RIGHT:
			m_moveDirection ^= CHAR_MOVE_DIRECTION_RIGHT;
			break;
		case KEY_MOVE_FORWARD:
			m_moveDirection ^= CHAR_MOVE_DIRECTION_UP;
			break;
		case KEY_MOVE_BACKWARD:
			m_moveDirection ^= CHAR_MOVE_DIRECTION_DOWN;
			break;
		};
	}

	//std::cout << key << " " << bIsPressed << " " << m_moveDirection << std::endl;
}

void GameCharPlayer::Update(GLfloat deltaTime)
{
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
