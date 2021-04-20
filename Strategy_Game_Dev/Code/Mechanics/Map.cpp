#include "Map.h"
#include "../Component/DataCenter.h"
#include "../Component/DInput.h"
#include "../Component/Graphic.h"

#include <stdio.h>

Map::Map()
{
	scrollTimer = 0;
}

Map::~Map()
{

}

void Map::Draw()
{
	DataCenter::GetInstance()->sprite->Begin(D3DXSPRITE_ALPHABLEND);

	//Draw the map 
	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			if (DataCenter::GetInstance()->tileMap[y][x] != 0)
			{
				//calculate the tile is at what row and col in the sprite
				tileSelected.y = DataCenter::GetInstance()->tileMap[y][x] / 12;
				tileSelected.x = DataCenter::GetInstance()->tileMap[y][x] % 12;

				tileRect.top = tileSelected.y * TILE_HEIGHT;

				tileRect.left = (tileSelected.x - 1) * TILE_WIDTH;

				tileRect.bottom = tileRect.top + TILE_HEIGHT;

				tileRect.right = tileRect.left + TILE_WIDTH;

				//render the tile at correct position

				pos.x = x * TILE_WIDTH;

				pos.y = y * TILE_HEIGHT;

				pos.z = 0.0f;

				if (pos.x + TILE_WIDTH > DataCenter::GetInstance()->screenPos.x &&
					pos.x < DataCenter::GetInstance()->screenPos.x + BUFFER_WIDTH &&
					pos.y + TILE_HEIGHT> DataCenter::GetInstance()->screenPos.y + 128 &&
					pos.y < DataCenter::GetInstance()->screenPos.y + BUFFER_HEIGHT)
				{
					DataCenter::GetInstance()->sprite->Draw(DataCenter::GetInstance()->tileSet, &tileRect, NULL,
						&D3DXVECTOR3(pos.x - DataCenter::GetInstance()->screenPos.x,
							pos.y - DataCenter::GetInstance()->screenPos.y,
							pos.z), D3DCOLOR_XRGB(255, 255, 255));
				}
			}
		}
	}

	DataCenter::GetInstance()->sprite->End();
}

void Map::MapScrolling()
{
	scrollTimer += 1.0f / 2;

	if (scrollTimer >= 1)
	{
		if (DInput::GetInstance()->diKeys[DIK_W])
		{
			DataCenter::GetInstance()->screenPos.y -= 64;
		}

		else if (DInput::GetInstance()->diKeys[DIK_S])
		{
			DataCenter::GetInstance()->screenPos.y += 64;
		}

		if (DInput::GetInstance()->diKeys[DIK_A])
		{
			DataCenter::GetInstance()->screenPos.x -= 64;
		}

		else if (DInput::GetInstance()->diKeys[DIK_D])
		{
			DataCenter::GetInstance()->screenPos.x += 64;
		}

		

		DataCenter::GetInstance()->screenPos.x = max(DataCenter::GetInstance()->screenPos.x, 0 - TILE_WIDTH);
		DataCenter::GetInstance()->screenPos.x = min(DataCenter::GetInstance()->screenPos.x, MAX_MAP_X * TILE_WIDTH - BUFFER_WIDTH + TILE_WIDTH);
		DataCenter::GetInstance()->screenPos.y = max(DataCenter::GetInstance()->screenPos.y, 0 - TILE_HEIGHT);
		DataCenter::GetInstance()->screenPos.y = min(DataCenter::GetInstance()->screenPos.y, MAX_MAP_Y * TILE_HEIGHT - BUFFER_HEIGHT + TILE_HEIGHT);
		
		//printf("%.2f,%.2f\n", DataCenter::GetInstance()->screenPos.x, DataCenter::GetInstance()->screenPos.y);
		
		scrollTimer = 0;
	}
}
