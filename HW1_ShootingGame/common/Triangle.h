#pragma once
#include "CShape.h"

class Triangle : public CShape
{
public:
	Triangle();
	virtual ~Triangle();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
};