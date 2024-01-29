#include "MineSweeper.h"
#include "game.h"

#include "DxLib.h"
#include <random>

namespace
{
	constexpr int kBlockSize = 16;

	constexpr int kBlockNumX = 80;
	constexpr int kBlockNumY = 45;
	constexpr int kBlockNum = kBlockNumX * kBlockNumY;

	constexpr int kMineNum = 512;
}

MineSweeper::MineSweeper()
{
}

MineSweeper::~MineSweeper()
{
}

void MineSweeper::create(int seed)
{
	m_block.clear();

	for (int i = 0; i < kBlockNum; i++)
	{
		BlockData data;
		data.isMine = (i < kMineNum);
		data.isOpen = false;
		m_block.push_back(data);
	}
	std::random_device seed_gen;
	std::mt19937 engine(seed_gen());
	std::shuffle(m_block.begin(), m_block.end(), engine);
}

void MineSweeper::update()
{
	int selectIndex = getSelectIndex();

	if (selectIndex >= 0)
	{
		if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0)
		{
			LONGLONG start = GetNowHiPerformanceCount();

			// open前にする処理がある場合ここに書くこと(処理時間に含むようにすること)


			if (open(selectIndex))
			{
				// openに掛かった時間を表示する
				printfDx("openTime:%d\n", GetNowHiPerformanceCount() - start);
			}
		}
	}

	// デバッグ機能	全て開いていない状態にする
	if ((GetMouseInput() & MOUSE_INPUT_RIGHT) != 0)
	{
		for (auto& data : m_block)
		{
			data.isOpen = false;
		}
	}
}

void MineSweeper::draw()
{
	int selectIndex = getSelectIndex();

	for (int i = 0; i < kBlockNum; i++)
	{
		int posX = (i % kBlockNumX) * kBlockSize;
		int posY = (i / kBlockNumX) * kBlockSize;

		if (!m_block[i].isOpen)
		{
			DrawBox(posX, posY, posX + kBlockSize, posY + kBlockSize, 0x808080, true);
		}

		if (i == selectIndex)
		{
			DrawBox(posX, posY, posX + kBlockSize, posY + kBlockSize, 0xffff00, false);
			DrawBox(posX + 1, posY + 1, posX + kBlockSize - 1, posY + kBlockSize - 1, 0xffff00, false);
			DrawBox(posX + 2, posY + 2, posX + kBlockSize - 2, posY + kBlockSize - 2, 0xffff00, false);
		}
		else
		{
			DrawBox(posX, posY, posX + kBlockSize, posY + kBlockSize, 0xffffff, false);
		}
		
		if (m_block[i].isMine)
		{
			DrawString(posX, posY, "雷", 0xff0000);
		}
		else
		{
			DrawFormatString(posX+4, posY, 0xffffff, "%d", getNum(i));
		}
	}
}

int MineSweeper::getNum(int index)
{
	if (m_block[index].isMine)	return -1;

	int result = 0;
	// 8方向の地雷の数を数える
	int x = index % kBlockNumX;
	int y = index / kBlockNumX;

	for (int ofsX = -1; ofsX <= 1; ofsX++)
	{
		for (int ofsY = -1; ofsY <= 1; ofsY++)
		{
			// 自身は数に含めない
			if (ofsX == 0 && ofsY == 0)	continue;

			// 端っこチェック
			if (x == 0 && ofsX == -1)	continue;
			if (y == 0 && ofsY == -1)	continue;
			if (x == (kBlockNumX - 1) && ofsX == 1)	continue;
			if (y == (kBlockNumY - 1) && ofsY == 1)	continue;

			int checkIndex = index + ofsX + ofsY * kBlockNumX;

			if (m_block[checkIndex].isMine)	result++;
		}
	}

	return result;
}

int MineSweeper::getSelectIndex() const
{
	int mouseX = 0;
	int mouseY = 0;
	GetMousePoint(&mouseX, &mouseY);
	if (mouseX < 0)	return -1;
	if (mouseY < 0)	return -1;
	if (mouseX > Game::kScreenWidth)	return -1;
	if (mouseY > Game::kScreenHeight)	return -1;


	int selectIndex = mouseX / kBlockSize + mouseY / kBlockSize * kBlockNumX;

	return selectIndex;
}

bool MineSweeper::open(int index)
{
	// 既に開かれている
	if (m_block[index].isOpen)	return false;

	m_block[index].isOpen = true;
	return true;
}
