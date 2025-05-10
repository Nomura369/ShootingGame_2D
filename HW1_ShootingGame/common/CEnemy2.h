#pragma once
#include <list>
using namespace std;

#include "CShape.h"
#include "CAttack.h"

// 定義敵人類別(2)
class CEnemy2 : public CShape
{
public:
	CEnemy2(int colorType = 0);
	virtual ~CEnemy2();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	glm::vec3 _bodyColor; // 機身顏色
	glm::vec3 _midColor; // 中間色
	glm::vec3 _wingColor; // 機翼和尾部顏色
	bool _isAttacking;
	float _attackTimer; // （正計時）
	float _attackIntervalTime; // 子彈攻擊的間隔
};