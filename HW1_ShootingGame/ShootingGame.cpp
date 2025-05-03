// Draw a  Circle with a radius of 0.8 unit
//#define GLM_ENABLE_EXPERIMENTAL 1

#include <iostream>
#include <fstream>
#include <sstream>

#include <glew/include/GL/glew.h>
#include <glfw/include/GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
//#include <glm/gtx/string_cast.hpp>

#include "common/initshader.h"
#include "common/arcball.h"
#include "common/wmhandler.h"
#include "common/CShaderPool.h"
#include "common/CPlayer.h"
#include "common/CShield.h"
#include "common/CBullet.h"

// 視窗大小
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800

#define SHIELD_NUM 3

Arcball g_arcball; // arcball 設定（不必更動）

/* ---------- 遊戲的狀態控制 ---------- */
bool g_bRotating = false; // 控制是否旋轉
//bool g_bMoving = false;
bool g_bRunning = false; // 判斷遊戲為開始 or 暫停（與原本的 g_bMoving 差不多）
bool g_bShooting = false; // 玩家是否按下按鍵發射子彈
bool g_bShot = false; // 記錄子彈被發射的瞬間
float sAngle = 0.0f; // 計算護盾的旋轉角度（每幀更新）
float bulletY = 0.0f; // 子彈的 Y 軸位移量

GLuint g_shaderProg; // Shader Program ID

// 投影矩陣
glm::mat4 g_viewMx = glm::mat4(1.0f);
glm::mat4 g_projMx = glm::mat4(1.0f);
GLfloat g_viewScale = 4.0f;

/* ---------- 圖形物件宣告 ---------- */
CPlayer g_player;
CShield g_shield[3];
CBullet g_bullet;

glm::mat4 g_mxPSDist[SHIELD_NUM]; // 玩家到護盾間的位移矩陣
glm::vec3  g_PSDist[SHIELD_NUM] = { // 各護盾與玩家的距離
    glm::vec3(1.0f, 0.0f, 0.0f), 
    glm::vec3(-0.5f, 0.8f, 0.0f),
    glm::vec3(-0.5f, -0.8f, 0.0f) 
};
glm::mat4 mxSRot; // 護盾的旋轉矩陣
glm::vec3 g_PMove; // 玩家的位移向量
glm::mat4 g_mxPMove; // 玩家的位移矩陣
glm::mat4 mxBMove; // 子彈的位移矩陣

//----------------------------------------------------------------------------
void loadScene(void)
{
    // getShader 函式可用於建立 shader program 或取得特定 shader program 的代表 ID 
    g_shaderProg = CShaderPool::instance().getShader("vshader21.glsl", "fshader21.glsl");

    /* ---------- 設定圖形物件資料 ---------- */
    g_player.setupVertexAttributes();
    g_player.setShaderID(g_shaderProg);
    
    for (int i = 0; i < 3; i++) {
        g_shield[i].setupVertexAttributes();
        g_shield[i].setShaderID(g_shaderProg);
        g_shield[i].setColor(glm::vec3(0.0f, 0.4f, 0.5f));
        // 設定護盾一開始相對於玩家的位置
        g_shield[i].setPos(g_PSDist[i]);
        g_mxPSDist[i] = glm::translate(glm::mat4(1.0f), g_PSDist[i]);
        g_shield[i].setTransformMatrix(g_mxPSDist[i]);
    }

    g_bullet.setupVertexAttributes();
    g_bullet.setShaderID(g_shaderProg);
    g_bullet.setScale(glm::vec3(0.9f, 0.9f, 0.9f));

    /* -------------------------------------- */

    GLint viewLoc = glGetUniformLocation(g_shaderProg, "mxView"); 	// 取得 MVP 變數的位置
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(g_viewMx));

    g_projMx = glm::ortho(-3.0f, 3.0f, -4.0f, 4.0f, -2.0f, 2.0f);
    GLint projLoc = glGetUniformLocation(g_shaderProg, "mxProj"); 	// 取得 MVP 變數的位置
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(g_projMx));
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // 設定清除 back buffer 背景的顏色
}
//----------------------------------------------------------------------------

void render( void )
{
    glClear( GL_COLOR_BUFFER_BIT );			// clear the window
    g_bullet.draw();
    g_player.draw();
    for(int i = 0; i < 3; i++) g_shield[i].draw();
}
//----------------------------------------------------------------------------

float g_angle = 0.0f;
void update(float dt)
{
    if (g_bRunning)
    {
        sAngle += 3.0f * dt;
        if (sAngle > 360.0f) sAngle -= 360.0f;
        // 讓護盾跟著玩家的戰鬥機（滑鼠）位移並旋轉
        mxSRot = glm::rotate(glm::mat4(1.0f), sAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        for (int i = 0; i < 3; i++) g_shield[i].setTransformMatrix(g_mxPMove * mxSRot);
        
        float maxY = 10.0f; // 將子彈射到螢幕外面
        if (g_bShooting) {
            static const float x = g_PMove.x;
            static const float z = g_PMove.z;
            bulletY += 5.0f * dt; // 位移速度
            if (g_bullet.getPos().y > maxY) g_bShooting = false;
            mxBMove = glm::translate(glm::mat4(1.0f), glm::vec3(x, bulletY, z));
            g_bullet.setTransformMatrix(mxBMove);
        }
        else { // 發射前跟著戰鬥機（滑鼠）移動
            g_bullet.setTransformMatrix(g_mxPMove);
        }
    }
}

void releaseAll()
{


}

int main() {
    // ------- 檢查與建立視窗  ---------------  
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 設定 OpenGL 版本與 Core Profile
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //只啟用 OpenGL 3.3 Core Profile（不包含舊版 OpenGL 功能）
    //glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 禁止視窗大小改變

    // 建立 OpenGL 視窗與該視窗執行時所需的的狀態、資源和環境(context 上下文)
    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Shoot! ", nullptr, nullptr);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    // 設定將這個視窗的資源(OpenGL 的圖形上下文）與當前執行緒綁定，讓該執行緒能夠操作該視窗的資源
    glfwMakeContextCurrent(window);

    // 設定視窗大小, 這樣 OpenGL 才能知道如何將視窗的內容繪製到正確的位置
    // 基本上寬與高設定成視窗的寬與高即可
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

    if (glewInit() != GLEW_OK) {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }
    // ---------------------------------------

    // 設定相關事件的 callback 函式，以便事件發生時，能呼叫對應的函式
    glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);// 視窗大小被改變時
    glfwSetKeyCallback(window, keyCallback);                        // 有鍵盤的按鍵被按下時
    glfwSetMouseButtonCallback(window, mouseButtonCallback);        // 有滑鼠的按鍵被按下時
    glfwSetCursorPosCallback(window, cursorPosCallback);            // 滑鼠在指定的視窗上面移動時

    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN); // 隱藏鼠標

    // 呼叫 loadScene() 建立與載入 GPU 進行描繪的幾何資料 
    loadScene();

    float lastTime = (float)glfwGetTime();
    while (!glfwWindowShouldClose(window)) {
        float currentTime = (float)glfwGetTime();
        float deltaTime = currentTime - lastTime; // 計算前一個 frame 到目前為止經過的時間
        lastTime = currentTime;
        update(deltaTime);      // 呼叫 update 函式，並將 deltaTime 傳入，讓所有動態物件根據時間更新相關內容
        render();
        glfwSwapBuffers(window);
        glfwPollEvents();
    }
    releaseAll(); // 程式結束前釋放所有的資源
    glfwTerminate();
    return 0;
}