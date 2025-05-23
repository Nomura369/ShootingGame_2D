﻿/*
功能需求
(8%) 操控與背景部分 
    (1%) 滑鼠可以控制戰鬥機的左右移動 v
    (1%) 戰鬥機傭有防禦裝置，並以父子關係方式呈現 v
    (1%) 可以發射飛彈 v
    (3%) 能提供連續發射(LINKED LIST，自己撰寫，使用STL 2分) v
    (2%)  能產生有速度感的背景物件，或是其他裝飾性的物件 v
(11%) 敵人部分
    (2%) 有至少三種以上不同外形的敵人(不同的顏色)，基本的四方型不算在內 v
    (3%) 以物件導向的多型來控制所有的敵人 v
    (1%)  敵人可以不斷的產生，而且具有不同的顏色 v
    (1%)  敵人能隨機朝向玩家發射子彈攻擊 v
    (2%)  戰鬥機發射的子彈可以打到敵人，而且敵人會消失 v
    (2%)  有 BOSS 級的敵人，且會根據被攻擊的多寡至少三種不同的狀態(外型改變或攻擊方式)可以切換
(4%) (玩家部分)
    (2%)  能判斷玩家是否被打中 並做出合理的反應 v
    (2%)  玩家的船艦至少有三種狀態(外型改變)，且有提供玩家的船艦可改變狀態的機制 v
    (8%) 其他你覺得可以展示的技術，包含物理或是數學的運算
        (2%)提供階層式動態控制，並以時間為基礎進行動態的展示 v
        (2%)發射導向飛彈攻擊移動的 Boss
        敵人被打到有其他的效果 v
        戰鬥機被打到時有其他的效果 v
        背景除了速度感物件外，有其他的效果
        …
總分： 19 + 敵人和戰鬥機被打到的其他效果
(4%) 創意分數，老師的個人的主觀
*/

// Draw a  Circle with a radius of 0.8 unit
//#define GLM_ENABLE_EXPERIMENTAL 1

#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>

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
#include "common/CBulletManager.h"
#include "common/CGradient.h"
#include "common/CStar.h"
#include "common/CEnemy1.h"
#include "common/CEnemy2.h"
#include "common/CEnemy3.h"
#include "common/CEnemyManager.h"
#include "common/CAttack.h"
#include "common/CAttackManager.h"
#include "common/CGrid.h"
#include "common/CTriangle.h"
#include "common/CDeathEffectManager.h"

// 視窗大小
#define SCREEN_WIDTH  600
#define SCREEN_HEIGHT 800

#define SHIELD_NUM 3
#define STAR_NUM 100

Arcball g_arcball; // arcball 設定（不必更動）

/* ---------- 遊戲的狀態控制 ---------- */
bool g_bRotating = false; // 控制是否旋轉
bool g_bRunning = false; // 判斷遊戲為開始 or 暫停（與原本的 g_bMoving 差不多）
bool g_bShooting = false; // 玩家是否按下按鍵發射子彈
float sAngle = 0.0f; // 計算護盾的旋轉角度（每幀更新）
float enemyTimer = 0.0f; // 計算敵人生成的時間
float enemyIntervalTime = rand() % 3 + 2.0f; // 每個敵人的生成時間間隔（2.0f-4.0f 之間的整數秒）
int score; // 計算玩家得分

GLuint g_shaderProg; // Shader Program ID
GLuint flashShaderProg; // 專門用於閃爍效果的 Shader Program ID

// 投影矩陣
glm::mat4 g_viewMx = glm::mat4(1.0f);
glm::mat4 g_projMx = glm::mat4(1.0f);
GLfloat g_viewScale = 3.0f;
GLfloat g_viewScaleForY = 4.0f;

/* ---------- 圖形物件宣告 ---------- */
CPlayer g_player;
CShield g_shield[SHIELD_NUM];
CGradient gradient;
CStar star[STAR_NUM];

// Singleton Pattern
CBulletManager* CBulletManager::instance = nullptr;
CBulletManager* g_BMInstance = CBulletManager::getInstance(); 
CEnemyManager* CEnemyManager::instance = nullptr;
CEnemyManager* g_EMInstance = CEnemyManager::getInstance();

glm::mat4 g_mxPSDist[SHIELD_NUM]; // 玩家到護盾間的位移矩陣
glm::vec3 g_PSDist[SHIELD_NUM] = { // 各護盾與玩家的距離
    glm::vec3(1.0f, 0.0f, 0.0f), 
    glm::vec3(-0.5f, 0.8f, 0.0f),
    glm::vec3(-0.5f, -0.8f, 0.0f) 
};
glm::mat4 mxSRot; // 護盾的旋轉矩陣
glm::vec3 PMove; // 玩家的位移向量
glm::mat4 mxPMove; // 玩家的位移矩陣

