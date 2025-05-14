#pragma once
#include "CShape.h"

// �w�q�ƹ����O�A�@�����a����԰���
class CPlayer : public CShape
{
public:
	CPlayer();
	virtual ~CPlayer();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
	virtual void onCollision(CShape* other) override;

private:
	bool _isHit, _isFlashing; // �O�_�Q�ĤH�Ψ�l�u����
	float _timer;
};