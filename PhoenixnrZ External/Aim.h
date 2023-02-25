#pragma once

float GetHypotenuseFromCenter(const D3DXVECTOR3& Point, LPDIRECT3DDEVICE9 pDevice)
{
	float PositionX = 0;
	float PositionY = 0;
	float ScreenCenterX, ScreenCenterY;
	D3DXVECTOR3 Screen;

	HWND hWindow = Overlay::GetInstance()->targetWindow;

	ScreenCenterX = GetWindowSize(hWindow).x / 2;
	ScreenCenterY = GetWindowSize(hWindow).y / 2;

	if (ProjectToScreen(Point, &Screen, pDevice) == FALSE)
		return 9999.0f;

	PositionX = Screen.x > ScreenCenterX ? Screen.x - ScreenCenterX : ScreenCenterX - Screen.x;
	PositionY = Screen.y > ScreenCenterY ? Screen.y - ScreenCenterY : ScreenCenterY - Screen.y;

	return sqrt(PositionX * PositionX + PositionY * PositionY);
}

DWORD GetAimKey()
{
	switch (Function[25])
	{
	case 0:
		return 0x02;
		break;
	case 1:
		return 0x01;
		break;
	}
}

int GetAimHeight()
{
	switch (Function[26])
	{
	case 0:
		return Bip01_Head;
		break;
	case 1:
		return Bip01_Spine2;
		break;
	}
}



void AimHead(D3DXVECTOR3 HeadPos, LPDIRECT3DDEVICE9 pDevice)
{

	D3DXVECTOR3 HeadPos2;

	HWND hWindow = Overlay::GetInstance()->targetWindow;

	DWORD ScreenCenterX = GetWindowSize(hWindow).x / 2;
	DWORD ScreenCenterY = GetWindowSize(hWindow).y / 2;


	POINT Target;

	if (HeadPos.x != -1 && HeadPos.y != -1)
	{


		if ((DWORD)HeadPos.x > (ScreenCenterX)) {
			Target.x = HeadPos.x - (ScreenCenterX);
			Target.x /= 2;
			Target.x = +Target.x;
		}
		if ((DWORD)HeadPos.x < (ScreenCenterX)) {
			Target.x = (ScreenCenterX - HeadPos.x);
			Target.x /= 2;
			Target.x = -Target.x;
		}
		if ((DWORD)HeadPos.x == (ScreenCenterX)) {
			Target.x = -1;
		}
		if ((DWORD)HeadPos.y > (ScreenCenterY)) {
			Target.y = HeadPos.y - (ScreenCenterY);
			Target.y /= 2;
			Target.y = +Target.y;
		}
		if ((DWORD)HeadPos.y < (ScreenCenterY)) {
			Target.y = (ScreenCenterY - HeadPos.y);
			Target.y /= 2;
			Target.y = -Target.y;
		}
		if ((DWORD)HeadPos.y == (ScreenCenterY)) {
			Target.y = -1;
		}

		if (Optmin.Hack7 == 1)
		{
			mouse_event(MOUSEEVENTF_MOVE, Target.x, Target.y, NULL, NULL);
		}

		if (Optmin.Hack7 == 2)
		{
			mouse_event(MOUSEEVENTF_MOVE, Target.x, Target.y, NULL, NULL);
		}
	}


}

