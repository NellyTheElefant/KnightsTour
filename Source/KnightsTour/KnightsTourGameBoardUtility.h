#pragma once

namespace GameBoardUtility
{
	const unsigned int DEFAULT_ROW_SIZE = 8;
	const unsigned int DEFAULT_COL_SIZE = 8;
	const float		   DEFAULT_TILE_SIZE = 400.0f;

	const char*		   TILE_MESH_PATH = "StaticMesh'/Game/Meshes/Floor_400x400.Floor_400x400'";

	enum class TILE_COLOUR
	{
		LIGHT,
		DARK,

		INVALID_COLOUR
	};

	enum class TILE_STATE
	{
		IDLE_LIGHT,
		IDLE_DARK,

		INVALID_STATE
	};
}

namespace SimpleMath
{
	inline bool IsEven(unsigned int x)
	{
		return (x % 2) == 0;
	}

	inline bool IsOdd(unsigned int x)
	{
		return !IsEven(x);
	}
}