#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CGradient.h"

CGradient::CGradient() : CShape()
{
    _vtxCount = 4;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 6;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m                 // �C��              // �k�V�q            // �K�Ϯy��
        -6.0f, 2.0f, 0.0f,     0.2f, 0.1f, 0.4f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0 - ���W
        6.0f, 2.0f, 0.0f,      0.2f, 0.1f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1 - �k�W
        -6.0f, -2.0f, 0.0f,    0.05f, 0.05f, 0.1f,  1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2 - ���U
        6.0f, -2.0f, 0.0f,     0.05f, 0.05f, 0.1f,  1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3 - �k�U
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2, // �W�T��
        1, 2, 3, // �U�T��
    };
}

CGradient::~CGradient() {
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	glDeleteProgram(_shaderProg);  //���� shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CGradient::draw() {
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}


void CGradient::reset() {

}

void CGradient::update(float dt) {
	CShape::reset();
	// �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}