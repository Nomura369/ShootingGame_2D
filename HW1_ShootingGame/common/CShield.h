#pragma once
#include "CShape.h"

// �w�q�@�����O�A�@�����a�԰��������m�˸m
class CShield : public CShape
{
public:
	CShield(float rds = 1.0f);
	virtual ~CShield();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	const float _segment = 20.0f; // �� 20 ��ΨӼ������
	float _radius; // �b�|
};