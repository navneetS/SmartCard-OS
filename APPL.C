#include<stdio.h>
#include<conio.h>
#include<stdlib.h>
#include<string.h>
#include "higher.h"
int main()
{
int i,menu,option,fno,rno;
char buff[32];
fcp *p,*q;
clrscr();
freeList();
start=osNewFile();
osCreateFile(start,1,1);
for(i=0;i<3;i++)
	osCreateFile(start->cp,1,1);
for(i=3;i<6;i++)
{
	p=osSearchFile(start,i);
	osCreateFile(p,1,0);
}
do
{
printf("*****************MENU******************\n1:Personal Information\t2:Academic Information\t3:Co-Curriculum Information\t4:Exit\n");
scanf("%d",&menu);
switch(menu)
{
case 1 : 
	p=osSearchFile(start,6);break;
case 2 :
	p=osSearchFile(start,7);break;
case 3 :
	p=osSearchFile(start,8);break;
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
case 4 :	printf("Enter the record number to which data is to be appended\n");
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
displayList();
getch();
return;
}
