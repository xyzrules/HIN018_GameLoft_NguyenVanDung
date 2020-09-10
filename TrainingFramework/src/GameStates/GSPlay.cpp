#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"

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
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Player character
	for (int i = 1; i <= GameManager::GetInstance()->GetPlayerNumber(); ++i) {
		SpawnPlayer(i, Vector2(screenWidth/4 , screenHeight/3*i));
	}

	//text game title
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("arialbd");
	std::string m_scoreText = "HEALTH POINTS: " + std::to_string(((int)(GameManager::GetInstance()->GetAncientHealthPoints())));
	m_score = std::make_shared<Text>(shader, font, m_scoreText, TEXT_COLOR::RED, 1.0);
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
		for (auto m_player : m_listPlayer) {
			m_player->HandleKeyEvent(key, bIsPressed);
		}
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}


/*
	Main gameplay loop
	Seperate with update to ease my eyes
	
	Codes in order from top to bottom

	ENEMY
	- Create enemies
	- Enemies increase over time
	- Enemies' speed increase over time

	PROJECTILE
	(object pool is hard @@)
	- Create projectile based on player's attack speed
	- Delete projectile if goes out of bounds

	HITBOX / COLLISION DETECTION
	- Enemy - Projectile
	- Player - Enemy


*/
void GSPlay::Gameplay()
{
	bool fixUI = false;

	// Create a new enemy if not maxed out
	// fix
	if (m_listEnemy.size() < GameManager::GetInstance()->GetMaxEnemy())
	{
		SpawnEnemy();
	}

	// Check if the player is ready to fire projectile
	for (auto m_player : m_listPlayer)
	{
		if (m_player->GetPlayerProjectileReady()) {
			SpawnProjectile(m_player->GetPlayerChar(), 0, m_player->Get2DPosition());
			m_player->SetPlayerProjectileReady(false);
		}
	}

	// Check projectiles if out of bounds then release memory
	for (auto m_projectile : m_listProjectile)
	{
		if (m_projectile->CheckProjectileOutOfBounds())
		{
			m_projectile->TakeDamage(10000.0f);
		}
	}

	// Check enemies if hit ancient then release memory and decrease ancient HP
	for (auto m_enemy : m_listEnemy) {
		if (m_enemy->CheckEnemyHitAncient()) {
			m_enemy->TakeDamage(10000.0f);
			GameManager::GetInstance()->DecreaseAncientHealthPoints(m_enemy->GetDamagePoint());
			fixUI = true;
		}
	}

	// Check player's and enemies' hitboxes
	for (auto it_en : m_listEnemy)
	{
		for (auto m_player : m_listPlayer) {
			ProcessCollision(it_en, m_player);
		}
	}

	// Check enemies' and projectiles' hitboxes
	for (auto it_en : m_listEnemy)
	{
		for (auto it_pro : m_listProjectile) {
			ProcessCollision(it_en, it_pro);
		}
	}

	// Check players' and projectiles' hitboxes
	// fix
	
	// Erase stuff that shouldn't be here (not player)
	for (auto it = m_listEnemy.begin(); it != m_listEnemy.end();)
	{
		if ((*it)->GetCharacterAlive() == false)
		{
			it = m_listEnemy.erase(it);
		}
		else ++it;
	}

	for (auto it = m_listProjectile.begin(); it != m_listProjectile.end();)
	{
		if ((*it)->GetCharacterAlive() == false)
		{
			it = m_listProjectile.erase(it);
		}
		else ++it;
	}

	// Work on UI
	// fix
	if (fixUI) {
		std::string m_scoreText = "HEALTH POINTS: " + std::to_string(((int)(GameManager::GetInstance()->GetAncientHealthPoints())));
		m_score->setText(m_scoreText);
	}

	// Check game ends
	if (GameManager::GetInstance()->IsEndGame()) {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_InGamePause);
	}
	
}

void GSPlay::SpawnPlayer(int playerId, Vector2 playerPos)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(GameManager::GetInstance()->GetPlayerSprite(playerId));
	std::shared_ptr<GameCharPlayer> m_player;
	switch (GameManager::GetInstance()->GetPlayerChar(playerId)) {
	case CHAR_CM:
		m_player = std::make_shared<GameCharCM>(model, shader, texture, 4, 0.13f);
		break;
	case CHAR_DR:
		m_player = std::make_shared<GameCharDrow>(model, shader, texture, 4, 0.13f);
		break;
	case CHAR_WR:
		m_player = std::make_shared<GameCharWind>(model, shader, texture, 4, 0.13f);
		break;
	case CHAR_LI:
		m_player = std::make_shared<GameCharLina>(model, shader, texture, 4, 0.13f);
		break;
	}

	m_player->Set2DPosition(playerPos);
	m_listPlayer.push_back(m_player);
}

