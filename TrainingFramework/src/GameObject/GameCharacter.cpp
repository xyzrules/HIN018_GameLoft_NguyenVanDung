#include "GameCharacter.h"

GameCharacter::GameCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture)
	: Sprite2D(model, shader, texture)
{
	m_moveDirection = 0;
	m_moveSpeedVertical = 100.0;
	m_moveSpeedHorizontal = 200.0;
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::SetMoveSpeed(GLint moveSpeed)
{
}

void GameCharacter::SetMoveDirection()
{
}

void GameCharacter::Update(GLfloat deltaTime)
{
}
