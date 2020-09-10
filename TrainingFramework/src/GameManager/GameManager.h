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

// Sizes & hitboxes
#define PLAYER_VERTICAL_SIZE					125.0f
#define PLAYER_HORIZONTAL_SIZE					100.0f
#define PLAYER_VERTICAL_HITBOX					100.0f
#define PLAYER_HORIZONTAL_HITBOX				80.0f

#define ENEMY_MELEE_VERTICAL_SIZE				125.0f
#define ENEMY_MELEE_HORIZONTAL_SIZE				100.0f
#define ENEMY_MELEE_VERTICAL_HITBOX				100.0f
#define ENEMY_MELEE_HORIZONTAL_HITBOX			100.0f

#define ENEMY_RANGE_VERTICAL_SIZE				125.0f
#define ENEMY_RANGE_HORIZONTAL_SIZE				100.0f
#define ENEMY_RANGE_VERTICAL_HITBOX				100.0f
#define ENEMY_RANGE_HORIZONTAL_HITBOX			100.0f

#define ENEMY_TANK_VERTICAL_SIZE				125.0f
#define ENEMY_TANK_HORIZONTAL_SIZE				100.0f
#define ENEMY_TANK_VERTICAL_HITBOX				100.0f
#define ENEMY_TANK_HORIZONTAL_HITBOX			100.0f

#define PROJECTILE_VERTICAL_SIZE				20.0f
#define PROJECTILE_HORIZONTAL_SIZE				20.0f
#define PROJECTILE_VERTICAL_HITBOX				20.0f
#define PROJECTILE_HORIZONTAL_HITBOX			20.0f

#define FIELD_LEFT_BOUND						100.0f
#define FIELD_RIGHT_BOUND						1000.0f
#define FIELD_LOWER_BOUND						650.0f
#define FIELD_UPPER_BOUND						100.0f

// Players set up
#define PLAYER_CHARACTER_ATTACK_SPEED			3.0f	//seconds
#define PLAYER_STARTING_VERTICAL_SPEED			100.0f
#define PLAYER_STARTING_HORIZONTAL_SPEED		200.0f
#define PLAYER_HEALTH_POINTS					1.0f
#define PLAYER_DAMAGE							10000.0f

// Enemies set up
#define ENEMY_NUMBER_STARTING_MULTIPLYER		2.0f
#define ENEMY_NUMBER_MULTIPLYER_DECAY			1.4f
#define ENEMY_TIME_APPLY_NUMBER_INCREASE		10.0f	//waves
#define ENEMY_NUMBER_MULTIPLYER_MINIMUM			1.05f
#define ENEMY_NUMBER_MAXIMUM					20.0f

#define ENEMY_SPEED_STARTING_MULTIPLYER			1.0f
#define ENEMY_SPEED_MULTIPLYER_INCREASE			1.01f
#define ENEMY_TIME_APPLY_SPEED_INCREASE			10.0f	//waves

	// melee
#define ENEMY_MELEE_STARTING_VERTICAL_SPEED		40.0f
#define ENEMY_MELEE_STARTING_HORIZONTAL_SPEED	500.0f
#define ENEMY_MELEE_STARTING_HEALTH_POINTS		20.0f
#define ENEMY_MELEE_DAMAGE						20.0f

	// range
#define ENEMY_RANGE_STARTING_VERTICAL_SPEED		40.0f
#define ENEMY_RANGE_STARTING_HORIZONTAL_SPEED	80.0f
#define ENEMY_RANGE_STARTING_HEALTH_POINTS		10.0f
#define ENEMY_RANGE_DAMAGE						10.0f
#define ENEMY_RANGE_PROJECTILE_SPEED			-250.0f
#define ENEMY_RANGE_PROJECTILE_HEALTH_POINTS	1.0f
#define ENEMY_RANGE_PROJECTILE_DAMAGE			10.0f

	// tank
#define ENEMY_TANK_STARTING_VERTICAL_SPEED		40.0f
#define ENEMY_TANK_STARTING_HORIZONTAL_SPEED	80.0f
#define ENEMY_TANK_STARTING_HEALTH_POINTS		50.0f
#define ENEMY_TANK_DAMAGE						20.0f

// Projectile set up
#define PROJECTILE_PLAYER_SPEED					300.0f
#define PROJECTILE_PLAYER_NORMAL_DAMAGE			10.0f


// Characters specific
#define PROJECTILE_SKILL_LINA_DAMAGE			50.0f
#define PROJECTILE_SKILL_CM_DAMAGE				50.0f

// Gameplay set up
#define ANCIENT_HITBOX_RANGE					50.0f
#define ANCIENT_HEALTH_POINTS					100.0f


enum Characters_Id
{
	CHAR_CM = 1,
	CHAR_WR,
	CHAR_DR,
	CHAR_LI,
	CHAR_TOTAL,
};

enum Enemies_Id {
	ENEMY_MELEE = 1,
	ENEMY_RANGE,
	ENEMY_TANK,
	ENEMY_TOTAL,
};

enum Projectiles_Id {
	PROJ_CM = 1,
	PROJ_WR,
	PROJ_DR,
	PROJ_LI,
	PROJ_ENEMY_RANGE,
	PROJ_TOTAL,
};

class GameManager : public CSingleton<GameManager>
{
public:
	GameManager();
	~GameManager();

	// Game
	void Init();
	void PrepareNew();
	void SaveResult();
	void SetNumberOfPlayers(int playerNumber);

	GLfloat GetAncientHealthPoints();
	void DecreaseAncientHealthPoints(GLfloat enemyHit);
	
	bool IsEndGame() { return *m_endGame; }
	bool IsReady() { return *m_ready; }

	// Players (quick note: charId = player character / playerId = the player (1 or 2))
	void ChooseCharacter(Characters_Id charId);
	int GetPlayerNumber();
	int GetPlayerChar(int playerId);
	std::string GetPlayerSprite(int playerId);

	// Enemies
	int SetEnemy();
	int GetMaxEnemy();
	std::string GetEnemySprite(int enemyId);
	
	// Projectiles
	std::string GetProjectileSprite(int projectileId);

private:
	// Timer
	std::shared_ptr<GLfloat> m_timer;

	// Players
	std::shared_ptr<GLint> m_playerNumber;
	std::shared_ptr<GLint> m_player1Char, m_player2Char;
	std::shared_ptr<GLfloat> m_player1DeathTimer, m_player2DeathTimer;
	std::string m_playerCharacterSpriteSheet[CHAR_TOTAL] = { "", "sprite_cm", "sprite_wind", "sprite_drow", "sprite_lina" };

	// Gameplay
	std::shared_ptr<bool> m_ready;					// Set ready after finishing character select
	std::shared_ptr<GLfloat> m_ancientHealthPoints;
	std::shared_ptr<GLint> m_score, m_highScore;	// Score = waves
	std::shared_ptr<bool> m_endGame;				// Set end game after ancient died

	// Enemies
	std::shared_ptr<GLfloat> m_maxEnemy, m_enemyNumberMultiplyer, m_enemyNumberTracker;
	std::shared_ptr<GLfloat> m_enemySpeedMultiplyer, m_enemySpeedTracker;
	std::string m_enemyCharacterSpriteSheet[ENEMY_TOTAL] = { "", "sprite_enemy_melee", "sprite_enemy_range", "sprite_enemy_tank"};
	
	// Projectile
	std::string m_projectileSpriteSheet[PROJ_TOTAL] = { "", "projectile_cm", "projectile_wind", "projectile_drow", "projectile_lina", "Dirt" };
};

	