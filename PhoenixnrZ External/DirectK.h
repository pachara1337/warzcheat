#pragma once

POINT cPos;
bool Janela[8][2];//MoverJanela
POINT ClickPosicao;//MoverJanela

D3DCOLOR black = D3DCOLOR_XRGB(0, 0, 0);
D3DCOLOR gray = D3DCOLOR_XRGB(175, 175, 175);
D3DCOLOR white = D3DCOLOR_XRGB(255, 255, 255);
D3DCOLOR red = D3DCOLOR_XRGB(255, 0, 0);
D3DCOLOR orange = D3DCOLOR_XRGB(255, 128, 0);
D3DCOLOR yellow = D3DCOLOR_XRGB(255, 242, 0);
D3DCOLOR green = D3DCOLOR_XRGB(0, 255, 0);
D3DCOLOR lime = D3DCOLOR_XRGB(128, 255, 0);
D3DCOLOR green_dark = D3DCOLOR_XRGB(0, 128, 0);
D3DCOLOR blue = D3DCOLOR_XRGB(0, 0, 255);
D3DCOLOR cyan = D3DCOLOR_XRGB(0, 128, 255);
D3DCOLOR purple = D3DCOLOR_XRGB(255, 0, 255);

#define AzulW8				D3DCOLOR_ARGB(255, 0, 87, 130)
#define CinzaFundoJanela	D3DCOLOR_ARGB(255, 230, 230, 230)
#define VermelhoSistemaOFF  D3DCOLOR_ARGB(255, 255, 60, 60)
#define VermelhoSistemaON	D3DCOLOR_ARGB(255, 255, 23, 23)
#define Cinza				D3DCOLOR_ARGB(255, 150, 150, 150)

#define Red		D3DCOLOR_ARGB(255, 255, 000, 000)
#define Green	D3DCOLOR_ARGB(255, 0, 255, 34)
#define Blue	D3DCOLOR_ARGB(255, 63, 50, 226)
#define White	D3DCOLOR_ARGB(255, 255, 255, 255)
#define Black	D3DCOLOR_ARGB(255, 000, 000, 000)
#define Yellow	D3DCOLOR_ARGB(255, 255, 255, 000)
#define Purple	D3DCOLOR_ARGB(255, 100, 000, 150)
#define Pink	D3DCOLOR_ARGB(255, 255, 020, 145)
#define Orange	D3DCOLOR_ARGB(255, 255, 165, 000)
#define Grey	D3DCOLOR_ARGB(255, 128, 128, 128)
#define TGrey	D3DCOLOR_ARGB(10, 128, 128, 128)
#define Cyan	D3DCOLOR_ARGB(255, 0, 142, 210)
#define TBlack  D3DCOLOR_ARGB(200, 0, 0, 0)
#define TBlack2  D3DCOLOR_ARGB(150, 0, 0, 0)
#define TBlue	D3DCOLOR_ARGB(200, 63, 50, 226)
#define Cor1      D3DCOLOR_ARGB(255, 035, 035, 035)
#define Cor2      D3DCOLOR_ARGB(255, 027, 027, 027)
#define Cor3	  D3DCOLOR_ARGB(255, 047, 047, 047)
#define Cor4	  D3DCOLOR_ARGB(255, 041, 041, 041)
#define Cor5      D3DCOLOR_ARGB(255, 55, 55, 55)
#define BoxBone3		D3DCOLOR_ARGB(0, 0, 0, 0)
#define Cor_bord      D3DCOLOR_ARGB(200, 29, 29, 29)

#define TBlackB			D3DCOLOR_ARGB(200, 13, 7, 0)
#define Seletor			D3DCOLOR_ARGB(255, 89, 87, 87)
#define RedVinho		D3DCOLOR_ARGB(255, 122, 0, 0)
#define TGrayBlack		D3DCOLOR_ARGB(255, 42, 42, 42)
#define TGrayEdited		D3DCOLOR_ARGB(150, 50, 50, 50)
#define Green2			D3DCOLOR_ARGB(255, 28, 57, 24)

#define D3DFVF_TEXTUREVERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1)

struct D3DTLVERTEX
{
	float fX;
	float fY;
	float fZ;
	float fRHW;
	D3DCOLOR Color;
	float fU;
	float fV;
};

