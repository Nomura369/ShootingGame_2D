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

private:
	const float _segment = 20.0f; // �� 20 ��ΨӼ������
	float _radius; // �b�|

	// �u���Q�o�g�ɪ����ʤ�V
	glm::vec3 _direction ;
};