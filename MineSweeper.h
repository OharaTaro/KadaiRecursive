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
	// 表示する数字	地雷の場合-1
	int getNum(int index);

	// マウスで選択している項目
	int getSelectIndex() const;

	// 指定したマスを開く
	bool open(int index);

private:

	std::vector<BlockData>	m_block;

};

