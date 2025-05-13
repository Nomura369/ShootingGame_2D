#pragma once
#include <list>
using namespace std;

#include "CEnemy1.h"
#include "CEnemy2.h"
#include "CEnemy3.h"

// �w�q�ĤH�޲z�����O�]Singleton pattern�^
class CEnemyManager
{
private:
	static CEnemyManager* instance;
	CEnemyManager();

	list<CShape*> _enemyList; // �]�~�ӯu�O�@�󯫩_���ơ^
	int _enemyType;
	int _enemyColor;
	float _randomX;
	
public:
	// �T�O�~�����o�ƻs�����O�����
	CEnemyManager(CEnemyManager& other) = delete;
	void operator = (const CEnemyManager&) = delete;

	// ��������O���ߤ@��Ҫ��R�A���
	static CEnemyManager* getInstance() {
		if (instance == nullptr) { // �p�G�٨S����ҴN�Ыؤ@��
			instance = new CEnemyManager();
		}
		return instance;
	}
	void instantiate(GLuint shaderProg, glm::vec3 playerMove); // �ͦ��ó]�w�ĤH
	void draw();
	void update(float dt);
	void handleDeath(); // �@���B�z _isActive == false ���l�u
	~CEnemyManager();

};