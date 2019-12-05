#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include "stack_linked_list.h"

bool checkLeftVaildSign(char expression[], int i) {
	if (i == 0) {
		return false;
	}

	else if (expression[i - 1] == '+' || expression[i - 1] == '-' || expression[i - 1] == '*' || expression[i - 1] == '/' || expression[i - 1] == '(') {
		return false;
	}

	else if (expression[i - 1] == ')' || expression[i - 1] == ' ') {
		if (!checkLeftVaildSign(expression, i - 1)) {
			return false;
		}
	}
	return true;
}

bool checkRightVaildSign(char expression[], int i) {
	if (expression[i + 1] == '\0') {
		return false;
	}
	else if (expression[i + 1] == '+' || expression[i + 1] == '-' || expression[i + 1] == '*' || expression[i + 1] == '/' || expression[i + 1] == ')') {
		return false;
	}

	else if (expression[i + 1] == '(' || expression[i + 1] == ' ') {
		if (!checkRightVaildSign(expression, i + 1)) {
			return false;
		}
	}
	return true;
}

bool checkVaildSign(char expression[], int i) {
	if (!checkLeftVaildSign(expression, i) || !checkRightVaildSign(expression, i)) {
		return false;
	}
	return true;
}

void Calculate(Stack* nums, char sign) {
	double calY = Pop(nums);
	double calX = Pop(nums);

	printf("%c ", sign);

	if (sign == '+') {
		Push(nums, calX + calY);
	}
	else if (sign == '-') {
		Push(nums, calX - calY);
	}
	else if (sign == '*') {
		Push(nums, calX * calY);
	}
	else if (sign == '/') {
		Push(nums, calX / calY);
	}

}

int main(void) {
	int i = 0;
	double answer = 0;
	int check_scan = 0;

	char expression[50] = { 0, };

	int num = 0;
	char sign = 0;
	int branket = 0;
	char beforeSign = 0;

	printf("Write expression: ");
	
	check_scan = scanf("%[^\n]s", expression);
	if (check_scan == 0) {
		printf("[Message]No expression input.\n");
		return 1;
	}

	Stack* nums = CreateStack(20);
	Stack* signs = CreateStack(20);

	Push(signs, (char)'\0');


	printf("Postfix : ");
	for (i = 0; i < 100; i++) {
		if ('0' <= expression[i] && expression[i] <= '9') {
			num = num * 10 + expression[i] - '0';
			if ('0' > expression[i + 1] || expression[i + 1] > '9') {
				Push(nums, (double)num);
				printf("%d ", num);
				num = 0;
			}
		}

		else if (expression[i] == '(') {
			Push(signs, (double)expression[i]);
			branket++;
		}

		else if (expression[i] == ')') {
			beforeSign = (char)Pop(signs);
			while (beforeSign != '(') {
				Calculate(nums, beforeSign);
				beforeSign = (char)Pop(signs);
			}

			if (--branket == -1) {
				printf("\n[Error] Wrong Expression. ): %d\n", i + 1);
				return -2;
			}
		}

		else if (expression[i] == '+') {
			beforeSign = (char)Pop(signs);
			while (beforeSign == '+' || beforeSign == '-' || beforeSign == '*' || beforeSign == '/') {
				Calculate(nums, beforeSign);
				beforeSign = (char)Pop(signs);
			}
			Push(signs, (double)beforeSign);

			Push(signs, (double)expression[i]);
			if (!checkVaildSign(expression, i)) {
				printf("\n[Error] Wrong Expression. +: %d\n", i + 1);
					return -3;
			}
		}
		else if (expression[i] == '-') {
			beforeSign = (char)Pop(signs);
			while (beforeSign == '+' || beforeSign == '-' || beforeSign == '*' || beforeSign == '/') {
				Calculate(nums, beforeSign);
				beforeSign = (char)Pop(signs);
			}
			Push(signs, (double)beforeSign);

			Push(signs, (double)expression[i]);
			if (!checkVaildSign(expression, i)) {
				printf("\n[Error] Wrong Expression. -: %d\n", i + 1);
				return -3;
			}
		}
		else if (expression[i] == '*') {
			beforeSign = (char)Pop(signs);
			if (beforeSign == '*' || beforeSign == '/') {
				Calculate(nums, beforeSign);
			}
			else {
				Push(signs, (double)beforeSign);
			}

			Push(signs, (double)expression[i]);
			if (!checkVaildSign(expression, i)) {
				printf("\n[Error] Wrong Expression. *: %d\n", i + 1);
				return -3;
			}
		}
		else if (expression[i] == '/') {
			beforeSign = (char)Pop(signs);
			if (beforeSign == '*' || beforeSign == '/') {
				Calculate(nums, beforeSign);
			}
			else {
				Push(signs, (double)beforeSign);
			}
			Push(signs, (double)expression[i]);
			if (!checkVaildSign(expression, i)) {
				printf("\n[Error] Wrong Expression. /: %d\n", i + 1);
				return -3;
			}
		}
		else if (expression[i] == '\0') {
			break;
		}
		else if (expression[i] != ' ') {
			printf("\n[Error]Not expected char.\n");
			return -1;
		}
	}

	while (CountStackItem(signs) != 1) {
		beforeSign = (char)Pop(signs);
		Calculate(nums, beforeSign);
	}


	printf("\nResult is : %g\n", Pop(nums));

	DestroyStack(nums);
	DestroyStack(signs);

	printf("Successfully exit.\n");
	return 0;
}