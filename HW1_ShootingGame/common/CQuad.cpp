#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CQuad.h"
#include "initshader.h"

CQuad::CQuad()
{
	_vao = 0; _vbo = 0; _ebo = 0;
	_shaderProg = 0;
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotX = 0.0f; _rotY = 0.0f; _rotZ = 0.0f;
	_rotAxis = 0;
	_bRotation = _bScale = _bPos = _bTransform = _bOnTransform = false;
	_mxScale = glm::mat4(1.0f);
	_mxPos = glm::mat4(1.0f);
	_mxRotX = glm::mat4(1.0f);
	_mxRotY = glm::mat4(1.0f);
	_mxRotZ = glm::mat4(1.0f);
	_mxRotation = glm::mat4(1.0f);
	_mxTRS = glm::mat4(1.0f);
	_mxTransform = glm::mat4(1.0f);
	_mxFinal = glm::mat4(1.0f);
	_points = new GLfloat[QUAD_VTX_COUNT * QUAD_VTX_ATTR_COUNT] {
		// ��m            // �C��         // �k�V�q       // �K�Ϯy��
		-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, // ���U
		 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, // �k�U
		 0.5f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f, // �k�W
		-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f  // ���W
	};
	_idx = new GLuint[QUAD_INDEX_COUNT]{ 0, 1, 2, 2, 3, 0 };

//	setupVertexAttributes(); // �o���b�D�{���Ѫ���I�s�A�N�������O�i�ŧi���骫��
}

CQuad::~CQuad()
{
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	glDeleteProgram(_shaderProg);  //���� shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CQuad::setupVertexAttributes()
{
	// �]�w VAO�BVBO �P EBO
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(_vao);

	// �]�w VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, QUAD_VTX_COUNT * QUAD_VTX_ATTR_COUNT * sizeof(_points), _points, GL_STATIC_DRAW);

	// �]�w EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, QUAD_INDEX_COUNT * sizeof(GLuint), _idx, GL_STATIC_DRAW);

	// ��m�ݩ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, QUAD_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	// �C���ݩ�
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, QUAD_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//�k�V�q�ݩ�
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, QUAD_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//�K�Ϯy���ݩ�
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, QUAD_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glBindVertexArray(0); // �Ѱ��� VAO ���j�w
}

GLuint CQuad::setShader(const char* vshader, const  char* fshader)
{
	_shaderProg = createShader(vshader, fshader);
	glUseProgram(_shaderProg);
	_modelMxLoc = glGetUniformLocation(_shaderProg, "mxModel"); 	// ���o model matrix �ܼƪ���m
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxTRS));
	return _shaderProg;
}

void CQuad::setShaderID(GLuint shaderID)
{
	_shaderProg = shaderID;
	glUseProgram(_shaderProg);
	_modelMxLoc = glGetUniformLocation(_shaderProg, "mxModel"); 	// ���o MVP �ܼƪ���m
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxTRS));
}

void CQuad::setColor(glm::vec3 vColor)
{
	_color = vColor;
	for (int i = 0; i < QUAD_VTX_COUNT; i++) {
		_points[i * QUAD_VTX_ATTR_COUNT + COLOR_OFFSET ]  = _color.x;
		_points[i * QUAD_VTX_ATTR_COUNT + COLOR_OFFSET+1] = _color.y;
		_points[i * QUAD_VTX_ATTR_COUNT + COLOR_OFFSET+2] = _color.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, QUAD_VTX_COUNT * QUAD_VTX_ATTR_COUNT * sizeof(_points), _points, GL_STATIC_DRAW);
}

void CQuad::draw()
{
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, QUAD_INDEX_COUNT, GL_UNSIGNED_INT, 0);
}

void CQuad::setScale(glm::vec3 vScale)
{
	_scale = vScale;
	_bScale = true;
	_mxScale = glm::scale(glm::mat4(1.0f), _scale);
}

void CQuad::setPos(glm::vec3 vPt)
{
	_pos = vPt;
	_bPos = true;
	_mxPos = glm::translate(glm::mat4(1.0f), _pos);
}

void CQuad::setRotX(float angle)
{
	_rotX = glm::radians(angle);
	_rotAxis = _rotAxis | 1;
	_mxRotX = glm::rotate(glm::mat4(1.0f), _rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	_mxRotation = _mxRotX;
	_bRotation = true;
}

void CQuad::setRotY(float angle)
{
	_rotY = glm::radians(angle);
	_rotAxis = _rotAxis | 2;
	_mxRotY = glm::rotate(glm::mat4(1.0f), _rotY, glm::vec3(0.0f, 1.0f, 0.0f));
	if (_rotAxis & 1)_mxRotation = _mxRotY * _mxRotX;
	else _mxRotation = _mxRotY;
	_bRotation = true;
}

void CQuad::setRotZ(float angle)
{
	_rotZ = glm::radians(angle);
	_mxRotZ = glm::rotate(glm::mat4(1.0f), _rotZ, glm::vec3(0.0f, 0.0f, 1.0f));
	if (_rotAxis == 1) _mxRotation = _mxRotZ * _mxRotX;
	else if (_rotAxis == 2) _mxRotation = _mxRotZ * _mxRotY;
	else if (_rotAxis == 3) _mxRotation = _mxRotZ * _mxRotY * _mxRotX;
	else _mxRotation = _mxRotZ;
	_bRotation = true;
}

void CQuad::updateMatrix()
{
	if (_bScale || _bPos || _bRotation)
	{
		_mxTRS = _mxPos * _mxRotation * _mxScale;
		if (_bOnTransform == true) _mxFinal = _mxTransform * _mxTRS;
		else _mxFinal = _mxTRS;
		_bScale = _bPos = _bRotation = false;
	}
	if ( _bTransform ) {
		_mxFinal = _mxTransform * _mxTRS;
		_bTransform = false;
	}
	// �p�h�Ӽҫ��ϥάۦP�� shader program,�]�C�@�Ӽҫ��� mxTRS �����P�A�ҥH�C��frame���n��s
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxFinal));
}

void CQuad::setTransformMatrix(glm::mat4 mxMatrix)
{
	_bOnTransform = _bTransform = true;
	_mxTransform = mxMatrix;
}
glm::mat4 CQuad::getModelMatrix() { return _mxFinal; }

GLuint CQuad::getShaderProgram() { return _shaderProg; }

void CQuad::reset()
{
	_scale = glm::vec3(1.0f, 1.0f, 1.0f);
	_color = glm::vec3(1.0f, 1.0f, 1.0f);
	_pos = glm::vec3(0.0f, 0.0f, 0.0f);
	_rotX = 0.0f; _rotY = 0.0f; _rotZ = 0.0f;
	_rotAxis = 0;
	_bRotation = _bScale = _bPos = _bTransform = _bOnTransform = false;
	_mxScale = glm::mat4(1.0f);
	_mxPos = glm::mat4(1.0f);
	_mxTRS = glm::mat4(1.0f);
	_mxRotX = glm::mat4(1.0f);
	_mxRotY = glm::mat4(1.0f);
	_mxRotZ = glm::mat4(1.0f);
	_mxRotation = glm::mat4(1.0f);
	_mxTransform = glm::mat4(1.0f);
	_mxFinal = glm::mat4(1.0f);
}