#include "GameCharacter.h"

GameCharacter::GameCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: AnimationSprite(model, shader, texture, numFrames, frameTime), m_characterAlive(true)
{
	SetSize(PLAYER_HORIZONTAL_SIZE, PLAYER_VERTICAL_SIZE);
}

GameCharacter::~GameCharacter()
{
}

void GameCharacter::SetMoveDirection()
{
}

GLfloat GameCharacter::GetHitboxVertical()
{
	return m_hitboxVertical;
}

GLfloat GameCharacter::GetHitboxHorizontal()
{
	return m_hitboxHorizontal;
}

void GameCharacter::Update(GLfloat deltaTime)
{
}

void GameCharacter::TakeDamage(GLfloat damage)
{
	m_healthPoints -= damage;
	if (m_healthPoints < 0.1) {
		m_characterAlive = false;
	}
}

GLfloat GameCharacter::GetDamagePoint()
{
	return m_damagePoints;
}

bool GameCharacter::GetCharacterAlive()
{
	return m_characterAlive;
}

std::string GameCharacter::GetSprite()
{
	return m_spriteName;
}
