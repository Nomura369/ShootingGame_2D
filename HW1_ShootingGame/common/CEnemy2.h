#pragma once
#include "CShape.h"

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
};