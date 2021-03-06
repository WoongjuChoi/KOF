#pragma once
#include <Windows.h>
#include <math.h>
#include <iostream>

using namespace std;

#define WIN_START_POS_X	200
#define WIN_START_POS_Y	50
#define WIN_SIZE_X	1200
#define WIN_SIZE_Y	700

#define PI 3.14159265357989
#define PI2 (3.14159265357989 * 2)

#define DEGREE_TO_RADIAN(x)		(x * PI / 180.0f)

#define SAFE_RELEASE(p)	{ if (p) { p->Release(); delete p; p = nullptr; } }

enum MoveDir { Left, Right, Up, Down };
enum eActs { standing, weekPunch, weekFoot, strongPunch, strongFoot, hit, die, victory, moveForward, moveBackward, end };
enum eBody { top, bottom, hitPoint, bodyend };
enum ePlayer { player1 = -1, player2 = 1 };
enum eCharacter {eHwajai, eYuri, eKing};

enum eDir { p1 = -1, p2 = 1 };

enum class eScene { title, cSelect, battle, winner};

extern HWND g_hWnd;
extern HINSTANCE g_hInstance;