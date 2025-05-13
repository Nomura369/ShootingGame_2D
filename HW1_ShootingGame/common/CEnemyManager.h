#pragma once
#include <list>
using namespace std;

#include "CEnemy1.h"
#include "CEnemy2.h"
#include "CEnemy3.h"

// 定義敵人管理器類別（Singleton pattern）
class CEnemyManager
{
private:
	static CEnemyManager* instance;
	CEnemyManager();

	list<CShape*> _enemyList; // （繼承真是一件神奇的事）
	int _enemyType;
	int _enemyColor;
	float _randomX;
	
public:
	// 確保外部不得複製此類別的實例
	CEnemyManager(CEnemyManager& other) = delete;
	void operator = (const CEnemyManager&) = delete;

	// 獲取該類別的唯一實例的靜態函數
	static CEnemyManager* getInstance() {
		if (instance == nullptr) { // 如果還沒有實例就創建一個
			instance = new CEnemyManager();
		}
		return instance;
	}
	void instantiate(GLuint shaderProg, glm::vec3 playerMove); // 生成並設定敵人
	void draw();
	void update(float dt);
	void handleDeath(); // 一次處理 _isActive == false 的子彈
	~CEnemyManager();

};