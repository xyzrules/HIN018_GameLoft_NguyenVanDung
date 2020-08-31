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
	m_timer = std::make_shared<float>(0);
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
	texture = ResourceManagers::GetInstance()->GetTexture("Rock");
	m_player = std::make_shared<GameCharPlayer>(model, shader, texture);
	m_player->Set2DPosition(screenWidth / 2, screenHeight / 2);
	m_player->SetSize(100, 200);

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
	if (key == KEY_BACK) {

	}
	else if (key == KEY_MOVE_BACKWARD
			|| key == KEY_MOVE_FORWARD
			|| key == KEY_MOVE_LEFT
			|| key == KEY_MOVE_RIGHT) {
		m_player->HandleKeyEvent(key, bIsPressed);
	}
}

void GSPlay::HandleTouchEvents(int x, int y, bool bIsPressed)
{
}

void GSPlay::Update(float deltaTime)
{
	m_player->Update(deltaTime);
	*m_timer += deltaTime;
}

void GSPlay::Draw()
{
	m_BackGround->Draw();
	m_player->Draw();
	m_score->Draw();
}

void GSPlay::SetNewPostionForBullet()
{
}