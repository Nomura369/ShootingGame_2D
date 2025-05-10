#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <cstdlib>
#include <iostream>

#include "CAttack.h"

#define M_PI 3.1415926f

CAttack::CAttack(float rds) : CShape()
{
    _direction = glm::vec3(0.0f, 0.0f, 0.0f); // �w�]�L��V�]�R��ʡ^
    _waitingTimer = 0.0f;
    _speed = 1.0f;
    _waitingStatus = 0;

    _radius = rds;

    std::vector<float> x;
    std::vector<float> y;
    float z = 0.0f;

    // ���N��ߩ�J���I�y�а}�C
    x.push_back(_pos.x);
    y.push_back(_pos.y);
    // ���Ͷ�P�y��
    for (int i = 1; i <= _segment + 1; ++i) {
        float angle = 2.0f * M_PI * i / _segment;
        x.push_back(0.0f + cos(angle) * _radius);
        y.push_back(0.0f + sin(angle) * _radius);
    }

    _vtxCount = 22;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 60;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m               // �C��                        // �k�V�q          // �K�Ϯy��
        x[0], y[0], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.5f, 1.0f, // 0 - ���
        x[1], y[1], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.0f, 0.5f,  // 1
        x[2], y[2], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 0.5f,  // 2
        x[3], y[3], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.0f, 0.0f,  // 3
        x[4], y[4], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 0.0f,  // 4
        x[5], y[5], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.5f, 0.0f,  // 5
        x[6], y[6], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // 6 
        x[7], y[7], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // 7
        x[8], y[8], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  0.0f, 1.0f,  // 8
        x[9], y[9], z,        _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 9
        x[10], y[10], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 10
        x[11], y[11], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 11
        x[12], y[12], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 12
        x[13], y[13], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 13
        x[14], y[14], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 14
        x[15], y[15], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 15
        x[16], y[16], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 16
        x[17], y[17], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 17 
        x[18], y[18], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 18
        x[19], y[19], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 19
        x[20], y[20], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 20
        x[21], y[21], z,      _color.x, _color.y, _color.z,  1.0f, 0.0f, 0.0f,  1.0f, 1.0f,   // 21�A�P 1 ���|
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2,    0, 2, 3,    0, 3, 4,
        0, 4, 5,    0, 5, 6,    0, 6, 7,
        0, 7, 8,    0, 8, 9,    0, 9, 10,
        0, 10, 11,  0, 11, 12,  0, 12, 13,
        0, 13, 14,  0, 14, 15,  0, 15, 16,
        0, 16, 17,  0, 17, 18,  0, 18, 19,
        0, 19, 20,  0, 20, 21
    };
}

CAttack::~CAttack()
{
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CAttack::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CAttack::update(float dt)
{
    _pos += _direction * dt * _speed;
    setPos(_pos);

    if (_waitingStatus == 1) { // �p��l�u�����ݮɶ�
        _waitingTimer += dt;
        if (_waitingTimer >= 5.0f) {
            _waitingStatus = 2; // ���u���}�l�i�����
            _waitingTimer = 0.0f;
        }
    }

    if (_pos.y < -10.0f) _isInWindow = false;
}

void CAttack::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}