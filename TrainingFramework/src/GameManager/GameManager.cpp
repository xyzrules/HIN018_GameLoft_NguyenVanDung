#include "GameManager.h"

GameManager::GameManager()
{
	m_timer = 0;
	m_rushTimer = 0;
	m_playerNumber = 0;
	m_player1Char = 0;
	m_player2Char = 0;
	m_player1DeathTimer = 0;
	m_player2DeathTimer = 0;

	m_score = 0;
	m_highScore = 0;
	m_endGame = false;
	m_ready = false;

	g_sfxVolume = std::make_shared<float>(0.8f);
	g_musicVolume = std::make_shared<float>(0.6f);
}

GameManager::~GameManager()
{
}

void GameManager::Init()
{
	srand(time(NULL));
	m_highScore = std::make_shared<GLint>(0);
	
}

void GameManager::PrepareNewGame()
{
	m_timer = std::make_shared<GLfloat>(0);
	m_rushTimer = std::make_shared<GLfloat>(0);
	m_rushTimerMultiplyer = std::make_shared<GLfloat>(1.0f);

	m_player1Char = std::make_shared<GLint>(0); 
	m_player2Char = std::make_shared<GLint>(0);
	m_ready = std::make_shared<bool>(false);
	m_endGame = std::make_shared<bool>(false);
	m_endWave = std::make_shared<bool>(true);
	m_score = std::make_shared<GLint>(0);
	m_ancientHealthPoints = std::make_shared<GLfloat>(ANCIENT_HEALTH_POINTS);

	m_enemySpawnRemaining = std::make_shared<GLfloat>(0);
	m_enemyAliveRemaining = std::make_shared<GLfloat>(0);
	m_enemyNumberMultiplyer = std::make_shared<GLfloat>(1.0f);
	m_enemySpawnPerRushRemaining = std::make_shared<GLfloat>(0);
	m_enemySpeedMultiplyer = std::make_shared<GLfloat>(1.0f);
}

void GameManager::PrepareNewWave()
{
	*m_endWave = false;
	*m_score += 1;
	if (*m_score == 1 || *m_score == PAUSE_AFTER_WAVES * 1 + 1 || *m_score == PAUSE_AFTER_WAVES * 2 + 1) {
		*m_enemySpawnRemaining = 1;
		*m_enemyAliveRemaining = 1;
	}
	else {
		*m_enemyNumberMultiplyer *= ENEMY_NUMBER_MULTIPLYER;
		*m_rushTimerMultiplyer *= RUSH_TIMER_MULTIPLYER;
		*m_enemySpeedMultiplyer *= ENEMY_SPEED_MULTIPLYER;

		*m_enemySpawnRemaining = ENEMY_NUMBER_STARTING_MAX * (*m_enemyNumberMultiplyer);
		*m_enemyAliveRemaining = ENEMY_NUMBER_STARTING_MAX * (*m_enemyNumberMultiplyer);

		//std::cout << *m_enemySpawnRemaining <<" "<< *m_enemyAliveRemaining <<" "<< *m_rushTimerMultiplyer << std::endl;
	}
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

void GameManager::EnemyRush()
{
	if (*m_rushTimer > RUSH_STARTING_TIMER* (*m_rushTimerMultiplyer)) {
		*m_rushTimer = 0;
		*m_enemySpawnPerRushRemaining = (float)*m_score / 2.0f;
	}
}

int GameManager::GetScore()
{
	return *m_score;
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

void GameManager::UpdateTimer(float deltaTime)
{
	*m_timer += deltaTime;
	*m_rushTimer += deltaTime;
	EnemyRush();
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

// Random an enemy
int GameManager::SetEnemy()
{
	if (*m_enemySpawnPerRushRemaining > 0 && *m_enemySpawnRemaining > 0) {
		*m_enemySpawnPerRushRemaining -= 1.0f;
		*m_enemySpawnRemaining -= 1.0f;
		//std::cout << "spawn " << *m_enemySpawnPerRushRemaining << std::endl;
		if (*m_score <= PAUSE_AFTER_WAVES)
		{
			return ENEMY_MELEE;
		}
		else if (*m_score == PAUSE_AFTER_WAVES * 1 + 1)
		{
			return ENEMY_RANGE;
		}
		else if (*m_score <= PAUSE_AFTER_WAVES * 2)
		{
			int res = rand() % 100;
			if (res < 70) return ENEMY_MELEE;
			else return ENEMY_RANGE;
		}
		else if (*m_score == PAUSE_AFTER_WAVES * 2 + 1) {
			return ENEMY_TANK;
		}
		else {
			int res = rand() % 100;
			if (res < 50) return ENEMY_MELEE;
			else if (res < 80) return ENEMY_RANGE;
			else return ENEMY_TANK;
		}
	}
	else return ENEMY_NONE;
}

void GameManager::KillEnemy()
{
	*m_enemyAliveRemaining -= 1;
	if (*m_enemyAliveRemaining <= 0) {
		*m_endWave = true;
	}
}

void GameManager::SpawnExtraEnemy()
{
	*m_enemyAliveRemaining += 1;
}

GLfloat GameManager::GetEnemySpeedMultiplyer()
{
	return *m_enemySpeedMultiplyer;
}

std::string GameManager::GetEnemySprite(int enemyId)
{
	return m_enemyCharacterSpriteSheet[enemyId];
}

std::string GameManager::GetProjectileSprite(int projectileId)
{
	return m_projectileSpriteSheet[projectileId];
}

float GameManager::GetMusicVolume()
{
	return *g_musicVolume;
}

float GameManager::GetSfxVolume()
{
	return *g_sfxVolume;
}

void GameManager::SetMusicVolume(float newVolume)
{
	*g_musicVolume = newVolume;
}

void GameManager::SetSfxVolume(float newVolume)
{
	*g_sfxVolume = newVolume;
}

int GameManager::GetPlayerNumber()
{
	return *m_playerNumber;
}
