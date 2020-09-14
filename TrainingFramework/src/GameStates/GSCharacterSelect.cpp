#include "GSCharacterSelect.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSCharacterSelect::GSCharacterSelect()
{
}

GSCharacterSelect::~GSCharacterSelect()
{
}

void GSCharacterSelect::Init()
{
	Application::gSoloud.stopAll();
	GameManager::GetInstance()->PrepareNewGame();

	m_BGSound = std::make_shared<SoLoud::WavStream>();
	m_BGSound->load("..\\Data\\Sounds\\character_select.mp3");
	Application::gSoloud.play(*m_BGSound, GameManager::GetInstance()->GetMusicVolume());
	m_CharacterSound = std::make_shared<SoLoud::Wav>();
	m_timer = std::make_shared<float>(0);

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// Buttons
	{
		//CM
		texture = ResourceManagers::GetInstance()->GetTexture("button_pick_cm");
		std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth * 1 /*Characters_Id::CHAR_CM*/ / 5, 600);
		button->SetSize(200, 100);
		button->SetOnClick([]() {
			GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_CM);
			});
		m_listButton.push_back(button);

		//WR
		texture = ResourceManagers::GetInstance()->GetTexture("button_pick_wind");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth * 2/*Characters_Id::CHAR_WR */ / 5, 600);
		button->SetSize(200, 100);
		button->SetOnClick([]() {
			GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_WR);
			});
		m_listButton.push_back(button);

		//DR
		texture = ResourceManagers::GetInstance()->GetTexture("button_pick_drow");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth * 3/*Characters_Id::CHAR_DR */ / 5, 600);
		button->SetSize(200, 100);
		button->SetOnClick([]() {
			GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_DR);
			});
		m_listButton.push_back(button);

		//LI
		texture = ResourceManagers::GetInstance()->GetTexture("button_pick_lina");
		button = std::make_shared<GameButton>(model, shader, texture);
		button->Set2DPosition(screenWidth * 4/*Characters_Id::CHAR_LI*/ / 5, 600);
		button->SetSize(200, 100);
		button->SetOnClick([]() {
			GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_LI);
			});
		m_listButton.push_back(button);
	}
	
	// Splash
	{
		texture = ResourceManagers::GetInstance()->GetTexture("splash_character_select");
		m_splashLogo = std::make_shared<Sprite2D>(model, shader, texture);
		m_splashLogo->Set2DPosition(screenWidth /2, 50);
		m_splashLogo->SetSize(800, 100);


		//Splash CM
		shader = ResourceManagers::GetInstance()->GetShader("BlackWhiteShader");
		texture = ResourceManagers::GetInstance()->GetTexture("splash_cm");
		auto m_splash = std::make_shared<Sprite2D>(model, shader, texture);
		m_splash->Set2DPosition(screenWidth * 1/*Characters_Id::CHAR_LI*/ / 5, screenHeight / 2 + 30);
		m_splash->SetSize(256, 580);
		m_listSplash.push_back(m_splash);

		//Splash Wr
		texture = ResourceManagers::GetInstance()->GetTexture("splash_wind");
		m_splash = std::make_shared<Sprite2D>(model, shader, texture);
		m_splash->Set2DPosition(screenWidth * 2/*Characters_Id::CHAR_LI*/ / 5, screenHeight / 2 + 30);
		m_splash->SetSize(256, 580);
		m_listSplash.push_back(m_splash);

		//Splash DR
		texture = ResourceManagers::GetInstance()->GetTexture("splash_drow");
		m_splash = std::make_shared<Sprite2D>(model, shader, texture);
		m_splash->Set2DPosition(screenWidth * 3/*Characters_Id::CHAR_LI*/ / 5, screenHeight / 2 + 30);
		m_splash->SetSize(256, 580);
		m_listSplash.push_back(m_splash);

		//Splash LI
		texture = ResourceManagers::GetInstance()->GetTexture("splash_lina");
		m_splash = std::make_shared<Sprite2D>(model, shader, texture);
		m_splash->Set2DPosition(screenWidth * 4/*Characters_Id::CHAR_LI*/ / 5, screenHeight / 2 + 30);
		m_splash->SetSize(256, 580);
		m_listSplash.push_back(m_splash);
	}

	//Animation
	{
		//Animation CM
		shader = ResourceManagers::GetInstance()->GetShader("AnimationShader");
		texture = ResourceManagers::GetInstance()->GetTexture("sprite_cm");
		auto m_animation = std::make_shared<AnimationSprite>(model, shader, texture, 4, 0.13f);
		m_animation->Set2DPosition(screenWidth * 1/*Characters_Id::CHAR_LI*/ / 5, 350);
		m_animation->SetSize(160, 200);
		m_listAnimation.push_back(m_animation);

		//Animation WR
		texture = ResourceManagers::GetInstance()->GetTexture("sprite_wind");
		m_animation = std::make_shared<AnimationSprite>(model, shader, texture, 4, 0.13f);
		m_animation->Set2DPosition(screenWidth * 2/*Characters_Id::CHAR_LI*/ / 5, 350);
		m_animation->SetSize(160, 200);
		m_listAnimation.push_back(m_animation);

		//Animation DR
		texture = ResourceManagers::GetInstance()->GetTexture("sprite_drow");
		m_animation = std::make_shared<AnimationSprite>(model, shader, texture, 4, 0.13f);
		m_animation->Set2DPosition(screenWidth * 3/*Characters_Id::CHAR_LI*/ / 5, 350);
		m_animation->SetSize(160, 200);
		m_listAnimation.push_back(m_animation);

		//Animation LI
		texture = ResourceManagers::GetInstance()->GetTexture("sprite_lina");
		m_animation = std::make_shared<AnimationSprite>(model, shader, texture, 4, 0.13f);
		m_animation->Set2DPosition(screenWidth * 4/*Characters_Id::CHAR_LI*/ / 5, 350);
		m_animation->SetSize(160, 200);
		m_listAnimation.push_back(m_animation);
	}

}