struct TEXTUREVERTEX
{
	D3DXVECTOR3 vec;
	FLOAT rhw;
	DWORD color;
	FLOAT u, v;
};

enum Gr_Orientation
{
	horizontal,
	vertical
};

void DrawLine(LPDIRECT3DDEVICE9 pDevice, float startX, float startY, float endX, float endY, D3DCOLOR dwColour)
{
	D3DTLVERTEX Vertex[2] = {
		{ (float)startX, (float)startY, 0.0f, 1.0f, dwColour },
		{ (float)endX, (float)endY, 1.0f, 1.0f, dwColour },
	};

	const DWORD FVFTL = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	IDirect3DBaseTexture9* pTexture = NULL;

	DWORD dwLighting = 0, dwZEnable = 0, dwZFunc = 0, dwFVF = 0, dwColorOp = 0, dwColorArg = 0;

	pDevice->GetTexture(0, &pTexture);
	pDevice->GetRenderState(D3DRS_LIGHTING, &dwLighting);
	pDevice->GetRenderState(D3DRS_ZENABLE, &dwZEnable);
	pDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
	pDevice->GetFVF(&dwFVF);
	pDevice->GetTextureStageState(0, D3DTSS_COLOROP, &dwColorOp);
	pDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &dwColorArg);

	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetFVF(FVFTL);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 1, &Vertex, sizeof(D3DTLVERTEX));

	pDevice->SetTexture(0, pTexture);
	pDevice->SetRenderState(D3DRS_LIGHTING, dwLighting);
	pDevice->SetRenderState(D3DRS_ZENABLE, dwZEnable);
	pDevice->SetRenderState(D3DRS_ZFUNC, dwZFunc);
	pDevice->SetFVF(dwFVF);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, dwColorOp);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, dwColorArg);
}

IDirect3DPixelShader9* pShader;

struct D3DTLVERTEXX
{
	float x, y, z, rhw;
	DWORD color;
};


D3DTLVERTEXX CreateD3DTLVERTEXX(float X, float Y, float Z, float RHW, D3DCOLOR color)
{
	D3DTLVERTEXX v = { X, Y, Z, RHW, color };
	return v;
}

void DrawCircle2(IDirect3DDevice9* pDevice, int x, int y, float radius, int Sides, D3DCOLOR dwColor)
{
	const int NUMPOINTS = 24;
	D3DTLVERTEXX Circle[NUMPOINTS + 1];
	int i;
	float X;
	float Y;
	float Theta;
	float WedgeAngle = (float)((2 * D3DX_PI) / NUMPOINTS);

	for (i = 0; i <= NUMPOINTS; i++)
	{
		Theta = i * WedgeAngle;
		X = (float)(x + radius * cos(Theta));
		Y = (float)(y - radius * sin(Theta));
		Circle[i] = CreateD3DTLVERTEXX((float)X, (float)Y, 0.0f, 1.0f, dwColor);
	}

	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);

	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, FALSE);
	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, NUMPOINTS, &Circle[0], sizeof(Circle[0]));
	pDevice->SetRenderState(D3DRS_ZENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_STENCILENABLE, TRUE);

	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(pShader);
}

void FillRGB(INT x, INT y, INT w, INT h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec = { x, y, x + w, y + h };
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, color, 0, 0);
}

void DrawBorder(INT x, INT y, INT w, INT h, INT px, D3DCOLOR BorderColor, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB(x, (y + h - px), w, px, BorderColor, pDevice);
	FillRGB(x, y, px, h, BorderColor, pDevice);
	FillRGB(x, y, w, px, BorderColor, pDevice);
	FillRGB((x + w - px), y, px, h, BorderColor, pDevice);
}

void DrawCheck(DWORD Color, float x, float y, LPDIRECT3DDEVICE9 pDevice)
{
	FillRGB(x, y, 1, 3, Color, pDevice);
	FillRGB(x + 1, y + 1, 1, 3, Color, pDevice);
	FillRGB(x + 2, y + 2, 1, 3, Color, pDevice);
	FillRGB(x + 3, y + 1, 1, 3, Color, pDevice);
	FillRGB(x + 4, y, 1, 3, Color, pDevice);
	FillRGB(x + 5, y - 1, 1, 3, Color, pDevice);
	FillRGB(x + 6, y - 2, 1, 3, Color, pDevice);
	FillRGB(x + 7, y - 3, 1, 3, Color, pDevice);
}

