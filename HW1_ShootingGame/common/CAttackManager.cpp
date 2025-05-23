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

void CAttackManager::addAttack1(GLuint shaderProg, glm::vec3 pos) { // 對應 _attackList1，一次處理一個
    // 生成並設定子彈
    CAttack* attack = new CAttack;
    _attackList1.push_back(attack);
    attack->setupVertexAttributes();
    attack->setShaderID(shaderProg);
    attack->setColor(glm::vec3(0.9f, 0.85f, 0.4f));

    glm::vec3 offset = glm::vec3(0.0f, -0.5f, 0.0f);
    attack->setPos(pos + offset);

    attack->setSpeed(3.5f);
    attack->setTargetMove(_targetMove[0]); // 設定攻擊目標（即為玩家）
    attack->updateDirection(); // 更新攻擊方向
}

void CAttackManager::addAttack2(GLuint shaderProg, glm::vec3 pos) { // 對應 _attackList2，一次處理一個
    // 生成並設定子彈
    CAttack* attack = new CAttack;
    _attackList2.push_back(attack);
    attack->setWaitingStatus(1); // 待攻擊狀態（由攻擊自行計算等待時間）
    attack->setupVertexAttributes();
    attack->setShaderID(shaderProg);
    attack->setColor(glm::vec3(0.95f, 0.8f, 0.2f));

    glm::vec3 offset = glm::vec3(0.0f, 1.0f, 0.0f);
    attack->setPos(pos + offset);
}

void CAttackManager::addAttack3(GLuint shaderProg, glm::vec3 pos) { // 對應 _attackList3，一次處理一個
    // 生成並設定子彈
    CAttack* attack = new CAttack;
    _attackList3.push_back(attack);
    attack->setupVertexAttributes();
    attack->setShaderID(shaderProg);
    attack->setColor(glm::vec3(0.96f, 1.0f, 0.3f));

    glm::vec3 offset = glm::vec3(0.0f, 0.0f, 0.0f);
    attack->setPos(pos + offset);

    //attack->setSpeed(3.0f);
    attack->updateDirection(); // 設定攻擊方向（隨機，使用預設的 targetMove）
}


void CAttackManager::update(float dt) { // 一次處理全部
    // CEnemy1
    for (CAttack* attack : _attackList1) {
        attack->update(dt);
    }

    // CEnemy2
    for (CAttack* attack : _attackList2) {
        if (attack->getWaitingStatus() == 2) {
            attack->setSpeed(2.5f);
            attack->setTargetMove(_targetMove[1]); // 設定攻擊目標（即為玩家）
            attack->updateDirection(); // 更新攻擊方向
            attack->setWaitingStatus(0);
        }
        attack->update(dt);
    }

    // CEnemy3
    for (CAttack* attack : _attackList3) {
        attack->update(dt);
    }
}

void CAttackManager::handleDeath() { // 一次處理全部
    for (auto it = _attackList1.begin(); it != _attackList1.end(); ) {
        CShape* att = *it;

        if (att->getIsActive()) {
            ++it; // 沒刪，就正常前進
        }
        else {
            delete att;
            att = nullptr;
            it = _attackList1.erase(it); // 刪掉並前進
        }
    }
    for (auto it = _attackList2.begin(); it != _attackList2.end(); ) {
        CShape* att = *it;

        if (att->getIsActive()) {
            ++it; // 沒刪，就正常前進
        }
        else {
            delete att;
            att = nullptr;
            it = _attackList2.erase(it); // 刪掉並前進
        }
    }
    for (auto it = _attackList3.begin(); it != _attackList3.end(); ) {
        CShape* att = *it;

        if (att->getIsActive()) {
            ++it; // 沒刪，就正常前進
        }
        else {
            delete att;
            att = nullptr;
            it = _attackList3.erase(it); // 刪掉並前進
        }
    }
}