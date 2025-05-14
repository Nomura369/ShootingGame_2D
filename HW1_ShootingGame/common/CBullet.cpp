#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "CBullet.h"
#include "CGrid.h"

CBullet::CBullet() : CShape()
{
    _tag = "bullet";

    _vtxCount = 18;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 36;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m               // �C��              // �k�V�q            // �K�Ϯy��
        0.0f, 0.3f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.15f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.05f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.05f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.15f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        -0.05f, -0.2f, 0.0f,  0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.05f, -0.2f, 0.0f,   0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 4, // (1)
        2, 3, 5, // (2)
        3, 5, 6, // (3)
    };
}

glm::vec3 CBullet::getPos() {
    return _pos;
}

CBullet::~CBullet()
{
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CBullet::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CBullet::update(float dt)
{
    float maxY = 10.0f; // �N�l�u�g��ù��~��

    _pos.y += 5.0f * dt; // �첾�t��
    if (_pos.y > maxY) _isActive = false;
    else {
        setPos(_pos);
        _isActive = true;
    }

    CGrid::insertObjects(this); // �N�l�u�[�J��u�I�������t��
}

void CBullet::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}

//bool CBullet::checkCollision(CShape* other) {
//    // �l�u�P�ĤH���I�������A�D�n��� bullet ������
//    
//}

void CBullet::onCollision(CShape* other) {
    // ���a���l�u����ĤH��|�����]�� CBulletManager ����^
    if (other->getTag() == "enemy") _isActive = false;
}