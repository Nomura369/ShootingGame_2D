#include <glew/include/GL/glew.h>
#include <glm/gtc/type_ptr.hpp>

#include "CPenta.h"
#include "initshader.h"

CPenta::CPenta()
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

	_points = new GLfloat[PENTA_VTX_COUNT * PENTA_VTX_ATTR_COUNT] {
		// ��m            // �C��         // �k�V�q       // �K�Ϯy��
		0.0f,   0.85065f, 0.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.5f, 1.0f,     // Vertex 0: ���� 90�X (pi/2)
		0.808f, 0.262f,   0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.975f, 0.654f, // Vertex 1: ���� 18�X (��0.31416����)
		0.5f,  -0.68819f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.794f, 0.096f, // Vertex 2: ���� -54�X (�� -0.94248 ����)
	   -0.5f,  -0.68819f, 0.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.206f, 0.096f, // Vertex 3: ���� -126�X (�� -2.19911 ����)
	   -0.808f, 0.262f,   0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.025f, 0.654f  // Vertex 4: ���� -198�X (�� -3.45575 ����)
	};
	_idx = new GLuint[PENTA_INDEX_COUNT]{ 0, 1, 2, 0 ,2 ,3, 0, 3, 4 };

//	setupVertexAttributes(); // �o���b�D�{���Ѫ���I�s�A�N�������O�i�ŧi���骫��
}

CPenta::~CPenta()
{
	glDeleteBuffers(1, &_vbo);  //������ VBO �P EBO
	glDeleteBuffers(1, &_ebo);
	glDeleteVertexArrays(1, &_vao); //�A���� VAO
	glDeleteProgram(_shaderProg);  //���� shader program
	if (_points != NULL) delete[] _points;
	if (_idx != NULL) delete[] _idx;
}

void CPenta::setupVertexAttributes()
{
	// �]�w VAO�BVBO �P EBO
	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);
	glGenBuffers(1, &_ebo);

	// Bind the Vertex Array Object first, then bind and set vertex buffer(s) and attribute pointer(s).
	glBindVertexArray(_vao);

	// �]�w VBO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, PENTA_VTX_COUNT * PENTA_VTX_ATTR_COUNT * sizeof(_points), _points, GL_STATIC_DRAW);

	// �]�w EBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _ebo);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, PENTA_INDEX_COUNT * sizeof(GLuint), _idx, GL_STATIC_DRAW);

	// ��m�ݩ�
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, PENTA_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(0));
	glEnableVertexAttribArray(0);

	// �C���ݩ�
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, PENTA_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//�k�V�q�ݩ�
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, PENTA_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	//�K�Ϯy���ݩ�
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, PENTA_VTX_ATTR_COUNT * sizeof(float), BUFFER_OFFSET(9 * sizeof(float)));
	glEnableVertexAttribArray(3);
	glBindVertexArray(0); // �Ѱ��� VAO ���j�w
}

GLuint CPenta::setShader(const char* vshader, const  char* fshader)
{
	_shaderProg = createShader(vshader, fshader);
	glUseProgram(_shaderProg);
	_modelMxLoc = glGetUniformLocation(_shaderProg, "mxModel"); 	// ���o MVP �ܼƪ���m
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxTRS));
	return _shaderProg;
}

void CPenta::setShaderID(GLuint shaderID)
{
	_shaderProg = shaderID;
	glUseProgram(_shaderProg);
	_modelMxLoc = glGetUniformLocation(_shaderProg, "mxModel"); 	// ���o MVP �ܼƪ���m
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxTRS));
}

void CPenta::setColor(glm::vec3 vColor)
{
	_color = vColor;
	for (int i = 0; i < PENTA_VTX_COUNT; i++) {
		_points[i * PENTA_VTX_ATTR_COUNT + COLOR_OFFSET ]  = _color.x;
		_points[i * PENTA_VTX_ATTR_COUNT + COLOR_OFFSET+1] = _color.y;
		_points[i * PENTA_VTX_ATTR_COUNT + COLOR_OFFSET+2] = _color.z;
	}
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, PENTA_VTX_COUNT * PENTA_VTX_ATTR_COUNT * sizeof(_points), _points, GL_STATIC_DRAW);
}

void CPenta::draw()
{
	glUseProgram(_shaderProg);
	updateMatrix();
	glBindVertexArray(_vao);
	glDrawElements(GL_TRIANGLES, PENTA_INDEX_COUNT, GL_UNSIGNED_INT, 0);
}

void CPenta::setScale(glm::vec3 vScale)
{
	_scale = vScale;
	_bScale = true;
	_mxScale = glm::scale(glm::mat4(1.0f), _scale);
}

void CPenta::setPos(glm::vec3 vPt)
{
	_pos = vPt;
	_bPos = true;
	_mxPos = glm::translate(glm::mat4(1.0f), _pos);
}

void CPenta::setRotX(float angle)
{
	_rotX = glm::radians(angle);
	_rotAxis = _rotAxis | 1;
	_mxRotX = glm::rotate(glm::mat4(1.0f), _rotX, glm::vec3(1.0f, 0.0f, 0.0f));
	_mxRotation = _mxRotX;
	_bRotation = true;
}

void CPenta::setRotY(float angle)
{
	_rotY = glm::radians(angle);
	_rotAxis = _rotAxis | 2;
	_mxRotY = glm::rotate(glm::mat4(1.0f), _rotY, glm::vec3(0.0f, 1.0f, 0.0f));
	if( _rotAxis & 1 )_mxRotation = _mxRotY * _mxRotX;  // �� X �b������q
	else _mxRotation = _mxRotY ;
	_bRotation = true;
}

void CPenta::setRotZ(float angle)
{
	_rotZ = glm::radians(angle);
	_mxRotZ = glm::rotate(glm::mat4(1.0f), _rotZ, glm::vec3(0.0f, 0.0f, 1.0f));
	if ( _rotAxis == 1 ) _mxRotation = _mxRotZ * _mxRotX; // �u�� X �b������q
	else if ( _rotAxis == 2 ) _mxRotation = _mxRotZ * _mxRotY; // �u�� Y �b������q
	else if ( _rotAxis == 3 ) _mxRotation = _mxRotZ * _mxRotY * _mxRotX; // �� X�BY �b������q
	else _mxRotation = _mxRotZ;
	_bRotation = true;
}

void CPenta::updateMatrix()
{
	if (_bScale || _bPos || _bRotation)
	{
		_mxTRS = _mxPos * _mxRotation * _mxScale;
		if (_bOnTransform == true) _mxFinal = _mxTransform * _mxTRS;
		else _mxFinal = _mxTRS;
		_bScale = _bPos = _bRotation = false;
	}
	if (_bTransform) {
		_mxFinal = _mxTransform * _mxTRS;
		_bTransform = false;
	}
	// �p�h�Ӽҫ��ϥάۦP�� shader program,�]�C�@�Ӽҫ��� mxTRS �����P�A�ҥH�C��frame���n��s
	glUniformMatrix4fv(_modelMxLoc, 1, GL_FALSE, glm::value_ptr(_mxFinal));
}

void CPenta::setTransformMatrix(glm::mat4 mxMatrix)
{
	_bOnTransform = _bTransform = true;
	_mxTransform = mxMatrix;
}

glm::mat4 CPenta::getModelMatrix() { return _mxFinal; }

GLuint CPenta::getShaderProgram() { return _shaderProg; }

void CPenta::reset()
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