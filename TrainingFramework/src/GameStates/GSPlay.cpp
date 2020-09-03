#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <time.h>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	
}


GSPlay::~GSPlay()
{

}


void GSPlay::Init()
{
	// Prep random seed
	srand(time(NULL));
	// Game timer
	m_timer = std::make_shared<float>(0);

	// Game timer (enemy number)
	m_enemyNumberTracker = std::make_shared<float>(0);

	// Game timer (enemy's speed)
	m_enemySpeedTracker = std::make_shared<float>(0);

	// Max enemy
	m_maxEnemy = std::make_shared<float>(1.0f);

	// Enemy number multiplyer
	m_enemyNumberMultiplyer = std::make_shared<float>(ENEMY_NUMBER_STARTING_MULTIPLYER);

	// Enemy speed multiplyer
	m_enemySpeedMultiplyer = std::make_shared<float>(ENEMY_SPEED_STARTING_MULTIPLYER);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Player character
	shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	texture = ResourceManagers::GetInstance()->GetTexture("Rock");
	m_player = std::make_shared<GameCharPlayer>(model, shader, texture, 1, 0.4, PLAYER_STARTING_VERTICAL_SPEED, PLAYER_STARTING_HORIZONTAL_SPEED);
	m_player->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_player->SetSize(100, 100);

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	m_score = std::make_shared< Text>(shader, font, "score: 10", TEXT_COLOR::RED, 1.0);
	m_score->Set2DPosition(Vector2(5, 25));
}

void GSPlay::Exit()
{
	
}


void GSPlay::Pause()
{

}

void GSPlay::Resume()
{

}


void GSPlay::HandleEvents()
{

}

void GSPlay::HandleKeyEvents(int key, bool bIsPressed)
{
	if (key == KEY_BACK)
	{

	}
	else if (	key	== KEY_MOVE_BACKWARD
			||	key	== KEY_MOVE_FORWARD
			||	key	== KEY_MOVE_LEFT
			||	key	== KEY_MOVE_RIGHT)
	{
		m_player->HandleKeyEvent(key, bIsPressed);
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

// Main gameplay
// Seperate with update to ease my eyes
void GSPlay::Gameplay()
{
	// Increase number of enemies over time every 3 second, using a max value as a cap
	// Early multiplyer is big, but decay over time
	if (*m_enemyNumberTracker > ENEMY_TIME_APPLY_NUMBER_INCREASE && *m_maxEnemy < ENEMY_NUMBER_MAXIMUM)
	{
		*m_enemyNumberTracker -= ENEMY_TIME_APPLY_NUMBER_INCREASE;
		*m_maxEnemy *= *m_enemyNumberMultiplyer;
		*m_enemyNumberMultiplyer /= ENEMY_NUMBER_MULTIPLYER_DECAY;
		if (*m_enemyNumberMultiplyer < ENEMY_NUMBER_MULTIPLYER_MINIMUM) {
			*m_enemyNumberMultiplyer = ENEMY_NUMBER_MULTIPLYER_MINIMUM;
		}
	}

	// Increase enemies' speed over time every 10 second (do this is GameCharEnemy class)
	if (*m_enemySpeedTracker > ENEMY_TIME_APPLY_SPEED_INCREASE)
	{
		*m_enemySpeedTracker -= ENEMY_TIME_APPLY_SPEED_INCREASE;
		*m_enemySpeedMultiplyer *= ENEMY_SPEED_MULTIPLYER_INCREASE;
	}

	// Create a new enemy if not maxed out (should be hard af later on)
	if (m_listEnemy.size() < *m_maxEnemy)
	{
		std::cout << *m_maxEnemy << std::endl;
		std::shared_ptr<GameCharEnemy> m_enemy;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Grass");
		
		m_enemy = std::make_shared<GameCharEnemy>(model, shader, texture, 1, 0.4, ENEMY_STARTING_VERTICAL_SPEED * *m_enemySpeedMultiplyer,ENEMY_STARTING_HORIZONTAL_SPEED * *m_enemySpeedMultiplyer);
		m_enemy->SetSize(100, 100);

		if (rand() % 2 == 1)
		{
			m_enemy->Set2DPosition(screenWidth, screenHeight / 2);
		}
		else 
		{
			m_enemy->Set2DPosition(0, screenHeight / 2);
		}
		m_listEnemy.push_back(m_enemy);
		std::cout << *m_maxEnemy <<" " << *m_enemyNumberMultiplyer << std::endl;
	}

	// Check if the player is ready to fire projectile
	if (m_player->GetPlayerProjectileReady()) {
		// Fire new projectile
		std::shared_ptr<GameProjectile> m_projectile;
		auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
		auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		auto texture = ResourceManagers::GetInstance()->GetTexture("Dirt");
		int projectileType = 0;

		if (!m_player->GetCharacterFacingRight()) {
			projectileType = 1;
		}

		m_projectile = std::make_shared<GameProjectile>(model, shader, texture, 1, 0.4, projectileType, 0);
		m_projectile->SetSize(20, 50);
		m_projectile->Set2DPosition(m_player->Get2DPosition());

		std::cout << "Projectile release" << std::endl;

		m_listProjectile.push_back(m_projectile);

		m_player->SetPlayerProjectileReady(false);
	}

	// Check player's and enemies' hitboxes

		// Kill player

	// Check enemies' and projectiles' hitboxes

		// Kill enemy + projectile

	// Check projectiles if out of bounds then release memory
	for (auto it = m_listProjectile.begin(); it != m_listProjectile.end();) {
		if ((*it)->CheckProjectileOutOfBounds()) {
			it = m_listProjectile.erase(it);
		}
		else ++it;
	}

	// Check player walking out of bounds (do this in GameCharPlayer class)
}

void GSPlay::Update(float deltaTime)
{
	Gameplay();
	m_player->Update(deltaTime);
	for (auto m_projectile : m_listProjectile) {
		m_projectile->Update(deltaTime);
	}
	for (auto m_enemy : m_listEnemy)
	{
		m_enemy->Update(deltaTime, *(m_player));
	}
	*m_enemyNumberTracker += deltaTime;
	*m_enemySpeedTracker += deltaTime;
	*m_timer += deltaTime;
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_player->Draw();
	for (auto m_projectile : m_listProjectile) {
		m_projectile->Draw();
	}
	for (auto m_enemy : m_listEnemy)
	{
		m_enemy->Draw();
	}
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}