#include "GameCharCM.h"

GameCharCM::GameCharCM(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId)
	:GameCharPlayer(model, shader, texture, numFrames, frameTime, playerId) 
{
	m_spriteName = "sprite_cm";
	m_playerChar = CHAR_CM;
}

GameCharCM::~GameCharCM()
{
}

void GameCharCM::ActivateSkill()
{
	m_playerSkillReady = false;
	m_playerSkillActivated = true;
	m_playerSkillTimer = SKILL_COOLDOWN_CM;
}

