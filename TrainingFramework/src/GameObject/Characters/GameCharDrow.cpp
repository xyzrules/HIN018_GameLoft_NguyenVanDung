#include "GameCharDrow.h"

GameCharDrow::GameCharDrow(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId)
	: GameCharPlayer(model, shader, texture, numFrames, frameTime, playerId)
{
	m_spriteName = "sprite_drow";
	m_playerChar = CHAR_DR;
}

GameCharDrow::~GameCharDrow()
{
}

void GameCharDrow::ActivateSkill()
{
	m_playerSkillReady = false;
	m_playerSkillEnded = false;
	m_playerSkillActivated = true;
	m_playerSkillTimer = SKILL_COOLDOWN_DROW;
	m_playerSkillDurationTimer = SKILL_DURATION_DROW;
}