//
//
//void AimAtPos(float x, float y, LPDIRECT3DDEVICE9 pDevice)
//{
//	HWND hWindow = Overlay::GetInstance()->targetWindow;
//
//	DWORD ScreenCenterX = GetWindowSize(hWindow).x / 2;
//	DWORD ScreenCenterY = GetWindowSize(hWindow).y / 2;
//
//	float AimSpeed;
//	float TargetX = 0;
//	float TargetY = 0;
//
//	if (Function[27] == 0)
//		AimSpeed = 3;
//	else if (Function[27] == 1)
//		AimSpeed = 2;
//
//	if (x != 0)
//	{
//		if (x > ScreenCenterX)
//		{
//			TargetX = -(ScreenCenterX - x);
//			TargetX /= AimSpeed;
//			if (TargetX + ScreenCenterX > ScreenCenterX * 2) TargetX = 0;
//		}
//
//		if (x < ScreenCenterX)
//		{
//			TargetX = x - ScreenCenterX;
//			TargetX /= AimSpeed;
//			if (TargetX + ScreenCenterX < 0) TargetX = 0;
//		}
//	}
//	if (y != 0)
//	{
//		if (y > ScreenCenterX)
//		{
//			TargetY = -(ScreenCenterY - y);
//			TargetY /= AimSpeed;
//			if (TargetY + ScreenCenterY > ScreenCenterY * 2) TargetY = 0;
//		}
//
//		if (y < ScreenCenterX)
//		{
//			TargetY = y - ScreenCenterY;
//			TargetY /= AimSpeed;
//			if (TargetY + ScreenCenterY < 0) TargetY = 0;
//		}
//	}
//
//	if (x && y && GetAsyncKeyState(GetAimKey()))
//	{
//		mouse_event(MOUSEEVENTF_MOVE, (DWORD)TargetX, (DWORD)TargetY, NULL, NULL);
//	}
//}

obj_Player* GetTargetByCrosshairz()
{
	obj_Player* pEntity = NULL;
	int fAngleLength;

	fAngleLength = 3000;




	if (VALID(pGame))
	{
		obj_Player* g_pLocal = (obj_Player*)pGame->GetLocalPlayer();
		if (VALID(g_pLocal))
		{
			for (int i = 0; i < pGameWorld->getMaxObjects(); i++)
			{
				GameObject* object = pGameWorld->getObject(i);

				if (object == NULL || object == (GameObject*)localPlayer)
					continue;

				if (object && object->getObjType() == OBJTYPE_HUMAN || object && object->getObjType() == OBJTYPE_HUMAN + 0x01)
				{

					obj_Player* pTarget = (obj_Player*)object;

					if (VALID(pTarget))
					{

						D3DXVECTOR3 lPos, vHead;

						pGetBonePos(pTarget, Bip01_Head, &vHead);
						//pGetBonePos(pTarget, เปลียนแกน(), &vHead);

						float AngleLength = GetHypotenuseFromCenter(vHead, Overlay::GetInstance()->pDevice);

						if (AngleLength < fAngleLength) // Nearer than last nearest enemy
						{
							pEntity = pTarget;
							fAngleLength = AngleLength;
						}
					}

				}
				//	object = pGameWorld->GetNextObject(object);
			}

		}

	}
	return pEntity;
}

