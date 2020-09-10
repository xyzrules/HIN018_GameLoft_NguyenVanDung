#include "GameCharCM.h"

GameCharCM::GameCharCM(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	:GameCharPlayer(model, shader, texture, numFrames, frameTime) 
{
	m_spriteName = "sprite_cm";
	m_playerChar = CHAR_CM;
}

GameCharCM::~GameCharCM()
{
}
