#pragma once
#include <vector>
using namespace std;

#include "CShape.h"

// 定義格線類別，使用靜態成員管理碰撞
class CGrid {
public:
    static void initialize(int width, int height, int cellSize);
    static void insertObjects(CShape* obj);
    static void checkGridCollisions();
    static void reset(); // 清空所有格子裡的物件
    //static vector<CShape*> getNearbyObjects(CShape* obj);

private:
    CGrid(); // 避免創建實體
    static int _gridWidth, _gridHeight, _cellSize;
    static int _rows, _cols;
    static vector<vector<CShape*>> _grids;  // 每個格子底下的物件列表（類似二維陣列）
};