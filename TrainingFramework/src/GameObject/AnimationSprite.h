#pragma once
#include "Sprite2D.h"

class AnimationSprite :
	public Sprite2D
{
public:
	AnimationSprite();
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime);
	AnimationSprite(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture, int numFrames, float frameTime, float loopPoint);
	~AnimationSprite();

	void Init();
	void Draw();
	void Update(GLfloat deltaTime);

protected:
	float m_numFrames;
	float m_frameTime;
	float m_currentFrame;
	float m_currentTime;
	float m_loopPoint;
};