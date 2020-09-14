#include "GameCharPlayer.h"

GameCharPlayer::GameCharPlayer(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId)
	: GameCharacter(model, shader, texture, numFrames, frameTime),
	m_playerId(playerId),
	m_playerProjectileReady(false), m_playerSkillReady(true), m_playerSkillActivated(false), m_playerSkillEnded(true),
	m_playerAttackTimer(0), m_playerSkillTimer(0), m_playerDeathTimer(0), m_playerSkillDurationTimer(0),
	m_playerAttackSpeedMultiplyer(1.0f), m_playerMovementSpeedMultiplyer(1.0f)
{
	m_healthPoints = PLAYER_HEALTH_POINTS;
	m_damagePoints = PLAYER_DAMAGE;
	m_hitboxVertical = PLAYER_VERTICAL_HITBOX;
	m_hitboxHorizontal = PLAYER_HORIZONTAL_HITBOX;
	m_moveSpeedHorizontal = PLAYER_STARTING_HORIZONTAL_SPEED;
	m_moveSpeedVertical = PLAYER_STARTING_VERTICAL_SPEED;

	m_moveDirection = 0;

	SetSize(PLAYER_HORIZONTAL_SIZE, PLAYER_VERTICAL_SIZE);
}

GameCharPlayer::~GameCharPlayer()
{
}

void GameCharPlayer::HandleKeyEvent(int key, bool bIsPressed)
{
	if (m_playerId == 1) {
		if (bIsPressed) {
			switch (key) {
			case KEY_PLAYER1_LEFT:
				m_moveDirection |= CHAR_MOVE_DIRECTION_LEFT;
				break;
			case KEY_PLAYER1_RIGHT:
				m_moveDirection |= CHAR_MOVE_DIRECTION_RIGHT;
				break;
			case KEY_PLAYER1_UP:
				m_moveDirection |= CHAR_MOVE_DIRECTION_UP;
				break;
			case KEY_PLAYER1_DOWN:
				m_moveDirection |= CHAR_MOVE_DIRECTION_DOWN;
				break;
			case KEY_PLAYER1_SKILL:
				if (m_playerSkillReady)	ActivateSkill();
				break;
			};
		}

		else {
			switch (key) {
			case KEY_PLAYER1_LEFT:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_LEFT;
				break;
			case KEY_PLAYER1_RIGHT:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_RIGHT;
				break;
			case KEY_PLAYER1_UP:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_UP;
				break;
			case KEY_PLAYER1_DOWN:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_DOWN;
				break;
			};
		}
	}

	else if (m_playerId == 2) {
		if (bIsPressed) {
			switch (key) {
			case KEY_PLAYER2_LEFT:
				m_moveDirection |= CHAR_MOVE_DIRECTION_LEFT;
				break;
			case KEY_PLAYER2_RIGHT:
				m_moveDirection |= CHAR_MOVE_DIRECTION_RIGHT;
				break;
			case KEY_PLAYER2_UP:
				m_moveDirection |= CHAR_MOVE_DIRECTION_UP;
				break;
			case KEY_PLAYER2_DOWN:
				m_moveDirection |= CHAR_MOVE_DIRECTION_DOWN;
				break;
			case KEY_PLAYER2_SKILL:
				if (m_playerSkillReady)	ActivateSkill();
				break;
			};
		}

		else {
			switch (key) {
			case KEY_PLAYER2_LEFT:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_LEFT;
				break;
			case KEY_PLAYER2_RIGHT:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_RIGHT;
				break;
			case KEY_PLAYER2_UP:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_UP;
				break;
			case KEY_PLAYER2_DOWN:
				m_moveDirection &= ~CHAR_MOVE_DIRECTION_DOWN;
				break;
			};
		}
	}

	//std::cout << key << " " << bIsPressed << " " << m_moveDirection << std::endl;
}

void GameCharPlayer::Update(GLfloat deltaTime)
{
	// Update timer
		// attack
	m_playerAttackTimer += deltaTime;
	if (m_playerAttackTimer > PLAYER_CHARACTER_ATTACK_SPEED* m_playerAttackSpeedMultiplyer)
	{
		m_playerAttackTimer -= PLAYER_CHARACTER_ATTACK_SPEED * m_playerAttackSpeedMultiplyer;
		SetPlayerProjectileReady(true);
	}

		// skill cooldown
	if (m_playerSkillTimer <= 0)
	{
		m_playerSkillReady = true;
	}
	else {
		m_playerSkillTimer -= deltaTime;
	}

		//	skill duration
	if (m_playerSkillDurationTimer <= 0){
		m_playerSkillDurationTimer = 0;
		if (m_playerChar == CHAR_WR && m_playerSkillEnded == false)
		{
			m_playerAttackSpeedMultiplyer /= SKILL_WIND_ATTACK_SPEED_MULTIPLYER;
			m_playerMovementSpeedMultiplyer /= SKILL_WIND_MOVEMENT_SPEED_MULTIPLYER;
		}
		m_playerSkillEnded = true;
	}
	else m_playerSkillDurationTimer -= deltaTime;
	
	//	Update movement
	AnimationSprite::Update(deltaTime);

	GLfloat xMove = 0.0, yMove = 0.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_UP) yMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_DOWN) yMove = 1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_LEFT) xMove = -1.0;
	if (m_moveDirection & CHAR_MOVE_DIRECTION_RIGHT) xMove = 1.0;

	Vector2 oldPos = this->Get2DPosition();
	Vector2 newPos;

	newPos.x = oldPos.x + xMove * deltaTime * m_moveSpeedHorizontal * m_playerMovementSpeedMultiplyer;
	newPos.y = oldPos.y + yMove * deltaTime * m_moveSpeedVertical * m_playerMovementSpeedMultiplyer;

	// Set field boundaries
	if (newPos.x < FIELD_LEFT_BOUND) {
		newPos.x = FIELD_LEFT_BOUND;
	}
	else if (newPos.x > FIELD_RIGHT_BOUND) {
		newPos.x = FIELD_RIGHT_BOUND;
	}

	if (newPos.y < FIELD_UPPER_BOUND) {
		newPos.y = FIELD_UPPER_BOUND;
	}
	else if (newPos.y > FIELD_LOWER_BOUND) {
		newPos.y = FIELD_LOWER_BOUND;
	}

	this->Set2DPosition(newPos);
}

GLint GameCharPlayer::GetPlayerId()
{
	return m_playerId;
}

void GameCharPlayer::SetPlayerId(GLint playerId)
{
	m_playerId = playerId;
}

GLint GameCharPlayer::GetPlayerChar()
{
	return m_playerChar;
}

bool GameCharPlayer::GetPlayerProjectileReady()
{
	return m_playerProjectileReady;
}

void GameCharPlayer::SetPlayerProjectileReady(bool ready)
{
	m_playerProjectileReady = ready;
}

bool GameCharPlayer::GetPlayerSkillReady()
{
	return m_playerSkillReady;
}


GLfloat GameCharPlayer::GetPlayerSkillTimer()
{
	return m_playerSkillTimer;
}

bool GameCharPlayer::GetPlayerSkillEnded()
{
	return m_playerSkillEnded;
}

bool GameCharPlayer::GetPlayerSkillActivated()
{
	if (m_playerSkillActivated) {
		m_playerSkillActivated = false;
		return true;
	}
	return false;
}

