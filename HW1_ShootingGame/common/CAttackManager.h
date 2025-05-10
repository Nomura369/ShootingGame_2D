#pragma once
#include <list>
using namespace std;

#include "CAttack.h"

// 定義攻擊管理器類別，使用靜態成員控管敵人的子彈
class CAttackManager
{
public:
	static void draw();
	static void addAttack1(GLuint shaderProg, glm::vec3 pos); // 對應 _attackList1
	static void addAttack2(GLuint shaderProg, glm::vec3 pos); // 對應 _attackList2
	static void addAttack3(GLuint shaderProg, glm::vec3 pos); // 對應 _attackList3
	static void update(float dt);
	static void setTargetMove(int index, glm::vec3 targetMove) {
		_targetMove[index] = targetMove;
	}

private:
	CAttackManager(); // 避免創建實體
	static list<CAttack*> _attackList1; // 給 CEnemy1 使用
	static list<CAttack*> _attackList2; // 給 CEnemy2 使用
	static list<CAttack*> _attackList3; // 給 CEnemy3 使用
	static glm::vec3 _targetMove[3]; // 記錄三種敵人的攻擊目標
};