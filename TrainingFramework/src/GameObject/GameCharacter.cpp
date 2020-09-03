#include "GameCharacter.h"

GameCharacter::GameCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: AnimationSprite (model, shader, texture, numFrames, frameTime), m_moveSpeedVertical(100.0), m_moveSpeedHorizontal(200.0), m_moveDirection(0), m_charFacingRight(true)
{
}

GameCharacter::GameCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, GLfloat moveSpeedVertical, GLfloat moveSpeedHorizontal)
	: AnimationSprite(model, shader, texture, numFrames, frameTime), m_moveSpeedVertical(moveSpeedVertical), m_moveSpeedHorizontal(moveSpeedHorizontal), m_moveDirection(0), m_charFacingRight(true)
{
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

bool GameCharacter::GetCharacterFacingRight()
{
	return m_charFacingRight;
}
