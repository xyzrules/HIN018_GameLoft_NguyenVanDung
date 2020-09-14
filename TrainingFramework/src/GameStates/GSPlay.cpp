#include "GSPlay.h"

#include "Shaders.h"
#include "Texture.h"
#include "Models.h"
#include "Camera.h"
#include "Font.h"
#include "Sprite2D.h"
#include "Sprite3D.h"
#include "Text.h"
#include <algorithm>

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSPlay::GSPlay()
{
	
}

GSPlay::~GSPlay()
{
}

bool sortLogic(std::shared_ptr<GameCharacter> x, std::shared_ptr<GameCharacter> y) {
	return (x->Get2DPosition().y < y->Get2DPosition().y);
}

void GSPlay::Init()
{
	// Early init
	// Sound
	Application::gSoloud.stopAll();
	m_BGSound = std::make_shared<SoLoud::WavStream>();
	m_pickItemsSound = std::make_shared<SoLoud::WavStream>();
	m_pickItemsSound->load("..\\Data\\Sounds\\item_pick.mp3");
	PlayBackgroundSound();

	m_cmSound = std::make_shared<SoLoud::Wav>();
	m_liSound = std::make_shared<SoLoud::Wav>();
	m_wrSound = std::make_shared<SoLoud::Wav>();
	m_drSound = std::make_shared<SoLoud::Wav>();

	m_waveTransition = std::make_shared<int>(TRANSITION_START_WAVE);
	m_transitionTimer = std::make_shared <float>(0);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_play");
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");

	//BackGround
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//Portrait Sprite
	std::shared_ptr<Sprite2D> m_portrait;
	for (int i = 1; i <= GameManager::GetInstance()->GetPlayerNumber(); ++i) {
		switch (GameManager::GetInstance()->GetPlayerChar(i)) {
		case CHAR_CM:
			texture = ResourceManagers::GetInstance()->GetTexture("portrait_sprite_cm");
			break;
		case CHAR_DR:
			texture = ResourceManagers::GetInstance()->GetTexture("portrait_sprite_drow");
			break;
		case CHAR_WR:
			texture = ResourceManagers::GetInstance()->GetTexture("portrait_sprite_wind");
			break;
		case CHAR_LI:
			texture = ResourceManagers::GetInstance()->GetTexture("portrait_sprite_lina");
			break;
		}
		m_portrait = std::make_shared<Sprite2D>(model, shader, texture);
		m_portrait->SetSize(200, 100);
		if (i == 1) m_portrait->Set2DPosition(100, PORTRAIT_P1);
		else m_portrait->Set2DPosition(100, PORTRAIT_P2);
		m_listPortrait.push_back(m_portrait);
	}

	//Skill icon
	std::shared_ptr<Sprite2D> m_icon;
	for (int i = 1; i <= GameManager::GetInstance()->GetPlayerNumber(); ++i) {
		switch (GameManager::GetInstance()->GetPlayerChar(i)) {
		case CHAR_CM:
			texture = ResourceManagers::GetInstance()->GetTexture("skill_icon_cm");
			break;
		case CHAR_DR:
			texture = ResourceManagers::GetInstance()->GetTexture("skill_icon_drow");
			break;
		case CHAR_WR:
			texture = ResourceManagers::GetInstance()->GetTexture("skill_icon_wind");
			break;
		case CHAR_LI:
			texture = ResourceManagers::GetInstance()->GetTexture("skill_icon_lina");
			break;
		}
		m_icon = std::make_shared<Sprite2D>(model, shader, texture);
		m_icon->SetSize(50, 50);
		if (i == 1) m_icon->Set2DPosition(140, PORTRAIT_P1);
		else m_icon->Set2DPosition(140, PORTRAIT_P2);
		m_listIcon.push_back(m_icon);
	}


	//Player character
	for (int i = 1; i <= GameManager::GetInstance()->GetPlayerNumber(); ++i) {
		SpawnPlayer(i, Vector2(screenWidth/4 , screenHeight/3*i));
	}

	//Text
		// health
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("lemonadestand");
	std::string m_ancientText = "" + std::to_string(((int)(GameManager::GetInstance()->GetAncientHealthPoints())));
	m_ancient = std::make_shared<Text>(shader, font, m_ancientText, TEXT_COLOR::RED, 2.0);
	m_ancient->Set2DPosition(Vector2(120, 70));
		// scores
	std::string m_scoreText = "WAVES  " + std::to_string(((int)(GameManager::GetInstance()->GetScore() + 1)));
	m_score = std::make_shared<Text>(shader, font, m_scoreText, TEXT_COLOR::DARK_BLUE, 2.0);
	m_score->Set2DPosition(Vector2(580, 50));
		// start wave
	std::string m_transitionScoreText = "WAVES " + std::to_string(((int)(GameManager::GetInstance()->GetScore() + 1)));
	m_transitionScore = std::make_shared<Text>(shader, font, m_transitionScoreText, TEXT_COLOR::CYAN, 2.5);
	m_transitionScore->Set2DPosition(Vector2(screenWidth / 2 - 20, screenHeight / 2));
		// clear wave
	m_transitionScoreText = "CLEAR";
	m_transitionClear = std::make_shared<Text>(shader, font, m_transitionScoreText, TEXT_COLOR::WHITE, 2.5);
	m_transitionClear->Set2DPosition(Vector2(screenWidth / 2, screenHeight / 2));

	for (int i = 1; i <= GameManager::GetInstance()->GetPlayerNumber(); ++i) {
		std::shared_ptr<Text> m_cooldownText = std::make_shared<Text>(shader, font, "", TEXT_COLOR::RED, 1.5);
		if (i == 1) m_cooldownText->Set2DPosition(130, PORTRAIT_P1 + 20);
		else m_cooldownText->Set2DPosition(130, PORTRAIT_P2 + 20);
		m_listCooldownCounter.push_back(m_cooldownText);
	}

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
	if (key == KEY_PAUSE)
	{
		GameStateMachine::GetInstance()->PushState(StateTypes::STATE_InGamePause);
	}
	else if (	key	== KEY_PLAYER1_LEFT
			||	key	== KEY_PLAYER1_RIGHT
			||	key	== KEY_PLAYER1_UP
			||	key	== KEY_PLAYER1_DOWN
			||	key == KEY_PLAYER1_SKILL
			||	key == KEY_PLAYER2_LEFT
			||	key == KEY_PLAYER2_RIGHT
			||	key == KEY_PLAYER2_UP
			||	key == KEY_PLAYER2_DOWN
			||	key == KEY_PLAYER2_SKILL
		)
	{
		for (auto m_player : m_listPlayer) {
			m_player->HandleKeyEvent(key, bIsPressed);
		}
	}
	else {
		//std::cout << key << std::endl;
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

/*
	Main gameplay loop
	Seperate with update to ease my eyes
*/
void GSPlay::Gameplay()
{
	bool fixUI = false;
	SortSprite();

	// Check the player skill's cooldown
	for (auto m_player : m_listPlayer) {
		ProcessSkillSprite(m_player);
	}

	if (*m_waveTransition == TRANSITION_CLEAR_WAVE) {
		if (*m_transitionTimer > WAVE_DELAY) {
			if (GameManager::GetInstance()->IsEndGame()) {
				GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_EndGame);
			}
			/*
			else if (GameManager::GetInstance()->GetScore() % PAUSE_AFTER_WAVES == 0) {
				*m_waveTransition = TRANSITION_PICK_ITEM;
				m_BGSound->stop();
				Application::gSoloud.play(*m_pickItemsSound);
			}
			*/
			else {
				*m_transitionTimer = 0;
				*m_waveTransition = TRANSITION_START_WAVE;
			}
		}
	}

	else if (*m_waveTransition == TRANSITION_PICK_ITEM) {
		// if (finish picking items)
		{
			*m_transitionTimer = 0;
			*m_waveTransition = TRANSITION_START_WAVE;
			m_pickItemsSound->stop();
			PlayBackgroundSound();
		}
	}

	else if (*m_waveTransition == TRANSITION_START_WAVE) {
		if (*m_transitionTimer > WAVE_DELAY) {
			*m_waveTransition = TRANSITION_NONE;
			GameManager::GetInstance()->PrepareNewWave();
			fixUI = true;
		}
	}

	else if (*m_waveTransition == TRANSITION_NONE){

		// check game ends
		if (GameManager::GetInstance()->IsEndGame()) {
			*m_transitionTimer = 0;
			*m_waveTransition = TRANSITION_CLEAR_WAVE;
			std::string m_endText = "YOUR ANCIENT IS LOST";
			m_transitionClear->Set2DPosition(screenWidth / 2 - 200, screenHeight / 2);
			m_transitionClear->setText(m_endText);
			fixUI = true;
		}

		// check wave ends
		if (GameManager::GetInstance()->IsEndWave()) {
			/*if (GameManager::GetInstance()->GetScore() % PAUSE_AFTER_WAVES == 0) {
				*m_waveTransition = 2;
			}
			else {*/
			*m_transitionTimer = 0;
			*m_waveTransition = TRANSITION_CLEAR_WAVE;
			
			std::string m_transitionScoreText = "WAVES " + std::to_string(((int)(GameManager::GetInstance()->GetScore() + 1)));
			m_transitionScore->setText(m_transitionScoreText);
			fixUI = true;
		}

		// Spawn enenmies
		SpawnEnemy(0, Vector2(0,0));

		

		for (auto m_player : m_listPlayer) {
			if (m_player->GetPlayerSkillActivated()) {
				ProcessSkill(m_player);
			}
		}

		// Check if the player is ready to fire projectile
		for (auto m_player : m_listPlayer)
		{
			if (m_player->GetPlayerProjectileReady()) {
				if (m_player->GetPlayerChar() == CHAR_DR && !m_player->GetPlayerSkillEnded()) {
					SpawnProjectile(m_player->GetPlayerChar(), PROJECTILE_DROW_1, m_player->Get2DPosition());
					SpawnProjectile(m_player->GetPlayerChar(), PROJECTILE_DROW_2, m_player->Get2DPosition());
					SpawnProjectile(m_player->GetPlayerChar(), PROJECTILE_DROW_3, m_player->Get2DPosition());
					SpawnProjectile(m_player->GetPlayerChar(), PROJECTILE_DROW_4, m_player->Get2DPosition());
				}
				SpawnProjectile(m_player->GetPlayerChar(), 0, m_player->Get2DPosition());
				m_player->SetPlayerProjectileReady(false);
			}
		}

		// Check if the enemy is ready to fire projectile
		for (auto m_enemy : m_listEnemy)
		{
			if (m_enemy->EnemySpecial()) {
				SpawnEnemy(1, m_enemy->Get2DPosition());
				GameManager::GetInstance()->SpawnExtraEnemy();
				break;
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

		/*
		// Check player's and enemies' hitboxes
		for (auto it_en : m_listEnemy)
		{
			for (auto m_player : m_listPlayer) {
				ProcessCollision(it_en, m_player);
			}
		}
		*/
		// Check enemies' and projectiles' hitboxes
		for (auto it_en : m_listEnemy)
		{
			for (auto it_pro : m_listProjectile) {
				ProcessCollision(it_en, it_pro);
			}
		}
	
		// Erase stuff that shouldn't be here (not player)
		for (auto it = m_listEnemy.begin(); it != m_listEnemy.end();)
		{
			if ((*it)->GetCharacterAlive() == false)
			{
				it = m_listEnemy.erase(it);
				GameManager::GetInstance()->KillEnemy();
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
			std::string m_ancientText = "" + std::to_string(((int)(GameManager::GetInstance()->GetAncientHealthPoints())));
			m_ancient->setText(m_ancientText);
			std::string m_scoreText = "WAVES " + std::to_string(((int)(GameManager::GetInstance()->GetScore() + 1)));
			m_score->setText(m_scoreText);
		}
	}
	
}

void GSPlay::SortSprite()
{
	std::sort(m_listPlayer.begin(), m_listPlayer.end(), sortLogic);
	std::sort(m_listEnemy.begin(), m_listEnemy.end(), sortLogic);

}

void GSPlay::SpawnPlayer(int playerId, Vector2 playerPos)
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
	auto texture = ResourceManagers::GetInstance()->GetTexture(GameManager::GetInstance()->GetPlayerSprite(playerId));
	std::shared_ptr<GameCharPlayer> m_player;
	switch (GameManager::GetInstance()->GetPlayerChar(playerId)) {
	case CHAR_CM:
		m_player = std::make_shared<GameCharCM>(model, shader, texture, 4, 0.13f, playerId);
		break;
	case CHAR_DR:
		m_player = std::make_shared<GameCharDrow>(model, shader, texture, 4, 0.13f, playerId);
		break;
	case CHAR_WR:
		m_player = std::make_shared<GameCharWind>(model, shader, texture, 4, 0.13f, playerId);
		break;
	case CHAR_LI:
		m_player = std::make_shared<GameCharLina>(model, shader, texture, 4, 0.13f, playerId);
		break;
	}
	m_player->Set2DPosition(playerPos);
	m_listPlayer.push_back(m_player);
}

void GSPlay::SpawnEnemy(int enemySpecial, Vector2 enemyPos)
{
	std::shared_ptr<GameCharEnemy> m_enemy;
	int enemyId = GameManager::GetInstance()->SetEnemy();
	if (enemySpecial != 0)	enemyId = ENEMY_RANGE_PROJ;

	if (enemyId != ENEMY_NONE) {
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
		case ENEMY_RANGE_PROJ:
			m_enemy = std::make_shared<GameCharEnemyRangeProjectile>(model, shader, texture, 4, 0.13f);
			break;
		}
		
		if (enemySpecial != 0) {
			m_enemy->Set2DPosition(enemyPos);
		}
		else
		{
			GLfloat enemyHeight = 0.0f;
			while (enemyHeight < FIELD_UPPER_BOUND || enemyHeight > FIELD_LOWER_BOUND) {
				enemyHeight = (GLfloat)(rand() % screenHeight);
			}
			m_enemy->Set2DPosition(screenWidth + 100.0f, enemyHeight);
		}
		m_listEnemy.push_back(m_enemy);
	}
}

void GSPlay::SpawnProjectile(int playerChar, int projectileType, Vector2 pos)
{
	std::shared_ptr<GameProjectile> m_projectile;
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");

	switch (projectileType) {
	case PROJECTILE_NORMAL:
	case PROJECTILE_DROW_1:
	case PROJECTILE_DROW_2:
	case PROJECTILE_DROW_3:
	case PROJECTILE_DROW_4:
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture(GameManager::GetInstance()->GetProjectileSprite(playerChar));
		m_projectile = std::make_shared<GameProjectile>(model, shader, texture, 1, 10, projectileType);
		m_projectile->SetSize(PROJECTILE_HORIZONTAL_SIZE, PROJECTILE_VERTICAL_SIZE);
		break;
	}
	case PROJECTILE_CM_SKILL:
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite_cm_skill");
		m_projectile = std::make_shared<GameProjectile>(model, shader, texture, 25, 0.066f, projectileType);
		m_projectile->SetSize(PROJECTILE_SKILL_CM_HORIZONTAL_SIZE, PROJECTILE_SKILL_CM_VERTICAL_SIZE);
		break;
	}
	case PROJECTILE_LINA_SKILL:
	{
		auto texture = ResourceManagers::GetInstance()->GetTexture("sprite_lina_skill");
		m_projectile = std::make_shared<GameProjectile>(model, shader, texture, 1, 10, projectileType);
		m_projectile->SetSize(PROJECTILE_SKILL_CM_HORIZONTAL_SIZE, PROJECTILE_SKILL_CM_VERTICAL_SIZE);
		break;
	}
	}

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

	if (char1->GetCharacterAlive() && char2->GetCharacterAlive()){
		bool hit = false;
		/*
		std::cout << pos1.x << " " << pos1.y << " " << hitboxH1 << " " << hitboxV1 << std::endl;
		std::cout << pos2.x << " " << pos2.y << " " << hitboxH2 << " " << hitboxV2 << std::endl;
		*/
		if (((pos1.x + hitboxH1 / 2.0f >= pos2.x - hitboxH2 / 2.0f)
			&& (pos1.x + hitboxH1 / 2.0f <= pos2.x + hitboxH2 / 2.0f)) ||
			((pos1.x - hitboxH1 / 2.0f >= pos2.x - hitboxH2 / 2.0f)
				&& (pos1.x - hitboxH1 / 2.0f <= pos2.x + hitboxH2 / 2.0f)))
		{
			//std::cout << "IN FOR X" << std::endl;
			if (((pos1.y + hitboxV1 / 2.0f >= pos2.y - hitboxV2 / 2.0f)
				&& (pos1.y + hitboxV1 / 2.0f <= pos2.y + hitboxV2 / 2.0f)) ||
				((pos1.y - hitboxV1 / 2.0f >= pos2.y - hitboxV2 / 2.0f)
					&& (pos1.y - hitboxV1 / 2.0f <= pos2.y + hitboxV2 / 2.0f)))
			{
				//std::cout << "HIT" << std::endl;
				hit = true;
			}
		}

		if (((pos2.x + hitboxH2 / 2.0f >= pos1.x - hitboxH1 / 2.0f)
			&& (pos2.x + hitboxH2 / 2.0f <= pos1.x + hitboxH1 / 2.0f)) ||
			((pos2.x - hitboxH2 / 2.0f >= pos1.x - hitboxH1 / 2.0f)
				&& (pos2.x - hitboxH2 / 2.0f <= pos1.x + hitboxH1 / 2.0f)))
		{
			if (((pos2.y + hitboxV2 / 2.0f >= pos1.y - hitboxV1 / 2.0f)
				&& (pos2.y + hitboxV2 / 2.0f <= pos1.y + hitboxV1 / 2.0f)) ||
				((pos2.y - hitboxV2 / 2.0f >= pos1.y - hitboxV1 / 2.0f)
					&& (pos2.y - hitboxV2 / 2.0f <= pos1.y + hitboxV1 / 2.0f)))
			{
				hit = true;
			}
		}

		if (hit)
		{
			//std::cout << "HIT" << std::endl;
			char1->TakeDamage(char2->GetDamagePoint());
			char2->TakeDamage(char1->GetDamagePoint());
		}
		
	}
}

