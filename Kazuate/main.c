#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int input_num, ans_num;

	printf("”‚ğ“–‚Ä‚Ä‚Ë\n");

	ans_num = rand() % 100;
	scanf("%d", &input_num);

	while(input_num != ans_num)
	{
		if(input_num < ans_num)
		{
			printf("‚à‚Á‚Æ‘å‚«‚È”‚Å‚·\n");
		}
		else
		{
			printf("‚à‚Á‚Æ¬‚³‚È”‚Å‚·\n");
		}
		scanf("%d", &input_num);
	}
	printf("³‰ğ‚Í %d ‚Å‚µ‚½I‚¨‚ß‚Å‚Æ‚¤I\n", ans_num);

	return 0;
}



