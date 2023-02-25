#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <d3d9.h>
#include <d3dx9.h> 
#include "Menu2.h"
#include <vector>
using namespace std;

LPD3DXFONT tFont;
static ID3DXLine* pLine;

void cMenu::PostReset(LPDIRECT3DDEVICE9 pDevice)
{
	if (tFont == NULL) D3DXCreateFontA(pDevice, 16, 0, FW_BOLD, 1, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, ANTIALIASED_QUALITY, DEFAULT_PITCH | FF_DONTCARE, "Prompt", &tFont);
	if (pLine == NULL) D3DXCreateLine(pDevice, &pLine);
}

void cMenu::PreReset(LPDIRECT3DDEVICE9 pDevice)
{
	if (tFont)
	{
		tFont->Release();
		tFont = NULL;
		tFont = FALSE;
	}
	tFont = NULL;
}

void cMenu::Init()
{
	if (!INIT) {
		X = 25; //25
		Y = 15; //15
		WIDTH = 270;
		I_OFS = 30;
		S_OFS = WIDTH - 50;
		T_SPC = 16;
		F_SPC = 16;
		I_SPC = 20;
		I_CUR = 0;
		SHOW = true;
		INIT = true;
	}
}



int cMenu::nofields(char* str)
{
	char* ptr;
	int no;
	for (no = 1; (ptr = strchr(str, (char)'|')) != NULL; no++)str = ptr + 1;
	return no;
}

void cMenu::getfield(char* str, char* dst, int no)
{
	char* ptr;
	int  i;
	for (i = 1; (ptr = strchr(str, (char)'|')) != NULL; i++)
	{
		if (i == no) break;
		str = ptr + 1;
	}
	if (ptr)
	{
		i = (int)(ptr - str);
		strncpy(dst, str, i);
		dst[i] = 0;
	}
	else
		strcpy(dst, str);
}

void cMenu::FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void cMenu::DrawPoint(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB((int)x, (int)y, (int)w, (int)h, color, pDevice);
}

void cMenu::DrawLine(float x, float y, float x2, float y2, float width, DWORD color)
{
	D3DXVECTOR2 vLine[2];
	pLine->SetWidth(width);
	pLine->SetAntialias(false);
	pLine->SetGLLines(true);
	vLine[0].x = x;
	vLine[0].y = y;
	vLine[1].x = x2;
	vLine[1].y = y2;
	pLine->Begin();
	pLine->Draw(vLine, 2, color);
	pLine->End();
}

void cMenu::DrawBox(int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	struct Vertex
	{
		float x, y, z, ht;
		DWORD Color;
	}
	V[4] = { {x,y + h, 0.0f, 1.0f, Color}, {x,y, 0.0f, 1.0f, Color},{x + w,y + h, 0.0f, 1.0f, Color},{x + w,y, 0.0f, 1.0f, Color} };
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(0);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, V, sizeof(Vertex));
	return;
}

void cMenu::DrawBorder(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice)
{
	DrawBox(x, y - 1, w, s, Color, pDevice);
	DrawBox(x - 1, y, s, h, Color, pDevice);
	DrawBox((x + w), y, s, h, Color, pDevice);
	DrawBox(x, (y + h), w, s, Color, pDevice);
	return;
}

void cMenu::DrawString(int x, int y, DWORD color, const char* fmt, ...)
{
	RECT FontPos = { x, y, x + 120, y + 16 };
	char buf[1024] = { '\0' };
	va_list va_alist;
	va_start(va_alist, fmt);
	vsprintf(buf, fmt, va_alist);
	va_end(va_alist);
	tFont->DrawText(NULL, buf, -1, &FontPos, DT_NOCLIP, color);
}

void cMenu::Dwarzc1(char* String, int x, int y, D3DCOLOR color) {

	DrawString(x - 1, y, D3DCOLOR_XRGB(255, 0, 0), String);
	DrawString(x + 1, y, D3DCOLOR_XRGB(255, 0, 0), String);
	DrawString(x, y - 1, D3DCOLOR_XRGB(255, 0, 0), String);
	DrawString(x, y + 1, D3DCOLOR_XRGB(255, 0, 0), String);

	DrawString(x, y, color, String);
}

void cMenu::additem(char* title, int type, int* var, char* states)
{
	strcpy(items[NO].title, title);
	getfield(states, items[NO].state, *var + 1);
	items[NO].type = type;
	items[NO].max = nofields(states);
	items[NO].val = var;
	NO++;
}

void cMenu::aitem(char* title, int* var, char* states)
{
	additem(title, T_ITEM, var, states);
}

