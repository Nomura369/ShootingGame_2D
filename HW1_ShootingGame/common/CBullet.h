#pragma once
#include "CShape.h"

// �w�q�l�u���O�A�@�����a��������q
class CBullet : public CShape
{
public:
	CBullet();
	glm::vec3 getPos();
	virtual ~CBullet();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override; // �D�n�Ψӱ���l�u������
	/*virtual bool checkCollision(CShape* other) override;*/
	virtual void onCollision(CShape* other) override;
};