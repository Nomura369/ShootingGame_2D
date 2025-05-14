#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "CPlayer.h"
#include "CShaderPool.h"
#include "CGrid.h"

CPlayer::CPlayer() : CShape()
{ 
    _tag = "player";
    _life = 3;
    _isHit = _isFlashing =  false;
    _timer = 0.0f;

    _vtxCount = 18;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 36;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置               // 顏色              // 法向量          // 貼圖座標
        0.0f, -0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.3f, -0.3f, 0.0f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.3f, -0.3f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        -0.7f, -0.3f, 0.0f,   0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.7f, -0.3f, 0.0f,    0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.0f, 0.2f, 0.0f,     0.8f, 0.8f, 0.8f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        -0.1f, 0.2f, 0.0f,    0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - 三角形
        -0.1f, 0.2f, 0.0f,    0.1f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - 長方形
        -0.4f, 0.2f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.1f, 0.2f, 0.0f,     0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - 三角形
        0.1f, 0.2f, 0.0f,     0.1f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - 長方形
        0.4f, 0.2f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.4f, 0.4f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        -0.1f, 0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - 三角形
        -0.1f, 0.5f, 0.0f,    0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - 長方形
        0.4f, 0.4f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
        0.1f, 0.5f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - 三角形
        0.1f, 0.5f, 0.0f,     0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - 長方形
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
	glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //再釋放 VAO
	glDeleteProgram(_shaderProg);  //釋放 shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CPlayer::draw()
{
    if (!_isFlashing) {
        if (_life == 2) {
            _vtxCount = 18;           // 頂點數量
            _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
            _idxCount = 36 - 3;          // 繪製需要的索引數

            _points = new GLfloat[_vtxCount * _vtxAttrCount]{
                // 位置               // 顏色              // 法向量          // 貼圖座標
                0.0f, -0.5f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
                -0.3f, -0.3f, 0.0f,   0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
                0.3f, -0.3f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
                -0.7f, -0.3f, 0.0f,   0.1f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
                0.7f, -0.3f, 0.0f,    0.1f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
                0.0f, 0.2f, 0.0f,     0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
                -0.1f, 0.2f, 0.0f,    0.6f, 0.6f, 0.6f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - 三角形
                -0.1f, 0.2f, 0.0f,    0.0f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - 長方形
                -0.4f, 0.2f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
                0.1f, 0.2f, 0.0f,     0.6f, 0.6f, 0.6f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - 三角形
                0.1f, 0.2f, 0.0f,     0.0f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - 長方形
                0.4f, 0.2f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
                -0.4f, 0.4f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
                -0.1f, 0.5f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - 三角形
                -0.1f, 0.5f, 0.0f,    0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - 長方形
                0.4f, 0.4f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
                0.1f, 0.5f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - 三角形
                0.1f, 0.5f, 0.0f,     0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - 長方形
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
                //2, 4, 11 // (12)
            };
            setupVertexAttributes();
        }
        else if (_life == 1) {
            _vtxCount = 18;           // 頂點數量
            _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
            _idxCount = 36 - 6;          // 繪製需要的索引數

            _points = new GLfloat[_vtxCount * _vtxAttrCount]{
                // 位置               // 顏色              // 法向量          // 貼圖座標
                0.0f, -0.5f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
                -0.3f, -0.3f, 0.0f,   0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
                0.3f, -0.3f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
                -0.7f, -0.3f, 0.0f,   0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
                0.7f, -0.3f, 0.0f,    0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
                0.0f, 0.2f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
                -0.1f, 0.2f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - 三角形
                -0.1f, 0.2f, 0.0f,    0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - 長方形
                -0.4f, 0.2f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
                0.1f, 0.2f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - 三角形
                0.1f, 0.2f, 0.0f,     0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - 長方形
                0.4f, 0.2f, 0.0f,     0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
                -0.4f, 0.4f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
                -0.1f, 0.5f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - 三角形
                -0.1f, 0.5f, 0.0f,    0.0f, 0.3f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - 長方形
                0.4f, 0.4f, 0.0f,     0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
                0.1f, 0.5f, 0.0f,     0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - 三角形
                0.1f, 0.5f, 0.0f,     0.0f, 0.3f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - 長方形
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
                //1, 3, 8, // (11)
                //2, 4, 11 // (12)
            };
            setupVertexAttributes();
        }
        glUseProgram(_shaderProg);
        updateMatrix();
        glBindVertexArray(_vao);
        glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
    }
}

void CPlayer::update(float dt)
{
    glUseProgram(_shaderProg);
    GLint loc = glGetUniformLocation(_shaderProg, "isFlashing");
    if (loc != -1) {
        glUniform1i(loc, _isFlashing ? 1 : 0);
    }

    CGrid::insertObjects(this); // 加入格線碰撞偵測系統

    // 閃爍效果（無敵時間）
    if (_isHit) {
        _timer += dt;
        _isFlashing = true;
        if (_timer < 0.5f) {
            _isFlashing = false;
        }
        else if(_timer < 1.0f){
            _isFlashing = true;
        }
        else if (_timer < 1.5f) {
            _isFlashing = false;
        }
        else if (_timer < 2.0f) {
            _isFlashing = true;
        }
        else {
            _isHit = _isFlashing = false;
            _timer = 0.0f; // 重設計時器
        }
    }
}

void CPlayer::onCollision(CShape* other) {
    // 玩家撞到敵人或其攻擊會損失一條生命
    if (other->getTag() == "enemy" || other->getTag() == "attack") {
        if (!_isHit) { // 觸發閃爍效果（無敵時間）
            _life--;
            std::cout << "玩家生命值：" << _life << std::endl;
            _isHit = true;
        }
        if (_life == 0) {
            _isActive = false;
        }
    }
}

void CPlayer::reset() {
	CShape::reset();
	// 如有需要，可加入其他特定於四邊形的重設動作
}