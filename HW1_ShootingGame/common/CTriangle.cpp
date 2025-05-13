#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CTriangle.h"

CTriangle::CTriangle() : CShape()
{
	_vtxCount = 3; _vtxAttrCount = 11; _idxCount = 3;

	_points = new GLfloat[_vtxCount * _vtxAttrCount]{
		// 位置                // 顏色             // 法向量           // 貼圖座標
		 0.0f, 0.05f, 0.0f,    1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.5f, 1.0f, // 上
		-0.1f, -0.05f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // 左下
		 0.1f, -0.05f, 0.0f,   1.0f, 1.0f, 1.0f,   0.0f, 0.0f, 1.0f,   1.0f, 0.0f // 右下
	};
	_idx = new GLuint[_idxCount]{ 0, 1, 2 };
}

CTriangle::~CTriangle()
{
	glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //再釋放 VAO
	glDeleteProgram(_shaderProg);  //釋放 shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CTriangle::draw()
{
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CTriangle::update(float dt)
{


}

void CTriangle::reset() {
	CShape::reset();
	// 如有需要，可加入其他特定於四邊形的重設動作
}