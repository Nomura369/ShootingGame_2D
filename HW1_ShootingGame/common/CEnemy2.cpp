#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CEnemy2.h"

CEnemy2::CEnemy2(int colorType) : CShape()
{
    _isAttacking = false;
    _attackTimer = 0.0f;
    _attackIntervalTime = 2.0f;

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

    _vtxCount = 7;           // ���I�ƶq
    _vtxAttrCount = 11;      // �C�ӳ��I���ݩʼƶq�G��m(3), �C��(3), �k�V�q(3), �K�Ϯy��(2)
    _idxCount = 9;          // ø�s�ݭn�����޼�

    _points = new GLfloat[_vtxCount * _vtxAttrCount]{
        // ��m                  // �C��                                   // �k�V�q          // �K�Ϯy��
        0.0f, 0.6f, 0.0f,     _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    0.5f, 1.0f, // 0
        0.0f, -0.6f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 0.5f,  // 1
        -0.2f, 0.0f, 0.0f,    _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    1.0f, 0.5f,  // 2
        0.2f, 0.0f, 0.0f,     _bodyColor.x, _bodyColor.y, _bodyColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 0.0f,  // 3
        0.0f, 0.3f, 0.0f,     _midColor.x, _midColor.y, _midColor.z,       1.0f, 0.0f, 0.0f,    1.0f, 0.0f,  // 4
        -0.6f, 0.0f, 0.0f,    _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.5f, 0.0f,  // 5
        0.6f, 0.0f, 0.0f,     _wingColor.x, _wingColor.y, _wingColor.z,    1.0f, 0.0f, 0.0f,    0.0f, 1.0f,  // 6
    };

    _idx = new GLuint[_idxCount]{
        4, 5, 6, // (1)
        0, 1, 2, // (2)
        0, 1, 3, // (3)
    };
}

CEnemy2::~CEnemy2()
{
    glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
    glDeleteBuffers(1, &_ebo);
    glDeleteVertexArrays(1, &_vao); //�A���� VAO
    glDeleteProgram(_shaderProg);  //���� shader program
    if (_points != NULL) delete[] _points;
    if (_idx != NULL) delete[] _idx;
}

void CEnemy2::draw()
{
    glUseProgram(_shaderProg);
    updateMatrix();
    glBindVertexArray(_vao);
    glDrawElements(GL_TRIANGLES, _idxCount, GL_UNSIGNED_INT, 0);

    // ø�s�ò{�����Ҧ��l�u
    /*for (CAttack* attack : _attackList) {
        attack->draw();
    }*/
}

void CEnemy2::update(float dt)
{
    glm::mat4 mxMove; // �ĤH���첾�x�}

    _pos.y -= 2.0f * dt; // �첾�t�ס]��I���֡^
    mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, _pos.y, 0.0f));
    setTransformMatrix(mxMove);

    if (_pos.y < -10.0f) _isInWindow = false;

    // �����Ҧ��G�@��V�U�ֳt���ʤ@��o�g�u��
    //_attackTimer += dt;
    //if (_attackTimer >= _attackIntervalTime) {
    //    // �ͦ��ó]�w�l�u
    //    CAttack* currentAttack = new CAttack;
    //    _attackList.push_back(currentAttack);
    //    currentAttack->setupVertexAttributes();
    //    currentAttack->setShaderID(getShaderProgram());
    //    currentAttack->setPos(_pos); // �b�ĤH����ͦ�
    //    currentAttack->setColor(glm::vec3(0.95f, 0.8f, 0.2f));
    //    currentAttack->setTargetMove(_targetMove); // �¦V���a����

    //    _attackTimer = 0.0f; // ���]�����p�ɾ�
    //}
    //// ��s�{�����Ҧ��l�u
    //for (CAttack* attack : _attackList) {
    //    attack->update(dt);
    //}
}

void CEnemy2::reset() {
    CShape::reset();
    // �p���ݭn�A�i�[�J��L�S�w��|��Ϊ����]�ʧ@
}