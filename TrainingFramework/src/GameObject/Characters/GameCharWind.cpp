#include "GameCharWind.h"

GameCharWind::GameCharWind(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, int playerId)
	: GameCharPlayer(model, shader, texture, numFrames, frameTime, playerId)
{
	m_spriteName = "sprite_wind";
	m_playerChar = CHAR_WR;
}

GameCharWind::~GameCharWind()
{
}


void GameCharWind::ActivateSkill()
{
	m_playerSkillReady = false;
	m_playerSkillEnded = false;
	m_playerSkillActivated = true;
	m_playerSkillTimer = SKILL_COOLDOWN_WIND;
	m_playerSkillDurationTimer = SKILL_DURATION_WIND;
	m_playerAttackSpeedMultiplyer *= SKILL_WIND_ATTACK_SPEED_MULTIPLYER;
	m_playerMovementSpeedMultiplyer *= SKILL_WIND_MOVEMENT_SPEED_MULTIPLYER;
}
