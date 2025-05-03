#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "Quad.h"

Quad::Quad() : CShape() 
{
	_vtxCount = 4; _vtxAttrCount = 11; _idxCount = 6;

	_points = new GLfloat[_vtxCount * _vtxAttrCount]{
		// 位置            // 顏色         // 法向量       // 貼圖座標
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // 左下
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // 右下
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // 右上
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f  // 左上
	};
	_idx = new GLuint[_idxCount]{ 0, 1, 2, 2, 3, 0 };
	//	setupVertexAttributes(); // 這行改在主程式由物件呼叫，就能讓類別可宣告實體物件
}

Quad::~Quad()
{
	glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //再釋放 VAO
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
	// 如有需要，可加入其他特定於四邊形的重設動作
}
