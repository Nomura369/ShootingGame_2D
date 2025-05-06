#include <cstdio>
#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/matrix_transform.hpp>
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
	currentBullet->setScale(glm::vec3(0.9f, 0.9f, 0.9f));
	// ��l��m�Y���ƹ���m�]�վ� Y �b�����^
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
		pGet->bullet->update(dt);
		if (pGet->bullet->_isInWindow) {
			pGet = pGet->Link;
		}
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