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


	// 목적지에 도착할 때까지 실행
	while (pos != dest)
	{
		// 현재 바라보는 방향 기준으로 오른쪽으로 갈 수 있는지 확인
		int NewDir = (_dir - 1 + DIR_COUNT) % DIR_COUNT;
		if (CanGo(pos + front[NewDir]))
		{
			// 오른쪽으로 90도 회전
			_dir = NewDir;

			// 앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		// 현재 바라보는 방향 기준으로 전진 할 수 있는지 확인
		else if (CanGo(pos + front[_dir]))
		{
			// 앞으로 한 보 전진
			pos += front[_dir];
			_path.push_back(pos);
		}
		// 왼쪽 방향으로 90도 회전
		else
		{
			_dir = (_dir + 1) % DIR_COUNT;
		}
	}

	// 스택을 사용해서 불필요한 길 탐색 제거
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