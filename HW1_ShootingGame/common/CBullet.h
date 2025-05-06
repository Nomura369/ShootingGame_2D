#pragma once
#include "CShape.h"

// 定義子彈類別，作為玩家的攻擊手段
class CBullet : public CShape
{
public:
	CBullet();
	glm::vec3 getPos();
	virtual ~CBullet();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
	bool fly(float dt); // 控制子彈的移動，並回傳子彈是否還在視窗內
	bool _isInWindow;
};