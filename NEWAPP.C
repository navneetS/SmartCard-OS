#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include "higher.h"
int main()
{
int i,j,menu,option,fno,rno,a,stu=0,lib=0;
char buff[32],c;
fcp *p,*q,*t;
clrscr();
freeList();
start=osNewFile();
randomize();
do
{
do
{
printf("*********************LOAD/UNLOAD YOUR APPLICATIONS******************\n");
printf("1: Load Student application\t2: Load Library application\n3: Unload student application\t4: Unload Library application\n5:Proceed\t\t\t6: Exit \n");
scanf("%d",&a);
switch(a)
{
case 1:
	if(stu==0)
	{
		p=osCreateFile(start,1,1);
		for(i=0;i<3;i++)
		{
			q=osCreateFile(p,1,1);
			osCreateFile(q,1,0);
		}
		stu=1;
	}
	else
		printf("Application is loaded\n");
	break;
case 2:
	if(lib==0)
	{
		p=osCreateFile(start,2,1);
		osCreateFile(p,2,0);
		lib=1;
	}
	else
		printf("Application is loaded\n");
	break;
case 3:
	if(stu==0)
		printf("Application not loaded\n");
	else
	{
		p=start->cp;
		while(p!=NULL)
		{
			if(getAID(p)==1)
			{
				osDeleteFile(p,getFID(p));
				break;
			}
			else
				p=p->sp;
		}
		stu=0;
	}
	break;
case 4:
	if(lib==0)
		printf("Application not loaded\n");
	else
	{
		p=start->cp;
		while(p!=NULL)
		{
			if(getAID(p)==2)
			{
				osDeleteFile(p,getFID(p));
				break;
			}
			else
				p=p->sp;
		}
		lib=0;
	}
	break;
case 6 :       exit(0);
	break;
case 99 :
	i=1+random(100);
	printf("Enter your response for %d: ",i);
	j=((int)i/2+1);
	scanf("%d",&i);
	if(i==j)
	{
	printf("\nThe File Structure:\n");
	if(start->cp!=NULL)
	{
		p=start->cp;
		do
		{
			while(p->sp!=NULL)
				p=p->sp;
			if(p->cp!=NULL)
				p=p->cp;
		}while(p->sp!=NULL || p->cp!= NULL);
		osDisplayFileStr(start,getFID(p));
	}
		else
			printf("Only MF exists\n");
	printf("The Free List:\n");
	displayList();
	printf("\n");
	}
	else
		printf("Authentication failed\n" );
	break;
}
}while(a<5 || a==99);

do
{
printf("************************Select your option*********************\n");
printf("1: Student application\t\t\t2: Library application\n3: Go to loading/unloading section\t4: Exit\n");
scanf("%d",&a);
switch(a)
{
case 1:      { 
	if(stu==1)
	{
	t=start->cp;
	while(getAID(t)!=1)
		t=t->sp;
	do
	{
	printf("*****************MENU******************\n1:Personal Information\t2:Academic Information\t3:Co-Curriculum Information\t4:Exit\n");
	scanf("%d",&menu);
	switch(menu)
	{
	case 1 :
		p=osSearchFile(start,getFID((t->cp)->cp));break;
	case 2 :
		p=osSearchFile(start,getFID(((t->cp)->sp)->cp));break;
	case 3 :
		p=osSearchFile(start,getFID((((t->cp)->sp)->sp)->cp));break;
	}
	if(menu<4)
	{
		do
		{
			printf("**********SELECT YOUR OPTION***********\n1:Add Record\t2:Delete Record\t3:Write Record\n4:Append Record\t5:Display Records\t6:Exit\n");
			scanf("%d",&option);
			switch(option)
			{
			case 1 :
				printf("Enter the data:  ");
				scanf(" ");
				gets(buff);
				addrecord(p,buff);
				break;
			case 2: printf("Enter the record number to be deleted\n");
				scanf("%d",&rno);
				i=(rno-1)/15;
				q=p;
				while(i!=0)
				{
					q=q->sp;
					i--;
				}
				if(checkNode(q->fid))
				{
					p=osSearchFile(start,p->fid);
					i=((rno-1)%15+1);
					deleterecord(q,i);
				}
				else
					printf("File not Exists\n");
				break;
			case 3: printf("Enter the record number to be re-written\n");
				scanf("%d",&rno);
				printf("Enter the data:  ");
				scanf(" ");
				gets(buff);
				i=(rno-1)/15;
				q=p;
				while(i!=0)
				{
					q=q->sp;
					i--;
				}
				if(checkNode(q->fid))
				{
					p=osSearchFile(start,p->fid);
					i=((rno-1)%15+1);
					writerecord(q,i,buff);
				}
				else
					printf("File not Exists\n");
				break;
			case 4 :printf("Enter the record number to which data is to be appended\n");
				scanf("%d",&rno);
				printf("Enter the data:  ");
				scanf(" ");
				gets(buff);
				i=(rno-1)/15;
				q=p;
				while(i!=0)
				{
					q=q->sp;
					i--;
				}
				if(checkNode(q->fid))
				{
					p=osSearchFile(start,p->fid);
					i=((rno-1)%15+1);
					appendrecord(q,i,buff);
					break;
				}
				else
					printf("File not Exists\n");
				break;
			case 5:
				displayrecord(p);
				break;
			}
		}
		while(option<6);
	}
	}while(menu<4);
	}
	else
		printf("Application not loaded\n");
	break;
	}
case 2: 	{
	if(lib==1)
	{
	t=start->cp;
	while(getAID(t)!=2)
		t=t->sp;
	p=t->cp;
	do
		{
			printf("**********SELECT YOUR OPTION***********\n1:Add Record\t2:Delete Record\t3:Write Record\n4:Append Record\t5:Display Records\t6:Exit\n");
			scanf("%d",&option);
			switch(option)
			{
			case 1 :
				printf("Enter the data:  ");
				scanf(" ");
				gets(buff);
				addrecord(p,buff);
				break;
			case 2: printf("Enter the record number to be deleted\n");
				scanf("%d",&rno);
				i=(rno-1)/15;
				q=p;
				while(i!=0)
				{
					q=q->sp;
					i--;
				}
				if(checkNode(q->fid))
				{
					p=osSearchFile(start,p->fid);
					i=((rno-1)%15+1);
					deleterecord(q,i);
				}
				else
					printf("File not Exists\n");
				break;
			case 3: printf("Enter the record number to be re-written\n");
				scanf("%d",&rno);
				printf("Enter the data:  ");
				scanf(" ");
				gets(buff);
				i=(rno-1)/15;
				q=p;
				while(i!=0)
				{
					q=q->sp;
					i--;
				}
				if(checkNode(q->fid))
				{
					p=osSearchFile(start,p->fid);
					i=((rno-1)%15+1);
					writerecord(q,i,buff);
				}
				else
					printf("File not Exists\n");
				break;
			case 4 :printf("Enter the record number to which data is to be appended\n");
				scanf("%d",&rno);
				printf("Enter the data:  ");
				scanf(" ");
				gets(buff);
				i=(rno-1)/15;
				q=p;
				while(i!=0)
				{
					q=q->sp;
					i--;
				}
				if(checkNode(q->fid))
				{
					p=osSearchFile(start,p->fid);
					i=((rno-1)%15+1);
					appendrecord(q,i,buff);
					break;
				}
				else
					printf("File not Exists\n");
				break;
			case 5:
				displayrecord(p);
				break;
			}
		}
		while(option<6);
	}
	else
		printf("Application not loaded\n");
	break;
	}
}
}while(a<3);
}while(a==3);
getch();
return;
}
