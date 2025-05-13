#include "CGrid.h"

// ��l���R�A�����ܼ�
int CGrid::_gridWidth;
int CGrid::_gridHeight;
int CGrid::_cellSize;
int CGrid::_rows;
int CGrid::_cols;
vector<vector<CShape*>> CGrid::_grids;

void CGrid::initialize(int width, int height, int cellSize)
{
    _gridWidth = width;
    _gridHeight = height;
    _cellSize = cellSize;

    _cols = width / cellSize;
    _rows = height / cellSize;
    _grids.resize(_rows * _cols);
}

void CGrid::insertObjects(CShape* obj) {
    int col = (int)(obj->getPos().x) / _cellSize;
    int row = (int)(obj->getPos().y) / _cellSize;

    if (col < 0) col = 0;
    if (col >= _cols) col = _cols - 1;
    if (row < 0) row = 0;
    if (row >= _rows) row = _rows - 1;

    _grids[row * _cols + col].push_back(obj);
}

void CGrid::checkGridCollisions() {
    for (int row = 0; row < _rows; ++row) {
        for (int col = 0; col < _cols; ++col) {
            int baseIndex = row * _cols + col;
            auto& baseCell = _grids[baseIndex];

            // �M�� baseCell ���Ҧ�����
            for (size_t i = 0; i < baseCell.size(); ++i) {
                CShape* objA = baseCell[i];

                // �ˬd���椤�᭱������A�קK�����ˬd
                for (size_t j = i + 1; j < baseCell.size(); ++j) {
                    CShape* objB = baseCell[j];
                    
                    bool isValid = !objA || !objA->getIsActive() || !objB || !objB->getIsActive();
                    if (isValid) continue;
                    else if (objA->checkCollision(objB)) {
                        objA->onCollision(objB);
                        objB->onCollision(objA);
                    }
                }

                // �ˬd 8 �ӾF��
                for (int dr = -1; dr <= 1; ++dr) {
                    for (int dc = -1; dc <= 1; ++dc) {
                        // ���L�ۤv�]�w�g�B�z�L�^
                        if (dr == 0 && dc == 0) continue;

                        int neighborRow = row + dr;
                        int neighborCol = col + dc;

                        if (neighborRow >= 0 && neighborRow < _rows &&
                            neighborCol >= 0 && neighborCol < _cols) {

                            int neighborIndex = neighborRow * _cols + neighborCol;
                            auto& neighborCell = _grids[neighborIndex];

                            for (CShape* objB : neighborCell) {
                                bool isValid = !objA || !objA->getIsActive() || !objB || !objB->getIsActive();
                                if (isValid) continue;
                                else if (objA->checkCollision(objB)) {
                                    objA->onCollision(objB);
                                    objB->onCollision(objA);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
}

void CGrid::reset() {
    for (auto& cell : _grids) {
        cell.clear();
    }
}