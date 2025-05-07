#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CBullet.h"

CBullet::CBullet() : CShape()
{
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
    glm::mat4 mxBMove; // �l�u���첾�x�}
    float maxY = 10.0f; // �N�l�u�g��ù��~��

    _pos.y += 5.0f * dt; // �첾�t��
    if (_pos.y > maxY) _isInWindow = false;
    else {
        _isInWindow = true;
        mxBMove = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, _pos.y, 0.0f));
        setTransformMatrix(mxBMove);
    }
}

void CBullet::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}