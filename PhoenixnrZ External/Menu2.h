#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <d3d9.h>
#include <d3dx9.h>
using namespace std;

static BOOL	Init;
#define ITEM_ARRAY 64

#define MC_MAXX					(X+WIDTH)
#define MC_FCTR(x,y)			((x+y)/2)
#define MC_ITEMY(index)			(Y+(index*I_SPC)+T_SPC+(T_SPC/2))
#define MC_ITEMY1(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)-1)
#define MC_ITEMY2(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+20)
#define MC_ITEMY3(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+41)
#define MC_ITEMY4(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+60)
#define MC_ITEMY5(index)		(Y+(index*I_SPC)+T_SPC+(T_SPC/2)+81)
#define MC_MSY					(Y+T_SPC+(T_SPC/2))

class cMenu {
public:
struct	sitem {
char	title[50];
char	state[50];
int		type;
int		max;
int		no;
int		*val;
} items[ITEM_ARRAY];

enum MENUBOX {
WHITE		=	D3DCOLOR_ARGB(255, 255, 255, 255),
WHITE2		=	D3DCOLOR_ARGB(255, 112, 114, 113),
RED			=	D3DCOLOR_ARGB(255, 234, 0, 0),
purple      = D3DCOLOR_ARGB(255, 100, 000, 150),
GREEN		=	D3DCOLOR_ARGB(255, 255, 255, 255),
PINK		=	D3DCOLOR_ARGB(255, 255, 255, 255),
ORANGE		=	D3DCOLOR_ARGB(255, 222, 106, 52),
MBOX		=	D3DCOLOR_ARGB(255, 24, 80, 151),
BEVEN		=	D3DCOLOR_ARGB(255, 17, 67, 131),
MEVEN		=	D3DCOLOR_ARGB(255, 79, 82, 84),
MBORDER		=	D3DCOLOR_ARGB(180, 0, 0, 0),
CRADIT		=	D3DCOLOR_ARGB(255, 255, 255, 255)

};

enum gr_orientation {
horizontal,
vertical
};

enum I_TYPES {
T_TEXT = 0,
T_ITEM = 1,
T_CAT  = 2
};

int  X, Y;
POINT mofs;
POINT mpos;
int  WIDTH;
int  I_OFS, S_OFS;
int  I_SPC, I_TSPC;
int  T_SPC, F_SPC;
int  NO;
int  I_CUR;
bool SHOW;
bool INIT;

void	DrawBox( int x, int y, int w, int h, D3DCOLOR Color, LPDIRECT3DDEVICE9 pDevice);
void	DrawBorder(int x, int y, int w, int h, int s, D3DCOLOR Color, LPDIRECT3DDEVICE9 device);
void	DrawLine(float x, float y, float x2, float y2, float width, DWORD color);
void	FillRGB(int x, int y, int w, int h, D3DCOLOR color, IDirect3DDevice9* pDevice);
void	DrawPoint(int x, int y, int w, int h, D3DCOLOR color, LPDIRECT3DDEVICE9 pDevice );
void	DrawString(int x, int y, DWORD color, const char *fmt, ...);
void	Dwarzc1(char* String, int x, int y, D3DCOLOR color);
char*	oprintf (const char *fmt, ...);
void	PostReset(LPDIRECT3DDEVICE9 pDevice);
void	PreReset(LPDIRECT3DDEVICE9 pDevice);
void	ShowMenu(LPDIRECT3DDEVICE9 pDevice);
void	ShowBox(LPDIRECT3DDEVICE9 pDevice);
private:

void	aitem(char *title, int *var, char *states);
void	additem(char *title, int type, int *var, char *states);
void	getfield(char *str, char *dst, int no);
int		nofields(char *str);
void	Init(void);
}; extern cMenu Menu;

struct Option {
int Hack1;
int Hack2;
int Hack3;
int Hack4;
int Hack5;
int THEN = 1;
int Hack6;
int Hack7;
int Hack8;
int NoReload;
int speedmode;
int Hack9;
int Hack10;
int Hack11;
int dawdawdawd;
int Hack12;
int Hack43;
int Hack13;
int Hack14;
int Hack15;
int Hack99;
int Hack16;
int Hack17;
int Hack18;
int Hack19;
int Hack70;
int Hack7000;
int Hack21;
int Hack71;
int Hack35;
int Hack36;
int Hack37;
int Hack142;
int Hack143;
int Hack144;
int Hack1488 = 1;
int Hack1489 = 1;
int Hack145;
int Hack11445;
}; extern Option Optmin;
