#include <Windows.h>//��������
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
	//trueΪʵ�ģ�falseΪ���ģ�trueΪ�׷���falseΪ�ڷ���
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
	//��������
	for (int i = GAP; i <= 600; i += GAP)
	{
		line(i, GAP, i, 600);
	}
	for (int j = GAP; j <= 600; j += GAP)
	{
			line(GAP, j, 600, j);
	}
	//������������
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
	////ֱ�߼��
	for (int i = 0; i < 15; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (board[i][j] == 1 && board[i][j + 1] == 1 && board[i][j + 2] == 1 && board[i][j + 3] == 1 && board[i][j + 4] == 1)
			{
				return 1;//�����ʤ
			}
			else if(board[i][j] == 2 && board[i][j + 1] == 2 && board[i][j + 2] == 2 && board[i][j + 3] == 2 && board[i][j + 4] == 2)
			{
				return 2;//�����ʤ
			}
		}
	}
	// ��ֱ���
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
	// б���⣨�����ϵ����£�
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 0; j < 11; ++j)
		{
			if (board[i][j] == 1 && board[i + 1][j + 1] == 1 && board[i + 2][j + 2] == 1 && board[i + 3][j + 3] == 1 && board[i + 4][j + 4] == 1)
			{
				return 1; // �����ʤ
			}
			else if (board[i][j] == 2 && board[i + 1][j + 1] == 2 && board[i + 2][j + 2] == 2 && board[i + 3][j + 3] == 2 && board[i + 4][j + 4] == 2)
			{
				return 2; // �����ʤ
			}
		}
	}

	// б���⣨�����ϵ����£�
	for (int i = 0; i < 11; ++i)
	{
		for (int j = 4; j < 15; ++j)
		{
			if (board[i][j] == 1 && board[i + 1][j - 1] == 1 && board[i + 2][j - 2] == 1 && board[i + 3][j - 3] == 1 && board[i + 4][j - 4] == 1)
			{
				return 1; // �����ʤ
			}
			else if (board[i][j] == 2 && board[i + 1][j - 1] == 2 && board[i + 2][j - 2] == 2 && board[i + 3][j - 3] == 2 && board[i + 4][j - 4] == 2)
			{
				return 2; // �����ʤ
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

	bool chess_type = false;//�ж���������

	bool keyPressed = false; // ����״̬,���ڰ����İ��º͵�����ᱻ��⣬�ᵼ��switch��䱻ִ�����Σ��ʼ��밴����⡣

	


	while (1)
	{
		cleardevice();

		BeginBatchDraw();

		DrawBoard(board);//�������̺�����

		DrawBox(movebox.lx, movebox.ly, movebox.rx, movebox.ry);

		EndBatchDraw();

		ExMessage mes = getmessage(EX_KEY);

		//���Ʒ����ƶ�������
		switch (mes.vkcode)
		{
		case VK_UP:
			if (movebox.ly >= INITIALY && !keyPressed)
			{
				movebox.ly -= BOXSIZE*2;
				movebox.ry -= BOXSIZE*2;
				keyPressed = true; // ��¼����״̬
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
		case VK_RETURN://����
			if (!keyPressed)
			{

				int x = (movebox.lx - BOXSIZE) / INITIALX;
				int y = (movebox.ly - BOXSIZE) / INITIALX;

				if (board[y][x] == 0)
				{ // ����Ƿ���������
					board[y][x] = chess_type ? 1 : 2; // 1Ϊ���壬2Ϊ����
					chess_type = !chess_type; // �л���������
				}
				
				keyPressed = true;
			}
		}
		if (VectoryCheck(board) == 1)
		{
			//PlaySound(TEXT("C:/Windows/Media/Windows Critical Stop.wav"), NULL, SND_ASYNC);
			MessageBox(NULL, "�׷�ʤ����", "����", MB_SYSTEMMODAL);
			closegraph();
		}
		else if (VectoryCheck(board) == 2)
		{
			//PlaySound(TEXT("C:/Windows/Media/Windows Critical Stop.wav"), NULL, SND_ASYNC);
			MessageBox(NULL, "�ڷ�ʤ����", "����", MB_SYSTEMMODAL);
			closegraph();
		}
		// ��ⰴ���ͷţ�����״̬
		if (mes.message == WM_KEYUP)
		{
			keyPressed = false; // �ͷŰ���ʱ����״̬
		}

		
	}

	return 0;
}