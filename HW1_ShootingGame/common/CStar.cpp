#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CStar.h"

#define GRID_H_DOT 9
#define GRID_V_DOT 7

CStar::CStar() : CShape()
{
    randomX = 0.0f;

    _vtxCount = 8;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 12;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m               // �C��              // �k�V�q            // �K�Ϯy��
        0.0f, 0.4f, 0.0f,     0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.1f, 0.0f, 0.0f,    0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.1f, 0.0f, 0.0f,     0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.0f, -0.4f, 0.0f,    0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.4f, 0.0f, 0.0f,    0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 4
        0.0f, 0.1f, 0.0f,     0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 5
        0.0f, -0.1f, 0.0f,    0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 6
        0.4f, 0.0f, 0.0f,     0.7f, 0.6f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 7
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2, // (1)
        1, 2, 3, // (2)
        4, 5, 6, // (3)
        5, 6, 7, // (4)
    };
}

CStar::~CStar() {
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CStar::setRandomPos() {
    // �H�����w�P�P�y��
    float x = -3.0f + (float)rand() / RAND_MAX * 6.0f;
    float y = -4.0f + (float)rand() / RAND_MAX * 8.0f;
    _pos = glm::vec3(x, y, 0.0f);
    _bPos = true;
    _mxPos = glm::translate(glm::mat4(1.0f), _pos);

    // �]�w�P�P�U���ɦ^��W�誺 X �y�С]�P update �禡�s���^
    randomX = -3.0f + (float)rand() / RAND_MAX * 6.0f;
}

void CStar::setRandomScale() {
    // �Y�� 0.1f - 0.5f �� 
    float randomScale = 0.1f + (float)rand() / RAND_MAX * 0.4f;
    _scale = glm::vec3(randomScale, randomScale, 1.0f);
    _bScale = true;
    _mxScale = glm::scale(glm::mat4(1.0f), _scale);
}

void CStar::draw() {
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}


void CStar::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}

void CStar::update(float dt) {
    glm::mat4 mxMove; // �P�P���첾�x�}
    float minY = -8.5f; // �N�P�P���ʨ�ù��~��

    _pos.y -= 1.0f * dt; // �첾�t�ס]�w�p��l�u�C�^
    if (_pos.y < minY) {
        _pos.y = -minY;
        mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, _pos.y, 0.0f));
    } else mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, _pos.y, 0.0f));
    setTransformMatrix(mxMove);
}