void GSPlay::ProcessSkill(std::shared_ptr<GameCharPlayer> player)
{
	// use skills
	switch (player->GetPlayerChar()) {
	case CHAR_CM:
	{
		// add sound
		if (rand() % 2)
		{
			m_cmSound->load("..\\Data\\Sounds\\cm_skill_1.wav");
		}
		else
		{
			m_cmSound->load("..\\Data\\Sounds\\cm_skill_2.wav");
		}
		Application::gSoloud.play(*m_cmSound, GameManager::GetInstance()->GetSfxVolume());
		int cnt = 0;
		while (cnt++ < PROJECTILE_SKILL_CM_COUNT) {
			SpawnProjectile(player->GetPlayerChar(), PROJECTILE_CM_SKILL,
				Vector2((rand() % (int)(FIELD_RIGHT_BOUND - FIELD_LEFT_BOUND - 100) + FIELD_LEFT_BOUND + 100),
				(rand() % (int)(FIELD_LOWER_BOUND - FIELD_UPPER_BOUND - 50) + FIELD_UPPER_BOUND + 50)));
		}
		break;
	}
	case CHAR_DR:
	{
		// add sound
		if (rand() % 2)
		{
			m_drSound->load("..\\Data\\Sounds\\drow_skill_1.wav");
		}
		else
		{
			m_drSound->load("..\\Data\\Sounds\\drow_skill_2.wav");
		}
		Application::gSoloud.play(*m_drSound, GameManager::GetInstance()->GetSfxVolume());
		break;
	}
	case CHAR_WR:
	{
		// speed up everything?
		if (rand() % 2)
		{
			m_wrSound->load("..\\Data\\Sounds\\wind_skill_1.wav");
		}
		else
		{
			m_wrSound->load("..\\Data\\Sounds\\wind_skill_2.wav");
		}
		Application::gSoloud.play(*m_wrSound, GameManager::GetInstance()->GetSfxVolume());
		break;
	}
	case CHAR_LI:
	{
		// add sound
		if (rand() % 2)
		{
			m_liSound->load("..\\Data\\Sounds\\lina_skill_1.wav");
		}
		else
		{
			m_liSound->load("..\\Data\\Sounds\\lina_skill_2.wav");
		}
		Application::gSoloud.play(*m_liSound, GameManager::GetInstance()->GetSfxVolume());
		SpawnProjectile(player->GetPlayerChar(), PROJECTILE_LINA_SKILL, player->Get2DPosition());
		break;
	}
	}
}

