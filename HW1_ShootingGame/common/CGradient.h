#pragma once
#include "CShape.h"

// �w�q���h���O�A�b�I�����������h�ĪG
class CGradient : public CShape
{
public:
	CGradient();
	virtual ~CGradient();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;
};