#pragma warning(disable : 4996)
#include "DataCenter.h"
#include "Graphic.h"
#include "G_Windows.h"

#include <stdio.h>

//Singleton
DataCenter * DataCenter::sInstance = NULL;

DataCenter * DataCenter::GetInstance()
{
	if (sInstance == NULL)
	{
		sInstance = new DataCenter();
	}

	return sInstance;
}

void DataCenter::ReleaseInstance()
{
	delete sInstance;
	sInstance = NULL;
}

DataCenter::DataCenter()
{
	
}

DataCenter::~DataCenter()
{
	
}

void DataCenter::Inti()
{
	hr[0] = D3DXCreateSprite(Graphic::GetInstance()->d3dDevice, &sprite);
	hr[1] = D3DXCreateTextureFromFile(Graphic::GetInstance()->d3dDevice, "Resource/Map/TileSet.png", &tileSet);
	hr[2] = D3DXCreateTextureFromFile(Graphic::GetInstance()->d3dDevice, "Resource/Unit/Minion_Sheet.png", &unitSet);

	for (int i = 0; i < 3; i++)
	{
		if (FAILED(hr[i]))
		{
			PostQuitMessage(0);
		}
	}
}

void DataCenter::Release()
{
	sprite->Release();
	sprite = NULL;

	tileSet->Release();
	tileSet = NULL;

	unitSet->Release();
	unitSet = NULL;
}

void DataCenter::LoadData(std::string name)
{
	FILE *fp;
	fp = fopen(name.c_str(), "rb");

	/* If we can't open the map then exit */
	if (fp == NULL)
	{
		printf("Failed to open map %s\n", name);
		system("Pause");
		exit(1);
	}

	/* Read the data from the file into the map */
	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			fscanf(fp, "%d,", &DataCenter::GetInstance()->tileMap[y][x]); //map[][] is a 2D array
		}
		fscanf(fp, "\n");
	}

	fscanf(fp, "\n");

	//load path
	for (int y = 0; y < MAX_MAP_Y; y++)
	{
		for (int x = 0; x < MAX_MAP_X; x++)
		{
			fscanf(fp, "%d,", &DataCenter::GetInstance()->pathMap[y][x]); //map[][] is a 2D array
		}
		fscanf(fp, "\n");
	}

	/* Close the file afterwards */
	fclose(fp);
}
