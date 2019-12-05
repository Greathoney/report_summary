#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int RecusiveBinSearch(int nArr[], int nBegin, int nEnd, int nTarget)
{
	int nMid = 0;

	if (nBegin > nEnd)
	{
		return -1;
	}

	nMid = (nBegin + nEnd) / 2;

	if (nArr[nMid] == nTarget)
	{
		return nMid;
	}
	else if (nTarget < nArr[nMid])
	{
		return RecusiveBinSearch(nArr, nBegin, nMid - 1, nTarget);
	}
	else
	{
		return RecusiveBinSearch(nArr, nMid + 1, nEnd, nTarget);
	}
}

int main(void)
{
	int i;
	int menu, search;

	int nArr[200] = { 0, };
	for (i = 0; i < 200; i++){
		nArr[i] = 2 * i + 1;
	}
	int nResult;

	printf("data in Array: ");
	for (i = 0; i < sizeof(nArr) / sizeof(int); ++i)
	{
		printf("%d ", nArr[i]);
	}

	printf("\n");

	while (1) {

		printf("1) search, 2) exit. : ");
		scanf("%d", &menu);

		switch (menu) {
		case 1:
			printf("Input to search. : ");
			scanf("%d", &search);

			nResult = RecusiveBinSearch(nArr, 0, sizeof(nArr) / sizeof(int) - 1, search);

			if (nResult == -1)
			{
				printf("There's no %d.\n", search);
			}
			else
			{
				printf("There's %d in index %d.\n", search, nResult);
			}
			break;
		case 2:
			printf("program exits.\n\n");
			return 0;
		}

		printf("\n");

	}
	return 0;
}
