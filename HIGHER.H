#include<stdio.h>
#include<conio.h>
#include<alloc.h>
#include<time.h>
#include<string.h>
#include<low1.h>
fcp *start=NULL;
status s;

fcp *freestart=NULL;

void freeList()
{
int i;
fcp *p,*q;
p=(fcp *)(malloc(sizeof(fcp)));
p->pp=NULL;
p->sp=NULL;
p->cp=NULL;
p->nex=NULL;
p->fid=0x3F00;
freestart=p;
for(i=2;i<=31;i++)
{
	p=(fcp *)(malloc(sizeof(fcp)));
	p->pp=NULL;
	p->sp=NULL;
	p->cp=NULL;
	p->nex=NULL;
	setFID(p);

	if(freestart==NULL)
		freestart=p;
	else
	{
	q=freestart;
	while (q->nex!=NULL)
		q=q->nex;
	q->nex=p;
	}
}
}

void displayList()
{
	fcp *p;
	p=freestart;
	if(p==NULL)
		printf("No free file exists\n");
	while(p!=NULL)
	{
		printf("%04X ",p->fid);
		p=p->nex;
	}
}


fcp* getnode()
{
	fcp *p;
	p=freestart;
	if(p==NULL)
		printf("No Files can be created...Max value reached\n" );
	else
	{
		freestart=freestart->nex;
		p->nex=NULL;
		return p;
	}
	return NULL;
}

void addNode(fcp *p)
{
	fcp *t;
	t=freestart;
	if(freestart==NULL)
		freestart=p;
	else
	{
		while(t->nex!=NULL)	
		t=t->nex;
		t->nex=p;
	}
	p->nex=NULL;
}


fcp* osNewFile() 
{
	fcp *p;
	p=getnode();
	if (p!=NULL)
	{

	p->pp=NULL;
	p->cp=NULL;
	p->sp=NULL;
	setPropInfo(p);
	setATTR(p,NO_ACCESS);
	setType(p,1);
	*(int *)(&s)=NFQ;
	return p;	
	}
	else
	{
	*(int *)(&s)=MEMERR;
	printf("MEM not ALLOc\n");
	return NULL;
	}
}

/* ===============SEARCH FOR FILE      */
fcp* osSearchFile(fcp *p,int a)
{
	if(getFID(p)!=a)
	{
		if(p->cp!=NULL)
			p=osSearchFile(p->cp,a);
		else
		{
			if(p->sp!=NULL)
				p=osSearchFile(p->sp,a);
			else
			{
				p=p->pp;
				if(p->sp!=NULL)
					p=osSearchFile(p->sp,a);
				else
					{
						while(p->sp==NULL)
							p=p->pp;
						p=osSearchFile(p->sp,a);
					}
			}
		}
	}
	return p;
}

/*================DISPLAY FILE STRUCTURE  */
fcp* osDisplayFileStr(fcp* p,int a)
{
	if(getFID(p)!=a)
	{
		if(p->cp!=NULL)
		{
			printf("%04X --> %04X\n",getFID(p),getFID(p->cp));
			p=osDisplayFileStr(p->cp,a);
		}
		else
		{
			if(p->sp!=NULL)
			{
				printf("%04X --> %04X\n",getFID(p->pp),getFID(p->sp));
				p=osDisplayFileStr(p->sp,a);
			}
			else
			{
				p=p->pp;
				if(p->sp!=NULL)
				{
					printf("%04X --> %04X\n",getFID(p->pp),getFID(p->sp));
					p=osDisplayFileStr(p->sp,a);
				}
				else
				{
					while(p->sp==NULL)
						p=p->pp;
					printf("%04X --> %04X\n",getFID(p->pp),getFID(p->sp));			
					p=osDisplayFileStr(p->sp,a);
				}

			}
		}
	}
	return p;
}