//----------------------------------------------------------------------------
void loadScene(void)
{
    // getShader 函式可用於建立 shader program 或取得特定 shader program 的代表 ID 
    g_shaderProg = CShaderPool::instance().getShader("vshader21.glsl", "fshader21.glsl");

    /* ---------- 設定圖形物件資料 ---------- */
    g_player.setupVertexAttributes();
    g_player.setShaderID(g_shaderProg);
    for (int i = 0; i < SHIELD_NUM; i++) {
        g_shield[i].setupVertexAttributes();
        g_shield[i].setShaderID(g_shaderProg);
        g_shield[i].setColor(glm::vec3(0.0f, 0.4f, 0.5f));
        // 設定護盾一開始相對於玩家的位置
        g_shield[i].setPos(g_PSDist[i]);
        g_mxPSDist[i] = glm::translate(glm::mat4(1.0f), g_PSDist[i]);
        g_shield[i].setTransformMatrix(g_mxPSDist[i]);
    }
    gradient.setupVertexAttributes();
    gradient.setShaderID(g_shaderProg);
    gradient.setPos(glm::vec3(0.0f, -3.0f, 0.0f)); // 置於場景下半部
    for (int i = 0; i < STAR_NUM; i++) {
        star[i].setupVertexAttributes();
        star[i].setShaderID(g_shaderProg);
        star[i].setRandomPos();
        star[i].setRandomScale();
    }

    /* -------------------------------------- */

    GLint viewLoc = glGetUniformLocation(g_shaderProg, "mxView"); 	// 取得 MVP 變數的位置
    glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(g_viewMx));

    g_projMx = glm::ortho(-3.0f, 3.0f, -4.0f, 4.0f, -2.0f, 2.0f);
    GLint projLoc = glGetUniformLocation(g_shaderProg, "mxProj"); 	// 取得 MVP 變數的位置
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(g_projMx));
    glClearColor(0.2f, 0.1f, 0.4f, 1.0f); // 設定清除 back buffer 背景的顏色
}
//----------------------------------------------------------------------------

void render( void )
{
    glClear( GL_COLOR_BUFFER_BIT );			// clear the window
    gradient.draw();
    for (int i = 0; i < STAR_NUM; i++) star[i].draw();
    g_BMInstance->draw();
    g_player.draw();
    for(int i = 0; i < g_player.getLife(); i++) g_shield[i].draw();

    g_EMInstance->draw();
    CAttackManager::draw(); // 繪製所有敵人彈幕
    CDeathEffectManager::draw(); // 繪製敵人死亡特效
}
//----------------------------------------------------------------------------

void update(float dt)
{
    if (g_bRunning)
    {
        CGrid::reset(); // 重置上一幀格線中的物件配置

        g_player.update(dt);

        // 更新玩家的位移向量和矩陣
        mxPMove = g_player.getModelMatrix();
        PMove = glm::vec3(mxPMove[3].x, mxPMove[3].y, mxPMove[3].z);
        
        sAngle += 3.0f * dt;
        if (sAngle > 360.0f) sAngle -= 360.0f;
        // 讓護盾跟著玩家的戰鬥機（滑鼠）位移並旋轉
        mxSRot = glm::rotate(glm::mat4(1.0f), sAngle, glm::vec3(0.0f, 0.0f, 1.0f));
        for (int i = 0; i < SHIELD_NUM; i++) g_shield[i].setTransformMatrix(mxPMove * mxSRot);
        
        if (g_bShooting) {
            g_BMInstance->instantiate(g_shaderProg, PMove); // 按下左鍵生成（發射）子彈
            g_bShooting = false;
        }
        g_BMInstance->update(dt);

        // 設定星星的移動
        for (int i = 0; i < STAR_NUM; i++) star[i].update(dt);

        // 根據隨機的時間間隔不斷生成敵人
        enemyTimer += dt;
        if (enemyTimer >= enemyIntervalTime) {
            g_EMInstance->instantiate(g_shaderProg, PMove);
            
            enemyTimer = 0.0f;
            if(score < 150) enemyIntervalTime = rand() % 3 + 2.0f; // 2.0f-4.0f 之間的整數秒
            else if (score < 300) enemyIntervalTime = rand() % 3 + 1.0f; // 1.0f-3.0f 之間的整數秒
            else enemyIntervalTime = rand() % 3 + 0.5f; // 0.5f-2.5f 之間的整數秒
        }
        g_EMInstance->update(dt);
        CAttackManager::update(dt); // 更新所有敵人彈幕
        CDeathEffectManager::update(dt); // 更新所有的敵人死亡特效

        CGrid::checkGridCollisions(); // 處理碰撞
        // 處理已失效的物件
        g_BMInstance->handleDeath();
        g_EMInstance->handleDeath();
        CDeathEffectManager::handleInActive();
        CAttackManager::handleDeath();

        score = g_EMInstance->getScore();
        if (!g_player.getIsActive()) {
            g_bRunning = false;
            std::cout << "遊戲結束，你死翹翹了" << endl;
            std::cout << "得分：" << score << "（擊殺數：" << score / 10 << "）" << endl;
        }
    }
}

void releaseAll()
{


}

int main() {
    srand((unsigned)time(NULL)); // 設定亂數種子（會在物件中使用到）

    // ------- 檢查與建立視窗  ---------------  
    if (!glfwInit()) {
        std::cerr << "Failed to initialize GLFW" << std::endl;
        return -1;
    }

    // 設定 OpenGL 版本與 Core Profile
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    //glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //只啟用 OpenGL 3.3 Core Profile（不包含舊版 OpenGL 功能）
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE); // 禁止視窗大小改變

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
    CGrid::initialize(SCREEN_WIDTH, SCREEN_HEIGHT, 1); // 建立碰撞格線
    std::cout << "請按空白鍵開始遊戲" << endl;
    std::cout << "用滑鼠操控戰鬥機移動，按左鍵發射子彈" << endl;
    std::cout << "總共有三條命，打敗一個敵人獲得十分" << endl;
    std::cout << "打完 boss 或玩家死亡即遊戲結束，加油" << endl << endl;

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