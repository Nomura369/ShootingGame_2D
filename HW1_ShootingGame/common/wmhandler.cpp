#include <iostream>

#include "wmhandler.h"
#include "arcball.h"
#include "CQuad.h"
#include "Quad.h"
#include "CTriangle.h"
#include "Triangle.h"
#include "CPenta.h"
#include "CPlayer.h"
#include "CShield.h"

extern Arcball g_arcball;

extern GLfloat g_viewScale;
extern bool g_bRotating;
//extern bool g_bMoving;
extern bool g_bRunning;
extern bool g_bShooting;
extern bool g_bShot;

extern CPlayer g_player;
extern CShield g_shield[3];
extern glm::vec3 g_PMove;
extern glm::mat4 g_mxPMove;

// �ƹ����s���U�� callback function(�^�I�禡) ---------------
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // Arcball* arcball = static_cast<Arcball*>(glfwGetWindowUserPointer(window));
    g_arcball.onMouseButton(button, action, xpos, ypos);
    //std::cout << "button = " << button << "action = " << action << "mods = " << mods << std::endl;

    if (g_bRunning) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
        {
            g_bShooting = true; // ���U����o�g�l�u
            g_bShot = true; // Ĳ�o�l�u�o�g������
        }  
    }
    
//#if EXAMPLE == 2
//    if ( g_bMoving )
//    {
//		if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//		{
//			g_bRotating = ! g_bRotating;
//		}
//    }
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//    {
//        g_penta.reset();
//    }
//#elif EXAMPLE == 3
//	if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//	{
//		g_bRotating = !g_bRotating;
//	}
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//    {
//        g_tri.reset(); g_tri.setPos(glm::vec3(-2.0f, 2.0f, 0.0f));
//        g_quad.reset(); g_quad.setPos(glm::vec3(2.0f, 2.0f, 0.0f));
//        g_penta[0].reset(); g_penta[0].setPos(glm::vec3(-2.0f, -2.0f, 0.0f));
//        g_penta[1].reset(); g_penta[1].setPos(glm::vec3(2.0f, -2.0f, 0.0f));
//    }
//#elif EXAMPLE == 4
//
//#elif EXAMPLE == 5
//    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
//    {
//        g_bRotating = !g_bRotating;
//    }
//    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS)
//    {
//        g_tri.reset(); g_tri.setPos(glm::vec3(-2.0f, 2.0f, 0.0f));
//        /*g_quad.reset(); g_quad.setPos(glm::vec3(2.0f, 2.0f, 0.0f));
//        g_penta[0].reset(); g_penta[0].setPos(glm::vec3(-2.0f, -2.0f, 0.0f));
//        g_penta[1].reset(); g_penta[1].setPos(glm::vec3(2.0f, -2.0f, 0.0f));*/
//    }
//#endif
}
// ---------------------------------------------------------------------------------------

// �ƹ��b���w�����W���ʮɪ� callback function (�^�I�禡)
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    // Arcball* arcball = static_cast<Arcball*>(glfwGetWindowUserPointer(window));
    g_arcball.onCursorMove(xpos, ypos, width, height);
    //std::cout << "x = " << xpos << "y = " << ypos << std::endl;
    
    if (g_bRunning) // �Y���U�ť������C���}�l�]���a�i�ηƹ�����ʡ^�A�A�����U�h�Ȱ�
    {
       // �H�ƹ��Z��(0,0)���Z���@���C�@�Ӽҫ����첾
       GLfloat dx = g_viewScale * ((float)xpos - width / 2.0f) / (width / 2.0f);
       GLfloat dy = -g_viewScale * ((float)ypos - height / 2.0f) / (height / 2.0f);
        
       g_PMove = glm::vec3(dx, dy, 0.0f);
       glm::mat4 mxMove = glm::translate(glm::mat4(1.0f), g_PMove);
       g_player.setTransformMatrix(mxMove);
       g_mxPMove = mxMove;
    }
        
