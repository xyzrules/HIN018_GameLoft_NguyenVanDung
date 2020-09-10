#include "GameManager.h"

GameManager::GameManager()
{
	m_timer = 0;
	m_playerNumber = 0;
	m_player1Char = 0;
	m_player2Char = 0;
	m_player1DeathTimer = 0;
	m_player2DeathTimer = 0;

	m_score = 0;
	m_highScore = 0;
	m_endGame = false;
	m_ready = false;
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	srand(time(NULL));
	m_highScore = std::make_shared<GLint>(0);
	
}

void GameManager::PrepareNew()
{
	m_player1Char = std::make_shared<GLint>(0); 
	m_player2Char = std::make_shared<GLint>(0);
	m_ready = std::make_shared<bool>(false);
	m_endGame = std::make_shared<bool>(false);
	m_ancientHealthPoints = std::make_shared<GLfloat>(ANCIENT_HEALTH_POINTS);
}

void GameManager::SaveResult()
{
}

GLfloat GameManager::GetAncientHealthPoints()
{
	return *m_ancientHealthPoints;
}

void GameManager::DecreaseAncientHealthPoints(GLfloat enemyHit)
{
	*m_ancientHealthPoints = *m_ancientHealthPoints - enemyHit;
	if (*m_ancientHealthPoints < 0.1f) {
		*m_endGame = true;
	}
}

void GameManager::ChooseCharacter(Characters_Id charId)
{
	if (*m_playerNumber == 1) {
		*m_player1Char = charId;
		*m_ready = true;
	}
	else {
		if (*m_player1Char == 0)
		{
			*m_player1Char = charId;
		}
		else
		{
			*m_player2Char = charId;
			*m_ready = true;
		}
	}
}

void GameManager::SetNumberOfPlayers(int playerNumber)
{
	m_playerNumber = std::make_shared<GLint>(playerNumber);
}

int GameManager::GetPlayerChar(int charId)
{
	if (charId == 1) {
		return *m_player1Char;
	}
	else return *m_player2Char;
}

std::string GameManager::GetPlayerSprite(int playerId)
{
	return m_playerCharacterSpriteSheet[(this->GetPlayerChar(playerId))];
}

int GameManager::SetEnemy()
{
	return ENEMY_MELEE;
}

int GameManager::GetMaxEnemy()
{
	return 5;
}

std::string GameManager::GetEnemySprite(int enemyId)
{
	return m_enemyCharacterSpriteSheet[enemyId];
}

std::string GameManager::GetProjectileSprite(int projectileId)
{
	return m_projectileSpriteSheet[projectileId];
}

int GameManager::GetPlayerNumber()
{
	return *m_playerNumber;
}
