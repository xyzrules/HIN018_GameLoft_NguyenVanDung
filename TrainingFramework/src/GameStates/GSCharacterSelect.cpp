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
	GameManager::GetInstance()->PrepareNew();

	auto model = ResourceManagers::GetInstance()->GetModel("Sprite2D");
	auto texture = ResourceManagers::GetInstance()->GetTexture("bg_main_menu");

	//BackGround
	auto shader = ResourceManagers::GetInstance()->GetShader("TextureShader");
	m_BackGround = std::make_shared<Sprite2D>(model, shader, texture);
	m_BackGround->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_BackGround->SetSize(screenWidth, screenHeight);

	//CM
	// fix (button position)
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	std::shared_ptr<GameButton> button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 1 /*Characters_Id::CHAR_CM*/ / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_CM);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//WR
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 2/*Characters_Id::CHAR_WR */ / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_WR);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//DR
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 3/*Characters_Id::CHAR_DR */ / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_DR);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);

	//LI
	texture = ResourceManagers::GetInstance()->GetTexture("button_back");
	button = std::make_shared<GameButton>(model, shader, texture);
	button->Set2DPosition(screenWidth * 4/*Characters_Id::CHAR_LI*/ / 5, 550);
	button->SetSize(200, 100);
	button->SetOnClick([]() {
		GameManager::GetInstance()->ChooseCharacter(Characters_Id::CHAR_LI);
		GameStateMachine::GetInstance()->ChangeState(StateTypes::STATE_Play);
		});
	m_listButton.push_back(button);
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
	for (auto it : m_listButton)
	{
		(it)->HandleTouchEvents(x, y, bIsPressed);
		if ((it)->IsHandle()) break;
	}
}

void GSCharacterSelect::Update(float deltaTime)
{
	m_BackGround->Update(deltaTime);
	for (auto it : m_listButton)
	{
		it->Update(deltaTime);
	}
}

void GSCharacterSelect::Draw()
{
	m_BackGround->Draw();
	for (auto it : m_listButton)
	{
		it->Draw();
	}
}
