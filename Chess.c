#include<stdio.h>

#define Width 15          //standard size of the board
#define WinAmount 5       //chess amount to win
#define BOARDWITH 2*Width+1 //9 board contain 1 chess

//the chess
const char* WHITE = "��", * BLACK = "��"; *INIT = "��";
int chess[Width][Width] = { 0 };

//the board
const char* LT = "��", * TOP = "��", * RT = "��";
const char* LEFT = "��", * CENTER = "��", * RIGHT = "��";
const char* LB = "��", * BOTTON = "��", * RB = "��";
const char* SPACE = " ";
char* BOARD[BOARDWITH][BOARDWITH];


void InitBoard();//initialize the board

void Draw();     //draw the board

int Game();      //the game

int isWin();     //judge whether the player win

void welcome();  //choose mode

int main()
{
	system("color 70");
	int getch();
	do {
		InitBoard();
		for (int m = 0; m < Width; m++) {
			for (int n = 0; n < Width; n++) {
				chess[m][n] = 0;
			}
		}
		welcome();
		//system("cls");
		printf("�Ƿ��˳���Ϸ?\n");
	} while (getch() != 0x1b);
	system("pause");

	return 0;
}

void InitBoard()
{
	int i, j;
	BOARD[0][0] = LT;
	BOARD[0][BOARDWITH - 1] = RT;
	BOARD[BOARDWITH - 1][0] = LB;
	BOARD[BOARDWITH - 1][BOARDWITH - 1] = RB;
	for (i = 0; i < BOARDWITH; i++) {			//TODO:simplify this
		for (j = 0; j < BOARDWITH; j++) {
			if (((i == 0) || (i == BOARDWITH - 1)) && ((j == 0) || (j == BOARDWITH - 1))) {
				continue;
			}
			else {
				switch (i)
				{
				case 0:BOARD[i][j] = TOP; break;
				case BOARDWITH - 1:BOARD[i][j] = BOTTON; break;
				default: {
					if (j == 0 || j == BOARDWITH - 1) {
						if (j == 0) {
							BOARD[i][j] = LEFT;
						}
						else {
							BOARD[i][j] = RIGHT;
						}
					}
					else {
						if (i % 2 == 1 && j % 2 == 1) {
							BOARD[i][j] = SPACE;
						}
						else {
							BOARD[i][j] = CENTER;
						}
					}
					break;
				}
				}
			}
		}
	}

}

void Draw()
{
	system("cls");
	int i, j;
	for (i = 0; i < BOARDWITH; i++) {
		for (j = 0; j < BOARDWITH; j++) {
			if (BOARD[i][j] == WHITE || BOARD[i][j] == BLACK || BOARD[i][j] == INIT) {
				printf("%s", BOARD[i][j]);
			}
			else printf("%s ", BOARD[i][j]);
		}
		printf("\n");
	}
}

