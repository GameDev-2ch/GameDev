#include <stdio.h>
#include <stdlib.h>

int main(void)
{
	int input_num, ans_num;

	printf("���𓖂ĂĂ�\n");

	ans_num = rand() % 100;
	scanf("%d", &input_num);

	while(input_num != ans_num)
	{
		if(input_num < ans_num)
		{
			printf("�����Ƒ傫�Ȑ��ł�\n");
		}
		else
		{
			printf("�����Ə����Ȑ��ł�\n");
		}
		scanf("%d", &input_num);
	}
	printf("������ %d �ł����I���߂łƂ��I\n", ans_num);

	return 0;
}