/*==============GATHER NODES WITH VALID FID*/
fcp* osGatherNodes(fcp* p,int a)
{
	if(getFID(p)!=a)
	{
		if(p->cp!=NULL)
		{
			node[incr++]=getFID(p);
			p=osGatherNodes(p->cp,a);
		}
		else
		{
			if(p->sp!=NULL)
			{
				node[incr++]=getFID(p);
				p=osGatherNodes(p->sp,a);
			}
			else
			{
				node[incr++]=getFID(p);
				p=p->pp;
				if(p->sp!=NULL)
					p=osGatherNodes(p->sp,a);
				else
				{
					while(p->sp==NULL)
						p=p->pp;				
					p=osGatherNodes(p->sp,a);
				}

			}
		}
	}
	else
		node[incr++]=getFID(p);
	return p;
}
/*==============CLEAR THE RECORDS OF THOSE FILES WHICH ARE DELETED*/
void clearRecord(fcp *p)
{
	rec *t;
	while(p->FIRST!=NULL)
	{	t=p->FIRST;
		p->FIRST=p->FIRST->next;
		t->next=NULL;
		free(t);
	}

}

/*==========CHECK IF NODE IS VALID OR NOT*/
int checkNode(int a)
{
			fcp *d;
			int i;
			for(i=0;i<40;i++)
				node[i]=0;
			i=0;
			if(start->cp!=NULL)
			{	
			d=start->cp;
			do
			{
			while(d->sp!=NULL)
				d=d->sp;
			if(d->cp!=NULL)
				d=d->cp;
			}while(d->sp!=NULL || d->cp!= NULL);
			incr=0;
			osGatherNodes(start,getFID(d));
			incr=0;
			i=0;
			}
			else
				node[0]=1;
			while(i<40)
			{
				if(node[i++]==a)
					return(1);
				
			}
			return(0);
}
/*================DISPLAY  FILE PARAMETERS*/
void osDisplayFileContent(int a)
{
	fcp *t;
	t=osSearchFile(start,a);
		printf("FID: %04X\nDate of Creation: %d/%d/%d\nTime Of Creation: %d:%d:%d\n" ,getFID(t),t->pi.day,t->pi.month,t->pi.year,t->pi.hr,t->pi.min,t->pi.sec);
	if(t->fid>1)
		printf("AID: %d\nTYPE: %d\nATTR: %x\n",getAID(t),getType(t),getATTR(t));
	if(getType(t)==EF)
		printf("Number of records: %d\n",getRecordCount(t));
}

/*=========CREATE A FILE (DF / EF)*/
 void osCreateFile(fcp *p,int aid,int type)
{

		fcp *q,*r;
		q=p;
		if(q->cp==NULL)
		{
			/*setFID(q);  */
			q=getnode();
			/*q=(fcp *)(malloc(sizeof(fcp))); */
			if (q!=NULL)
			{
			q->pp=p;
			q->cp=NULL;
			q->sp=NULL;
			p->cp=q;
			setPropInfo(q);
			setAID(q,aid);
			setType(q,type);
			setATTR(q,READ_WRITE_EXECUTE);
			*(int *)(&s)=NFQ;
			}
			else
			*(int *)(&s)=MEMERR;
		}
		else
		{
			q=q->cp;
			while(q->sp!=NULL)
				q=q->sp;
			/*r=(fcp *)(malloc(sizeof(fcp)));*/
			r=getnode();
			if (r!=NULL)
			{
			/*setFID(r); */
			r->sp=NULL;
			r->cp=NULL;
			r->pp=p;
			q->sp=r;
			setPropInfo(r);
			setAID(r,aid);
			setType(r,type);
			setATTR(r,READ_WRITE_EXECUTE);
			q=r;
			*(int *)(&s)=NFQ;
			}
			else
			*(int *)(&s)=MEMERR;

		}
		if(type==EF)
		{
			setRecordCount(q,0);
			q->FIRST=NULL;
		}
}

