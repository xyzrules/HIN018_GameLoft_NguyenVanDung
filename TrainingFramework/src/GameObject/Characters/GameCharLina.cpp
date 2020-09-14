#include "GameCharLina.h"

GameCharLina::GameCharLina(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId)
	: GameCharPlayer(model, shader, texture, numFrames, frameTime, playerId)
{
	m_spriteName = "sprite_lina";
	m_playerChar = CHAR_LI;
}

GameCharLina::~GameCharLina()
{
	
}

void GameCharLina::ActivateSkill()
{
	m_playerSkillReady = false;
	m_playerSkillActivated = true;
	m_playerSkillTimer = SKILL_COOLDOWN_LINA;
}
