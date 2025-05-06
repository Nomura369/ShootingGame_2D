#include <cstdio>
#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
#include "CBulletManager.h"

CBulletManager::CBulletManager() {
	pHead = pTail = pGet = nullptr;
}

void CBulletManager::instantiate(GLuint shaderProg, glm::vec3 playerMove) { // 一次處理一顆子彈
	if (pHead == nullptr) { // 鏈結串列為空時，建立第一個節點
		pHead = new NODE;
		pHead->bullet = new CBullet; // 生成子彈
		pHead->Link = nullptr;
		pTail = pHead;
	}
	else {
		pGet = new NODE;
		pGet->bullet = new CBullet; // 生成子彈
		pGet->Link = nullptr;
		pTail->Link = pGet;
		pTail = pGet;
	}
	// 設定子彈的基本資料
	CBullet* currentBullet = pTail->bullet;
	currentBullet->setupVertexAttributes();
	currentBullet->setShaderID(shaderProg);
	currentBullet->setScale(glm::vec3(0.9f, 0.9f, 0.9f));
	// 初始位置即為滑鼠位置（調整 Y 軸偏移）
	float offsetY = 0.0f;
	if (playerMove.y > 0.0f) {
		if (playerMove.y > 3.0f) offsetY = -1.4f;
		else if (playerMove.y > 2.0f) offsetY = -1.2f;
		else if (playerMove.y > 1.0f) offsetY = -0.6f;
		else offsetY = -0.2f;
	}
	else if (playerMove.y < 0.0f) {
		if (playerMove.y < -3.0f) offsetY = 1.7f;
		else if (playerMove.y < -2.0f) offsetY = 1.5f;
		else if (playerMove.y < -1.0f) offsetY = 0.9f;
		else offsetY = 0.5f;
	}
	currentBullet->setPos(glm::vec3(playerMove.x, playerMove.y + offsetY, playerMove.z));
}

void CBulletManager::draw() { // 一次處理所有子彈
	pGet = pHead;
	while (pGet != nullptr) {
		if(pGet->bullet != nullptr) pGet->bullet->draw();
		pGet = pGet->Link;
	}
}

void CBulletManager::update(float dt) { // 一次處理所有子彈
	pGet = pHead;
	while (pGet != nullptr) {
		pGet->bullet->update(dt);
		if (pGet->bullet->_isInWindow) {
			pGet = pGet->Link;
		}
		else { // 理論上最先生成的會最先消失
			PNODE temp = pGet->Link;
			pGet = nullptr;
			delete pGet;
			pGet = temp;
		}
	}
}

CBulletManager::~CBulletManager() {
	while (pHead != nullptr) { //每次都先釋放最前面的
		PNODE temp = pHead;
		pHead = pHead->Link;
		if (temp != nullptr) delete temp;
	}
}