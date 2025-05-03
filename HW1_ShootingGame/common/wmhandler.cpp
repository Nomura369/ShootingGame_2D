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

// 滑鼠按鈕按下後 callback function(回呼函式) ---------------
void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods) {
    double xpos, ypos;
    glfwGetCursorPos(window, &xpos, &ypos);
    // Arcball* arcball = static_cast<Arcball*>(glfwGetWindowUserPointer(window));
    g_arcball.onMouseButton(button, action, xpos, ypos);
    //std::cout << "button = " << button << "action = " << action << "mods = " << mods << std::endl;

    if (g_bRunning) {
        if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) 
        {
            g_bShooting = true; // 按下左鍵發射子彈
            g_bShot = true; // 觸發子彈發射的瞬間
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

// 滑鼠在指定視窗上移動時的 callback function (回呼函式)
void cursorPosCallback(GLFWwindow* window, double xpos, double ypos) {
    int width, height;
    glfwGetWindowSize(window, &width, &height);
    // Arcball* arcball = static_cast<Arcball*>(glfwGetWindowUserPointer(window));
    g_arcball.onCursorMove(xpos, ypos, width, height);
    //std::cout << "x = " << xpos << "y = " << ypos << std::endl;
    
    if (g_bRunning) // 若按下空白鍵讓遊戲開始（玩家可用滑鼠控制移動），再次按下則暫停
    {
       // 以滑鼠距離(0,0)的距離作為每一個模型的位移
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
//        // 以滑鼠距離(0,0)的距離作為每一個模型的位移
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
//        // 以滑鼠距離(0,0)的距離作為每一個模型的位移
//        GLfloat dx = g_viewScale * ((float)xpos - width / 2.0f) / (width / 2.0f);
//        GLfloat dy = -g_viewScale * ((float)ypos - height / 2.0f) / (height / 2.0f);
//        float xAngle = 3.1415916f*dx/4.0f; // dx -4 到 +4 代表角度  -PI 到  PI 度
//        float yAngle = 3.1415916f*dy/2.0f; // dy -4 到 +4 代表角度 -2PI 到 2PI 度
//        mxGRot = glm::rotate(glm::mat4(1.0f), xAngle, glm::vec3(0.0f, 0.0f, 1.0f));
//        mxBRot = glm::rotate(glm::mat4(1.0f), yAngle, glm::vec3(0.0f, 0.0f, 1.0f));
//
//        for (i = 0; i < 4; i++) g_GQuad[i].setTransformMatrix(mxGRot);
//        for (i = 0; i < 4; i++) g_BQuad[i].setTransformMatrix(mxGRot*g_mxGDist[i]*mxBRot);
//    }
//#elif EXAMPLE == 5
//    if (g_bMoving)
//    {
//        // 以滑鼠距離(0,0)的距離作為每一個模型的位移
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
// 當視窗大小改變的 callback function
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

// 當鍵盤按鍵按下時的 callback function (回呼函式)
// key : GLFW_KEY_0、 GLFW_KEY_a、GLFW_KEY_ESCAPE、GLFW_KEY_SPACE
//       完整定義在這邊 https://www.glfw.org/docs/latest/group__keys.html
// action : 
//          GLFW_PRESS：按鍵被按下。
//          GLFW_RELEASE：按鍵被釋放。
//          GLFW_REPEAT：按鍵被重複觸發（長按時會觸發多次）
// mods : 
//          GLFW_MOD_SHIFT：Shift 鍵被按下。
//          GLFW_MOD_CONTROL：Ctrl 鍵被按下。
//          GLFW_MOD_ALT：Alt 鍵被按下。
//          GLFW_MOD_SUPER：Windows 鍵或 Command 鍵被按下。
//          GLFW_MOD_CAPS_LOCK：Caps Lock 鍵被啟用。
//          GLFW_MOD_NUM_LOCK：Num Lock 鍵被啟用。
// 
//  注意：1. 一個按鍵按下到放開會產生兩次 keyCallback，
//           根據功能需求判斷是按下或是放掉去執行對應的功能
//        2. 使用 glfw 英文字母沒有分大小寫，都是傳回大寫的 ASCII 編碼
//           搭配檢查左右 shift 鍵是否按下是大寫還是小寫(假設 caps 鍵沒有被按下)
//       
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
    switch (key)
    {
        case GLFW_KEY_ESCAPE:
            if (action == GLFW_PRESS) { glfwSetWindowShouldClose(window, true); }
            break;

        case GLFW_KEY_SPACE: // 按下空白鍵讓遊戲開始 or 暫停
            if (action == GLFW_PRESS) { 
                g_bRunning = !g_bRunning;
            }
            break;
        default: // 針對英文字母大小寫進行處理
            if (action == GLFW_PRESS || action == GLFW_REPEAT) {
                // 檢查 Shift 鍵(左右兩邊各一個)是否被按下
                bool isShiftPressed = (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) ||
                                      (glfwGetKey(window, GLFW_KEY_RIGHT_SHIFT) == GLFW_PRESS);
                // 判斷字母鍵的大小寫，預設使用鍵盤是沒有按下 CAPS 鍵
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