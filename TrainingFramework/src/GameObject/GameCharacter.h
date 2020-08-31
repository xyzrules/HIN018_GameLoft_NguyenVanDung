#pragma once
#include "Sprite2D.h"

enum CHAR_MOVE_DIRECTION {
	CHAR_MOVE_DIRECTION_UP		=	1 << 0,
	CHAR_MOVE_DIRECTION_DOWN	=	1 << 1,
	CHAR_MOVE_DIRECTION_LEFT	=	1 << 2,
	CHAR_MOVE_DIRECTION_RIGHT	=	1 << 3,
};

class GameCharacter :
	public Sprite2D
{
public:
	GameCharacter(std::shared_ptr<Models> model, std::shared_ptr<Shaders> shader, std::shared_ptr<Texture> texture);
	~GameCharacter();


	virtual void SetMoveDirection();
	void SetMoveSpeed(GLint moveSpeed);
	void Update(GLfloat deltaTime);

protected:
	GLint m_moveDirection;
	GLfloat m_moveSpeedVertical, m_moveSpeedHorizontal;
};