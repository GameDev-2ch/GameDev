#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int input_num, ans_num;

	printf("意識を集中して。頭に浮かんだ数は何でしょう\n");

	ans_num = rand() % 100;
	scanf("%d", &input_num);

	while(input_num != ans_num)
	{
		if(input_num < ans_num)
		{
			printf("もっと大きな数です\n");
		}
		else
		{
			printf("もっと小さな数です\n");
		}
		scanf("%d", &input_num);
	}
	printf("正解は %d でした！おめでとう！\n", ans_num);

	return 0;
}

