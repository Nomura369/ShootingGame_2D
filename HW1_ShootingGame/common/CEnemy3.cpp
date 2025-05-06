#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CEnemy3.h"

CEnemy3::CEnemy3(int colorType) : CShape()
{
    //_isAttacking = false;

    glm::vec3 bodyChoice[3] = {
        glm::vec3(0.5f, 0.3f, 0.3f), // ����
        glm::vec3(0.3f, 0.5f, 0.3f), // ���
        glm::vec3(0.3f, 0.3f, 0.5f)  // �Ŧ�
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

    _bodyColor = bodyChoice[colorType]; // ����|�Τ@�H�H�����覡���w�����C��
    _midColor = midChoice[colorType]; // ������
    _wingColor = wingChoice[colorType]; // ���l�M�����C��

    _vtxCount = 12;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 12;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m                  // �C��                                   // �k�V�q          // �K�Ϯy��
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
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
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
    glm::mat4 mxMove; // �ĤH���첾�x�}
    float amplitude = 0.7f; // sin �i�e��
    float frequency = 2.0f; // �i�ʱK����

    _pos.y -= 1.2f * dt; // �����U���t�ס]��I���֤@�I�^
    _pos.x = amplitude * sin(frequency * _pos.y);
    mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(_pos.x, _pos.y, 0.0f));
    setTransformMatrix(mxMove);
    // �����Ҧ��G�@��V�U�D��@��o�g�u��


}

void CEnemy3::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}