#include <cstdlib>

#include <glew/include/GL/glew.h>

#include "CEnemyManager.h"
#include "CGrid.h"

CEnemyManager::CEnemyManager() {
	_enemyType = 0;
	_enemyColor = 0;
	_randomX = 0.0f;
}

CEnemyManager::~CEnemyManager() {
	for (CShape* ene : _enemyList) {
		delete ene;
	}
	_enemyList.clear();
}

void CEnemyManager::instantiate(GLuint shaderProg, glm::vec3 playerMove) { // �@���B�z�@��
	_enemyType = rand() % 3; // �q�T�ؼĤH�̿�@�إͦ�
	_enemyColor = rand() % 3; // �H����ܤ@�ئ�t
	if (_enemyType == 0) _enemyList.push_back(new CEnemy1(_enemyColor));
	else if (_enemyType == 1) _enemyList.push_back(new CEnemy2(_enemyColor));
	else if (_enemyType == 2) _enemyList.push_back(new CEnemy3(_enemyColor));

	// �]�w�ĤH���򥻸��
	CShape* currentEnemy = _enemyList.back();
	currentEnemy->setupVertexAttributes();
	currentEnemy->setShaderID(shaderProg);
	if (_enemyType > 0) currentEnemy->setRotZ(180.0f);

	// �]�w��l��m�]�q�ù��W�褧�~�H�����w X �b�y�С^
	_randomX = -2.5f + (float)rand() / RAND_MAX * 5.0f;
	currentEnemy->setPos(glm::vec3(_randomX, 4.0f, 0.0f));

	// �]�w�ĤH�������ؼС]�w�]�����a�^
	currentEnemy->setTargetMove(playerMove);
}

void CEnemyManager::draw() { // �@���B�z����
	for (CShape* ene : _enemyList) {
		ene->draw();
	}
}

void CEnemyManager::update(float dt) { // �@���B�z����
	for (auto it = _enemyList.begin(); it != _enemyList.end(); ) {
		CShape* ene = *it;
		ene->update(dt);

		if (ene->getIsInWindow() && ene->getIsAlive()) {
			++it; // �S�R�A�N���`�e�i
		}
		else {
			delete ene;
			it = _enemyList.erase(it); // �R���ëe�i
		}
	}
}