#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CBoss.h"
#include "CAttackManager.h"
#include "CGrid.h"
#include "CDeathEffect.h"
#include "CDeathEffectManager.h"

CBoss::CBoss() : CShape()
{
    _isAttacking = false;
    _attackTimer = 0.0f;
    _attackIntervalTime = 0.8f;

    _tag = "boss";
    _attackMode = 0;
    _life = 30; // ���a�� 10 ��

    _hexColor = glm::vec3(127.0f / 255.0f, 1.0f, 0.0f); // �����C��
    _triColor = glm::vec3(_hexColor.x - 0.4f, _hexColor.y - 0.4f, _hexColor.z - 0.4f); // �}�[�C��
    _winColor = glm::vec3(0.6f, 0.7f, 0.8f); // �׭������C��

    _vtxCount = 16 * 3;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 27 * 3;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m                  // �C��                                                  // �k�V�q          // �K�Ϯy��
        0.0f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.0f, 0.5f, 0.0f,        _hexColor.x + 0.2f, _hexColor.y + 0.2f, _hexColor.z + 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.4f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.4f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.4f, -0.3f, 0.0f,      _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.4f, -0.3f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.0f, -0.5f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        0.0f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.3f, 0.0f, 0.0f,       _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.3f, 0.0f, 0.0f,        _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        -0.26f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        -0.12f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.2f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        0.12f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        0.26f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        0.2f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15

        -0.4f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.4f, 0.5f, 0.0f,        _hexColor.x + 0.2f, _hexColor.y + 0.2f, _hexColor.z + 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.8f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.0f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.8f, -0.3f, 0.0f,      _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.0f, -0.3f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        -0.4f, -0.5f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        -0.4f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.7f, 0.0f, 0.0f,       _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        -0.1f, 0.0f, 0.0f,        _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        -0.66f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        -0.52f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.6f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        -0.28f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        -0.14f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        -0.2f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15

        0.4f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.4f, 0.5f, 0.0f,        _hexColor.x + 0.2f, _hexColor.y + 0.2f, _hexColor.z + 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.0f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.8f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.0f, -0.3f, 0.0f,      _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.8f, -0.3f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.4f, -0.5f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        0.4f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        0.1f, 0.0f, 0.0f,       _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.7f, 0.0f, 0.0f,        _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        0.14f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        0.28f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        0.2f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        1.32f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        1.46f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        1.4f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2, // (1)
        0, 1, 3, // (2)
        0, 2, 4, // (3)
        0, 3, 5, // (4)
        0, 4, 6, // (5)
        0, 5, 6, // (6)
        7, 8, 9, // (7)
        10, 11, 12, // (8)
        13, 14, 15, // (9)

        16, 17, 18, // (1)
        16, 17, 19, // (2)
        16, 18, 20, // (3)
        16, 19, 21, // (4)
        16, 20, 22, // (5)
        16, 21, 22, // (6)
        23, 24, 25, // (7)
        26, 27, 28, // (8)
        29, 30, 31, // (9)

        32, 33, 34, // (1)
        32, 33, 35, // (2)
        32, 34, 36, // (3)
        32, 35, 37, // (4)
        32, 36, 38, // (5)
        32, 37, 38, // (6)
        39, 40, 41, // (7)
        12, 43, 44, // (8)
        45, 46, 47, // (9)
    };
}

CBoss::~CBoss()
{
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CBoss::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CBoss::update(float dt)
{
    // �����Ҧ��G1.�H������  2.�˷Ǯg��  3. 1+2
    if (_life > 20) {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack(getShaderProgram(), _pos); // �ͦ��ó]�w�l�u
            _attackTimer = 0.0f; // ���]�����p�ɾ�
        }
    }
    else if (_life <= 20) {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack(getShaderProgram(), _pos); // �ͦ��ó]�w�l�u
            CAttackManager::setTargetMove(3, _targetMove); // �]�w�Ӧ������ؼ�
            _attackTimer = 0.0f; // ���]�����p�ɾ�
        }
    }
    else if (_life <= 10) {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack(getShaderProgram(), _pos); // �H���l�u

            CAttackManager::addAttack(getShaderProgram(), _pos); // �˷Ǥl�u
            CAttackManager::setTargetMove(3, _targetMove); // �]�w�Ӧ������ؼ�

            _attackTimer = 0.0f; // ���]�����p�ɾ�
        }
    }

    CGrid::insertObjects(this); // �N boss �[�J��u�I�������t��
}

void CBoss::onCollision(CShape* other) {
    // boss ���쪱�a���l�u��|��֥ͩR
    if (other->getTag() == "bullet") {
        _life--;
        if (_life == 0) {
            CDeathEffectManager::createEffect(_shaderProg, _pos); // ���񦺤`�S��
            _isActive = false;
        }
    }
    else if (other->getTag() == "player") {
        // boss ���쪱�a���|���
    }
}

void CBoss::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}