#include "GameCharDrow.h"

GameCharDrow::GameCharDrow(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime)
	: GameCharPlayer(model, shader, texture, numFrames, frameTime)
{
	m_spriteName = "sprite_drow";
	m_playerChar = CHAR_DR;
}

GameCharDrow::~GameCharDrow()
{
}
