#include <cstdlib>

#include <glew/include/GL/glew.h>

#include "CEnemyManager.h"

CEnemyManager::CEnemyManager() {
	_enemyType = 0;
	_enemyColor = 0;
	_randomX = 0.0f;
}

CEnemyManager::~CEnemyManager() {

}

void CEnemyManager::instantiate(GLuint shaderProg) { // �@���B�z�@��
	_enemyType = rand() % 3; // �q�T�ؼĤH�̿�@�إͦ�
	_enemyColor = rand() % 3; // �H����ܤ@�ئ�t
	if (_enemyType == 0) _enemyList.push_back(new CEnemy1(_enemyColor));
	else if (_enemyType == 1) _enemyList.push_back(new CEnemy2(_enemyColor));
	else if (_enemyType == 2) _enemyList.push_back(new CEnemy3(_enemyColor));

	// �]�w�ĤH���򥻸��
	CShape* currentEnemy = _enemyList.back();
	currentEnemy->setupVertexAttributes();
	currentEnemy->setShaderID(shaderProg);

	// �]�w��l��m�]�q�ù��W�褧�~�H�����w X �b�y�С^
	_randomX = -3.0f + (float)rand() / RAND_MAX * 6.0f;
	currentEnemy->setPos(glm::vec3(_randomX, 8.5f, 0.0f));
}