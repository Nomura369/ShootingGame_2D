#pragma once

#include "CShape.h"
#include "CAttack.h"

// 定義敵人類別(1)
class CEnemy1 : public CShape
{
public:
	CEnemy1(int colorType = 0);
	virtual ~CEnemy1();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	glm::vec3 _hexColor; // 機身顏色
	glm::vec3 _triColor; // 腳架顏色
	glm::vec3 _winColor; // 擋風玻璃顏色
	bool _isAttacking;
	float _attackTimer; // （正計時）
	float _attackIntervalTime;
};