//#if EXAMPLE == 2
//    if (g_bMoving) {
//        float px =  g_viewScale * ((float)xpos - width / 2) / (width / 2);
//        float py = -g_viewScale * ((float)ypos - height / 2) / (height / 2);
//        g_penta.setPos(glm::vec3(px, py, 0));
//    }
//#elif EXAMPLE == 3
//    if (g_bMoving)
//    {
//        // �H�ƹ��Z��(0,0)���Z���@���C�@�Ӽҫ����첾
//		GLfloat dx = g_viewScale * ((float)xpos - width / 2.0f) / (width / 2.0f);
//		GLfloat dy = -g_viewScale * ((float)ypos - height / 2.0f) / (height / 2.0f);
//
//		glm::mat4 mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, 0.0f));
//        g_tri.setTransformMatrix(mxMove);
//		g_quad.setTransformMatrix(mxMove);
//		g_penta[0].setTransformMatrix(mxMove);
//		g_penta[1].setTransformMatrix(mxMove);
//    }
//#elif EXAMPLE == 4
//    glm::mat4 mxGRot, mxBRot;
//    int i;
//    if (g_bMoving)
//    {
//        // �H�ƹ��Z��(0,0)���Z���@���C�@�Ӽҫ����첾
//        GLfloat dx = g_viewScale * ((float)xpos - width / 2.0f) / (width / 2.0f);
//        GLfloat dy = -g_viewScale * ((float)ypos - height / 2.0f) / (height / 2.0f);
//        float xAngle = 3.1415916f*dx/4.0f; // dx -4 �� +4 �N����  -PI ��  PI ��
//        float yAngle = 3.1415916f*dy/2.0f; // dy -4 �� +4 �N���� -2PI �� 2PI ��
//        mxGRot = glm::rotate(glm::mat4(1.0f), xAngle, glm::vec3(0.0f, 0.0f, 1.0f));
//        mxBRot = glm::rotate(glm::mat4(1.0f), yAngle, glm::vec3(0.0f, 0.0f, 1.0f));
//
//        for (i = 0; i < 4; i++) g_GQuad[i].setTransformMatrix(mxGRot);
//        for (i = 0; i < 4; i++) g_BQuad[i].setTransformMatrix(mxGRot*g_mxGDist[i]*mxBRot);
//    }
//#elif EXAMPLE == 5
//    if (g_bMoving)
//    {
//        // �H�ƹ��Z��(0,0)���Z���@���C�@�Ӽҫ����첾
//        GLfloat dx = g_viewScale * ((float)xpos - width / 2.0f) / (width / 2.0f);
//        GLfloat dy = -g_viewScale * ((float)ypos - height / 2.0f) / (height / 2.0f);
//
//        glm::mat4 mxMove = glm::translate(glm::mat4(1.0f), glm::vec3(dx, dy, 0.0f));
//        g_tri.setTransformMatrix(mxMove);
//        /*g_quad.setTransformMatrix(mxMove);
//        g_penta[0].setTransformMatrix(mxMove);
//        g_penta[1].setTransformMatrix(mxMove);*/
//    }
//#endif
}
// ---------------------------------------------------------------------------------------
// 
// ������j�p���ܪ� callback function
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// ����L������U�ɪ� callback function (�^�I�禡)
// key : GLFW_KEY_0�B GLFW_KEY_a�BGLFW_KEY_ESCAPE�BGLFW_KEY_SPACE
//       ����w�q�b�o�� https://www.glfw.org/docs/latest/group__keys.html
// action : 
//          GLFW_PRESS�G����Q���U�C
//          GLFW_RELEASE�G����Q����C
//          GLFW_REPEAT�G����Q����Ĳ�o�]�����ɷ|Ĳ�o�h���^
// mods : 
//          GLFW_MOD_SHIFT�GShift ��Q���U�C
//          GLFW_MOD_CONTROL�GCtrl ��Q���U�C
//          GLFW_MOD_ALT�GAlt ��Q���U�C
//          GLFW_MOD_SUPER�GWindows ��� Command ��Q���U�C
//          GLFW_MOD_CAPS_LOCK�GCaps Lock ��Q�ҥΡC
//          GLFW_MOD_NUM_LOCK�GNum Lock ��Q�ҥΡC
// 
//  �`�N�G1. �@�ӫ�����U���}�|���ͨ⦸ keyCallback�A
//           �ھڥ\��ݨD�P�_�O���U�άO�񱼥h����������\��
//        2. �ϥ� glfw �^��r���S�����j�p�g�A���O�Ǧ^�j�g�� ASCII �s�X
//           �f�t�ˬd���k shift ��O�_���U�O�j�g�٬O�p�g(���] caps ��S���Q���U)
//       
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
            break;

        case GLFW_KEY_SPACE: // ���U�ť������C���}�l or �Ȱ�
            if (action == GLFW_PRESS) { 
                g_bRunning = !g_bRunning;
            }
            break;
        default: // �w��^��r���j�p�g�i��B�z
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                // �ˬd Shift ��(���k����U�@��)�O�_�Q���U
                bool isShiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ||
                                      (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
                // �P�_�r���䪺�j�p�g�A�w�]�ϥ���L�O�S�����U CAPS ��
                if (key >= GLFW_KEY_A && key <= GLFW_KEY_Z) {
                    char letter = (isShiftPressed) ? ('A' + (key - GLFW_KEY_A)) : ('a' + (key - GLFW_KEY_A));
                    //std::cout << "key = " << letter << std::endl;
//#if EXAMPLE == 1    
//                    switch (letter) {
//                        case 'R':
//                        case 'r':
//                            g_arcball.reset();
//                            break;
//						case 'S':
//						case 's':
//                            g_quad->setScale(glm::vec3(0.25f, 0.25f, 1.0f));
//                            break;
//                        case 'L':
//                        case 'l':
//                            g_quad->setScale(glm::vec3(1.2f, 1.2f, 1.0f));
//                            break;
//                        case 'X':
//                        case 'x':
//                            g_quad->setRotX(45.0f);
//                            break;
//                        case 'Y':
//                        case 'y':
//                            g_quad->setRotY(45.0f);
//                            break;
//                        case 'Z':
//                        case 'z':
//                            g_quad->setRotZ(45.0f);
//                            break;
//                    }
//#elif EXAMPLE == 2
//                    switch (letter) {
//                        case 'S':
//                        case 's':
//                            g_penta.setScale(glm::vec3(0.2f, 0.2f, 1.0f));
//                            break;
//                        case 'L':
//                        case 'l':
//                            g_penta.setScale(glm::vec3(1.2f, 1.2f, 1.0f));
//                            break;
//                    }
//#elif EXAMPLE == 3
//                    switch (letter) {
//                    case 'S':
//                    case 's':
//                        g_tri.setScale(glm::vec3(0.25f, 0.25f, 1.0f));
//                        break;
//                    case 'L':
//                    case 'l':
//                        g_tri.setScale(glm::vec3(1.2f, 1.2f, 1.0f));
//                        break;
//                    }
//#elif EXAMPLE == 4
//
//#elif EXAMPLE == 5
//                    switch (letter) {
//                    case 'S':
//                    case 's':
//                        g_tri.setScale(glm::vec3(0.25f, 0.25f, 1.0f));
//                        break;
//                    case 'L':
//                    case 'l':
//                        g_tri.setScale(glm::vec3(1.2f, 1.2f, 1.0f));
//                        break;
//                    }
//
//#endif
                }   
            }
        break;
    }
}