void GSCharacterSelect::Exit()
{
}

void GSCharacterSelect::Pause()
{
}

void GSCharacterSelect::Resume()
{
}

void GSCharacterSelect::HandleEvents()
{
}

void GSCharacterSelect::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSCharacterSelect::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	if (!GameManager::GetInstance()->IsReady())
	for (int it = 0; it < CHAR_TOTAL - 1; it++)
	{
		m_listButton[it]->HandleTouchEvents(x, y, bIsPressed);
		if (m_listButton[it]->IsHandle())
		{
			switch (it+1) {
			case CHAR_CM: {
				if (rand()%2 == 0)
				m_CharacterSound->load("..\\Data\\Sounds\\cm_cs_1.wav");
				else m_CharacterSound->load("..\\Data\\Sounds\\cm_cs_2.wav");
				break;
			}
			case CHAR_WR: {
				if (rand() % 2 == 0)
					m_CharacterSound->load("..\\Data\\Sounds\\wind_cs_1.wav");
				else m_CharacterSound->load("..\\Data\\Sounds\\wind_cs_2.wav");
				break;
			}
			case CHAR_DR: {
				if (rand() % 2 == 0)
					m_CharacterSound->load("..\\Data\\Sounds\\drow_cs_1.wav");
				else m_CharacterSound->load("..\\Data\\Sounds\\drow_cs_2.wav");
				break;
			}
			case CHAR_LI: {
				if (rand() % 2 == 0)
					m_CharacterSound->load("..\\Data\\Sounds\\lina_cs_1.wav");
				else m_CharacterSound->load("..\\Data\\Sounds\\lina_cs_2.wav");
				break;
			}
			}

			Application::gSoloud.play(*m_CharacterSound, GameManager::GetInstance()->GetSfxVolume());
			m_listButton[it]->SetSize(0, 0);
			m_listAnimation[it]->SetSize(0, 0);
			m_listSplash[it]->SetShaders(ResourceManagers::GetInstance()->GetShader("TextureShader"));

			break;
		}
	}
}

void GSCharacterSelect::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
	for (auto it : m_listAnimation) {
		it->Update(deltaTime);
	}
	if (GameManager::GetInstance()->IsReady()) {
		*m_timer += deltaTime;
		if (*m_timer > CHARACTER_SELECT_DELAY) {
			*m_timer = 0;
			m_BGSound->stop();
			GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		}
		
	}
}

void GSCharacterSelect::Draw()
{
	m_BackGround->Draw();
	m_splashLogo->Draw();
	for (auto it : m_listSplash)
	{
		it->Draw();
	}
	for (auto it : m_listAnimation) {
		it->Draw();
	}
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