/*===============ADDING FREE NODES TO LIST*/
fcp* osFreeFile(fcp* p,fcp *r,int a)
{
	if(getFID(p)!=a)
	{
		if(p->cp!=NULL)
		{
			addNode(p);
			if(p->type==EF)
				clearRecord(p);
			p=osFreeFile(p->cp,r,a);
		}
		else
		{
			if(p->sp!=NULL)
			{
				addNode(p);
				if(p->type==EF)
					clearRecord(p);
				p=osFreeFile(p->sp,r,a);
			}
			else
			{
				addNode(p);
				if(p->type==EF)
					clearRecord(p);
				p=p->pp;
				if(p->sp!=NULL)
					p=osFreeFile(p->sp,r,a);
				else
				{
					while(p->sp==NULL && r!=p)
						p=p->pp;
					if(r!=p)
						p=osFreeFile(p->sp,r,a);
				}

			}
		}
	}
	else
	{
		addNode(p);
		if(p->type==EF)
			clearRecord(p);
	}
	return p;
}

/*==================DELETE A FILE*/
void osDeleteFile( fcp *p,int a)
{
	fcp *r,*q,*s=NULL,*t,*d;
	r=p;
	p=osSearchFile(start,p->pp->fid);
	q=p->cp;
	if(getFID(q)!=a)
	{
		do
		{
			if(q->sp!=NULL)
				if(getFID(q->sp)!=a)
						q=q->sp;
		}while(getFID(q->sp)!=a);
	}
	if(r->sp!=NULL)
		s=r->sp;
	if(s!=NULL && q!=r)
		q->sp=s;
	else
	{
	if(s!=NULL)
		p->cp=s;
	}
	if(q->sp==NULL)
		p->cp=NULL;
	if(p->cp==q && q->sp==r)
		q->sp=NULL;
			if(r->sp==NULL)
				q->sp=NULL;
			r->sp=NULL;
			r->pp=NULL;
			if(r->cp!=NULL)
			{
			d=r->cp;
			do
			{
			while(d->sp!=NULL)
				d=d->sp;
			if(d->cp!=NULL)
				d=d->cp;
			}while(d->sp!=NULL || d->cp!= NULL);
			}
			else
				d=r;
	osFreeFile(r,r,getFID(d));
}
/*===========================RECORD=============*/

/*=============ADD RECORD*/
void addrecord (fcp *t,char buffer[])
{
	rec *r,*p;
	fcp *q;
	if(getType(t)==EF)
	{
		if(getRecordCount(t)!=MAX_RECORD_LIMIT)
		{
			r=(rec *)malloc(sizeof(rec));
			if (r!=NULL)
			{
				setRid( t,r);
				setBuff(r,buffer);
				r->next=NULL;
				if (t->FIRST==NULL)
					t->FIRST=r;

				else
				{
					p=t->FIRST;
					while (p->next!=NULL)
						p=p->next;
					 p->next=r;
				}
				*(int *)(&s)=NFQ;
				printf("Record Succesfully added\n");
			}
			else
				*(int *)(&s)=MEMERR;
		}
		else
		{
			if(t->sp==NULL)
			{
				osCreateFile(t->pp,1,0);
				q=t->sp;
				addrecord(q,buffer);
			}
			else
				{q=t->sp;
				addrecord(q,buffer);}
		}
	}
	else
	{
		printf("Action cant be performed on DF\n");
		*(int *)(&s)=IFILE;

	}
}
/*=============APPEND RECORD*/
void appendrecord(fcp *t,int did,char buffer[])
{
	rec *p;
	if(getType(t)==EF)
	{
		p=t->FIRST;
		if(p==NULL)
			printf("File is empty..No record to delete\n");
		else
		{
			while(getRid(p)!=did && p!=NULL)
				p=p->next;
			if(p==NULL)
				{printf("Record Not found\n"); *(int *)(&s)=NREC;}
			else
				{
					strcat(p->databuffer,buffer);
					printf("Reocrd Successfully Appended\n");
				}
		}
	}
	else
		{printf("Action cant be performed on DF\n");*(int *)(&s)=IFILE;}
}

/*=============WRITE RECORD */

void writerecord( fcp *t,int did,char buffer[])
{
	rec *p;
	if(getType(t)==EF)
	{
		p=t->FIRST;
		if(p==NULL)
			printf("File is empty..No record to delete\n");
		else
		{
			while(getRid(p)!=did && p!=NULL )
				p=p->next;
			if(p==NULL)
				{printf("Record Not found\n");*(int *)(&s)=NREC;}
			else
				{
					strcpy(p->databuffer,buffer);
					printf("Record Successfully Re-written\n");
				}
		}
	}
	else
		{printf("Action cant be performed on DF\n");*(int *)(&s)=IFILE;}
}

