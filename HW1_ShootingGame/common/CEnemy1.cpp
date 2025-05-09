#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CEnemy1.h"

CEnemy1::CEnemy1(int colorType) : CShape()
{
    _isAttacking = false;
    _attackTimer = 0.0f;
    _attackIntervalTime = 2.0f;

    glm::vec3 hexChoice[3] = {
        glm::vec3(0.8f, 0.4f, 0.4f), // ����
        glm::vec3(0.4f, 0.8f, 0.4f), // ���
        glm::vec3(0.4f, 0.4f, 0.8f)  // �Ŧ�
    };
    _hexColor = hexChoice[colorType]; // �����C��
    _triColor = glm::vec3(_hexColor.x - 0.4f, _hexColor.y - 0.4f, _hexColor.z - 0.4f); // �}�[�C��
    _winColor = glm::vec3(0.7f, 0.8f, 0.9f); // �׭������C��

    _vtxCount = 16;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 27;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m                  // �C��                                                  // �k�V�q          // �K�Ϯy��
        0.0f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.0f, 0.5f, 0.0f,        _hexColor.x+0.2f, _hexColor.y+0.2f, _hexColor.z+0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.4f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.4f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.4f, -0.3f, 0.0f,      _hexColor.x-0.2f, _hexColor.y-0.2f, _hexColor.z-0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.4f, -0.3f, 0.0f,       _hexColor.x-0.2f, _hexColor.y-0.2f, _hexColor.z-0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.0f, -0.5f, 0.0f,       _hexColor.x-0.2f, _hexColor.y-0.2f, _hexColor.z-0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        0.0f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.3f, 0.0f, 0.0f,       _winColor.x-0.1f, _winColor.y-0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.3f, 0.0f, 0.0f,        _winColor.x-0.1f, _winColor.y-0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        -0.26f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        -0.12f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.2f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        0.12f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        0.26f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        0.2f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
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
    };
}

CEnemy1::~CEnemy1()
{
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CEnemy1::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
    
    // ø�s�ò{�����Ҧ��l�u
    for (CAttack* attack : _attackList) {
        attack->draw();
    }
}

void CEnemy1::update(float dt)
{
    float startY = 4.5f; // �ӼĤH�ͦ��ɪ� Y �b��m
    float endY = 2.0f; // ���ĤH���ʨ�w�I�i������]���|���W�X���������p�^

    if (!_isAttacking) {
        _pos.y -= 1.2f * dt; // �첾�t�ס]��I���֤@�I�I�^
        setPos(_pos);
        if (_pos.y <= endY) {
            _isAttacking = true;
            _pos.y = endY;
        }
    }
    else {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            // �ͦ��ó]�w�l�u
            CAttack* attack = new CAttack;
            _attackList.push_back(attack);
            attack->setupVertexAttributes();
            attack->setShaderID(getShaderProgram());
            attack->setColor(glm::vec3(0.95f, 0.8f, 0.2f));

            attack->setPos(_pos);
            attack->setDirection(_targetMove); // �]�w������V�]�ؼС^

            _attackTimer = 0.0f; // ���]�����p�ɾ�
        }
        // ��s�{�����Ҧ��l�u
        for (CAttack* attack : _attackList) {
            attack->update(dt);
        }
    }

}

void CEnemy1::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}