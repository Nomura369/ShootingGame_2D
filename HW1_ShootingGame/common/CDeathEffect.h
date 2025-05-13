#pragma once
#include <list>
using namespace std;

#include "CTriangle.h"

// 敵人的死亡特效類別
class CDeathEffect {
public:
	CDeathEffect(GLuint shaderProg, glm::vec3 pos); // 敵人死亡即觸發
	~CDeathEffect();
	void draw();
	void update(float dt);
	bool getIsActive();

private:
	list<CTriangle*> _triangleList;
	glm::vec3 _directions[8] = {
		glm::vec3(1.0f,  0.0f, 0.0f),  // 右
		glm::vec3(1.0f,  1.0f, 0.0f),  // 右上
		glm::vec3(0.0f,  1.0f, 0.0f),  // 上
		glm::vec3(-1.0f,  1.0f, 0.0f),  // 左上
		glm::vec3(-1.0f,  0.0f, 0.0f),  // 左
		glm::vec3(-1.0f, -1.0f, 0.0f),  // 左下
		glm::vec3(0.0f, -1.0f, 0.0f),  // 下
		glm::vec3(1.0f, -1.0f, 0.0f),  // 右下
	};
	float _randomSpeed, _randomScale, _randomRotZ;
	bool _isActive; // 由三角形特效是否播放完畢來判斷
};
