#include "Level.h"
#include "../Component/DataCenter.h"
#include "../Component/DInput.h"

void Level::Init()
{
	DataCenter::GetInstance()->Inti();
	DataCenter::GetInstance()->screenPos.x = 0;
	DataCenter::GetInstance()->screenPos.y = 0;

	DataCenter::GetInstance()->LoadData("Data/OriginMap.txt");
}

void Level::Update()
{
	
}

void Level::FixUpdate()
{
	map.MapScrolling();
}

void Level::Draw()
{
	map.Draw();
}

void Level::Release()
{
	DataCenter::GetInstance()->Release();
}