int count(int Chess[Width][Width], int cx, int cy, int Player, int direction)//direction 0 is count in transverse,1 is portrait,2 is left top,3 is right top
{
	int Amount = 1;
	int a = 1;
	switch (direction)
	{
	case 0: {  //count transverse
		while (Amount <= 5 && Chess[cx + a][cy] == Player && (cx + a) < Width) { //count right side
			Amount += 1;
			a += 1;
		}
		a = 1;
		if (Amount == WinAmount) {
			break;
		}
		else {
			while (Amount <= 5 && Chess[cx - a][cy] == Player && (cx - a) > -1) { //count left side
				Amount += 1;
				a += 1;
			}
		}
		break;
	}
	case 1: {  //count portrait
		while (Amount <= 5 && Chess[cx][cy + a] == Player && (cy + a) < Width) { //count up side
			Amount += 1;
			a += 1;
		}
		a = 1;
		if (Amount == WinAmount) {
			break;
		}
		else {
			while (Amount <= 5 && Chess[cx][cy - a] == Player && (cy - a) > -1) { //count down side
				Amount += 1;
				a += 1;
			}
		}
		break;
	}
	case 2: { //count left top to right bottom
		while (Amount <= 5 && Chess[cx + a][cy + a] == Player && (cx + a) < Width && (cy + a < Width)) { //count left top side
			Amount += 1;
			a += 1;
		}
		a = 1;
		if (Amount == WinAmount) {
			break;
		}
		else {
			while (Amount <= 5 && Chess[cx - a][cy - a] == Player && (cx - a) > -1 && (cy - a) > -1) { //count right bottom side
				Amount += 1;
				a += 1;
			}
		}
		break;
	}
	case 3: { //count right top to left bottom
		while (Amount <= 5 && Chess[cx - a][cy + a] == Player && (cx - a) > -1 && (cy + a < Width)) {  //count right top side
			Amount += 1;
			a += 1;
		}
		a = 1;
		if (Amount == WinAmount) {
			break;
		}
		else {
			while (Amount <= 5 && Chess[cx + a][cy - a] == Player && (cx + a) < Width && (cy - a) > -1) {
				Amount += 1;
				a += 1;
			}
		}
		break;
	}
	default:
		break;
	}
	return Amount;
}

int isWin(int Chess[Width][Width], int cx, int cy, int Player)
{
	int Result = 0;
	int k;
	for (k = 0; k < 4; k++) {
		if (count(Chess, cx, cy, Player, k) >= WinAmount) {
			Result = 1;
		}
	}
	return Result;
}

