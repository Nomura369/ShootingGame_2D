#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CGradient.h"

CGradient::CGradient() : CShape()
{
    _vtxCount = 4;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 6;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置                 // 顏色              // 法向量            // 貼圖座標
        -6.0f, 2.0f, 0.0f,     0.2f, 0.1f, 0.4f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0 - 左上
        6.0f, 2.0f, 0.0f,      0.2f, 0.1f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1 - 右上
        -6.0f, -2.0f, 0.0f,    0.05f, 0.05f, 0.1f,  1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2 - 左下
        6.0f, -2.0f, 0.0f,     0.05f, 0.05f, 0.1f,  1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3 - 右下
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2, // 上三角
        1, 2, 3, // 下三角
    };
}

CGradient::~CGradient() {
	glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //再釋放 VAO
	glDeleteProgram(_shaderProg);  //釋放 shader program
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
	// 如有需要，可加入其他特定於四邊形的重設動作
}