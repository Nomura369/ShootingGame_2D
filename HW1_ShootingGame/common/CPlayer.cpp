#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CPlayer.h"

CPlayer::CPlayer() : CShape()
{ 
    _vtxCount = 18;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 36;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m         // �C��              // �k�V�q          // �K�Ϯy��
        0.0f, -0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.3f, -0.3f, 0.0f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.3f, -0.3f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        -0.7f, -0.3f, 0.0f,   0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.7f, -0.3f, 0.0f,    0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.0f, 0.2f, 0.0f,     0.8f, 0.8f, 0.8f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        -0.1f, 0.2f, 0.0f,    0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - �T����
        -0.1f, 0.2f, 0.0f,    0.1f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - �����
        -0.4f, 0.2f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.1f, 0.2f, 0.0f,     0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - �T����
        0.1f, 0.2f, 0.0f,     0.1f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - �����
        0.4f, 0.2f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.4f, 0.4f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        -0.1f, 0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - �T����
        -0.1f, 0.5f, 0.0f,    0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - �����
        0.4f, 0.4f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
        0.1f, 0.5f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - �T����
        0.1f, 0.5f, 0.0f,     0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - �����
    };

    _idx = new GLuint[_idxCount]{
        0, 5, 8, // (1)
        0, 5, 11, // (2)
        0, 1, 8, // (3)
        0, 2, 11, // (4)
        6, 8, 12, // (5)
        9, 11, 15, // (6)
        6, 12, 13, // (7)
        9, 15, 16, // (8)
        7, 14, 17, // (9)
        7, 10, 17, // (10)
        1, 3, 8, // (11)
        2, 4, 11 // (12)
    };
}

CPlayer::~CPlayer()
{
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	glDeleteProgram(_shaderProg);  //���� shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CPlayer::draw()
{
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CPlayer::update(float dt)
{


}

void CPlayer::reset() {
	CShape::reset();
	// �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}