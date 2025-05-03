#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Triangle.h"

Triangle::Triangle() : CShape()
{
	_vtxCount = 3; _vtxAttrCount = 11; _idxCount = 3;

	_points = new GLfloat[_vtxCount * _vtxAttrCount]{
		// ��m            // �C��         // �k�V�q       // �K�Ϯy��
		 0.0f, 0.57735f,   0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f, // �W���I
		-0.5f, -0.288675f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // ���U��
		 0.5f, -0.288675f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f // �k�U��
	};
	_idx = new GLuint[_idxCount]{ 0, 1, 2 };
	//	setupVertexAttributes(); // �o���b�D�{���Ѫ���I�s�A�N�������O�i�ŧi���骫��
}

Triangle::~Triangle()
{
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	glDeleteProgram(_shaderProg);  //���� shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void Triangle::draw()
{
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void Triangle::update(float dt)
{


}

void Triangle::reset() {
	CShape::reset();
	// �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}