#pragma once
#include "CShape.h"

// 定義滑鼠類別，作為玩家控制的戰鬥機
class CPlayer : public CShape
{
public:
	CPlayer();
	virtual ~CPlayer();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
	virtual void onCollision(CShape* other) override;

private:
	bool _isHit, _isFlashing; // 是否被敵人或其子彈打中
	float _timer;
};