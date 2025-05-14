#pragma once
#include "CShape.h"

// �w�q�������O�A����ĤH���u��
class CAttack : public CShape
{
public:
	CAttack(float rds = 0.1f);
	virtual ~CAttack();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override; // �D�n�O����u��������
	void updateDirection() {
		_direction = glm::normalize(_targetMove - _pos);
	}
	void setSpeed(float speed = 3.0f) {
		_speed = speed; // �w�]�񪱮a���l�u�C�@��
	}
	void setWaitingStatus(int status) {
		_waitingStatus = status;
	}
	int getWaitingStatus() {
		return _waitingStatus;
	}
	virtual void onCollision(CShape* other) override;

private:
	const float _segment = 20.0f; // �� 20 ��ΨӼ������
	float _radius; // �b�|
	
	glm::vec3 _direction; // �u���Q�o�g�ɪ����ʤ�V

	float _speed; // �l�u�����ʳt��

	int _waitingStatus; // �u���O�_���b���ݧ����G0-��l�ȡB1-���ݤ��B2-�����ݡ]�w�o�g�^
	float _waitingTimer; // �]���p�ɡ^
};