/*=============VIEW RECORD*/
void viewrec(fcp *t,int rid)
{
	rec *p,*r;
	int a;
	if(getType(t)==EF)
	{
		p=t->FIRST;
		while (p!=NULL && getRid(p)!=rid)
		p=p->next;
		if (p==NULL)
		{
		printf ("No such record Exists\n");
		*(int *)(&s)=NREC;
		}
		else
		{
			printf ("\nId:%d Buffer %s\n",getRid(p),getBuff(p));
			do
			{
				printf ("1.Move Next 2.Move Prev 3:Exit\n");
				scanf("%d",&a);
				switch(a)
				{
					case 1:
						if (getRid(p)==t->record)
						{
							printf("You are at last record\n");
							a=3;
						}
						else
						{
							p=p->next;
							printf ("Id:%d Buffer %s\n",getRid(p),getBuff(p));
						}
						break;

					case 2:
						if (getRid(p)==1)
						{
							printf("You are at first record\n");
							a=3;
						}
						else
						{
							r=t->FIRST;
							while (getRid(r->next)!=getRid(p))
							r=r->next;
							p=r;
							printf ("Id:%d Buffer %s\n",getRid(p),getBuff(p));
						}
						break;

					case 3:
						printf ("Bye\n");
						break;
				}
			}
			while (a!=3);
		}
	}
	else
		{printf("Action cant be performed on DF\n");*(int *)(&s)=IFILE;}
}

/*=============DISPLAY RECORD*/
int displayrecord(fcp *t)
{
	rec *p;
	int a=1;
	while(t!=NULL)
	{
		if(getType(t)==EF)
		{

			p=t->FIRST;
			while (p!=NULL)
			{
				printf ("Rec No:%d",a++);
				printf ("  Buffer: %s\n",getBuff(p));
				p=p->next;
			}

		}
		else
		{
			printf("Action cant be performed on DF\n");
			*(int *)(&s)=IFILE;
		}
		t=t->sp;
	}
return;
}


/*============MOVE RECORD FROM ONE FILE TO ANOTHER*/
void moverec(fcp *s,fcp *d)
{
	char a[32];
	strcpy(a,(s->FIRST)->databuffer);
	addrecord(d,a);
}


/*=============DELETE RECORD*/
int deleterecord(fcp *t,int did)
{
	rec *p,*f,*q;
	int flag=0;
	if(getType(t)==EF)
	{
		p=t->FIRST;
		if(p==NULL)
			printf("File is empty..No record to delete\n");
		else
		{
			if(did==1)
			{
				p=p->next;
				free(t->FIRST);
				t->FIRST=p;
				while(p!=NULL)
				{
					(p->rid)--;
					p=p->next;
				}
				(t->record)--;
				printf("Record Successfully Deleted\n");
			}
			else
			{
				while (getRid(p)!=did )
				{
					if (p->next!=NULL)
					{
						f=p;
						p=p->next;
						if(getRid(p)==did)
							flag=1;
					}
					else
						break;
				}
				if(p->next==NULL && flag==0)
					printf("Sorry!! data not found\n");
				else
				if(getRid(p)==did)
				{
					f->next=p->next;
					free(p);
					q=f->next;
					while(q!=NULL)
					{
						(q->rid)--;
						q=q->next;
					}
					(t->record)--;
					printf("Record Successfully Deleted\n");
				}
			}
			if(t->sp!=NULL)
			{
				if(t->record!=MAX_RECORD_LIMIT)
				{
					moverec(t->sp,t);
					deleterecord(t->sp,1);
				}
				if((t->sp)->record<1 || (t->sp)->record >15)
						osDeleteFile(t->sp,t->sp->fid);

			}
		}
	}
	else
		{printf("Action cant be performed on DF\n");*(int *)(&s)=IFILE;}
return;
}
