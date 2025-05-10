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
	float _insTimer; // 生成子彈計時器
	float _insIntervalTime; // 生成子彈的時間間隔
	float _attackTimer; // 子彈進行攻擊計時器
	float _attackIntervalTime; // 子彈攻擊的間隔
	list<CAttack*> _attackList;
};