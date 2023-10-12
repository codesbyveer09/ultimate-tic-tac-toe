#include <stdio.h>
#include <stdlib.h>

char SBLS[3] = {' ', 'O', 'X'};


void disp(char big_arr[9])
{
	char s[] = "-----------", ss[] = "|";
	
	system("cls");
	printf("\n");
	
	for (int i = 0; i < 9; i++)
	{
		printf(" %c ", SBLS[big_arr[i]]), ( ((i+1)%3) ? printf("%s", ss) : ( (i == 8) ? printf("\n") : printf("\n%s\n", s) ) );
	}

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
	char ipt = ' ', big_arr[9] = {}, ult_arr[9] = {};
	int pos, i = 0;

	while (ipt != 'X' && ipt != 'O')
	{
		printf("Player 1, Enter Your Choice (X/O): ");
		ipt = getchar(), getchar();//to avoid printf loops
		ipt = (ipt >= 'a' && ipt <= 'z') ? ipt-32 : ipt;
	}

	if (ipt == 'X')		SBLS[1] = 'X', SBLS[2] = 'O';
	else				SBLS[1] = 'O', SBLS[2] = 'X';

	printf("Player 2 : %c\n\n", SBLS[2]);
	int cap_w = chkbrd(big_arr);												//Capital WWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWWW

	while (!cap_w)
	{
		do
		{
			pos = 0;
			printf("Player %d/%c's Turn\nEnter Pos(1-9): ", i+1, SBLS[i+1]);
			scanf("%d", &pos);
			pos--;
		}
		while (((0 > pos) || (pos > 8)) || (big_arr[pos] != 0));

		big_arr[pos] = i+1;
		disp(big_arr);
		i=(++i)%2;
		cap_w = chkbrd(big_arr);
	}

	if (cap_w == 3)
		printf("Ohh... It was a Tie...");
	else
		printf("Yaay!! Player %d/%c Won!!", cap_w, SBLS[cap_w]);
}
