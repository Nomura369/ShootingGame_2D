#include <glew/include/GL/glew.h>

#include "CAttackManager.h"

// 初始化靜態成員變數
list<CAttack*> CAttackManager::_attackList1;
list<CAttack*> CAttackManager::_attackList2;
list<CAttack*> CAttackManager::_attackList3;
glm::vec3 CAttackManager::_targetMove[3] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
};

void CAttackManager::draw() { // 一次處理全部
    for (CAttack* attack : _attackList1) {
        attack->draw();
    }
    for (CAttack* attack : _attackList2) {
        attack->draw();
    }
    for (CAttack* attack : _attackList3) {
        attack->draw();
    }
}

void CAttackManager::addAttack1(GLuint shaderProg, glm::vec3 enemyPos) { // 對應 _attackList1，一次處理一個
    // 生成並設定子彈
    CAttack* attack = new CAttack;
    _attackList1.push_back(attack);
    attack->setupVertexAttributes();
    attack->setShaderID(shaderProg);
    attack->setColor(glm::vec3(0.9f, 0.85f, 0.4f));

    glm::vec3 offset = glm::vec3(0.0f, -0.5f, 0.0f);
    attack->setPos(enemyPos + offset);
    attack->setTargetMove(_targetMove[0]); // 設定攻擊目標（即為玩家）
    attack->updateDirection(); // 更新攻擊方向
}
void addAttack2(); // 對應 _attackList2，一次處理一個
void addAttack3(); // 對應 _attackList3，一次處理一個


void CAttackManager::update(float dt) { // 一次處理全部
    for (CAttack* attack : _attackList1) {
        attack->update(dt);
    }
    for (CAttack* attack : _attackList2) {
        attack->update(dt);
    }
    for (CAttack* attack : _attackList3) {
        attack->update(dt);
    }
}