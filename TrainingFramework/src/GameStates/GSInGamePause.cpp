#include "GSInGamePause.h"

extern int screenWidth; //need get on Graphic engine
extern int screenHeight; //need get on Graphic engine

GSInGamePause::GSInGamePause()
{
}

GSInGamePause::~GSInGamePause()
{
}

void GSInGamePause::Init()
{
	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	// splash
	texture = ResourceManagers::GetInstance()->GetTexture("splash_pause");
	
	m_splashPause = std::make_shared<Sprite2D>(model, shader, texture);
	m_splashPause->Set2DPosition(screenWidth / 2, screenHeight / 3);
	m_splashPause->SetSize(600, 300);

	//quit button
	// fix
	texture = ResourceManagers::GetInstance()->GetTexture("button_give_up");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 3 / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Menu);
		});
	m_listButton.push_back(button);

	//resume button
	texture = ResourceManagers::GetInstance()->GetTexture("button_resume");button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 2 / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameStateMachine::GetInstance()->PopState();
		});
	m_listButton.push_back(button);
}

void GSInGamePause::Exit()
{
}

void GSInGamePause::Pause()
{
}

void GSInGamePause::Resume()
{
}

void GSInGamePause::HandleEvents()
{
}

void GSInGamePause::HandleKeyEvents(int key, bool bIsPressed)
{
}

void GSInGamePause::HandleTouchEvents(int x, int y, bool bIsPressed)
{
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSInGamePause::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSInGamePause::Draw()
{
	m_BackGround->Draw();
	m_splashPause->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
