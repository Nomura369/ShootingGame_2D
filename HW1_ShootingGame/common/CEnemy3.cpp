#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CEnemy3.h"

CEnemy3::CEnemy3(int colorType) : CShape()
{
    //_isAttacking = false;

    glm::vec3 bodyChoice[3] = {
        glm::vec3(0.5f, 0.3f, 0.3f), // 紅色
        glm::vec3(0.3f, 0.5f, 0.3f), // 綠色
        glm::vec3(0.3f, 0.3f, 0.5f)  // 藍色
    };
    glm::vec3 midChoice[3] = {
        glm::vec3(0.6f, 0.4f, 0.4f),
        glm::vec3(0.4f, 0.6f, 0.4f),
        glm::vec3(0.4f, 0.4f, 0.6f)
    };
    glm::vec3 wingChoice[3] = {
        glm::vec3(0.7f, 0.5f, 0.5f),
        glm::vec3(0.5f, 0.7f, 0.5f),
        glm::vec3(0.5f, 0.5f, 0.7f)
    };

    _bodyColor = bodyChoice[colorType]; // 之後會統一以隨機的方式指定機身顏色
    _midColor = midChoice[colorType]; // 中間色
    _wingColor = wingChoice[colorType]; // 機翼和尾部顏色

    _vtxCount = 12;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 12;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置                  // 顏色                                   // 法向量          // 貼圖座標
        0.0f, 0.6f, 0.0f,     _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.2f, -0.2f, 0.0f,   _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.2f, -0.2f, 0.0f,    _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.0f, 0.1f, 0.0f,     _midColor.x, _midColor.y, _midColor.z,       1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.5f, -0.3f, 0.0f,   _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.5f, -0.3f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        -0.2f, -0.3f, 0.0f,   _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        -0.3f, -0.5f, 0.0f,   _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.1f, -0.5f, 0.0f,   _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.2f, -0.3f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 9
        0.1f, -0.5f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 10
        0.3f, -0.5f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 11
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2, // (1)
        3, 4, 5, // (2)
        6, 7, 8, // (3)
        9, 10, 11, // (4)
    };
}

CEnemy3::~CEnemy3()
{
    glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //再釋放 VAO
    glDeleteProgram(_shaderProg);  //釋放 shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CEnemy3::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CEnemy3::update(float dt)
{
    glm::mat4 mxMove; // 敵人的位移矩陣
    float amplitude = 0.7f; // sin 波寬度
    float frequency = 2.0f; // 波動密集度

    _pos.y -= 1.2f * dt; // 垂直下降速度（比背景快一點）
    _pos.x = amplitude * sin(frequency * _pos.y);
    mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(_pos.x, _pos.y, 0.0f));
    setTransformMatrix(mxMove);
    // 攻擊模式：一邊向下蛇行一邊發射彈幕


}

void CEnemy3::reset() {
    CShape::reset();
    // 如有需要，可加入其他特定於四邊形的重設動作
}