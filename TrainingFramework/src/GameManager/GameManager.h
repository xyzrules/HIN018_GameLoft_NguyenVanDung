#pragma once

#include "GameManager/Singleton.h"
#include "GameConfig.h"
#include "GameObject/Shaders.h"
#include "GameObject/Texture.h"
#include "GameObject/Models.h"
#include "GameObject/Font.h"
#include "GameObject/Camera.h"
#include "GameObject/Sprite2D.h"
#include "GameObject/Sprite3D.h"
#include "GameObject/Text.h"
#include <time.h>

// Controls
#define KEY_PAUSE				27	// key Esc
#define KEY_PLAYER1_LEFT		65	// key a
#define KEY_PLAYER1_RIGHT		68	// key d
#define KEY_PLAYER1_UP			87	// key w
#define KEY_PLAYER1_DOWN		83	// key s
#define KEY_PLAYER1_SKILL		32	// key Space
#define KEY_PLAYER2_LEFT		37	// key <-
#define KEY_PLAYER2_RIGHT		39	// key ->
#define KEY_PLAYER2_UP			38	// key ^|
#define KEY_PLAYER2_DOWN		40	// key v|
#define KEY_PLAYER2_SKILL		17	// key Right Ctrl

// Sizes & hitboxes
#define PLAYER_VERTICAL_SIZE					125.0f
#define PLAYER_HORIZONTAL_SIZE					100.0f
#define PLAYER_VERTICAL_HITBOX					100.0f
#define PLAYER_HORIZONTAL_HITBOX				80.0f

#define ENEMY_MELEE_VERTICAL_SIZE				125.0f
#define ENEMY_MELEE_HORIZONTAL_SIZE				100.0f
#define ENEMY_MELEE_VERTICAL_HITBOX				100.0f
#define ENEMY_MELEE_HORIZONTAL_HITBOX			80.0f

#define ENEMY_RANGE_VERTICAL_SIZE				125.0f
#define ENEMY_RANGE_HORIZONTAL_SIZE				100.0f
#define ENEMY_RANGE_VERTICAL_HITBOX				100.0f
#define ENEMY_RANGE_HORIZONTAL_HITBOX			80.0f

#define ENEMY_TANK_VERTICAL_SIZE				150.0f
#define ENEMY_TANK_HORIZONTAL_SIZE				120.0f
#define ENEMY_TANK_VERTICAL_HITBOX				125.0f
#define ENEMY_TANK_HORIZONTAL_HITBOX			100.0f

#define PROJECTILE_VERTICAL_SIZE				25.0f
#define PROJECTILE_HORIZONTAL_SIZE				25.0f
#define PROJECTILE_VERTICAL_HITBOX				25.0f
#define PROJECTILE_HORIZONTAL_HITBOX			25.0f

#define FIELD_LEFT_BOUND						200.0f
#define FIELD_RIGHT_BOUND						1000.0f
#define FIELD_LOWER_BOUND						650.0f
#define FIELD_UPPER_BOUND						150.0f

// Players set up
#define PLAYER_CHARACTER_ATTACK_SPEED			0.5f		//seconds
#define PLAYER_STARTING_VERTICAL_SPEED			140.0f
#define PLAYER_STARTING_HORIZONTAL_SPEED		280.0f
#define PLAYER_HEALTH_POINTS					1000.0f		// points
#define PLAYER_DAMAGE							10000.0f	// points

// Enemies set up
	// melee
#define ENEMY_MELEE_STARTING_VERTICAL_SPEED		40.0f
#define ENEMY_MELEE_STARTING_HORIZONTAL_SPEED	70.0f
#define ENEMY_MELEE_STARTING_HEALTH_POINTS		50.0f		// points
#define ENEMY_MELEE_DAMAGE						10.0f		// points

	// range
#define ENEMY_RANGE_STARTING_VERTICAL_SPEED		40.0f
#define ENEMY_RANGE_STARTING_HORIZONTAL_SPEED	70.0f
#define ENEMY_RANGE_STARTING_HEALTH_POINTS		25.0f		// points
#define ENEMY_RANGE_ATTACK_SPEED				4.0f		// seconds
#define ENEMY_RANGE_DAMAGE						10.0f		// points

#define ENEMY_RANGE_PROJECTILE_VERTICAL_SPEED	40.0f
#define ENEMY_RANGE_PROJECTILE_HORIZONTAL_SPEED	180.0f
#define ENEMY_RANGE_PROJECTILE_HEALTH_POINTS	1.0f		// points
#define ENEMY_RANGE_PROJECTILE_DAMAGE			1.0f		// points

	// tank
#define ENEMY_TANK_STARTING_VERTICAL_SPEED		40.0f
#define ENEMY_TANK_STARTING_HORIZONTAL_SPEED	30.0f
#define ENEMY_TANK_STARTING_HEALTH_POINTS		200.0f		// points
#define ENEMY_TANK_DAMAGE						20.0f		// points

// Projectile set up
#define PROJECTILE_PLAYER_SPEED					300.0f
#define PROJECTILE_PLAYER_NORMAL_DAMAGE			25.0f		// points

// Characters specific
	// cooldown
#define SKILL_COOLDOWN_CM						20.0f		// seconds
#define SKILL_COOLDOWN_LINA						35.0f		// seconds
#define SKILL_COOLDOWN_DROW						15.0f		// seconds
#define SKILL_COOLDOWN_WIND						12.0f		// seconds
	// passive skill with duration
#define SKILL_DURATION_DROW						5.0f		// seconds

#define SKILL_DURATION_WIND						5.0f		// seconds
#define SKILL_WIND_ATTACK_SPEED_MULTIPLYER		0.3f
#define SKILL_WIND_MOVEMENT_SPEED_MULTIPLYER	2.5f

	// active skill
