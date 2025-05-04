#pragma once
#include "CShape.h"

// �w�q�P�P���O�A�@���I���˹��A��y�C�����t�׷P�]���b�Q����{�^
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
