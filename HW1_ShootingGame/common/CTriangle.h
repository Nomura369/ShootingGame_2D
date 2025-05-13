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
	void setVelocity(glm::vec3 v) {
		_velocity = v;
	}

private:
	glm::vec3 _velocity;
	float _timer;
	glm::vec3 _startColor;
	glm::vec3 _endColor;
};