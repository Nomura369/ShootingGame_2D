#pragma once
#include "CShape.h"

// 定義護盾類別，作為玩家戰鬥機的防禦裝置
class CShield : public CShape
{
public:
	CShield(float rds = 1.0f);
	virtual ~CShield();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	const float _segment = 20.0f; // 用 20 邊形來模擬圓形
	float _radius; // 半徑
};