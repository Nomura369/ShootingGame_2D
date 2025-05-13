#pragma once
#include <list>
using namespace std;

#include "CDeathEffect.h"

// �w�q�S�ĺ޲z�����O�A�ϥ��R�A�������޼ĤH�����`�S��
class CDeathEffectManager
{
public:
	static void createEffect(GLuint shaderProg, glm::vec3 pos);
	static void draw();
	static void update(float dt);
	static void handleInActive();

private:
	CDeathEffectManager(); // �קK�Ыع���
	static list<CDeathEffect*> _effectList;
};