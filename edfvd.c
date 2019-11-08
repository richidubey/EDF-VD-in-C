//Currrent 8th Nov 15:24 status: Preemption Not Enabled :'( 

#include<stdio.h>
#include<stdbool.h>		//To use bool in C, this header file is required.
#include<limits.h>		//For INT_MAX
#include<stdlib.h>	//For random numbers generation
#include<time.h>	//For seeding with currrent time
int main()
{
	
	int X,n;
	
	
	printf("\t\tHello\n\nEnter the System's Criticality Level : ");
	scanf("%d",&X);
	
	
	printf("Enter number of Tasks: ");
	scanf("%d",&n);	

	float r[n],d[n],p[n],C[n][X];
	float c[n][X];
	int x[n];
	
	for(int i=0;i<n;i++)
	{
		printf("\n\tFor Task %d",i+1);
		
		printf("\nRelease Time : ");
		scanf("%f",&r[i]);
		
		printf("Deadline : ");
		scanf("%f",&d[i]);
		
		p[i]=d[i]-r[i];
		
		entcri:
		printf("Criticality : ");
		scanf("%d",&x[i]);
		
		if(x[i]>2)
		{
			printf("\n!!Criticality Greater than 2 not accepted. Please try again!\n\n");
			goto entcri;
		}
		
		for(int j=0;j<x[i];j++)
		{
			printf("WCET at level %d:",j+1);
			scanf("%f",&C[i][j]);
		}
	}	
	
	printf("\n\n-----------------Entry Completed---------------\n");	
	
	
	float u11=0,u22=0,u21=0;
	
	for(int i=0;i<n;i++)
	{
		if(x[i]==1)
		u11+=((float)C[i][0]/(d[i]-r[i]));
		
		if(x[i]==2)
		{
		u21+=((float)C[i][0]/(d[i]-r[i]));
		u22+=((float)C[i][1]/(d[i]-r[i]));
		}
	}
	
	int work;
	
	if(u11+u22<=1)
	{	
		work=1;
		printf("\nThis Falls in case 1, i.e. U1(1) + U2(2) <=1\n");
	}
	else if (u11+(u21/(1-u22))<=1)
	{
		work=2;
		printf("\nThis Falls in case 2, i.e. U1(1) + U2(1)/1-U2(2) <=1\n");
	}
	
	
	
	else
	{ 
		printf("Doesnt belong to any case! \n");	
		printf("\nWith U1(1) = %f, U2(1) = %f, U2(2)=%f\n",u11,u21,u22);
		return 0;
	}
	
	printf("\nWith U1(1) = %f, U2(1) = %f, U2(2)=%f\n",u11,u21,u22);
	

		
	for(int i=0;i<n;i++)
	{
		printf("\n**For Task %d\n",i+1);
		
		for(int j=0;j<x[i];j++)		
		{	
			srand(time(0));					//To seed with current time
		//	float use=(float)rand()/((float)(RAND_MAX/((float)C[i][j])))+0.5*(float)C[i][j];		//So final value lies anywhere from .5C[i][j] to 1.5C[i][j]. Yay.
			
			
//Doubt : How to change this range and which range is better and more awesome? 
			
			
			float use;
			
			int choice=rand()%2;
			
			
			use=((float)rand()/(float)(RAND_MAX))*((float)C[i][j]-(float).7*C[i][j])+(float).7*C[i][j];	//To gen random nos. between .7 to 1.0 	
			
			
		//	else 
		//	{
				
				
		//		if(choice==0)
		//			use=((float)rand()/(float)(RAND_MAX))*((float)C[i][j]-(float).7*C[i][j])+(float).7*C[i][j];	//To gen random nos. between .7 to 1.0
					
		//		else 
		//			use=((float)rand()/(float)(RAND_MAX))*((float)C[i][1]-(float).7*C[i][1])+(float).7*C[i][1];	//To gen random nos. between .7 to 1.0
				
				
		//	}
			c[i][j]=use;
			printf("Level  %d's Realised Value: %f\n",j+1,c[i][j]);
			printf("Level  %d's entered WCET  : %f\n",j+1,C[i][j]); 
		//	if(choice==1)
		//	printf("Task %d is executing in Level 2",i+1);
		}
	}	
	
	printf("\n");
	
	int predict[n],choose;
	
	for(int i=0;i<n;i++)
	{
		predict[i]=0;
		
		if(x[i]==1)
		continue;
		
		choose=rand()%2;
		
		if(choose==1)
		{
			predict[i]=1;
			printf("**Task %d choosen for Level 2\n",i+1);
		}
		
	}
	
printf("\n\n---------------------Scheduling Started-------------------\n");
		
	if(work==1)	//1st Case
	{
		//Apply EDF to normal unmodified deadlines, if system reaches level 2, discard all level 1 jobs and execute only level 2 jobs.
		
	// Step 1 : Applying EDF
	
		bool done[n];		//notes whether a task is completed or not
		
		
		for(int i=0;i<n;i++)
		done[i]=false;
		
		
		int min=INT_MAX,mintask,count=0,level=1;
		
		float t=0;
		
			//t is current system time
		
		while(count!=n&&level==1)
		{
			for(int i=0;i<n;i++)
			{
				if(d[i]<min && done[i]==false)
				{
					min=d[i];
					mintask=i;
				}
			}
			
			
			
			
			if(r[mintask]>t)
			t=r[mintask];
			
			
			
			if(c[mintask][predict[mintask]]>C[mintask][0])
			{
				printf("Executing Task %d at t= %f (Arrival = %f)\n",mintask+1,t,r[mintask]);
				
				printf("System's Criticality Level Changed to 2 because of task %d",mintask+1);
				
				t+=C[mintask][0];
				printf(" at time t =%f\n",t);
				
				c[mintask][1]=c[mintask][1]-C[mintask][0];
				
				
				level=2;
				
			}
			
			else 
			{
				printf("Executing Task %d at t= %f (Arrival = %f)\n",mintask+1,t,r[mintask]);
				
				printf("Finished Executing Task %d at t= %f (Deadline = %f) \n",mintask+1,t+c[mintask][0],r[mintask]+p[mintask]);
				t+=c[mintask][0];
				done[mintask]=true;
				count++;
			}
			
			
			min=INT_MAX;
		}
		
		if(count==n)
		{
			printf("All tasks completed their execution successfully\n");
		}
		
		else if(level==2)
		{
			printf("\n!!Criticality Level 2 Entered, tasks of criticality level 1 dropped\n\n");
			
			//Step 2: Execute Tasks of Criticality Level 2 in EDF Mode
//Doubt :: What if the task in criticality level 2 also exceeds its WCET ?? 
	
		
			
					
			while(count!=n)
			{
				for(int i=0;i<n;i++)
				{
					if(d[i]<min && done[i]==false && x[i]==2)
					{
						min=d[i];
						mintask=i;
					}
				}
				
				
				done[mintask]=true;
				
				if(r[mintask]>t)
				t=r[mintask];
				
				printf("Task %d executed from t = %f (Arrival = %f)\n",mintask+1,t,r[mintask]);
				
				printf("Finished  task %d at %f (In Criticality Level 2, Deadline = %f)\n",mintask+1,t+c[mintask][1],r[mintask]+p[mintask]);
				t+=c[mintask][1];
				
				count++;
				min=INT_MAX; 			
				 
			}
			
	   	}
	
		else printf("Error in program!!");
		
		
		
	}
	
	else if (work==2)
	{
		printf("\t\tCase II \n");
		
		
		
		float lambda=((float)u21)/(1-(float)u11);
		
		printf("Task\tFinal Deadline\n");
		for(int i=0;i<n;i++)
		{
			if(x[i]==2)
			{
				d[i]=r[i]+p[i]*lambda;
			}
			printf("%d\t%f\n",i+1,d[i]); 
		}
		
		
		//Apply EDF to New Deadlines, if system reaches level 2, discard all level 1 jobs amd execute only level 2 jobs with normal unmodified deadlines.
		
	// Step 1 : Applying EDF to new deadlines
	
		bool done[n];		//notes whether a task is completed or not
		
		
		for(int i=0;i<n;i++)
		done[i]=false;
		
		
		int min=INT_MAX,mintask,count=0,level=1;
		
		float t=0;
		
			//t is current system time
		
		while(count!=n&&level==1)
		{
			for(int i=0;i<n;i++)
			{
				if(d[i]<min && done[i]==false)
				{
					min=d[i];
					mintask=i;
				}
			}
			
			
			
			
			if(r[mintask]>t)
			t=r[mintask];
			
			
			
			if(c[mintask][predict[mintask]]>C[mintask][0])
			{
				printf("Executing Task %d at t= %f Arrival=(%f)\n",mintask+1,t,r[mintask]);
				
				printf("System's Criticality Level Changed to 2 because of task %d",mintask+1);
				
				t+=C[mintask][0];
				printf(" at time t =%f\n",t);
				
				c[mintask][1]=c[mintask][1]-C[mintask][0];
				
				
				level=2;
				
			}
			
			else 
			{
				printf("Executing Task %d at t= %f (Arrival = %f)\n",mintask+1,t,r[mintask]);
				
				printf("Finished Executing Task %d at t= %f (Deadline = %f) \n",mintask+1,t+c[mintask][0],r[mintask]+p[mintask]);
				t+=c[mintask][0];
				done[mintask]=true;
				count++;
			}
			
			
			min=INT_MAX;
		}
		
		if(count==n)
		{
			printf("All tasks completed their execution successfully\n");
		}
		
		else if(level==2)
		{
			printf("\n!!Criticality Level 2 Entered, tasks of criticality level 1 dropped.\nDeadline of all Level 2 Tasks modified back to Original Level \n\n");
			
			//Step 2: Execute Tasks of Criticality Level 2 in EDF Mode with unmodified deadlines
	
		
			printf("RemTask\tFinal Deadline\n");
			for(int i=0;i<n;i++)
			{
				if(x[i]==2&&done[i]==false)
				{
					d[i]=r[i]+p[i];
				
				printf("%d\t%f\n",i+1,d[i]); 
				}
			}
			
					
			while(count!=n)
			{
				for(int i=0;i<n;i++)
				{
					if(d[i]<min && done[i]==false && x[i]==2)
					{
						min=d[i];
						mintask=i;
					}
				}
				
				
				done[mintask]=true;
				
				if(r[mintask]>t)
				t=r[mintask];
				
				printf("Task %d executed from t = %f (Arrival = %f)\n",mintask+1,t,r[mintask]);
				
				printf("Finished  task %d at %f (In Criticality Level 2, Deadline = %f)\n",mintask+1,t+c[mintask][1],r[mintask]+p[mintask]);
				t+=c[mintask][1];
				
				count++;
				min=INT_MAX; 			
				 
			}
			
	   	}
	
		else printf("Error in program!!");
		
		
		
		
		
	}
	
	
	
	return 0;
}














