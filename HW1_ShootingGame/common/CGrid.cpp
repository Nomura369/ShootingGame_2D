#include "CGrid.h"

CGrid::CGrid(float width, float height, float cellSize)
{
    _gridWidth = width;
    _gridHeight = height;
    _cellSize = cellSize;

    _cols = (int)(width / cellSize);
    _rows = (int)(height / cellSize);
    _grids.resize(_rows * _cols);
}

void CGrid::insertObjects(CShape* obj) {
    int col = (obj->getPos().x) / _cellSize;
    int row = (obj->getPos().y) / _cellSize;
    if (col >= 0 && col < _cols && row >= 0 && row < _rows) {
        _grids[row * _cols + col].push_back(obj);
    }
}

vector<CShape*> CGrid::getNearbyObjects(CShape* obj) {
    vector<CShape*> nearbyObjects;

    int col = (obj->getPos().x) / _cellSize;
    int row = (obj->getPos().y) / _cellSize;

    // 檢查物體所在的格子及周圍格子
    for (int i = row - 1; i <= row + 1; ++i) {
        for (int j = col - 1; j <= col + 1; ++j) {
            if (i >= 0 && i < _rows && j >= 0 && j < _cols) {
                for (auto* obj : _grids[i * cols + j]) {
                    nearbyObjects.push_back(obj);
                }
            }
        }
    }
    return nearbyObjects;
}