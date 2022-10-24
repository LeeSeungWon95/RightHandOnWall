#include "pch.h"
#include "Player.h"
#include "Board.h"
#include <stack>

void Player::Init(Board* board)
{
	_pos = board->GetEnterPos();
	_board = board;

	Pos pos = _pos;

	_path.clear();
	_path.push_back(pos);

	Pos dest = board->GetExitPos();

	Pos front[4] =
	{
		Pos {-1, 0},	// UP
		Pos {0, -1},	// LEFT
		Pos {1, 0},		// DOWN
		Pos {0, 1}		// RIGHT
	};


	// �������� ������ ������ ����
	while (pos != dest)
	{
		// ���� �ٶ󺸴� ���� �������� ���������� �� �� �ִ��� Ȯ��
		int NewDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[NewDir]))
		{
			// ���������� 90�� ȸ��
			_dir = NewDir;

			// ������ �� �� ����
			pos += front[_dir];
			_path.push_back(pos);
		}
		// ���� �ٶ󺸴� ���� �������� ���� �� �� �ִ��� Ȯ��
		else if (CanGo(pos + front[_dir]))
		{
			// ������ �� �� ����
			pos += front[_dir];
			_path.push_back(pos);
		}
		// ���� �������� 90�� ȸ��
		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	// ������ ����ؼ� ���ʿ��� �� Ž�� ����
	stack<Pos> s;
	for (int i = 0; i < _path.size() - 1; ++i)
	{
		if (s.empty() == false && s.top() == _path[i + 1])
		{
			s.pop();
		}
		else
		{
			s.push(_path[i]);
		}
	}
	s.push(_path.back());

	vector<Pos> temp_path;
	while (s.empty() == false)
	{
		temp_path.push_back(s.top());
		s.pop();
	}
	std::reverse(temp_path.begin(), temp_path.end());
	_path = temp_path;
}

void Player::Update(uint64 deltaTick)
{
	if (_pathIndex >= _path.size())
	{
		return;
	}
	_sumTick += deltaTick;
	if (_sumTick >= MOVE_TICK)
	{
		_sumTick = 0;

		_pos = _path[_pathIndex];
		_pathIndex++;
	}
}

bool Player::CanGo(Pos pos)
{
	TileType tileType = _board->GetTileType(pos);
	return tileType == TileType::EMPTY;
}