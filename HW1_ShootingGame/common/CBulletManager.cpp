#include <cstdio>
#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "CBulletManager.h"
#include "CGrid.h"

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
	currentBullet->setPos(playerMove); // 初始位置即為滑鼠位置
}

void CBulletManager::draw() { // 一次處理所有子彈
	pGet = pHead;
	while (pGet != nullptr) {
		if(pGet->bullet != nullptr) pGet->bullet->draw();
		pGet = pGet->Link;
	}
}

void CBulletManager::update(float dt) { // 一次處理所有子彈
	PNODE prev = nullptr; // 前一個節點
	pGet = pHead;

	while (pGet != nullptr) {
		pGet->bullet->update(dt);
		if (pGet->bullet->getIsInWindow() && pGet->bullet->getIsAlive()) {
			prev = pGet;
			pGet = pGet->Link;
		}
		else { // 理論上最先生成的會最先飛出視窗 + 與敵人碰撞後會消失
			PNODE toDelete = pGet;
			if (prev == nullptr) {
				pHead = pGet->Link;
			}
			else {
				prev->Link = pGet->Link;
			}
			pGet = pGet->Link;
			delete toDelete;
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