int Game() {
	int key;
	int getch();
	int x = 1, y = 1;
	int player = 1;   //1 is black,-1 is white
	int result = 0;
	char* color = BLACK;
	BOARD[x][y] = INIT;
	Draw();
	do {
		color = player == 1 ? BLACK : WHITE;
		printf("��ǰλ�ã�%d,%d��\n", (y + 1) / 2, (x + 1) / 2);
		printf("��ǰ��ɫ:%s\n", color);
		key = getch();
		if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = SPACE;
		switch (key)
		{
		case 's': {
			if (x < BOARDWITH - 2) x += 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'w': {
			if (x > 1) x -= 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'd': {
			if (y < BOARDWITH - 2) y += 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'a': {
			if (y > 1) y -= 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case ' ': {
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) {
				BOARD[x][y] = color;
				chess[(x + 1) / 2 - 1][(y + 1) / 2 - 1] = player;
				if (isWin(chess, (x + 1) / 2 - 1, (y + 1) / 2 - 1, player)) {

					Draw();
					switch (player)
					{
					case 1:printf("BLACK Win!\n"); break;
					case -1:printf("WHITE Win!\n"); break;
					default:
						break;
					}
					return 0;
				};
				player = (-1 * player);
			}
			break;
		}
		case -1:printf("error input");
		default:
			break;
		}
		Draw();
	} while (key != 0x1b);
}

int Repentance()//����
{

}

int AIGame()// human do first step
{
	int key;
	int getch();
	int x = 1, y = 1;
	int player = 1;   //1 is black,-1 is white
	int result = 0;
	char* color = BLACK;
	BOARD[x][y] = INIT;
	Draw();
	do {
		color = player == 1 ? BLACK : WHITE;
		printf("��ǰλ�ã�%d,%d��\n", (y + 1) / 2, (x + 1) / 2);
		printf("��ǰ��ɫ:%s\n", color);
		if (player == 1) {
			key = getch();
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = SPACE;
			switch (key)
			{
			case 's': {
				if (x < BOARDWITH - 2) x += 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'w': {
				if (x > 1) x -= 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'd': {
				if (y < BOARDWITH - 2) y += 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'a': {
				if (y > 1) y -= 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case ' ': {
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) {
					BOARD[x][y] = color;
					chess[(x + 1) / 2 - 1][(y + 1) / 2 - 1] = player;
					if (isWin(chess, (x + 1) / 2 - 1, (y + 1) / 2 - 1, player)) {

						Draw();
						switch (player)
						{
						case 1:printf("BLACK Win!\n"); break;
						case -1:printf("WHITE Win!\n"); break;
						default:
							break;
						}
						return 0;
					};
					player = (-1 * player);
				}
				break;
			}
			case -1:printf("error input");
			default:
				break;
			}
		}
		else {

			/*if (!) {
				attack();
			}*/
			defend((x + 1) / 2 - 1, (y + 1) / 2 - 1, player);

			player = -1 * player;
		}
		Draw();
		for (int t = 0; t < Width; t++) {
			for (int r = 0; r < Width; r++) {
				printf("%d  ", chess[t][r]);

			}
			printf("\n");
		}
	} while (key != 0x1b);

}

void move(int i, int j, int* x, int* y)//j=1:right,j=-1:left
{
	int mx = *x, my = *y;
	switch (i)
	{
	case 0: {
		mx = mx + j;
		break;
	}
	case 1: {
		my = my + j;
		break;
	}
	case 2: {
		mx = mx - j;
		my = my - j;
		break;
	}
	case 3: {
		mx = mx - j;
		my = my + j;
		break;
	}
	default:
		break;
	}
	*x = mx;
	*y = my;
}

int defend(int px, int py, int Player)
{
	int i, j = -1, k;
	int result = 0;
	char* Color = Player == 1 ? BLACK : WHITE;
	Player = -1 * Player;

	// prevent the situation 1101 or 1011
	int one[4] = { 1,1,0,1 };
	int two[4] = { 1,0,1,1 };
	// judge the row |
	for (k = 0; k < 4; k++) {
		if (px - k < 0 || (px - k + 3 > Width - 1)) {
			if (px - k < 0) {
				break;
			}
			else {
				continue;
			}
		}
		result = 1;
		for (j = 0; j < 4; j++) {
			result *= chess[px - k + j][py] == two[j];
		}
		if (result) {
			chess[px - k + 1][py] = (-1 * Player);
			BOARD[(px - k + 1) * 2 + 1][py * 2 + 1] = Color;
			break;
		}
		else {
			result = 1;
			for (j = 0; j < 4; j++) {
				result *= chess[px - k + j][py] == one[j];
			}
			if (result) {
				chess[px - k + 2][py] = (-1 * Player);
				BOARD[(px - k + 2) * 2 + 1][py * 2 + 1] = Color;
				break;
			}
		}

	}
	//judge the line --
	if (!result) {
		for (k = 0; k < 4; k++) {
			if (py - k < 0 || (py - k + 3 > Width - 1)) {
				if (py - k < 0) {
					break;
				}
				else {
					continue;
				}
			}
			result = 1;

			for (j = 0; j < 4; j++) {
				result *= chess[px][py - k + j] == two[j];
			}
			if (result) {
				chess[px][py - k + 1] = (-1 * Player);
				BOARD[px * 2 + 1][(py - k + 1) * 2 + 1] = Color;
				break;
			}
			else {
				result = 1;
				for (j = 0; j < 4; j++) {
					result *= chess[px][py - k + j] == one[j];
				}
				if (result) {
					chess[px][py - k + 2] = (-1 * Player);
					BOARD[px * 2 + 1][(py - k + 2) * 2 + 1] = Color;
					break;
				}
			}


		}
	}
	//judge the left top
	if (!result) {
		for (k = 0; k < 4; k++) {
			if (py - k < 0 || px - k < 0 || py - k + 3 > Width - 1 || px - k + 3 > Width - 1) {
				if (py - k < 0 || px - k < 0) {//���˴β��ҵ�����ڽ�����ֹͣ���Ҹ÷���
					break;
				}
				else {//���˴β��ҵ��յ��ڽ����������˴β��ң���ʼ��һ�β���
					continue;
				}
			}

			result = 1;

			for (j = 0; j < 4; j++) {
				result *= chess[px - k + j][py - k + j] == two[j];
			}
			if (result) {
				chess[px - k + 1][py - k + 1] = (-1 * Player);
				BOARD[(px - k + 1) * 2 + 1][(py - k + 1) * 2 + 1] = Color;
				break;
			}
			else {
				result = 1;
				for (j = 0; j < 4; j++) {
					result *= chess[px - k + j][py - k + j] == one[j];
				}
				if (result) {
					chess[px - k + 2][py - k + 2] = (-1 * Player);
					BOARD[(px - k + 2) * 2 + 1][(py - k + 2) * 2 + 1] = Color;
					break;
				}
			}

		}
	}
	//judge the right top /
	if (!result) {
		for (k = 0; k < 4; k++) {
			if (px - k < 0 || py + k > Width - 1 || px - k + 3 > Width - 1 || py + k - 3 < 0) {
				if (px - k < 0 || py + k > Width - 1) {
					break;
				}
				else {
					continue;
				}
			}
			result = 1;

			for (j = 0; j < 4; j++) {
				result *= chess[px - k + j][py + k - j] == two[j];
			}
			if (result) {
				chess[px - k + 1][py + k - 1] = (-1 * Player);
				BOARD[(px - k + 1) * 2 + 1][(py + k - 1) * 2 + 1] = Color;
				break;
			}
			else {
				result = 1;
				for (j = 0; j < 4; j++) {
					result *= chess[px - k + j][py + k - j] == one[j];
				}
				if (result) {
					chess[px - k + 2][py + k - 2] = (-1 * Player);
					BOARD[(px - k + 2) * 2 + 1][(py + k - 2) * 2 + 1] = Color;
					break;
				}
			}

		}
	}

	// three or four in a row
	if (!result) {
		for (i = 0; i < 4; i++) {
			if (count(chess, px, py, Player, i) == 4) {
				j = i;
				//printf("(%d,%d),4", px, py);
			}
			else if (count(chess, px, py, Player, i) == 3 && j == -1) {
				j = i;
				//printf("(%d,%d),3", px, py);
			}
		}
		int dx[2] = { px,px }, dy[2] = { py,py };
		switch (count(chess, px, py, Player, j))
		{
		case 3: {
			k = -1;
			while (chess[dx[1]][dy[1]] == Player)
			{
				move(j, k, &dx[1], &dy[1]);
				if (dx[1] < 0 || dy[1] < 0) {
					dx[1] = dx[0];
					dy[1] = dy[0];
					break;
				}

			}
			if (chess[dx[1]][dy[1]] == 0) {
				chess[dx[1]][dy[1]] = (-1 * Player);
				BOARD[(dx[1] * 2) + 1][(dy[1] * 2) + 1] = Color;
				result = 1;
			}
			break;
		}
		case 4: {
			k = 1;
			while (chess[dx[1]][dy[1]] == Player)
			{
				move(j, k, &dx[1], &dy[1]);
				if (dx[1] > Width || dy[1] > Width) {
					dx[1] = dx[0];
					dy[1] = dy[0];
					break;
				}

			}
			if (chess[dx[1]][dy[1]] == 0) {
				chess[dx[1]][dy[1]] = (-1 * Player);
				BOARD[(dx[1] * 2) + 1][(dy[1] * 2) + 1] = Color;
				result = 1;
			}
			break;
		}
		default:
			break;
		}
	}

	return result;
}

int attack()
{

}

int isForbidden()//�ж��Ƿ��ǽ���
{

}

void welcome() {
	int gamemode = 0;
	printf("*****������*****\n");
	printf("1.˫�˶�ս\n");
	printf("2.�˻���ս\n");
	scanf_s("%d", &gamemode);
	if (gamemode == 1) Game();
	else AIGame();
}