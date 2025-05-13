#include <glew/include/GL/glew.h>

#include "CDeathEffectManager.h"

// 初始化靜態成員變數
list<CDeathEffect*> CDeathEffectManager::_effectList;

void CDeathEffectManager::createEffect(GLuint shaderProg, glm::vec3 pos) {
    CDeathEffect* effect = new CDeathEffect(shaderProg, pos);
    _effectList.push_back(effect);
}


void CDeathEffectManager::draw() { // 一次處理全部
    for (CDeathEffect* effect : _effectList) {
        effect->draw();
    }
}

void CDeathEffectManager::update(float dt) { // 一次處理全部
    for (CDeathEffect* effect : _effectList) {
        effect->update(dt);
    }
}

void CDeathEffectManager::handleInActive(){
	for (auto it = _effectList.begin(); it != _effectList.end(); ) {
		CDeathEffect* effect = *it;

		if (effect->getIsActive()) {
			++it; // 沒刪，就正常前進
		}
		else {
			delete effect;
			effect = nullptr;
			it = _effectList.erase(it); // 刪掉並前進
		}
	}
}