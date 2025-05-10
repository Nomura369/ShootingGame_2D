#pragma once
#include <list>
using namespace std;

#include "CShape.h"
#include "CAttack.h"

// �w�q�ĤH���O(2)
class CEnemy2 : public CShape
{
public:
	CEnemy2(int colorType = 0);
	virtual ~CEnemy2();
	virtual void draw() override;
	virtual void reset() override;
	virtual void update(float dt) override;

private:
	glm::vec3 _bodyColor; // �����C��
	glm::vec3 _midColor; // ������
	glm::vec3 _wingColor; // ���l�M�����C��
	bool _isAttacking;
	float _insTimer; // �ͦ��l�u�p�ɾ�
	float _insIntervalTime; // �ͦ��l�u���ɶ����j
	float _attackTimer; // �l�u�i������p�ɾ�
	float _attackIntervalTime; // �l�u���������j
	list<CAttack*> _attackList;
};