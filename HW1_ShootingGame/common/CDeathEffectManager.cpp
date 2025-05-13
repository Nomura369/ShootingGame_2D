#include <glew/include/GL/glew.h>

#include "CDeathEffectManager.h"

// ��l���R�A�����ܼ�
list<CDeathEffect*> CDeathEffectManager::_effectList;

void CDeathEffectManager::createEffect(GLuint shaderProg, glm::vec3 pos) {
    CDeathEffect* effect = new CDeathEffect(shaderProg, pos);
    _effectList.push_back(effect);
}


void CDeathEffectManager::draw() { // �@���B�z����
    for (CDeathEffect* effect : _effectList) {
        effect->draw();
    }
}

void CDeathEffectManager::update(float dt) { // �@���B�z����
    for (CDeathEffect* effect : _effectList) {
        effect->update(dt);
    }
}

void CDeathEffectManager::handleInActive(){
	for (auto it = _effectList.begin(); it != _effectList.end(); ) {
		CDeathEffect* effect = *it;

		if (effect->getIsActive()) {
			++it; // �S�R�A�N���`�e�i
		}
		else {
			delete effect;
			effect = nullptr;
			it = _effectList.erase(it); // �R���ëe�i
		}
	}
}