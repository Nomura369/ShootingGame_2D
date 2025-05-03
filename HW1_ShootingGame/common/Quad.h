#pragma once
#include "CShape.h"

class Quad : public CShape
{
public:
	Quad();
	virtual ~Quad();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
};