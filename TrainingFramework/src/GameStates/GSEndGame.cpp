#include "GSEndGame.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSEndGame::GSEndGame()
{
}

GSEndGame::~GSEndGame()
{
	m_BGSound->stop();
}

void GSEndGame::Init()
{
	Application::gSoloud.stopAll();
	m_BGSound = std::make_shared<SoLoud::WavStream>();
	m_BGSound->load("..\\Data\\Sounds\\game_over.mp3");
	Application::gSoloud.play(*m_BGSound, GameManager::GetInstance()->GetMusicVolume());

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// splash
	
	texture = ResourceManagers::GetInstance()->GetTexture("splash_game_over");
	m_splashEndgame = std::make_shared<Sprite2D>(model, shader, texture);
	m_splashEndgame->Set2DPosition(screenWidth / 2, screenHeight / 3);
	m_splashEndgame->SetSize(600, 300);
	
	shader = ResourceManagers::GetInstance()->GetShader("TextShader");
	std::shared_ptr<Font> font = ResourceManagers::GetInstance()->GetFont("lemonadestand");
	std::string m_scoreText = "YOUR SCORE: " + std::to_string(((int)(GameManager::GetInstance()->GetScore())));
	m_score = std::make_shared<Text>(shader, font, m_scoreText, TEXT_COLOR::RED, 2.0);
	m_score->Set2DPosition(screenWidth / 2 - 100, 400);
	
	//quit button
	shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	texture = ResourceManagers::GetInstance()->GetTexture("button_give_up");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 3 / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//replay button
	// fix
	texture = ResourceManagers::GetInstance()->GetTexture("button_retry");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 2 / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_CharacterSelect);
		});
	m_listButton.push_back(button);
}

void GSEndGame::Exit()
{
}

void GSEndGame::Pause()
{
}

void GSEndGame::Resume()
{
}

void GSEndGame::HandleEvents()
{
}

void GSEndGame::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSEndGame::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSEndGame::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	//m_splashEndgame->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSEndGame::Draw()
{
	m_BackGround->Draw();
	m_splashEndgame->Draw();
	m_score->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
