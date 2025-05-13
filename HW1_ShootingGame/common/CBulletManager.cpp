#include <cstdio>
#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>

#include "CBulletManager.h"
#include "CGrid.h"

CBulletManager::CBulletManager() {
	pHead = pTail = pGet = nullptr;
}

void CBulletManager::instantiate(GLuint shaderProg, glm::vec3 playerMove) { // �@���B�z�@���l�u
	if (pHead == nullptr) { // �쵲��C���ŮɡA�إ߲Ĥ@�Ӹ`�I
		pHead = new NODE;
		pHead->bullet = new CBullet; // �ͦ��l�u
		pHead->Link = nullptr;
		pTail = pHead;
	}
	else {
		pGet = new NODE;
		pGet->bullet = new CBullet; // �ͦ��l�u
		pGet->Link = nullptr;
		pTail->Link = pGet;
		pTail = pGet;
	}
	// �]�w�l�u���򥻸��
	CBullet* currentBullet = pTail->bullet;
	currentBullet->setupVertexAttributes();
	currentBullet->setShaderID(shaderProg);
	currentBullet->setScale(glm::vec3(0.9f, 0.9f, 0.9f));
	currentBullet->setPos(playerMove); // ��l��m�Y���ƹ���m
}

void CBulletManager::draw() { // �@���B�z�Ҧ��l�u
	pGet = pHead;
	while (pGet != nullptr) {
		if(pGet->bullet != nullptr) pGet->bullet->draw();
		pGet = pGet->Link;
	}
}

void CBulletManager::update(float dt) { // �@���B�z�Ҧ��l�u
	PNODE prev = nullptr; // �e�@�Ӹ`�I
	pGet = pHead;

	while (pGet != nullptr) {
		pGet->bullet->update(dt);
		if (pGet->bullet->getIsInWindow() && pGet->bullet->getIsAlive()) {
			prev = pGet;
			pGet = pGet->Link;
		}
		else { // �z�פW�̥��ͦ����|�̥����X���� + �P�ĤH�I����|����
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
	while (pHead != nullptr) { //�C����������̫e����
		PNODE temp = pHead;
		pHead = pHead->Link;
		if (temp != nullptr) delete temp;
	}
}