void drawRect(LPDIRECT3DDEVICE9 pDevice, int x, int y, int w, int h, uint color)
{
	D3DRECT rect = { x, y, (x + w), (y + h) };
	pDevice->Clear(1, &rect, D3DCLEAR_TARGET, color, 0.f, 0);
}
void DrawFillRect(LPDIRECT3DDEVICE9 pDevice, float X, float Y, float W, float H, D3DCOLOR Color)
{
	D3DTLVERTEX Vertex[4] = {
		{ (float)X, (float)(Y + H), 0.0f, 1.0f, Color },
		{ (float)X, (float)Y, 0.0f, 1.0f, Color },
		{ (float)(X + W), (float)(Y + H), 0.0f, 1.0f, Color },
		{ (float)(X + W), (float)Y, 0.0f, 1.0f, Color }
	};

	const DWORD FVFTL = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	IDirect3DBaseTexture9* pTexture = NULL;

	DWORD dwLighting = 0, dwZEnable = 0, dwZFunc = 0, dwFVF = 0, dwColorOp = 0, dwColorArg = 0;

	pDevice->GetTexture(0, &pTexture);
	pDevice->GetRenderState(D3DRS_LIGHTING, &dwLighting);
	pDevice->GetRenderState(D3DRS_ZENABLE, &dwZEnable);
	pDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
	pDevice->GetFVF(&dwFVF);
	pDevice->GetTextureStageState(0, D3DTSS_COLOROP, &dwColorOp);
	pDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &dwColorArg);

	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetFVF(FVFTL);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);


	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, &Vertex, sizeof(D3DTLVERTEX));

	pDevice->SetTexture(0, pTexture);
	pDevice->SetRenderState(D3DRS_LIGHTING, dwLighting);
	pDevice->SetRenderState(D3DRS_ZENABLE, dwZEnable);
	pDevice->SetRenderState(D3DRS_ZFUNC, dwZFunc);
	pDevice->SetFVF(dwFVF);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, dwColorOp);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, dwColorArg);
}

void DrawRect(int x, int y, int h, int w, DWORD Color, LPDIRECT3DDEVICE9 pDevice)
{
	D3DRECT rec;
	rec.x1 = x;
	rec.x2 = x + w;
	rec.y1 = y;
	rec.y2 = y + h;
	pDevice->Clear(1, &rec, D3DCLEAR_TARGET, Color, 0, 0);
}

enum circle_type { full, half, quarter };
enum text_alignment { lefted, centered, righted };


LPDIRECT3DVERTEXBUFFER9 g_pVB;    // Buffer to hold vertices
struct vertex
{
	float x, y, z, t;
	DWORD Color;
};

DWORD Circle2(LPDIRECT3DDEVICE9 pDevice, float x, float y, float radius, int rotate, int type, bool smoothing, int resolution, DWORD color)
{
	std::vector<vertex> circle(resolution + 2);
	float angle = rotate * D3DX_PI / 180;
	float pi;

	if (type == full) pi = D3DX_PI;        // Full circle
	if (type == half) pi = D3DX_PI / 2;      // 1/2 circle
	if (type == quarter) pi = D3DX_PI / 4;   // 1/4 circle

	for (int i = 0; i < resolution + 2; i++)
	{
		circle[i].x = (float)(x - radius * cos(i * (2 * pi / resolution)));
		circle[i].y = (float)(y - radius * sin(i * (2 * pi / resolution)));
		circle[i].z = 0;
		circle[i].t = 1;
		circle[i].Color = color;
	}

	// Rotate matrix
	int _res = resolution + 2;
	for (int i = 0; i < _res; i++)
	{
		circle[i].x = x + cos(angle) * (circle[i].x - x) - sin(angle) * (circle[i].y - y);
		circle[i].y = y + sin(angle) * (circle[i].x - x) + cos(angle) * (circle[i].y - y);
	}

	pDevice->CreateVertexBuffer((resolution + 2) * sizeof(vertex), D3DUSAGE_WRITEONLY, D3DFVF_XYZRHW | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &g_pVB, NULL);

	VOID* pVertices;
	g_pVB->Lock(0, (resolution + 2) * sizeof(vertex), (void**)&pVertices, 0);
	memcpy(pVertices, &circle[0], (resolution + 2) * sizeof(vertex));
	g_pVB->Unlock();


	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	if (smoothing)
	{
		pDevice->SetRenderState(D3DRS_MULTISAMPLEANTIALIAS, TRUE);
		pDevice->SetRenderState(D3DRS_ANTIALIASEDLINEENABLE, TRUE);
	}
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	pDevice->SetStreamSource(0, g_pVB, 0, sizeof(vertex));
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE);

	pDevice->DrawPrimitive(D3DPT_LINESTRIP, 0, resolution);
	if (g_pVB != NULL) g_pVB->Release();

	return 1;
}

