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

    _vtxCount = 18;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 36;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m               // �C��              // �k�V�q          // �K�Ϯy��
        0.0f, -0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        -0.3f, -0.3f, 0.0f,   0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        0.3f, -0.3f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        -0.7f, -0.3f, 0.0f,   0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.7f, -0.3f, 0.0f,    0.2f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        0.0f, 0.2f, 0.0f,     0.8f, 0.8f, 0.8f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        -0.1f, 0.2f, 0.0f,    0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - �T����
        -0.1f, 0.2f, 0.0f,    0.1f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - �����
        -0.4f, 0.2f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
        0.1f, 0.2f, 0.0f,     0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - �T����
        0.1f, 0.2f, 0.0f,     0.1f, 0.8f, 0.7f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - �����
        0.4f, 0.2f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
        -0.4f, 0.4f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
        -0.1f, 0.5f, 0.0f,    0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - �T����
        -0.1f, 0.5f, 0.0f,    0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - �����
        0.4f, 0.4f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
        0.1f, 0.5f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - �T����
        0.1f, 0.5f, 0.0f,     0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - �����
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
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	glDeleteProgram(_shaderProg);  //���� shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CPlayer::draw()
{
    if (!_isFlashing) {
        if (_life == 2) {
            _vtxCount = 18;           // ���I�ƶq
            _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
            _idxCount = 36 - 3;          // ø�s�ݭn�����޼�

            _points = new GLfloat[_vtxCount * _vtxAttrCount]{
                // ��m               // �C��              // �k�V�q          // �K�Ϯy��
                0.0f, -0.5f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
                -0.3f, -0.3f, 0.0f,   0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
                0.3f, -0.3f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
                -0.7f, -0.3f, 0.0f,   0.1f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
                0.7f, -0.3f, 0.0f,    0.1f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
                0.0f, 0.2f, 0.0f,     0.7f, 0.7f, 0.7f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
                -0.1f, 0.2f, 0.0f,    0.6f, 0.6f, 0.6f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - �T����
                -0.1f, 0.2f, 0.0f,    0.0f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - �����
                -0.4f, 0.2f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
                0.1f, 0.2f, 0.0f,     0.6f, 0.6f, 0.6f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - �T����
                0.1f, 0.2f, 0.0f,     0.0f, 0.7f, 0.6f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - �����
                0.4f, 0.2f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
                -0.4f, 0.4f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
                -0.1f, 0.5f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - �T����
                -0.1f, 0.5f, 0.0f,    0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - �����
                0.4f, 0.4f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
                0.1f, 0.5f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - �T����
                0.1f, 0.5f, 0.0f,     0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - �����
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
            _vtxCount = 18;           // ���I�ƶq
            _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
            _idxCount = 36 - 6;          // ø�s�ݭn�����޼�

            _points = new GLfloat[_vtxCount * _vtxAttrCount]{
                // ��m               // �C��              // �k�V�q          // �K�Ϯy��
                0.0f, -0.5f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
                -0.3f, -0.3f, 0.0f,   0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
                0.3f, -0.3f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
                -0.7f, -0.3f, 0.0f,   0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
                0.7f, -0.3f, 0.0f,    0.0f, 0.6f, 0.5f,    1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
                0.0f, 0.2f, 0.0f,     0.5f, 0.5f, 0.5f,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
                -0.1f, 0.2f, 0.0f,    0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6 - �T����
                -0.1f, 0.2f, 0.0f,    0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 7 - �����
                -0.4f, 0.2f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 8
                0.1f, 0.2f, 0.0f,     0.4f, 0.4f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 9 - �T����
                0.1f, 0.2f, 0.0f,     0.0f, 0.5f, 0.4f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 10 - �����
                0.4f, 0.2f, 0.0f,     0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 11
                -0.4f, 0.4f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 12
                -0.1f, 0.5f, 0.0f,    0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 13 - �T����
                -0.1f, 0.5f, 0.0f,    0.0f, 0.3f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 14 - �����
                0.4f, 0.4f, 0.0f,     0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 15
                0.1f, 0.5f, 0.0f,     0.2f, 0.2f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 16 - �T����
                0.1f, 0.5f, 0.0f,     0.0f, 0.3f, 0.2f,    1.0f, 0.0f, 0.0f,    1.0f, 1.0f,   // 17 - �����
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

    CGrid::insertObjects(this); // �[�J��u�I�������t��

    // �{�{�ĪG�]�L�Įɶ��^
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
            _timer = 0.0f; // ���]�p�ɾ�
        }
    }
}

void CPlayer::onCollision(CShape* other) {
    // ���a����ĤH�Ψ�����|�l���@���ͩR
    if (other->getTag() == "enemy" || other->getTag() == "attack") {
        if (!_isHit) { // Ĳ�o�{�{�ĪG�]�L�Įɶ��^
            _life--;
            std::cout << "���a�ͩR�ȡG" << _life << std::endl;
            _isHit = true;
        }
        if (_life == 0) {
            _isActive = false;
        }
    }
}

void CPlayer::reset() {
	CShape::reset();
	// �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}