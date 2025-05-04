#pragma once
#include <glm/glm.hpp>

// 定義格線座標類別，作為放置物件或碰撞偵測的依據（Singleton pattern）
class CGridCoord
{
private:
	static CGridCoord* instance;
	CGridCoord(); // 建立格線座標陣列
	glm::vec3* gridDots;

public:
	// 確保外部不得複製此類別的實例
	CGridCoord(CGridCoord& other) = delete;
	void operator = (const CGridCoord&) = delete;
	~CGridCoord();

	// 獲取該類別的唯一實例的靜態函數
	static CGridCoord* getInstance() {
		if (instance == nullptr) { // 如果還沒有實例就創建一個
			instance = new CGridCoord();
		}
		return instance;
	}
	
	glm::vec3* getGridDots(); // 取得格線座標陣列
	
};