void DrawBox(LPDIRECT3DDEVICE9 pDevice, float x, float y, float w, float h, D3DCOLOR dwColour)
{
	DrawLine(pDevice, x, y, x + w, y, dwColour); // top 
	DrawLine(pDevice, x, y + h, x + w + 1, y + h, dwColour); // bottom 
	DrawLine(pDevice, x, y, x, y + h, dwColour); // left 
	DrawLine(pDevice, x + w, y, x + w, y + h, dwColour); // right
}

//void DrawFillRectOut(LPDIRECT3DDEVICE9 pDevice, float x, float y, float w, float h, D3DCOLOR dwOutCol, D3DCOLOR dwFillCol)
//{
//	DrawFillRect(pDevice, x, y, w, h, dwFillCol);
//	DrawOutline(pDevice, x, y, w, h, dwOutCol);
//}

bool MouseIsOver(int x, int y, int w, int h)
{
	int bover;
	GetCursorPos(&cPos);
	ScreenToClient(GetForegroundWindow(), &cPos);
	if (cPos.x >= x && cPos.x <= x + w && cPos.y >= y && cPos.y <= y + h)
	{
		bover = 1;
	}
	else {
		bover = 0;
	}
	return bover;
}

VOID DrawMouse(DWORD color, LPDIRECT3DDEVICE9 pDevice)
{
	POINT myCursor;
	GetCursorPos(&myCursor);
	ScreenToClient(GetForegroundWindow(), &myCursor);

	DrawRect(myCursor.x, myCursor.y, 30, 1, color, pDevice);
	DrawRect(myCursor.x + 1, myCursor.y, 28, 1, color, pDevice);
	DrawRect(myCursor.x + 2, myCursor.y, 26, 1, color, pDevice);
	DrawRect(myCursor.x + 3, myCursor.y, 24, 1, color, pDevice);
	DrawRect(myCursor.x + 4, myCursor.y, 22, 1, color, pDevice);
	DrawRect(myCursor.x + 5, myCursor.y, 20, 1, color, pDevice);
	DrawRect(myCursor.x + 6, myCursor.y, 18, 1, color, pDevice);
	DrawRect(myCursor.x, myCursor.y, 1, 30, color, pDevice);
	DrawRect(myCursor.x, myCursor.y + 1, 1, 28, color, pDevice);
	DrawRect(myCursor.x, myCursor.y + 2, 1, 26, color, pDevice);
	DrawRect(myCursor.x, myCursor.y + 3, 1, 24, color, pDevice);
	DrawRect(myCursor.x, myCursor.y + 4, 1, 22, color, pDevice);
	DrawRect(myCursor.x, myCursor.y + 5, 1, 20, color, pDevice);
	DrawRect(myCursor.x, myCursor.y + 6, 1, 18, color, pDevice);
}

