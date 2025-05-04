#pragma once
#include "CShape.h"

// 定義漸層類別，在背景中模擬漸層效果
class CGradient : public CShape
{
public:
	CGradient();
	virtual ~CGradient();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
};