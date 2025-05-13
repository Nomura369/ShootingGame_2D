#pragma once
#include "CShape.h"

class CTriangle : public CShape
{
public:
	CTriangle();
	virtual ~CTriangle();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
};