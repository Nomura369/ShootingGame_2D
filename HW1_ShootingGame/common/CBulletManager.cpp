#include <cstdio>
#include <cstdlib>

#include <glew/include/GL/glew.h>
#include "CBulletManager.h"

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
	currentBullet->setPos(playerMove); // �ͦ��b�ƹ���U�I������m
	currentBullet->setScale(glm::vec3(0.9f, 0.9f, 0.9f));
}

void CBulletManager::draw() { // �@���B�z�Ҧ��l�u
	pGet = pHead;
	while (pGet != nullptr) {
		if(pGet->bullet != nullptr) pGet->bullet->draw();
		pGet = pGet->Link;
	}
}

void CBulletManager::update(float dt) { // �@���B�z�Ҧ��l�u
	pGet = pHead;
	while (pGet != nullptr) {
		if(pGet->bullet->fly(dt)) pGet = pGet->Link;
		else { // �z�פW�̥��ͦ����|�̥�����
			PNODE temp = pGet->Link;
			pGet = nullptr;
			delete pGet;
			pGet = temp;
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