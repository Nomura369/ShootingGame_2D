#pragma once

#include "CShape.h"
#include "CAttack.h"

// 定義頭目類別
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
	glm::vec3 _hexColor; // 機身顏色
	glm::vec3 _triColor; // 腳架顏色
	glm::vec3 _winColor; // 擋風玻璃顏色
	bool _isAttacking;
	float _attackTimer; // （正計時）
	float _attackIntervalTime;
	int _attackMode;
};