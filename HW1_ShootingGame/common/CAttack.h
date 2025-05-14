#pragma once
#include "CShape.h"

// 定義攻擊類別，控制敵人的彈幕
class CAttack : public CShape
{
public:
	CAttack(float rds = 0.1f);
	virtual ~CAttack();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override; // 主要是控制彈幕的移動
	void updateDirection() {
		_direction = glm::normalize(_targetMove - _pos);
	}
	void setSpeed(float speed = 3.0f) {
		_speed = speed; // 預設比玩家的子彈慢一些
	}
	void setWaitingStatus(int status) {
		_waitingStatus = status;
	}
	int getWaitingStatus() {
		return _waitingStatus;
	}
	virtual void onCollision(CShape* other) override;

private:
	const float _segment = 20.0f; // 用 20 邊形來模擬圓形
	float _radius; // 半徑
	
	glm::vec3 _direction; // 彈幕被發射時的移動方向

	float _speed; // 子彈的移動速度

	int _waitingStatus; // 彈幕是否正在等待攻擊：0-初始值、1-等待中、2-未等待（已發射）
	float _waitingTimer; // （正計時）
};