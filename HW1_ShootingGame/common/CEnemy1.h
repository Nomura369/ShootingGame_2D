#pragma once

#include "CShape.h"
#include "CAttack.h"

// �w�q�ĤH���O(1)
class CEnemy1 : public CShape
{
public:
	CEnemy1(int colorType = 0);
	virtual ~CEnemy1();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	glm::vec3 _hexColor; // �����C��
	glm::vec3 _triColor; // �}�[�C��
	glm::vec3 _winColor; // �׭������C��
	bool _isAttacking;
	float _attackTimer; // �]���p�ɡ^
	float _attackIntervalTime;
};