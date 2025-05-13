#pragma once
#include <list>
using namespace std;

#include "CShape.h"
#include "CAttack.h"

// 定義敵人類別(3)
class CEnemy3 : public CShape
{
public:
	CEnemy3(int colorType = 0);
	virtual ~CEnemy3();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
	// virtual bool checkCollision(CShape* other) override;
	virtual void onCollision(CShape* other) override;

private:
	glm::vec3 _bodyColor; // 機身顏色
	glm::vec3 _midColor; // 中間色
	glm::vec3 _wingColor; // 機翼和尾部顏色
	bool _isAttacking;
	float _attackTimer;
	float _attackIntervalTime;
	list<CAttack*> _attackList;
	float _originX;
	bool _isOriginX;
};