void cMenu::ShowMenu(LPDIRECT3DDEVICE9 pDevice)
{
	int	Btnl = GetAsyncKeyState(VK_LBUTTON) & 1;
	int	Btnr = GetAsyncKeyState(VK_RBUTTON) & 1;
	int	left = GetAsyncKeyState(VK_LEFT) & 1;
	int	right = GetAsyncKeyState(VK_RIGHT) & 1;
	int	up = GetAsyncKeyState(VK_UP) & 1;
	int	down = GetAsyncKeyState(VK_DOWN) & 1;
	Init();
	if (GetAsyncKeyState(VK_F1) & 1) SHOW = (!SHOW); //ปรับปุ่มเปิด/ปิดเมนู
	//if (GetAsyncKeyState(VK_F10) & 1) SHOW = (!SHOW);
	if (SHOW) {
		//- Move Menu - Ctrl
		/*DWORD EvenColor; //เปิด
		GetCursorPos(&mpos);
		ScreenToClient(GetForegroundWindow(),&mpos);
		if(GetAsyncKeyState(VK_LCONTROL)) {
		if((mpos.x-15, mpos.y-15, WIDTH+5, T_SPC+10)) {
		EvenColor = BEVEN;
		X = (mpos.x-268/2); //ปรับความกว้างเมนู 268/2
		Y = (mpos.y-5); //ปรับรอบข้างเมนู 10
		}} else {EvenColor = MBOX;}  //เปิดดิ*/
		//- Draw Menu && NO*I_SPC = Auto Draw
		DrawBorder(X, Y + 8, WIDTH + 5, T_SPC + 10, 1, MBOX, pDevice); //10
		DrawBox(X, Y + 8, WIDTH + 5, T_SPC + 10, MBOX, pDevice); //10
		DrawBorder(X, MC_MSY + 10, WIDTH + 5, (25 * I_SPC) + 3, 1, MBOX, pDevice); //ปรับความกว้างของเมนู
		DrawBox(X, MC_MSY + 10, WIDTH + 5, (25 * I_SPC) + 2, MBORDER, pDevice); //ปรับความกว้างของเมนู
		DrawBox(X, MC_MSY + 10 + (25 * I_SPC) + 3, WIDTH + 5, 1, MBOX, pDevice); //แถบสี่เหลี่ยมข้างล่างสุด
		DrawBorder(X, MC_MSY + 10 + (25 * I_SPC) + 3, WIDTH + 5, 1, 1, MBOX, pDevice); //แถบสี่เหลี่ยมข้างล่างสุด

		//- Text-Font
		//DrawString(MC_FCTR(X, MC_MAXX)-70, Y+14, PINK, "กดเปิด F1 II WARZSIRIUSZ II"); //PINK
		Dwarzc1("[Release] OFF/ON Menu F1", MC_FCTR(X, MC_MAXX) - 70, Y + 14, PINK); //PINK

		//DrawString(MC_FCTR(X, MC_MAXX)-70, MC_MSY+10+(20*I_SPC)+7, CRADIT, "กด Q แสดง/ซ่อน เมนู"); 
		NO = 0;
		//aitem("เปิดเช็คหลังกำแพง", &Optmin.Hack13, "ปิด|เปิด");


			aitem("กันถ่ายจอ", &Optmin.THEN, "ปิด|เปิด");
			aitem("แสดงชื่อ & แคลน", &Optmin.Hack4, "ปิด|เปิด");
			aitem("กรอบ", &Optmin.Hack2, "ปิด|เปิด");
			aitem("โครงกระดูก", &Optmin.Hack5, "ปิด|เปิด");
			aitem("เลือด", &Optmin.Hack1, "ปิด|เปิด");
			aitem("ล็อคเป้า", &Optmin.Hack7, "ปิด|ซ้าย|ขวา");
			aitem("ตำแหน่งล็อค", &Optmin.Hack16, "ปิด|หัว|ตัว");
		//	aitem("เช็คหลังกำแพง", &Optmin.Hack9, "ปิด|เปิด");
			aitem("เป้ากลางจอ", &Optmin.Hack13, "ปิด|เปิด");
			


			aitem("ลดดีด & ลดกระจาย", &Optmin.Hack70, "ปิด|เปิด");
			aitem("ปั้มยาไม่ดีเลย์", &Optmin.Hack7000, "ปิด|เปิด");
			aitem("เก็บของเร็ว [E]", &Optmin.Hack144, "ปิด|เปิด");
			aitem("วิงทะลุ [V]", &Optmin.Hack145, "ปิด|เปิด");
			aitem("ดิส 1 วิ [G]", &Optmin.Hack11445, "ปิด|เปิด");
			
		/*if (Optmin.THEN == 1)
		{
			aitem("TH/ENG", &Optmin.THEN, "TH|ENG");
			aitem("Name", &Optmin.Hack5, "OFF|ON");
			aitem("Box 3D", &Optmin.Hack1, "OFF|ON");
			aitem("Skeleton", &Optmin.Hack6, "OFF|ON");
			aitem("Health", &Optmin.Hack4, "OFF|ON");
			aitem("Aimbot", &Optmin.Hack7, "OFF|LBUTTON|RBUTTON");
			aitem("SelectyourAimType", &Optmin.Hack16, "OFF|Head|Chest");
			aitem("ShowTarget", &Optmin.Hack15, "OFF|ON");
			aitem("Respawn0Sec[F3]", &Optmin.Hack9, "OFF|ON");
			aitem("Noclip[V]", &Optmin.Hack8, "OFF|ON");
			aitem("Disconect[F2]", &Optmin.Hack10, "OFF|ON");
			aitem("Heal2Sec", &Optmin.Hack12, "OFF|ON");
			aitem("Crosshair", &Optmin.Hack11, "OFF|ON");
			aitem("NoRecoil", &Optmin.Hack70, "OFF|ON");
			aitem("NoSpread", &Optmin.Hack71, "OFF|ON");
			aitem("JumpThrough", &Optmin.Hack35, "OFF|ON");
			aitem("InstancePickup[E]", &Optmin.Hack36, "OFF|ON");
			aitem("Fastpickup[E]", &Optmin.Hack37, "OFF|ON");
			aitem("Reload", &Optmin.NoReload, "OFF|ON");
			aitem("Fastgun", &Optmin.speedmode, "OFF|ON");
		}*/

		for (int no = 0; no < NO; no++)
		{
			D3DCOLOR TextMin;
			D3DCOLOR TextOpt;
			TextMin = (*(items[no].val) > 0) ? WHITE : WHITE;
			TextOpt = (*(items[no].val) > 0) ? GREEN : RED;
			if (items[no].type == T_CAT)
				TextMin = RED;
			if (I_CUR == no) {
				DrawBox(X + 1, MC_ITEMY(no) + 11, WIDTH + 3, I_SPC, MEVEN, pDevice);
				TextMin = ORANGE;
			}
			if (mpos.x > X && mpos.x<MC_MAXX && mpos.y>MC_ITEMY(no) && mpos.y < MC_ITEMY(no) + I_SPC) {
				DrawBox(X + 1, MC_ITEMY(no) + 11, WIDTH + 3, I_SPC, MEVEN, pDevice);
				TextMin = ORANGE;
				I_CUR = no;
			}
			if (items[no].type == T_CAT) {
				TextOpt = RED;
				DrawString(X + I_OFS, MC_ITEMY(no) + 14, TextMin, items[no].title);
			}
			else {
				DrawString(X + I_OFS, MC_ITEMY(no) + 14, TextMin, items[no].title);
			}
			DrawString(X + S_OFS, MC_ITEMY(no) + 14, TextOpt, items[no].state);
		}

		int mno = 999;
		if (mpos.x > X && mpos.x < MC_MAXX && mpos.y<MC_ITEMY(NO) && mpos.y>Y)
			mno = ((mpos.y - T_SPC) > Y) ? ((mpos.y - Y - T_SPC - (T_SPC / 2)) / I_SPC) : (999);
		if (mno != 999 && Btnr && (*items[mno].val) > 0)
		{
			(*items[mno].val) -= 1;
		}
		if (mno != 999 && Btnl && (*items[mno].val) < (items[mno].max - 1))
		{
			(*items[mno].val) += 1;
		}

		if (left && (*items[I_CUR].val) > 0)
		{
			(*items[I_CUR].val) -= 1;
		}
		if (right && (*items[I_CUR].val) < (items[I_CUR].max - 1))
		{
			(*items[I_CUR].val) += 1;
		}
		if (up) {
			do {
				I_CUR = (I_CUR == 0) ? (NO - 1) : (I_CUR - 1);
			} while (items[I_CUR].type == T_TEXT);
		}
		if (down || items[I_CUR].type == T_TEXT) {
			do {
				I_CUR = (I_CUR + 1) % NO;
			} while (items[I_CUR].type == T_TEXT);
		}
		if (I_CUR > NO)I_CUR = NO - 1;
	}
}
