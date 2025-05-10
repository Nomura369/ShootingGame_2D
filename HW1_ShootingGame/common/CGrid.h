#pragma once
#include <vector>
using namespace std;

#include "CShape.h"

class CGrid {
public:
    CGrid(float width, float height, float cellSize);
    void insertObjects(CShape* obj);

    vector<CShape*> getNearbyObjects(CShape* obj);

private:
    float _gridWidth, _gridHeight, _cellSize;
    int _rows, _cols;
    vector<vector<CShape*>> _grids;  // 每個格子底下的物體列表（類似二維陣列）
};