#include <Windows.h>//包含弹窗
#include <iostream>
#include <graphics.h>
#define CHESSSIZE 10
#define GAP 40
#define INITIALX 40
#define INITIALY 40
#define BOXSIZE 20
using namespace std;
struct Box
{
	int lx = INITIALX - BOXSIZE;
	int ly = INITIALY - BOXSIZE;
	int rx = INITIALX + BOXSIZE;
	int ry = INITIALY + BOXSIZE;
};
void DrawChess(int x,int y,int r,bool type)
{
	//true为实心，false为空心（true为白方，false为黑方）
	if (type)
	{
		fillcircle(x, y, r);
	}else
	{
		circle(x, y, r);
	}
}
void DrawBox(int lx,int ly,int rx,int ry) 
{
	rectangle(lx, ly, rx, ry);
}
void DrawBoard(char board[15][15])
{
	//绘制棋盘
	for (int i = GAP; i <= 600; i += GAP)
	{
		line(i, GAP, i, 600);
	}
	for (int j = GAP; j <= 600; j += GAP)
	{
			line(GAP, j, 600, j);
	}
	//绘制已有棋子
	for (int i = 0;i < 15; ++i)
	{
		for (int j = 0;j < 15; ++j)
		{
			if (board[i][j] == 1)
			{
				DrawChess(INITIALX + j * BOXSIZE*2, INITIALY + i * BOXSIZE*2, CHESSSIZE, true);
			}
			else if (board[i][j] == 2)
			{
				DrawChess(INITIALX + j * BOXSIZE*2, INITIALY + i * BOXSIZE*2, CHESSSIZE, false);
			}
		}
	}

}
int VectoryCheck(char board[15][15])
{
	////直线检测
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1 && board[i][j + 4] == 1)
			{
				return 1;//白棋获胜
			}
			else if(board[i][j] == 2 && board[i][j + 1] == 2 && board[i][j + 2] == 2 && board[i][j + 3] == 2 && board[i][j + 4] == 2)
			{
				return 2;//黑棋获胜
			}
		}
	}
	// 垂直检测
	for (int j = 0; j < 15; ++j)
	{
		for (int i = 0; i < 11; ++i)
		{
			if (board[i][j] == 1 && board[i + 1][j] == 1 && board[i + 2][j] == 1 && board[i + 3][j] == 1 && board[i + 4][j] == 1)
			{
				return 1;
			}
			else if (board[i][j] == 2 && board[i + 1][j] == 2 && board[i + 2][j] == 2 && board[i + 3][j] == 2 && board[i + 4][j] == 2)
			{
				return 2;
			}
		}
	}
	// 斜向检测（从左上到右下）
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (board[i][j] == 1 && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 1 && board[i + 3][j + 3] == 1 && board[i + 4][j + 4] == 1)
			{
				return 1; // 白棋获胜
			}
			else if (board[i][j] == 2 && board[i + 1][j + 1] == 2 && board[i + 2][j + 2] == 2 && board[i + 3][j + 3] == 2 && board[i + 4][j + 4] == 2)
			{
				return 2; // 黑棋获胜
			}
		}
	}

	// 斜向检测（从右上到左下）
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 4; j < 15; ++j)
		{
			if (board[i][j] == 1 && board[i + 1][j - 1] == 1 && board[i + 2][j - 2] == 1 && board[i + 3][j - 3] == 1 && board[i + 4][j - 4] == 1)
			{
				return 1; // 白棋获胜
			}
			else if (board[i][j] == 2 && board[i + 1][j - 1] == 2 && board[i + 2][j - 2] == 2 && board[i + 3][j - 3] == 2 && board[i + 4][j - 4] == 2)
			{
				return 2; // 黑棋获胜
			}
		}
	}

	return false;
}


int main()
{
	initgraph(640, 640);	

	char board[15][15] = { 0 };

	Box movebox;

	bool chess_type = false;//判断棋子类型

	bool keyPressed = false; // 按键状态,由于按键的按下和弹起均会被检测，会导致switch语句被执行两次，故加入按键检测。

	


	while (1)
	{
		cleardevice();

		BeginBatchDraw();

		DrawBoard(board);//绘制棋盘和棋子

		DrawBox(movebox.lx, movebox.ly, movebox.rx, movebox.ry);

		EndBatchDraw();

		ExMessage mes = getmessage(EX_KEY);

		//控制方框移动与落子
		switch (mes.vkcode)
		{
		case VK_UP:
			if (movebox.ly >= INITIALY && !keyPressed)
			{
				movebox.ly -= BOXSIZE*2;
				movebox.ry -= BOXSIZE*2;
				keyPressed = true; // 记录按下状态
			}
			break;
		case VK_DOWN:
			if (movebox.ry <= 600 && !keyPressed)
			{
				movebox.ly += BOXSIZE*2;
				movebox.ry += BOXSIZE*2;
				keyPressed = true;
			}
			break;
		case VK_LEFT:
			if (movebox.lx >= INITIALX && !keyPressed)
			{
				movebox.lx -= BOXSIZE*2;
				movebox.rx -= BOXSIZE*2;
				keyPressed = true;
			}
			break;
		case VK_RIGHT:
			if (movebox.rx <= 600 && !keyPressed)
			{
				movebox.lx += BOXSIZE*2;
				movebox.rx += BOXSIZE*2;
				keyPressed = true;
			}
			break;
		case VK_RETURN://落子
			if (!keyPressed)
			{

				int x = (movebox.lx - BOXSIZE) / INITIALX;
				int y = (movebox.ly - BOXSIZE) / INITIALX;

				if (board[y][x] == 0)
				{ // 检查是否已有棋子
					board[y][x] = chess_type ? 1 : 2; // 1为白棋，2为黑棋
					chess_type = !chess_type; // 切换棋子类型
				}
				
				keyPressed = true;
			}
		}
		if (VectoryCheck(board) == 1)
		{
			//PlaySound(TEXT("C:/Windows/Media/Windows Critical Stop.wav"), NULL, SND_ASYNC);
			MessageBox(NULL, "白方胜利！", "结束", MB_SYSTEMMODAL);
			closegraph();
		}
		else if (VectoryCheck(board) == 2)
		{
			//PlaySound(TEXT("C:/Windows/Media/Windows Critical Stop.wav"), NULL, SND_ASYNC);
			MessageBox(NULL, "黑方胜利！", "结束", MB_SYSTEMMODAL);
			closegraph();
		}
		// 检测按键释放，重置状态
		if (mes.message == WM_KEYUP)
		{
			keyPressed = false; // 释放按键时重置状态
		}

		
	}

	return 0;
}