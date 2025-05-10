#pragma once
#include <list>
using namespace std;

#include "CAttack.h"

// �w�q�����޲z�����O�A�ϥ��R�A�������޼ĤH���l�u
class CAttackManager
{
public:
	static void draw();
	static void addAttack1(GLuint shaderProg, glm::vec3 pos); // ���� _attackList1
	static void addAttack2(GLuint shaderProg, glm::vec3 pos); // ���� _attackList2
	static void addAttack3(GLuint shaderProg, glm::vec3 pos); // ���� _attackList3
	static void update(float dt);
	static void setTargetMove(int index, glm::vec3 targetMove) {
		_targetMove[index] = targetMove;
	}

private:
	CAttackManager(); // �קK�Ыع���
	static list<CAttack*> _attackList1; // �� CEnemy1 �ϥ�
	static list<CAttack*> _attackList2; // �� CEnemy2 �ϥ�
	static list<CAttack*> _attackList3; // �� CEnemy3 �ϥ�
	static glm::vec3 _targetMove[3]; // �O���T�ؼĤH�������ؼ�
};