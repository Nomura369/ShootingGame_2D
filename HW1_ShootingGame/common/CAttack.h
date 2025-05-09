#pragma once
#include "CShape.h"

// 定義攻擊類別，控制敵人的彈幕
class CAttack : public CShape
{
public:
	CAttack(float rds = 0.15f);
	// glm::vec3 getPos();
	virtual ~CAttack();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override; // 主要是控制彈幕的移動
	//bool getIsInWindow();
	void setTargetMove(glm::vec3 targetMove) {
		_targetMove = targetMove;
		_direction = glm::normalize(_targetMove - _pos);
	}
	

private:
	const float _segment = 20.0f; // 用 20 邊形來模擬圓形
	float _radius; // 半徑

	//bool _isInWindow; // 記錄子彈是否還在視窗內

	// 彈幕被發射時的移動方向
	glm::vec3 _targetMove;
	glm::vec3 _direction ;
};