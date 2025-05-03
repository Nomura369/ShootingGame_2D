#pragma once
#include "CBullet.h"

// �w�q�l�u�޲z�����O�A�D�n�Q���쵲��C���ީҦ��l�u�]Singleton pattern�^
class CBulletManager
{
private:
	static CBulletManager* instance;
	CBulletManager(); // �إ��쵲��C

public:
	// �T�O�~�����o�ƻs�����O�����
	CBulletManager(CBulletManager& other) = delete;
	void operator = (const CBulletManager&) = delete;

	// ��������O���ߤ@��Ҫ��R�A���
	static CBulletManager* getInstance() {
		if (instance == nullptr) { // �p�G�٨S����ҴN�Ыؤ@��
			instance = new CBulletManager();
		}
		return instance;
	}
	void instantiate(GLuint shaderProg, glm::vec3 playerMove); // �ͦ��l�u
	void draw(); // �@���e�X�쵲��C���{���������l�u
	void update(float dt); // �@����s�����l�u�����ʪ��A
	~CBulletManager(); // �����쵲��C

protected:
	typedef struct TNode {
		CBullet* bullet;
		struct TNode* Link;
	} NODE, * PNODE; // �l�u�`�I�ŧi
	//int count; // �O���ثe�`�I���ƶq
	//CBullet* in; // �O�����n��i�h���l�u���
	PNODE pHead, pTail, pGet;
};