#pragma once
#include <list>
using namespace std;

#include "CShape.h"
#include "CAttack.h"

// �w�q�ĤH���O(2)
class CEnemy2 : public CShape
{
public:
	CEnemy2(int colorType = 0);
	virtual ~CEnemy2();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	glm::vec3 _bodyColor; // �����C��
	glm::vec3 _midColor; // ������
	glm::vec3 _wingColor; // ���l�M�����C��
	bool _isAttacking;
	float _attackTimer; // �]���p�ɡ^
	float _attackIntervalTime; // �l�u���������j
};