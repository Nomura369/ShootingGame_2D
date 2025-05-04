#pragma once
#include <glm/glm.hpp>

// �w�q��u�y�����O�A�@����m����θI���������̾ڡ]Singleton pattern�^
class CGridCoord
{
private:
	static CGridCoord* instance;
	CGridCoord(); // �إ߮�u�y�а}�C
	glm::vec3* gridDots;

public:
	// �T�O�~�����o�ƻs�����O�����
	CGridCoord(CGridCoord& other) = delete;
	void operator = (const CGridCoord&) = delete;
	~CGridCoord();

	// ��������O���ߤ@��Ҫ��R�A���
	static CGridCoord* getInstance() {
		if (instance == nullptr) { // �p�G�٨S����ҴN�Ыؤ@��
			instance = new CGridCoord();
		}
		return instance;
	}
	
	glm::vec3* getGridDots(); // ���o��u�y�а}�C
	
};