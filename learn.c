#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int main()
{
	
	int a=5;
	
	float f=((float)a)/4;
	
	printf("%f\n",f);
	

	srand(time(0));
	
	for(int i=0;i<10;i++)
	{
		
		
		printf("%d\n",rand()%15);
	}	
	
	return 0;
		
}