void GSPlay::ProcessSkillSprite(std::shared_ptr<GameCharPlayer> player)
{
	int id = player->GetPlayerId() - 1;
	if (!player->GetPlayerSkillReady()) {
		m_listIcon[id]->SetShaders(ResourceManagers::GetInstance()->GetShader("BlackWhiteShader"));
		m_listCooldownCounter[id]->setText(std::to_string((int)player->GetPlayerSkillTimer()));
	}
	else {
		m_listIcon[id]->SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));
		m_listCooldownCounter[id]->setText("");
	}
	

}

void GSPlay::PlayBackgroundSound()
{
	switch (rand() % 4 + 1) {
	case 1:
		m_BGSound->load("..\\Data\\Sounds\\play_1.mp3");
		break;
	case 2:
		m_BGSound->load("..\\Data\\Sounds\\play_2.mp3");
		break;
	case 3:
		m_BGSound->load("..\\Data\\Sounds\\play_3.mp3");
		break;
	case 4:
		m_BGSound->load("..\\Data\\Sounds\\play_4.mp3");
		break;
	}
	m_BGSound->setLooping(1);
	Application::gSoloud.play(*m_BGSound, GameManager::GetInstance()->GetMusicVolume());
}

void GSPlay::Update(float deltaTime)
{
	// Update the timer(s) in GameManager
	GameManager::GetInstance()->UpdateTimer(deltaTime);

	Gameplay();
	if (*m_waveTransition == TRANSITION_PICK_ITEM) {
		
	}
	else {
		if (*m_waveTransition == TRANSITION_CLEAR_WAVE || *m_waveTransition == TRANSITION_START_WAVE) {
			*m_transitionTimer += deltaTime;
		}
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

	for (auto it : m_listPortrait) {
		it->Draw();
	}
	for (auto it : m_listIcon) {
		it->Draw();
	}

	for (auto it : m_listCooldownCounter) {
		it->Draw();
	}

	for (auto m_projectile : m_listProjectile) {
		m_projectile->Draw();
	}
	for (auto m_enemy : m_listEnemy)
	{
		m_enemy->Draw();
	}
	m_ancient->Draw();
	m_score->Draw();

	if (*m_waveTransition == TRANSITION_CLEAR_WAVE) {
		m_transitionClear->Draw();
	}
	else if (*m_waveTransition == TRANSITION_START_WAVE) {
		m_transitionScore->Draw();
	}
}