void GSPlay::SpawnEnemy()
{
	std::shared_ptr<GameCharEnemy> m_enemy;
	int enemyId = GameManager::GetInstance()->SetEnemy();
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(GameManager::GetInstance()->GetEnemySprite(enemyId));

	switch (enemyId) {
	case ENEMY_MELEE:
		m_enemy = std::make_shared<GameCharEnemyMelee>(model, shader, texture, 4, 0.13f);
		break;
	case ENEMY_RANGE:
		m_enemy = std::make_shared<GameCharEnemyRange>(model, shader, texture, 4, 0.13f);
		break;
	case ENEMY_TANK:
		m_enemy = std::make_shared<GameCharEnemyTank>(model, shader, texture, 4, 0.13f);
		break;
	}
	GLfloat enemyHeight = 0.0f;
	while (enemyHeight < FIELD_UPPER_BOUND || enemyHeight > FIELD_LOWER_BOUND) {
		enemyHeight = (GLfloat)(rand() % screenHeight);
	}

	m_enemy->Set2DPosition(screenWidth + 100.0f, enemyHeight);
	m_listEnemy.push_back(m_enemy);
}

void GSPlay::SpawnProjectile(int playerChar, int projectileType, Vector2 pos)
{
	std::shared_ptr<GameProjectile> m_projectile;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(GameManager::GetInstance()->GetProjectileSprite(playerChar));
	//int projectileType = 0;
	m_projectile = std::make_shared<GameProjectile>(model, shader, texture, 1, 10, projectileType);
	m_projectile->SetSize(PROJECTILE_HORIZONTAL_SIZE, PROJECTILE_VERTICAL_SIZE);
	m_projectile->Set2DPosition(pos);

	m_listProjectile.push_back(m_projectile);
}

void GSPlay::ProcessCollision(std::shared_ptr<GameCharacter> char1, std::shared_ptr<GameCharacter> char2)
{
	Vector2 pos1 = char1->Get2DPosition();
	Vector2 pos2 = char2->Get2DPosition();

	GLfloat hitboxH1 = char1->GetHitboxHorizontal();
	GLfloat hitboxV1 = char1->GetHitboxVertical();

	GLfloat hitboxH2 = char2->GetHitboxHorizontal();
	GLfloat hitboxV2 = char2->GetHitboxVertical();

	/*
	std::cout << "x" << std::endl;
	std::cout << pos1.x + hitboxH1 / 2.0f << " " << pos2.x - hitboxH2 / 2.0f << std::endl;
	std::cout << pos2.x + hitboxH2 / 2.0f << " " << pos1.x - hitboxH1 / 2.0f << std::endl;
	std::cout << "y" << std::endl;
	std::cout << pos1.y + hitboxV1 / 2.0f << " " << pos1.y - hitboxV1 / 2.0f << std::endl;
	std::cout << pos2.y + hitboxV2 / 2.0f << " " << pos2.y - hitboxV2 / 2.0f << std::endl;
	*/

	if (((pos1.x + hitboxH1 / 2.0f > pos2.x - hitboxH2 / 2.0f)
		&& (pos1.x + hitboxH1 / 2.0f < pos2.x + hitboxH2 / 2.0f)) ||
		((pos1.x - hitboxH1 / 2.0f > pos2.x - hitboxH2 / 2.0f)
			&& (pos1.x - hitboxH1 / 2.0f < pos2.x + hitboxH2 / 2.0f)))
	{
		//std::cout << "IN FOR X" << std::endl;
		if (((pos1.y + hitboxV1 / 2.0f > pos2.y - hitboxV2 / 2.0f)
			&& (pos1.y + hitboxV1 / 2.0f < pos2.y + hitboxV2 / 2.0f)) ||
			((pos1.y - hitboxV1 / 2.0f > pos2.y - hitboxV2 / 2.0f)
				&& (pos1.y - hitboxV1 / 2.0f < pos2.y + hitboxV2 / 2.0f)))
		{
			//std::cout << "HIT" << std::endl;
			char1->TakeDamage(char2->GetDamagePoint());
			char2->TakeDamage(char1->GetDamagePoint());
		}
	}

	else if (((pos2.x + hitboxH2 / 2.0f > pos1.x - hitboxH1 / 2.0f)
		&& (pos2.x + hitboxH2 / 2.0f < pos1.x + hitboxH1 / 2.0f)) ||
		((pos2.x - hitboxH2 / 2.0f > pos1.x - hitboxH1 / 2.0f)
			&& (pos2.x - hitboxH2 / 2.0f < pos1.x + hitboxH1 / 2.0f)))
	{
		if (((pos2.y + hitboxV2 / 2.0f > pos1.y - hitboxV1 / 2.0f)
			&& (pos2.y + hitboxV2 / 2.0f < pos1.y + hitboxV1 / 2.0f)) ||
			((pos2.y - hitboxV2 / 2.0f > pos1.y - hitboxV1 / 2.0f)
				&& (pos2.y - hitboxV2 / 2.0f < pos1.y + hitboxV1 / 2.0f)))
		{
			char1->TakeDamage(char2->GetDamagePoint());
			char2->TakeDamage(char1->GetDamagePoint());
		}
	}
}

void GSPlay::Update(float deltaTime)
{
	Gameplay();
	for (auto m_player : m_listPlayer) {
		m_player->Update(deltaTime);
	}

	// fix
	for (auto m_enemy : m_listEnemy)
	{
		m_enemy->Update(deltaTime);
	}

	for (auto m_projectile : m_listProjectile) {
		m_projectile->Update(deltaTime);
	}
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	for (auto m_player : m_listPlayer) {
		//if (m_player->GetCharacterAlive())
		// fix
		{
			m_player->Draw();
		}
		
	}
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