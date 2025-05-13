#include <cstdlib>

#include "CDeathEffect.h"

#define NUM 8 // 三角形數量和方位數量相同

CDeathEffect::CDeathEffect(GLuint shaderProg, glm::vec3 pos) {
	_isActive = true;

	for (int i = 0; i < NUM; i++) {
		CTriangle* triangle = new CTriangle;
		_triangleList.push_back(triangle);
		triangle->setupVertexAttributes();
		triangle->setShaderID(shaderProg);
		triangle->setPos(pos);

		_randomSpeed = (float)(rand() % 3) + 1.0f; // 1.0f ~ 3.0f
		glm::vec3 velocity = glm::normalize(_directions[i]) * _randomSpeed;
		triangle->setVelocity(velocity);

		_randomScale = 1.5f + (float)rand() / RAND_MAX * 2.0f; // 1.5f ~ 3.5f
		triangle->setScale(glm::vec3(_randomScale, _randomScale, _randomScale));

		_randomRotZ = 1.0f + (float)rand() / RAND_MAX * 358.0f; // 1.0f ~ 359.0f
		triangle->setRotZ(_randomRotZ);

		triangle->setColor(glm::vec3(0.8f, 0.4f, 0.0f)); // 暗橘色
	}
}

CDeathEffect::~CDeathEffect() {
	for (CTriangle* tri : _triangleList) {
		delete tri;
	}
	_triangleList.clear();
}

void CDeathEffect::draw() {
	for (CTriangle* tri : _triangleList) {
		tri->draw();
	}
}

void CDeathEffect::update(float dt) {
	bool allInactive = true;

	for (CTriangle* tri : _triangleList) {
		if (tri->getIsActive()) {
			tri->update(dt);
			allInactive = false;
		}
	}

	_isActive = !allInactive; // 三角形特效全數播放完畢
}

bool CDeathEffect::getIsActive() { return _isActive; }