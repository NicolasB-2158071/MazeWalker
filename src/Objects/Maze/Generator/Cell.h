#pragma once

struct Cell
{
	bool wallLeft{ true };
	bool wallTop{ true };
	bool wallRight{ true };
	bool wallBottom{ true };

	bool visited{ false };
};