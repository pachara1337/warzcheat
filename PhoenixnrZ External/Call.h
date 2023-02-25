#pragma once

obj_Player* localPlayer = NULL;
#define AutoGamewold                    0                        // 0 ปิด 1 เปิด หาค่า clientgame gameworld auto    
int Gamewoldaoto = AutoGamewold;
vSendToHost pSendToHost;


static ObjectManager* GameWorld()
{
	ObjectManager* pGamePlus = (ObjectManager*)(*(DWORD*)((DWORD)hGameBase + pGameWorld_Adr));

	pGamePlus = (ObjectManager*)((DWORD)pGamePlus ^ pGameWorld_Xor);

	return pGamePlus; //pGame_Adr
}

static ClientGameLogic* pGetGame()
{
	ClientGameLogic* pGamePlus = (ClientGameLogic*)(*(DWORD*)((DWORD)hGameBase + pGame_Adr));

	pGamePlus = (ClientGameLogic*)((DWORD)pGamePlus ^ pGame_Xor);

	return pGamePlus; //pGameWorld_Adr
}


static tRender* Render1()
{
	return (tRender*)(*(DWORD*)((DWORD)hGameBase + dwRenderAddress));
}

void Engine()
{

	GetRender = (tRender)((DWORD)Render1);
	pRenderer = GetRender();

	if (Gamewoldaoto == 0)
	{
		while (pGame == 0)
		{
			GetGame = (tGetGame)((DWORD)pGetGame);
			pGame = GetGame();
			//_cprintf("pGame %p\n",pGame);
		}
	}

	if (Gamewoldaoto == 1)
	{
		// 75 ?? E8 ?? ?? ?? ?? 05
		DWORD pGetGame = 0;
		while (pGetGame == 0)
		{
			pGetGame = FindPattern(hGameBase, 0, (BYTE*)"\x75\x00\xE8\x00\x00\x00\x00\x05", "x?x????x", 3);
		}
		GetGame = (tGetGame)(*(DWORD*)pGetGame + pGetGame + 4);
		pGame = GetGame();

	}

	if (Gamewoldaoto == 0)
	{
		while (pGameWorld == 0)
		{
			GetGameWorld = (tGetGameWorld)((DWORD)GameWorld);
			pGameWorld = GetGameWorld();
		//	_cprintf("pGameWorld %p\n", pGameWorld);
		}




	}

	if (Gamewoldaoto == 1)
	{
		DWORD pGetGameWorld = 0;
		while (pGetGameWorld == 0)
		{
			pGetGameWorld = FindPattern(hGameBase, 0, (BYTE*)"\xE8\x00\x00\x00\x00\x05\x00\x00\x00\x00\x50", "x????x????x", 1); //find all server
		}
		pGetGameWorld = (*(DWORD*)pGetGameWorld + pGetGameWorld + 4);
		GetGameWorld = (tGetGameWorld)((DWORD)pGetGameWorld);
		pGameWorld = GetGameWorld();
	}

	//system("cls");


}