#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CStar.h"

CStar::CStar() : CShape()
{
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
    // x �y�ЩM y �y�Ъ��d��Ҭ� -3.0f �� 3.0f
    float randomX = -3.0f + (float)rand() / RAND_MAX * 6.0f;
    float randomY = -3.0f + (float)rand() / RAND_MAX * 6.0f;
    _pos = glm::vec3(randomX, randomY, 0.0f);
    _bPos = true;
    _mxPos = glm::translate(glm::mat4(1.0f), _pos);
}

void CStar::setRandomScale() {
    // �Y�� 0.4f - 1.0f ��
    float randomScale = 0.4f + (float)rand() / RAND_MAX * 0.6f;
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

}

void CStar::update(float dt) {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}