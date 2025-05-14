#pragma once

#include "CShape.h"
#include "CAttack.h"

// �w�q�Y�����O
class CBoss : public CShape
{
public:
	CBoss();
	virtual ~CBoss();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
	// virtual bool checkCollision(CShape* other) override;
	virtual void onCollision(CShape* other) override;
	int getAttackMode() { return _attackMode; }
	void setAttackMode(int attackMode) { _attackMode = attackMode; }

private:
	glm::vec3 _hexColor; // �����C��
	glm::vec3 _triColor; // �}�[�C��
	glm::vec3 _winColor; // �׭������C��
	bool _isAttacking;
	float _attackTimer; // �]���p�ɡ^
	float _attackIntervalTime;
	int _attackMode;
};