#pragma once
#include <list>
using namespace std;

#include "CTriangle.h"

// �ĤH�����`�S�����O
class CDeathEffect {
public:
	CDeathEffect(GLuint shaderProg, glm::vec3 pos); // �ĤH���`�YĲ�o
	~CDeathEffect();
	void draw();
	void update(float dt);
	bool getIsActive();

private:
	list<CTriangle*> _triangleList;
	glm::vec3 _directions[8] = {
		glm::vec3(1.0f,  0.0f, 0.0f),  // �k
		glm::vec3(1.0f,  1.0f, 0.0f),  // �k�W
		glm::vec3(0.0f,  1.0f, 0.0f),  // �W
		glm::vec3(-1.0f,  1.0f, 0.0f),  // ���W
		glm::vec3(-1.0f,  0.0f, 0.0f),  // ��
		glm::vec3(-1.0f, -1.0f, 0.0f),  // ���U
		glm::vec3(0.0f, -1.0f, 0.0f),  // �U
		glm::vec3(1.0f, -1.0f, 0.0f),  // �k�U
	};
	float _randomSpeed, _randomScale, _randomRotZ;
	bool _isActive; // �ѤT���ίS�ĬO�_���񧹲��ӧP�_
};
