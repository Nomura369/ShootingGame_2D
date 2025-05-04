#include <cstdlib>

#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CStar.h"

#define GRID_H_DOT 9
#define GRID_V_DOT 7

CStar::CStar() : CShape()
{
    randomX = 0.0f;

    _vtxCount = 8;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 12;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置               // 顏色              // 法向量            // 貼圖座標
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
    glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //再釋放 VAO
    glDeleteProgram(_shaderProg);  //釋放 shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CStar::setRandomPos() {
    // 隨機指定星星座標
    float x = -3.0f + (float)rand() / RAND_MAX * 6.0f;
    float y = -4.0f + (float)rand() / RAND_MAX * 8.0f;
    _pos = glm::vec3(x, y, 0.0f);
    _bPos = true;
    _mxPos = glm::translate(glm::mat4(1.0f), _pos);

    // 設定星星下降時回到上方的 X 座標（與 update 函式連結）
    randomX = -3.0f + (float)rand() / RAND_MAX * 6.0f;
}

void CStar::setRandomScale() {
    // 縮放 0.1f - 0.5f 倍 
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
    // 如有需要，可加入其他特定於四邊形的重設動作
}

void CStar::update(float dt) {
    glm::mat4 mxMove; // 星星的位移矩陣
    float minY = -8.5f; // 將星星移動到螢幕外面

    _pos.y -= 1.0f * dt; // 位移速度（預計比子彈慢）
    if (_pos.y < minY) {
        _pos.y = -minY;
        mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(randomX, _pos.y, 0.0f));
    } else mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, _pos.y, 0.0f));
    setTransformMatrix(mxMove);
}