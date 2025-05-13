#pragma once
#include <vector>
using namespace std;

#include "CShape.h"

// �w�q��u���O�A�ϥ��R�A�����޲z�I��
class CGrid {
public:
    static void initialize(int width, int height, int cellSize);
    static void insertObjects(CShape* obj);
    static void checkGridCollisions();
    static void reset(); // �M�ũҦ���l�̪�����
    //static vector<CShape*> getNearbyObjects(CShape* obj);

private:
    CGrid(); // �קK�Ыع���
    static int _gridWidth, _gridHeight, _cellSize;
    static int _rows, _cols;
    static vector<vector<CShape*>> _grids;  // �C�Ӯ�l���U������C��]�����G���}�C�^
};