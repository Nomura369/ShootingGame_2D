#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CEnemy1.h"
#include "CAttackManager.h"
#include "CGrid.h"
#include "CDeathEffect.h"
#include "CDeathEffectManager.h"

CEnemy1::CEnemy1(int colorType) : CShape()
{
    _isAttacking = false;
    _attackTimer = 0.0f;
    _attackIntervalTime = 2.0f;

    _tag = "enemy";

    glm::vec3 hexChoice[3] = {
        glm::vec3(0.8f, 0.4f, 0.4f), // 紅色
        glm::vec3(0.4f, 0.8f, 0.4f), // 綠色
        glm::vec3(0.4f, 0.4f, 0.8f)  // 藍色
    };
    _hexColor = hexChoice[colorType]; // 機身顏色
    _triColor = glm::vec3(_hexColor.x - 0.4f, _hexColor.y - 0.4f, _hexColor.z - 0.4f); // 腳架顏色
    _winColor = glm::vec3(0.7f, 0.8f, 0.9f); // 擋風玻璃顏色

    _vtxCount = 16;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 27;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置                  // 顏色                                                  // 法向量          // 貼圖座標
        0.0f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.0f, 0.5f, 0.0f,        _hexColor.x+0.2f, _hexColor.y+0.2f, _hexColor.z+0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.4f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.4f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.4f, -0.3f, 0.0f,      _hexColor.x-0.2f, _hexColor.y-0.2f, _hexColor.z-0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.4f, -0.3f, 0.0f,       _hexColor.x-0.2f, _hexColor.y-0.2f, _hexColor.z-0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.0f, -0.5f, 0.0f,       _hexColor.x-0.2f, _hexColor.y-0.2f, _hexColor.z-0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        0.0f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.3f, 0.0f, 0.0f,       _winColor.x-0.1f, _winColor.y-0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.3f, 0.0f, 0.0f,        _winColor.x-0.1f, _winColor.y-0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        -0.26f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        -0.12f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.2f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        0.12f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        0.26f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        0.2f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
    };

    _idx = new GLuint[_idxCount]{
        0, 1, 2, // (1)
        0, 1, 3, // (2)
        0, 2, 4, // (3)
        0, 3, 5, // (4)
        0, 4, 6, // (5)
        0, 5, 6, // (6)
        7, 8, 9, // (7)
        10, 11, 12, // (8)
        13, 14, 15, // (9)
    };
}

CEnemy1::~CEnemy1()
{
    glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //再釋放 VAO
    glDeleteProgram(_shaderProg);  //釋放 shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CEnemy1::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CEnemy1::update(float dt)
{
    float endY = 2.0f; // 讓敵人移動到定點進行攻擊（不會有超出視窗的情況）

    if (!_isAttacking) {
        _pos.y -= 1.7f * dt; // 位移速度（比背景快一點點）
        setPos(_pos);
        if (_pos.y <= endY) {
            _isAttacking = true;
            _pos.y = endY;
        }
    }
    else {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack1(getShaderProgram(), _pos); // 生成並設定子彈
            CAttackManager::setTargetMove(0, _targetMove); // 設定該次攻擊目標
            _attackTimer = 0.0f; // 重設攻擊計時器
        }
    }

    CGrid::insertObjects(this); // 將子彈加入格線碰撞偵測系統
}

void CEnemy1::onCollision(CShape* other) {
    // 敵人撞到玩家的子彈後後會消失（由 CEnemyManager 控制）
    if (other->getTag() == "bullet") {
        _life--;
        if (_life == 0) {
            CDeathEffectManager::createEffect(_shaderProg, _pos); // 播放死亡特效
            _isActive = false;
        }
    }
    else if (other->getTag() == "player") { 
        // 敵人撞到玩家不會怎樣
    }
}

void CEnemy1::reset() {
    CShape::reset();
    // 如有需要，可加入其他特定於四邊形的重設動作
}