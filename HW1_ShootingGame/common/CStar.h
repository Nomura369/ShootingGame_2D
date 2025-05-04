#pragma once
#include "CShape.h"

// 定義星星類別，作為背景裝飾，營造遊戲的速度感（正在想怎麼實現）
class CStar : public CShape
{
public:
	CStar();
	virtual ~CStar();
	void setRandomPos();
	void setRandomScale();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
};