void DrawOutline(LPDIRECT3DDEVICE9 pDevice, float x, float y, float w, float h, D3DCOLOR dwColour)
{
	D3DTLVERTEX Vertex[5] = {
		{(float)x , (float)y, 0.0f, 1.0f, dwColour},
		{(float)(x + w) , (float)y , 0.0f, 1.0f, dwColour},
		{(float)(x + w), (float)(y - h), 0.0f, 1.0f, dwColour},
		{(float)x, (float)(y - h), 0.0f, 1.0f, dwColour},
		{(float)x, (float)y, 0.0f, 1.0f, dwColour}
	};

	const DWORD FVFTL = D3DFVF_XYZRHW | D3DFVF_DIFFUSE;
	IDirect3DBaseTexture9* pTexture = NULL;

	DWORD dwLighting = 0, dwZEnable = 0, dwZFunc = 0, dwFVF = 0, dwColorOp = 0, dwColorArg = 0;

	pDevice->GetTexture(0, &pTexture);
	pDevice->GetRenderState(D3DRS_LIGHTING, &dwLighting);
	pDevice->GetRenderState(D3DRS_ZENABLE, &dwZEnable);
	pDevice->GetRenderState(D3DRS_ZFUNC, &dwZFunc);
	pDevice->GetFVF(&dwFVF);
	pDevice->GetTextureStageState(0, D3DTSS_COLOROP, &dwColorOp);
	pDevice->GetTextureStageState(0, D3DTSS_COLORARG1, &dwColorArg);

	pDevice->SetTexture(0, NULL);
	pDevice->SetRenderState(D3DRS_LIGHTING, FALSE);
	pDevice->SetRenderState(D3DRS_ZENABLE, FALSE);
	pDevice->SetRenderState(D3DRS_ZFUNC, D3DCMP_ALWAYS);
	pDevice->SetFVF(FVFTL);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG1);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, D3DTA_DIFFUSE);

	pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, 4, &Vertex, sizeof(D3DTLVERTEX));

	pDevice->SetTexture(0, pTexture);
	pDevice->SetRenderState(D3DRS_LIGHTING, dwLighting);
	pDevice->SetRenderState(D3DRS_ZENABLE, dwZEnable);
	pDevice->SetRenderState(D3DRS_ZFUNC, dwZFunc);
	pDevice->SetFVF(dwFVF);
	pDevice->SetTextureStageState(0, D3DTSS_COLOROP, dwColorOp);
	pDevice->SetTextureStageState(0, D3DTSS_COLORARG1, dwColorArg);
}
void DrawFillRect2(float x, float y, float w, float h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice)
{
	vertex q[4];

	q[0].Color = q[1].Color = q[2].Color = q[3].Color = color;

	q[0].z = q[1].z = q[2].z = q[3].z = 0;
	q[0].t = q[1].t = q[2].t = q[3].t = 0;

	q[0].x = q[2].x = x;
	q[0].y = q[1].y = y - h;
	q[1].x = q[3].x = x + w;
	q[2].y = q[3].y = y;



	pDevice->SetTexture(0, NULL);
	pDevice->SetPixelShader(NULL);
	pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	pDevice->SetFVF(D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1);
	pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, q, sizeof(vertex));
}

void DrawFillRectOutz2(LPDIRECT3DDEVICE9 pDevice, float x, float y, float w, float h, D3DCOLOR dwOutCol, D3DCOLOR dwFillCol)
{
	DrawFillRect2(x, y, w, h, dwFillCol, pDevice);

	DrawOutline(pDevice, x, y, w, h, dwOutCol);
}

int DrawText_UTF8(int x, int y, int w, int h, D3DCOLOR color, ID3DXFont* tFont)
{
	RECT Font;
	Font.bottom = 0;
	Font.left = (x - 1.1);
	Font.top = y - (h*1.025);
	Font.right = 0;

	//tFont->DrawTextW(&Font, DT_NOCLIP, color);
	return 0;
}

void DrawFillhealth(LPDIRECT3DDEVICE9 pDevice, float x, float y, float health, float w, float h, D3DCOLOR dwOutCol, D3DCOLOR dwFillCol, D3DCOLOR color, ID3DXFont* tFont)
{
	DrawFillRect2(x, y, w, h, dwFillCol, pDevice);
	float hw = (float)((h * health) / 100);
	DrawFillRect2(x, y, w - 1, hw, dwOutCol, pDevice);

	DrawText_UTF8(x - 1, y, w, hw, black, tFont);
	DrawText_UTF8(x + 1, y, w, hw, black, tFont);
	DrawText_UTF8(x, y, w, hw - 1, black, tFont);
	DrawText_UTF8(x, y, w, hw + 1, black, tFont);

	DrawText_UTF8(x, y, w, hw, color, tFont);
}



