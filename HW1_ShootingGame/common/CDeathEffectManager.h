#pragma once
#include <list>
using namespace std;

#include "CDeathEffect.h"

// 定義特效管理器類別，使用靜態成員控管敵人的死亡特效
class CDeathEffectManager
{
public:
	static void createEffect(GLuint shaderProg, glm::vec3 pos);
	static void draw();
	static void update(float dt);
	static void handleInActive();

private:
	CDeathEffectManager(); // 避免創建實體
	static list<CDeathEffect*> _effectList;
};