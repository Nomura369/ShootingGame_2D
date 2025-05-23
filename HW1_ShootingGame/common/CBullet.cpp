#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "CBullet.h"
#include "CGrid.h"

CBullet::CBullet() : CShape()
{
    _tag = "bullet";

    _vtxCount = 18;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 36;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置               // 顏色              // 法向量            // 貼圖座標
        0.0f, 0.3f, 0.0f,     1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.15f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.05f, 0.0f, 0.0f,   1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.05f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.15f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        -0.05f, -0.2f, 0.0f,  0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.05f, -0.2f, 0.0f,   0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 4, // (1)
        2, 3, 5, // (2)
        3, 5, 6, // (3)
    };
}

glm::vec3 CBullet::getPos() {
    return _pos;
}

CBullet::~CBullet()
{
    glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //再釋放 VAO
    glDeleteProgram(_shaderProg);  //釋放 shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CBullet::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CBullet::update(float dt)
{
    float maxY = 10.0f; // 將子彈射到螢幕外面

    _pos.y += 5.0f * dt; // 位移速度
    if (_pos.y > maxY) _isActive = false;
    else {
        setPos(_pos);
        _isActive = true;
    }

    CGrid::insertObjects(this); // 將子彈加入格線碰撞偵測系統
}

void CBullet::reset() {
    CShape::reset();
    // 如有需要，可加入其他特定於四邊形的重設動作
}

//bool CBullet::checkCollision(CShape* other) {
//    // 子彈與敵人的碰撞偵測，主要交由 bullet 側執行
//    
//}

void CBullet::onCollision(CShape* other) {
    // 玩家的子彈撞到敵人後會消失（由 CBulletManager 控制）
    if (other->getTag() == "enemy") _isActive = false;
}