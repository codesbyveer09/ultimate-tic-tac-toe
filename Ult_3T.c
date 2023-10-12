#include <stdio.h>
#include <stdlib.h>

char SBLS[3] = {' ', 'O', 'X'};

void disp(char big_arr[9][9], int b_pos)
{
	char s[] = "---------------+---------------+---------------", ss[] = "|", sss[] = "  -----------  |  -----------  |  -----------", ssss[] = "               |               |               ";
	system("cls");
	
	for (int i = 1; i <= 81; i++)
	{
		if ((i-1)%9 == 0)							printf("  ");
		
		int y = ((i-1)/3)%3 + 3*((i-1)/27), x = (i-1)%3 + 3*(((i-1)/9)%3);
		printf(" %c ", SBLS[big_arr[y][x]]);

		if (i%3)								printf("%s", ss);
		if (i%81)
		{
			if (i%3 == 0 && i%9)				printf("  %s  ", ss);
			if (i%27 == 0)						printf("\n%s\n%s\n%s\n", ssss, s, ssss);
			else if (i%9 == 0)					printf("\n%s\n", sss);
		}
	}
	printf("\n\n");
}


int chkbrd(char big_arr[9])
{
	int hz[2] = {}, tie = 0, vt[2][3] = {}, dg[2][2] = {};										//		--  |  \  /
	for (int i = 0; i < 9; i++)
	{
		if (!(i%3))
			hz[0] = 0, hz[1] = 0;
		if (big_arr[i])
		{
			hz[big_arr[i] - 1]++;
			vt[big_arr[i] - 1][i%3]++;

			if (i == 4)
				dg[1][big_arr[i] - 1]++, dg[0][big_arr[i] - 1]++;
			else if (!(i%4))
				dg[1][big_arr[i] - 1]++;
			else if (!(i%2))
				dg[0][big_arr[i] - 1]++;
		}
		if (hz[0] == 3)
			return 1;
		else if (hz[1] == 3)
			return 2;
		else if (hz[0] && hz[1])
			tie++;
	}

	for (int i = 0; i < 3; i++)
	{
		if (vt[0][i] == 3)
			return 1;
		else if (vt[1][i] == 3)
			return 2;
		else if (vt[0][i] && vt[1][i])
			tie++;
	}
	for (int i = 0; i < 2; i++)
	{
		if (dg[i][0] == 3)
			return 1;
		else if (dg[i][1] == 3)
			return 2;
		else if (dg[0][i] && dg[1][i])
			tie++;
	}
	if (tie == 8)
		return 3;
	return 0;
}

void main()
{
	char ipt = ' ', big_arr[9][9] = {}, ult_arr[9] = {};
	int b_pos = 0, s_pos = 0, turn = 0;

	system("cls");

	//disp(big_arr);

	while (ipt != 'X' && ipt != 'O')
	{
		printf("Player 1, Enter Your Choice (X/O): ");
		ipt = getchar(), getchar();//to avoid printf loops
		ipt = (ipt >= 'a' && ipt <= 'z') ? ipt-32 : ipt;
	}

	if (ipt == 'X')		SBLS[1] = 'X', SBLS[2] = 'O';
	else				SBLS[1] = 'O', SBLS[2] = 'X';

	printf("\nPlayer 1 : %c\nPlayer 2 : %c\n", SBLS[1], SBLS[2]);


	do
	{
		b_pos = 0;
		printf("Player 2, Enter Super Pos(1-9): ");
		b_pos = getchar() - '1', getchar();
	}
	while (((0 > b_pos) || (b_pos > 8)) || (ult_arr[b_pos] != 0));


	int cpl_w = 0;																	//CAP		WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW
	int sml_w = 0;																	//Smol    	wwwwwwwwwwwwwwwwwwwwwwwwwwwwwww

	while (!cpl_w)
	{
		
		while (!sml_w)
		{
			do
			{
				s_pos = 0;
				printf("\nCurrent Game: %d", b_pos+1);
				printf("\nPlayer %d/%c,\nEnter Pos(1-9): ", turn+1, SBLS[turn+1]);
				s_pos = getchar() - '1', getchar();
				
			}
			while (((0 > s_pos) || (s_pos > 8)) || (big_arr[b_pos][s_pos] != 0));

			big_arr[b_pos][s_pos] = turn+1;
			disp(big_arr, b_pos);

			for (int i = 0; i < 9; i++)
			{
				if (ult_arr[i] != chkbrd(big_arr[i]))
				{
					ult_arr[i] = sml_w = chkbrd(big_arr[i]);
				}
			}

			b_pos = s_pos;
			turn = (turn+1)%2;
		}

		if (sml_w == 3)
			printf("Ohh... It was a Tie...");
		else
			printf("Yaay!! Player %d/%c Won Game %d!!", sml_w, SBLS[sml_w], b_pos);
		
		cpl_w = chkbrd(ult_arr);
		sml_w = 0;
	}
	if (cpl_w == 3)
		printf("Ohh... It was a Tie...");
	else
		printf("Yaay!! Player %d/%c Won The\n\t\t\tULTIMATE\n\t\t\t\tTIC\n\t\t\t\t\t\tTAC\n\t\t\t\t\t\t\t\tTOE!!", cpl_w, SBLS[cpl_w]);
}
