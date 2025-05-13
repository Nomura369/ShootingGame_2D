#include <cstdlib>

#include <glew/include/GL/glew.h>

#include "CEnemyManager.h"
#include "CGrid.h"
#include "CDeathEffectManager.h"

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

void CEnemyManager::instantiate(GLuint shaderProg, glm::vec3 playerMove) { // 一次處理一個
	_enemyType = rand() % 3; // 從三種敵人裡選一種生成
	_enemyColor = rand() % 3; // 隨機選擇一種色系
	if (_enemyType == 0) _enemyList.push_back(new CEnemy1(_enemyColor));
	else if (_enemyType == 1) _enemyList.push_back(new CEnemy2(_enemyColor));
	else if (_enemyType == 2) _enemyList.push_back(new CEnemy3(_enemyColor));

	// 設定敵人的基本資料
	CShape* currentEnemy = _enemyList.back();
	currentEnemy->setupVertexAttributes();
	currentEnemy->setShaderID(shaderProg);
	if (_enemyType > 0) currentEnemy->setRotZ(180.0f);

	// 設定初始位置（從螢幕上方之外隨機指定 X 軸座標）
	_randomX = -2.5f + (float)rand() / RAND_MAX * 5.0f;
	currentEnemy->setPos(glm::vec3(_randomX, 4.0f, 0.0f));

	// 設定敵人的攻擊目標（預設為玩家）
	currentEnemy->setTargetMove(playerMove);
}

void CEnemyManager::draw() { // 一次處理全部
	for (CShape* ene : _enemyList) {
		ene->draw();
	}
}

void CEnemyManager::update(float dt) { // 一次處理全部
	for (auto ene : _enemyList) {
		ene->update(dt);
	}
}

void CEnemyManager::handleDeath() { // 一次處理全部
	for (auto it = _enemyList.begin(); it != _enemyList.end(); ) {
		CShape* ene = *it;

		if (ene->getIsActive()) {
			++it; // 沒刪，就正常前進
		}
		else {
			CDeathEffectManager::createEffect(ene->getShaderProgram(), ene->getPos()); // 播放死亡特效
			delete ene;
			ene = nullptr;
			it = _enemyList.erase(it); // 刪掉並前進
		}
	}
}