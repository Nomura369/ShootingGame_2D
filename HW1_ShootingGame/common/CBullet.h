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
	virtual void update(float dt) override;
	bool fly(float dt); // ����l�u�����ʡA�æ^�Ǥl�u�O�_�٦b������
	bool _isInWindow;
};