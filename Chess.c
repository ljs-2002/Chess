#include<stdio.h>

#define Width 15          //standard size of the board
#define WinAmount 5       //chess amount to win
#define BOARDWIDTH 2*Width+1 //9 board contain 1 chess

//the chess
const char* WHITE = "○", * BLACK = "●"; *INIT = "¤";
int chess[Width][Width] = { 0 };
int rechess[Width][Width] = { 0 };

//the board
const char* LT = "┌", * TOP = "┬", * RT = "┐";
const char* LEFT = "├", * CENTER = "┼", * RIGHT = "┤";
const char* LB = "└", * BOTTON = "┴", * RB = "┘";
const char* SPACE = " ";
char* BOARD[BOARDWIDTH][BOARDWIDTH];
char* REBOARD[BOARDWIDTH][BOARDWIDTH];

void InitBoard();//initialize the board

void Draw();     //draw the board

int Game();      //the game

void isWin();     //judge whether the player win

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
		printf("是否退出游戏?\n");
	} while (getch() != 0x1b);
	system("pause");

	return 0;
}

void InitBoard()
{
	int i, j;
	BOARD[0][0] = LT;
	BOARD[0][BOARDWIDTH - 1] = RT;
	BOARD[BOARDWIDTH - 1][0] = LB;
	BOARD[BOARDWIDTH - 1][BOARDWIDTH - 1] = RB;
	for (i = 0; i < BOARDWIDTH; i++) {			//TODO:simplify this
		for (j = 0; j < BOARDWIDTH; j++) {
			if (((i == 0) || (i == BOARDWIDTH - 1)) && ((j == 0) || (j == BOARDWIDTH - 1))) {
				continue;
			}
			else {
				switch (i)
				{
				case 0:BOARD[i][j] = TOP; break;
				case BOARDWIDTH - 1:BOARD[i][j] = BOTTON; break;
				default: {
					if (j == 0 || j == BOARDWIDTH - 1) {
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
	for (i = 0; i < BOARDWIDTH; i++) {
		for (j = 0; j < BOARDWIDTH; j++) {
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

void isWin(int Chess[Width][Width], int cx, int cy, int* player)
{
	int Result = 0;
	int k;
	int Player = *player;
	for (k = 0; k < 4; k++) {
		if (count(Chess, cx, cy, Player, k) >= WinAmount) {
			Result = 1;
		}
	}
	if (Result) {
		Draw();
		switch (Player)
		{
		case 1: {
			printf("BLACK Win!\n");
			break;
		}
		case -1: {
			printf("WHITE Win!\n"); 
			break;
		}
		default:
			break;
		}
		Player = 0;
	};
	*player = -1 * Player;
}

void Repentance(int* player, int* re, int mod)//悔棋,mod=1是储存模式，mod=2是复位模式
{
	switch (mod)
	{
	case 1: {
		for (int i = 0; i < BOARDWIDTH; i++) {
			for (int j = 0; j < BOARDWIDTH; j++) {
				REBOARD[i][j] = BOARD[i][j];
			}
		}
		for (int i = 0; i < Width; i++) {
			for (int j = 0; j < Width; j++) {
				rechess[i][j] = chess[i][j];
			}
		}
		*re = 1;//更新悔棋状态
		break;
	}
	case 2: {
		//将棋盘状态恢复到上一次落子
		int player_now = *player;
		for (int i = 0; i < BOARDWIDTH; i++) {
			for (int j = 0; j < BOARDWIDTH; j++) {
				BOARD[i][j] = REBOARD[i][j];
			}
		}
		for (int i = 0; i < Width; i++) {
			for (int j = 0; j < Width; j++) {
				chess[i][j] = rechess[i][j];
			}
		}
		//切换下棋的人
		*re = 0;//更新悔棋状态
		*player = (-1) * player_now;
		break;
	}
	default:
		break;
	}
}

int Game() {
	int key;
	int getch();
	int x = 1, y = 1;
	int player = 1;   //1 is black,-1 is white
	int result = 0;
	int re = 0;//判断是否可以悔棋，若在上次悔棋后没有落子则不能悔棋，re=0
	char* color = BLACK;
	BOARD[x][y] = INIT;

	//初始先储存一次棋盘状态
	Repentance(&player, &re, 1);

	Draw();
	do {
		color = player == 1 ? BLACK : WHITE;
		printf("当前位置（%d,%d）\n", (y + 1) / 2, (x + 1) / 2);
		printf("当前颜色:%s\n", color);

		key = getch();
		if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = SPACE;
		switch (key)
		{
		case 's': {
			if (x < BOARDWIDTH - 2) x += 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'w': {
			if (x > 1) x -= 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'd': {
			if (y < BOARDWIDTH - 2) y += 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'a': {
			if (y > 1) y -= 2;
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
			break;
		}
		case 'r': {
			if (re) {
				Repentance(&player, &re, 2);
			}
			break;
		}
		case ' ': {
			//落子时先储存当前棋盘状态
			Repentance(&player, &re, 1);

			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) {
				BOARD[x][y] = color;
				chess[(x + 1) / 2 - 1][(y + 1) / 2 - 1] = player;
				//判断输赢
				isWin(chess, (x + 1) / 2 - 1, (y + 1) / 2 - 1, &player);
				if (player == 0) {
					return 0;
				}
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

int AIGame()// human do first step
{
	int key;
	int getch();
	int x = 1, y = 1;
	int player = 1;   //1 is black,-1 is white
	int result = 0;
	int re = 0;
	char* color = BLACK;
	BOARD[x][y] = INIT;

	//先储存初始棋盘状态
	Repentance(&player, &re, 1);
	Draw();
	do {
		color = player == 1 ? BLACK : WHITE;
		printf("当前位置（%d,%d）\n", (y + 1) / 2, (x + 1) / 2);
		printf("当前颜色:%s\n", color);
		/*-------------------------------以下人类------------------------------------------*/
		if (player == 1) {
			key = getch();
			if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = SPACE;
			switch (key)
			{
			case 's': {
				if (x < BOARDWIDTH - 2) x += 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'w': {
				if (x > 1) x -= 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'd': {
				if (y < BOARDWIDTH - 2) y += 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'a': {
				if (y > 1) y -= 2;
				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) BOARD[x][y] = INIT;
				break;
			}
			case 'r': {
				if (re) {
					Repentance(&player, &re, 2);
					player *= -1;
				}
				break;
			}
			case ' ': {

				//落子时先储存当前棋盘状态
				Repentance(&player, &re, 1);

				if (BOARD[x][y] != WHITE && BOARD[x][y] != BLACK) {
					BOARD[x][y] = color;
					chess[(x + 1) / 2 - 1][(y + 1) / 2 - 1] = player;
					//判断输赢
					isWin(chess, (x + 1) / 2 - 1, (y + 1) / 2 - 1, &player);
					if (player == 0) {
						return 0;
					}
				}
				break;
			}
			case -1:printf("error input");
			default:
				break;
			}
		}/*-------------------------------以下机器------------------------------------------*/
		else {
			/*if (!) {
				attack();
			}*/
			x = (x + 1) / 2 - 1;
			y = (y + 1) / 2 - 1;
			result = defend(&x, &y, player);
			//判断输赢
			isWin(chess, (x + 1) / 2 - 1, (y + 1) / 2 - 1, &player);
			if (player == 0) {
				return 0;
			}
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

int defend(int* x, int* y, int Player)
{
	int i, j, k, px = *x, py = *y;
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
			*x = (px - k + 1) * 2 + 1, * y = py * 2 + 1;
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
				*x = (px - k + 2) * 2 + 1, * y = py * 2 + 1;
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
				*x = px * 2 + 1, * y = (py - k + 1) * 2 + 1;
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
					*x = px * 2 + 1, * y = (py - k + 2) * 2 + 1;
					break;
				}
			}


		}
	}
	//judge the left top
	if (!result) {
		for (k = 0; k < 4; k++) {
			if (py - k < 0 || px - k < 0 || py - k + 3 > Width - 1 || px - k + 3 > Width - 1) {
				if (py - k < 0 || px - k < 0) {//若此次查找的起点在界外则停止查找该方向
					break;
				}
				else {//若此次查找的终点在界外则跳过此次查找，开始下一次查找
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
				*x = (px - k + 1) * 2 + 1, * y = (py - k + 1) * 2 + 1;
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
					*x = (px - k + 2) * 2 + 1, * y = (py - k + 2) * 2 + 1;
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
				*x = (px - k + 1) * 2 + 1, * y = (py + k - 1) * 2 + 1;
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
					*x = (px - k + 2) * 2 + 1, * y = (py + k - 2) * 2 + 1;
					break;
				}
			}

		}
	}

	// three or four in a row
	if (!result) {
		j = -1;
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
		if (j != -1) {
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
					*x = (dx[1] * 2) + 1, * y = (dy[1] * 2) + 1;
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
					*x = (dx[1] * 2) + 1, * y = (dy[1] * 2) + 1;
					result = 1;
				}
				break;
			}
			default:
				break;
			}
		}
	}
	if (!result) {
		*x = 2 * (px + 1) - 1;
		*y = 2 * (py + 1) - 1;
	}

	return result;
}

int attack()
{

}

int isForbidden()//判断是否是禁手
{

}

void welcome() {
	int gamemode = 0;
	int getch();
	printf("*****五子棋*****\n");
	printf("1.双人对战\n");
	printf("2.人机对战\n");
	printf("按esc键退出\n");
	gamemode = getch();
	if (gamemode == 49) Game();
	else if (gamemode == 50) AIGame();
	else if (gamemode == 0x1b) return 0;
}