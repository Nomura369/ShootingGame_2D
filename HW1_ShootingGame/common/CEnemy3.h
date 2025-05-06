#pragma once
#include "CShape.h"

// �w�q�ĤH���O(3)
class CEnemy3 : public CShape
{
public:
	CEnemy3(int colorType = 0);
	virtual ~CEnemy3();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	glm::vec3 _bodyColor; // �����C��
	glm::vec3 _midColor; // ������
	glm::vec3 _wingColor; // ���l�M�����C��
	//bool _isAttacking;
};