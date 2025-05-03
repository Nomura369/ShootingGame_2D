#pragma once
#include "CBullet.h"

// 定義子彈管理器類別，主要利用鏈結串列控管所有子彈（Singleton pattern）
class CBulletManager
{
private:
	static CBulletManager* instance;
	CBulletManager(); // 建立鏈結串列

public:
	// 確保外部不得複製此類別的實例
	CBulletManager(CBulletManager& other) = delete;
	void operator = (const CBulletManager&) = delete;

	// 獲取該類別的唯一實例的靜態函數
	static CBulletManager* getInstance() {
		if (instance == nullptr) { // 如果還沒有實例就創建一個
			instance = new CBulletManager();
		}
		return instance;
	}
	void instantiate(GLuint shaderProg, glm::vec3 playerMove); // 生成子彈
	void draw(); // 一次畫出鏈結串列中現有的全部子彈
	void update(float dt); // 一次更新全部子彈的移動狀態
	~CBulletManager(); // 釋放鏈結串列

protected:
	typedef struct TNode {
		CBullet* bullet;
		struct TNode* Link;
	} NODE, * PNODE; // 子彈節點宣告
	//int count; // 記錄目前節點的數量
	//CBullet* in; // 記錄正要放進去的子彈資料
	PNODE pHead, pTail, pGet;
};