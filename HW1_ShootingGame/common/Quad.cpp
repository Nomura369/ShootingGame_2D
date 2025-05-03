#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Quad.h"

Quad::Quad() : CShape() 
{
	_vtxCount = 4; _vtxAttrCount = 11; _idxCount = 6;

	_points = new GLfloat[_vtxCount * _vtxAttrCount]{
		// ��m            // �C��         // �k�V�q       // �K�Ϯy��
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // ���U
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // �k�U
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // �k�W
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f  // ���W
	};
	_idx = new GLuint[_idxCount]{ 0, 1, 2, 2, 3, 0 };
	//	setupVertexAttributes(); // �o���b�D�{���Ѫ���I�s�A�N�������O�i�ŧi���骫��
}

Quad::~Quad()
{
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void Quad::draw()
{
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void Quad::update(float dt)
{

}

void Quad::reset() {
	CShape::reset();
	// �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}
