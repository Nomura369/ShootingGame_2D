#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CEnemy2.h"
#include "CAttackManager.h"
#include "CGrid.h"
#include "CDeathEffectManager.h"

CEnemy2::CEnemy2(int colorType) : CShape()
{
    _isAttacking = false;
    _attackTimer = 0.0f;
    _attackIntervalTime = 0.5f;

    _tag = "enemy";

    glm::vec3 bodyChoice[3] = {
        glm::vec3(0.5f, 0.3f, 0.3f), // ����
        glm::vec3(0.3f, 0.5f, 0.3f), // ���
        glm::vec3(0.3f, 0.3f, 0.5f)  // �Ŧ�
    };
    glm::vec3 midChoice[3] = {
        glm::vec3(0.6f, 0.4f, 0.4f),
        glm::vec3(0.4f, 0.6f, 0.4f),
        glm::vec3(0.4f, 0.4f, 0.6f)
    };
    glm::vec3 wingChoice[3] = {
        glm::vec3(0.7f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.7f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.7f)
    };
    
    _bodyColor = bodyChoice[colorType]; // ����|�Τ@�H�H�����覡���w�����C��
    _midColor = midChoice[colorType]; // ������
    _wingColor = wingChoice[colorType]; // ���l�M�����C��

    _vtxCount = 7;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 9;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m                  // �C��                                   // �k�V�q          // �K�Ϯy��
        0.0f, 0.6f, 0.0f,     _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.0f, -0.6f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.2f, 0.0f, 0.0f,    _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.2f, 0.0f, 0.0f,     _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.0f, 0.3f, 0.0f,     _midColor.x, _midColor.y, _midColor.z,       1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        -0.6f, 0.0f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.6f, 0.0f, 0.0f,     _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
    };

    _idx = new GLuint[_idxCount]{
        4, 5, 6, // (1)
        0, 1, 2, // (2)
        0, 1, 3, // (3)
    };
}

CEnemy2::~CEnemy2()
{
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CEnemy2::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CEnemy2::update(float dt)
{
    _pos.y -= 2.2f * dt; // �첾�t�ס]��I���֡^
    setPos(_pos);

    if (_pos.y < -4.0f) _isActive = false;

    // �����Ҧ��G�V�U�ֳt���ʷ|�d�U�y��u��
    // �o�Ǽu���|��������]�o������ CAttack �M CAttackManager �@�P����^
    _attackTimer += dt;
    if (_attackTimer >= _attackIntervalTime) {
        CAttackManager::addAttack2(getShaderProgram(), _pos);
        CAttackManager::setTargetMove(1, _targetMove); // �]�w�Ӧ������ؼ�
        _attackTimer = 0.0f; // ���]�l�u�ͦ��p�ɾ�
    }

    CGrid::insertObjects(this); // �N�l�u�[�J��u�I�������t��
}

void CEnemy2::onCollision(CShape* other) {
    // �ĤH���쪱�a���l�u���|�����]�� CEnemyManager ����^
    if (other->getTag() == "bullet") {
        _life--;
        if (_life == 0) {
            CDeathEffectManager::createEffect(_shaderProg, _pos); // ���񦺤`�S��
            _isActive = false;
        }
    }
    else if (other->getTag() == "player") {
        // �ĤH���쪱�a���|���
    }
}

void CEnemy2::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}