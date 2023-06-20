#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "math.h"

void ReadCSV(char WordList[][50])
{
	char tmp[1024];
	char *token;
	FILE *fp = fopen("EnWords/EnWords.csv", "r");

	if (fp == NULL)
	{
		fprintf(stderr, "No such file!");
		exit(EXIT_FAILURE);
	}

	for (long long int i = 0LL; i < 103978LL; i++)
	{
		if (i == 0LL)
		{
			;
		}
		else
		{
			fgets(tmp, 1024, fp);
			//printf("%s\n", tmp);
			token = strtok(tmp, "\"");
			//printf("%s\n", token);
			strcpy(WordList[i - 1], token);
			//printf("%s\n", WordList[i - 1]);
		}
	}
}

//	printf("%s\n", WordList[1]);

/*int _min(int num_1, int num_2, int num_3)
{
	int min;

	if (num_1 < num_2)
	{
		min = num_1;
	}
	else
	{
		min = num_2;
	}

	if (min > num_3)
	{
		min = num_3;
	}

	return min;
}*/

int LD(char str_1[], char str_2[])
{
	int len_1 = strlen(str_1);
	int len_2 = strlen(str_2);
	int res;
	//printf("%d %d\n", len_1, len_2);
	int matrix[len_1 + 1][len_2 + 1];

	for (int i = 0; i < len_1 + 1; i++)
	{
		matrix[i][0] = i;
//		printf("%d ", matrix[i][0]);
	}

//	printf("\n");

	for (int i = 0; i < len_2 + 1; i++)
	{
		matrix[0][i] = i;
//		printf("%d ", matrix[0][i]);
	}

	for (int i = 1; i < len_1 + 1; i++)
	{
		for (int j = 1; j < len_2 + 1; j++)
		{
			if (str_1[i - 1] == str_2[j - 1])
			{
				matrix[i][j] = fmin(matrix[i - 1][j - 1], fmin(matrix[i - 1][j] + 1, matrix[i][j - 1] + 1));
			}
			else
			{
				matrix[i][j] = fmin(matrix[i - 1][j - 1], fmin(matrix[i - 1][j], matrix[i][j - 1])) + 1;
			}
		}
	}

	res = matrix[len_1][len_2];
	//printf ("%d\n", res);
	
	return res;
}

int main(void)
{
	char WordList[103980][50];
	printf("Loading database...\n");
	ReadCSV(WordList);
	printf("Database loading finished.\n");
	//fflush(stdout);
	system("sleep 1 && clear");
	char input[50];
	int min_index = 0;
	int min = 9999;

	while (1)
	{
//		int min_index;
		min = 9999;

		printf("Here is a Spell Checker, please input the word.\nIf you want to quit, please input \"q\".\n");
		scanf("%s", input);		
//		printf("%d\n", LD(input, WordList[1]));
		
		if (strlen(input) == 1 && (input[0] == 'q' || input[0] == 'Q'))
		{
			break;
		}
		else
		{
			for (long long int i = 1LL; i < 103978LL; i++)
			{
				int tmp = LD(input, WordList[i]);
				if (tmp < min)
				{
					min = tmp;
					min_index = i;
				}
			}

//			printf("%d\n", min);

			if (min == 0)
			{
				printf("Correct spelling :)\n");
				system("echo Press any key to continue. && read -n 1 && clear");
			}
			else if (min == fmax(strlen(input), strlen(WordList[min_index])))
			{
				printf("We can't find the word in the database, maybe you can google it ):\n");
				system("echo Press any key to continue. && read -n 1 && clear");
			}
			else
			{
				printf("Misspell ):\n");
				printf("Do you mean \"%s\"?\n", WordList[min_index]);
				system("echo Press any key to continue. && read -n 1 && clear");
			}
		}
	}

	/*long long int avrage = 0LL;
	for (long long int i = 0LL; i < 103978LL; i++)
	{
		avrage += strlen(WordList[i]);

		//printf("%d\n", avrage / 103976);
	}
	printf("%d\n", avrage / 103976);*/
	
	system("clear");
	printf("Thanks for using!\n");
	system("sleep 1 && clear");
//	system("clear");

	return 0;
}
