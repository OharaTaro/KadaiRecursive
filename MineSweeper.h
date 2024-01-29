#pragma once
#include <vector>

class MineSweeper
{
public:
	MineSweeper();
	virtual ~MineSweeper();

	void create(int seed = -1);

	void update();
	void draw();

private:
	struct BlockData
	{
		bool isMine = false;
		bool isOpen = false;
	};

private:
	// �\�����鐔��	�n���̏ꍇ-1
	int getNum(int index);

	// �}�E�X�őI�����Ă��鍀��
	int getSelectIndex() const;

	// �w�肵���}�X���J��
	bool open(int index);

private:

	std::vector<BlockData>	m_block;

};