#define PROJECTILE_SKILL_LINA_VERTICAL_SIZE		250.0f
#define PROJECTILE_SKILL_LINA_HORIZONTAL_SIZE	200.0f
#define PROJECTILE_SKILL_LINA_VERTICAL_HITBOX	250.0f
#define PROJECTILE_SKILL_LINA_HORIZONTAL_HITBOX	120.0f
#define PROJECTILE_SKILL_LINA_DAMAGE			10000.0f	// points
#define PROJECTILE_SKILL_LINA_HEALTH			10000.0f	// points
#define PROJECTILE_SKILL_LINA_SPEED				500.0f

#define PROJECTILE_SKILL_CM_VERTICAL_SIZE		300.0f
#define PROJECTILE_SKILL_CM_HORIZONTAL_SIZE		160.0f
#define PROJECTILE_SKILL_CM_VERTICAL_HITBOX		230.0f
#define PROJECTILE_SKILL_CM_HORIZONTAL_HITBOX	180.0f
#define PROJECTILE_SKILL_CM_DAMAGE				10000.0f	// points
#define PROJECTILE_SKILL_CM_HEALTH				10000.0f	// points
#define PROJECTILE_SKILL_CM_TIME				1.5f		// seconds
#define PROJECTILE_SKILL_CM_COUNT				8

// Gameplay set up
#define ANCIENT_HITBOX_RANGE					70.0f
#define ANCIENT_HEALTH_POINTS					100.0f		// points

#define ENEMY_NUMBER_MULTIPLYER					1.3f
#define ENEMY_NUMBER_STARTING_MAX				3.0f
#define ENEMY_NUMBER_ON_FIELD_STARTING_MAX		1.0f

#define ENEMY_SPEED_MULTIPLYER					1.05f

#define RUSH_STARTING_TIMER						2.0f
#define RUSH_TIMER_MULTIPLYER					0.99f

#define PAUSE_AFTER_WAVES						5			// waves

enum Characters_Id
{
	CHAR_NONE = 0,
	CHAR_CM,
	CHAR_WR,
	CHAR_DR,
	CHAR_LI,
	CHAR_TOTAL,
};

enum Enemies_Id {
	ENEMY_NONE = 0,
	ENEMY_MELEE,
	ENEMY_RANGE,
	ENEMY_TANK,
	ENEMY_RANGE_PROJ,
	ENEMY_TOTAL,
};

enum Projectiles_Id {
	PROJ_NONE = 0,
	PROJ_CM,
	PROJ_WR,
	PROJ_DR,
	PROJ_LI,
	PROJ_TOTAL,
};

class GameManager : public CSingleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	// Game
	void Init();
	void PrepareNewGame();
	void PrepareNewWave();
	void SaveResult();
	void SetNumberOfPlayers(int playerNumber);
	void UpdateTimer(float deltaTime);

	GLfloat GetAncientHealthPoints();
	void DecreaseAncientHealthPoints(GLfloat enemyHit);
	void EnemyRush();
	
	int GetScore();
	bool IsEndWave() { return *m_endWave; }
	bool IsEndGame() { return *m_endGame; }
	bool IsReady() { return *m_ready; }

	// Players (quick note: charId = player character / playerId = the player (1 or 2))
	void ChooseCharacter(Characters_Id charId);
	int GetPlayerNumber();
	int GetPlayerChar(int playerId);
	std::string GetPlayerSprite(int playerId);

	// Enemies
	int SetEnemy();
	void KillEnemy();
	void SpawnExtraEnemy();
	GLfloat GetEnemySpeedMultiplyer();

	std::string GetEnemySprite(int enemyId);
	
	// Projectiles
	std::string GetProjectileSprite(int projectileId);

	// Sound
	float GetMusicVolume();
	float GetSfxVolume();
	void SetMusicVolume(float newVolume);
	void SetSfxVolume(float newVolume);

private:
	// Timer
	std::shared_ptr<GLfloat> m_rushTimer, m_timer;
	std::shared_ptr<GLfloat> m_rushTimerMultiplyer;

	// Players
	std::shared_ptr<GLint> m_playerNumber;
	std::shared_ptr<GLint> m_player1Char, m_player2Char;
	std::shared_ptr<GLfloat> m_player1DeathTimer, m_player2DeathTimer;
	std::string m_playerCharacterSpriteSheet[CHAR_TOTAL] = { "", "sprite_cm", "sprite_wind", "sprite_drow", "sprite_lina" };

	// Gameplay
	std::shared_ptr<bool> m_ready;					// Set ready after finishing character select
	std::shared_ptr<GLfloat> m_ancientHealthPoints;
	std::shared_ptr<GLint> m_score, m_highScore;	// Score = waves
	std::shared_ptr<bool> m_endGame, m_endWave;		// Set end game after ancient died, end wave after all enemies died

	// Enemies
	std::shared_ptr<GLfloat> m_enemySpawnRemaining, m_enemyAliveRemaining, m_enemyNumberMultiplyer, m_enemySpawnPerRushRemaining;
	std::shared_ptr<GLfloat> m_enemySpeedMultiplyer;
	std::string m_enemyCharacterSpriteSheet[ENEMY_TOTAL] = { "", "sprite_enemy_melee", "sprite_enemy_range", "sprite_enemy_tank", "projectile_enemy"};
	
	// Projectile
	std::string m_projectileSpriteSheet[PROJ_TOTAL] = { "", "projectile_cm", "projectile_wind", "projectile_drow", "projectile_lina"};

	// Other
	std::shared_ptr<float> g_musicVolume, g_sfxVolume;
};

	