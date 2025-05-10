#include <glew/include/GL/glew.h>

#include "CAttackManager.h"

// ��l���R�A�����ܼ�
list<CAttack*> CAttackManager::_attackList1;
list<CAttack*> CAttackManager::_attackList2;
list<CAttack*> CAttackManager::_attackList3;
glm::vec3 CAttackManager::_targetMove[3] = {
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
    glm::vec3(0.0f, 0.0f, 0.0f),
};

void CAttackManager::draw() { // �@���B�z����
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

void CAttackManager::addAttack1(GLuint shaderProg, glm::vec3 pos) { // ���� _attackList1�A�@���B�z�@��
    // �ͦ��ó]�w�l�u
    CAttack* attack = new CAttack;
    _attackList1.push_back(attack);
    attack->setupVertexAttributes();
    attack->setShaderID(shaderProg);
    attack->setColor(glm::vec3(0.9f, 0.85f, 0.4f));

    glm::vec3 offset = glm::vec3(0.0f, -0.5f, 0.0f);
    attack->setPos(pos + offset);

    attack->setSpeed(3.0f);
    attack->setTargetMove(_targetMove[0]); // �]�w�����ؼС]�Y�����a�^
    attack->updateDirection(); // ��s������V
}

void CAttackManager::addAttack2(GLuint shaderProg, glm::vec3 pos) { // ���� _attackList2�A�@���B�z�@��
    // �ͦ��ó]�w�l�u
    CAttack* attack = new CAttack;
    _attackList2.push_back(attack);
    attack->setWaitingStatus(1); // �ݧ������A�]�ѧ����ۦ�p�ⵥ�ݮɶ��^
    attack->setupVertexAttributes();
    attack->setShaderID(shaderProg);
    attack->setColor(glm::vec3(0.95f, 0.8f, 0.2f));

    glm::vec3 offset = glm::vec3(0.0f, 1.0f, 0.0f);
    attack->setPos(pos + offset);
}

void addAttack3(); // ���� _attackList3�A�@���B�z�@��


void CAttackManager::update(float dt) { // �@���B�z����
    // CEnemy1
    for (CAttack* attack : _attackList1) {
        attack->update(dt);
    }

    // CEnemy2
    for (CAttack* attack : _attackList2) {
        if (attack->getWaitingStatus() == 2) {
            attack->setSpeed(3.5f);
            attack->setTargetMove(_targetMove[1]); // �]�w�����ؼС]�Y�����a�^
            attack->updateDirection(); // ��s������V
            attack->setWaitingStatus(0);
        }
        attack->update(dt);
    }

    // CEnemy3
    for (CAttack* attack : _attackList3) {
        attack->update(dt);
    }
}