void AimbotPlayer()
{
	obj_Player* pEntity = NULL;
	if (pGame)
	{
		obj_Player* g_pLocal = (obj_Player*)pGame->GetLocalPlayer();
		if (VALID(g_pLocal))
		{
			pEntity = GetTargetByCrosshairz();

			if (!pEntity)
				return;

			if (!pEntity->isAlive())
				return;

			char aim[220];
			D3DXVECTOR3 lPos, vHead;
		//	NeckVec = GetBonePos(pEntity, 6);

			D3DXVECTOR3 headVec;
			pGetBonePos(pEntity, Bip01_Head, &headVec);
			D3DXVECTOR3 NeckVec;
			pGetBonePos(pEntity, Bip01_Neck, &NeckVec);

			D3DXVECTOR3 screenHead;
			ProjectToScreen(headVec, &screenHead, Overlay::GetInstance()->pDevice);
			D3DXVECTOR3 screenNeck;
			ProjectToScreen(NeckVec, &screenNeck, Overlay::GetInstance()->pDevice);

			//DWORD CheckAim = *(byte*)((DWORD)hGameBase + CheckAimbot);
			D3DCOLOR aimbot;
			D3DXVECTOR3 AimHead100;

		
			if (Optmin.Hack16 == 1)
			{
				AimHead100 = screenHead + ((screenHead - screenNeck) * 1.1);
			}

			if (Optmin.Hack16 == 2)
			{
				pGetBonePos(pEntity, Bip01_Spine2, &vHead);
			}

			//if (setting.aimtype == )
			//{
			//	pGetBonePos(pEntity, randomAim(Bip01_Head, Bip01_Spine2), &vHead);
			//}


			if (Optmin.Hack1488 && pEntity->IsPlayerTeam())
				return;

			if (Optmin.Hack1489 && pEntity->IsPlayerClan())
				return;

			D3DXVECTOR3 screenPos;
			ProjectToScreen(vHead, &screenPos, Overlay::GetInstance()->pDevice);



			D3DXVECTOR2 vAngles;
			if (pEntity != g_pLocal)
			{



				

				if (Optmin.Hack7 == 1)
		
						if (GetAsyncKeyState(0x01)) //0x02 ขวา
						{
						
								switch (Optmin.Hack16) {
								case 1:
									if (Optmin.Hack16 == 1)
									{
										AimHead(AimHead100, Overlay::GetInstance()->pDevice);
									}
									//AimHead(screenPos, pRenderer->pD3DDevice);

									if (Optmin.Hack16 == 2)
									{
										AimHead(screenPos, Overlay::GetInstance()->pDevice);
									}

								}

						}

				if (Optmin.Hack7 == 2)
					if (GetAsyncKeyState(0x02)) //0x02 ขวา
					{
					
							switch (Optmin.Hack16) {
							case 1:
								if (Optmin.Hack16 == 1)
								{
									AimHead(AimHead100, Overlay::GetInstance()->pDevice);
								}
								//AimHead(screenPos, pRenderer->pD3DDevice);

								if (Optmin.Hack16 == 2)
								{
									AimHead(screenPos, Overlay::GetInstance()->pDevice);
								}

							}

					}
			}
		}
	}
}


//
//obj_Player* GetTargetByCrosshair()
//{
//	obj_Player* pEntity = NULL;
//	float fAngleLength = FLT_MAX;
//
//	if (VALID(pGame))
//	{
//		for (int i = 0; i < pGameWorld->getMaxObjects(); i++)
//		{
//			GameObject* object = pGameWorld->getObject(i);
//
//			if (object && object->getObjType() == OBJTYPE_HUMAN || object && object->getObjType() == OBJTYPE_HUMAN1)
//			{
//				obj_Player* pTarget = (obj_Player*)object;
//
//				if (pTarget == localPlayer)
//					continue;
//
//				if (VALID(pTarget))
//				{
//					D3DXVECTOR3 lPos, vHead;
//
//					pGetBonePos(pTarget, GetAimHeight(), &vHead);
//
//					float AngleLength = GetHypotenuseFromCenter(vHead, Overlay::GetInstance()->pDevice);
//
//					if (AngleLength < fAngleLength) // Nearer than last nearest enemy
//					{
//						pEntity = pTarget;
//						fAngleLength = AngleLength;
//					}
//				}
//			}
//		}
//	}
//	return pEntity;
//}

//obj_Player* GetNextTarget(void)
//{
//	return GetTargetByCrosshair();
//}
//
//void AimBone()
//{
//	obj_Player* pEntity = NULL;
//	pEntity = GetNextTarget();
//
//	if (!pEntity)
//		return;
//
//	if (!pEntity->isAlive())
//		return;
//
	//if (Function[57] && pEntity->IsPlayerTeam())
	//	return;

	//if (Function[58] && pEntity->IsPlayerClan())
	//	return;
//
//	D3DXVECTOR3 lPos, vHead;
//
//	pGetBonePos(pEntity, GetAimHeight(), &vHead);
//
//	D3DXVECTOR3 screenPos;
//
//	if (ProjectToScreen(vHead, &screenPos, Overlay::GetInstance()->pDevice))
//	{
//	
//		{
//			if (Function[20])
//			{
//				AimAtPos(screenPos.x, screenPos.y, Overlay::GetInstance()->pDevice);
//
//				if (Function[23])
//				{
//					PrintText(screenPos.x, screenPos.y, Yellow, "lock");
//				}
//			}
//		}
//	}
//}
