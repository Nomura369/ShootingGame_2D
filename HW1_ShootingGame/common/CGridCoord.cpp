#include "CGridCoord.h"

#define GRID_H_DOT 9
#define GRID_V_DOT 7
#define GRID_DOT_DIST 1.0f

CGridCoord::CGridCoord() {
	int gridDotsNum = GRID_H_DOT * GRID_V_DOT;
	int i = 0;

	gridDots = new glm::vec3[gridDotsNum];
	for (float x = -3.0f; x <= 3.0f; x += GRID_DOT_DIST) {
		for (float y = -4.0f; y <= 4.0f; y += GRID_DOT_DIST) {
			gridDots[i] = glm::vec3(x, y, 0.0f);
			i++;
		}
		if (i == gridDotsNum) break;
	}
}

CGridCoord::~CGridCoord() {

}

glm::vec3* CGridCoord::getGridDots() {
	return gridDots;
}