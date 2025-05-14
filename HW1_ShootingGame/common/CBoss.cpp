#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CBoss.h"
#include "CAttackManager.h"
#include "CGrid.h"
#include "CDeathEffect.h"
#include "CDeathEffectManager.h"

CBoss::CBoss() : CShape()
{
    _isAttacking = false;
    _attackTimer = 0.0f;
    _attackIntervalTime = 0.8f;

    _tag = "boss";
    _attackMode = 0;
    _life = 30; // 玩家的 10 倍

    _hexColor = glm::vec3(127.0f / 255.0f, 1.0f, 0.0f); // 機身顏色
    _triColor = glm::vec3(_hexColor.x - 0.4f, _hexColor.y - 0.4f, _hexColor.z - 0.4f); // 腳架顏色
    _winColor = glm::vec3(0.6f, 0.7f, 0.8f); // 擋風玻璃顏色

    _vtxCount = 16 * 3;           // 頂點數量
    _vtxAttrCount = 11;      // 每個頂點的屬性數量：位置(3), 顏色(3), 法向量(3), 貼圖座標(2)
    _idxCount = 27 * 3;          // 繪製需要的索引數

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // 位置                  // 顏色                                                  // 法向量          // 貼圖座標
        0.0f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.0f, 0.5f, 0.0f,        _hexColor.x + 0.2f, _hexColor.y + 0.2f, _hexColor.z + 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.4f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.4f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.4f, -0.3f, 0.0f,      _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.4f, -0.3f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.0f, -0.5f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        0.0f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.3f, 0.0f, 0.0f,       _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.3f, 0.0f, 0.0f,        _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        -0.26f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        -0.12f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.2f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        0.12f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        0.26f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        0.2f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15

        -0.4f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.4f, 0.5f, 0.0f,        _hexColor.x + 0.2f, _hexColor.y + 0.2f, _hexColor.z + 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.8f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.0f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        -0.8f, -0.3f, 0.0f,      _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.0f, -0.3f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        -0.4f, -0.5f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        -0.4f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        -0.7f, 0.0f, 0.0f,       _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        -0.1f, 0.0f, 0.0f,        _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        -0.66f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        -0.52f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.6f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        -0.28f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        -0.14f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        -0.2f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15

        0.4f, 0.0f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.4f, 0.5f, 0.0f,        _hexColor.x + 0.2f, _hexColor.y + 0.2f, _hexColor.z + 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.0f, 0.3f, 0.0f,       _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.8f, 0.3f, 0.0f,        _hexColor.x, _hexColor.y, _hexColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.0f, -0.3f, 0.0f,      _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.8f, -0.3f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.4f, -0.5f, 0.0f,       _hexColor.x - 0.2f, _hexColor.y - 0.2f, _hexColor.z - 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
        0.4f, 0.2f, 0.0f,        _winColor.x, _winColor.y, _winColor.z,                   1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7
        0.1f, 0.0f, 0.0f,       _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.7f, 0.0f, 0.0f,        _winColor.x - 0.1f, _winColor.y - 0.1f, _winColor.z,         1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9
        0.14f, -0.37f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10
        0.28f, -0.44f, 0.0f,    _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        0.2f, -0.6f, 0.0f,      _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        1.32f, -0.44f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13
        1.46f, -0.37f, 0.0f,     _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14
        1.4f, -0.6f, 0.0f,       _triColor.x, _triColor.y, _triColor.z,                   1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
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

        16, 17, 18, // (1)
        16, 17, 19, // (2)
        16, 18, 20, // (3)
        16, 19, 21, // (4)
        16, 20, 22, // (5)
        16, 21, 22, // (6)
        23, 24, 25, // (7)
        26, 27, 28, // (8)
        29, 30, 31, // (9)

        32, 33, 34, // (1)
        32, 33, 35, // (2)
        32, 34, 36, // (3)
        32, 35, 37, // (4)
        32, 36, 38, // (5)
        32, 37, 38, // (6)
        39, 40, 41, // (7)
        12, 43, 44, // (8)
        45, 46, 47, // (9)
    };
}

CBoss::~CBoss()
{
    glDeleteBuffers(1, &_vbo);  //先釋放 VBO 與 EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //再釋放 VAO
    glDeleteProgram(_shaderProg);  //釋放 shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CBoss::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);
}

void CBoss::update(float dt)
{
    // 攻擊模式：1.隨機攻擊  2.瞄準射擊  3. 1+2
    if (_life > 20) {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack(getShaderProgram(), _pos); // 生成並設定子彈
            _attackTimer = 0.0f; // 重設攻擊計時器
        }
    }
    else if (_life <= 20) {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack(getShaderProgram(), _pos); // 生成並設定子彈
            CAttackManager::setTargetMove(3, _targetMove); // 設定該次攻擊目標
            _attackTimer = 0.0f; // 重設攻擊計時器
        }
    }
    else if (_life <= 10) {
        _attackTimer += dt;
        if (_attackTimer >= _attackIntervalTime) {
            CAttackManager::addAttack(getShaderProgram(), _pos); // 隨機子彈

            CAttackManager::addAttack(getShaderProgram(), _pos); // 瞄準子彈
            CAttackManager::setTargetMove(3, _targetMove); // 設定該次攻擊目標

            _attackTimer = 0.0f; // 重設攻擊計時器
        }
    }

    CGrid::insertObjects(this); // 將 boss 加入格線碰撞偵測系統
}

void CBoss::onCollision(CShape* other) {
    // boss 撞到玩家的子彈後會減少生命
    if (other->getTag() == "bullet") {
        _life--;
        if (_life == 0) {
            CDeathEffectManager::createEffect(_shaderProg, _pos); // 播放死亡特效
            _isActive = false;
        }
    }
    else if (other->getTag() == "player") {
        // boss 撞到玩家不會怎樣
    }
}

void CBoss::reset() {
    CShape::reset();
    // 如有需要，可加入其他特定於四邊形的重設動作
}