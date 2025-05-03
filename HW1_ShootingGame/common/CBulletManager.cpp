#include <cstdio>
#include <cstdlib>

#include <glew/include/GL/glew.h>
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
	currentBullet->setPos(playerMove); // 生成在滑鼠當下點擊的位置
	currentBullet->setScale(glm::vec3(0.9f, 0.9f, 0.9f));
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
		if(pGet->bullet->fly(dt)) pGet = pGet->Link;
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