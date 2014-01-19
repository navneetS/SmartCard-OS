#include<high1.h>

void setPropInfo(fcp *t)
{

	struct tm *Sys_T = NULL;
	time_t Tval = 0;
	Tval = time(NULL);
	Sys_T = localtime(&Tval);
	t->pi.hr=Sys_T->tm_hour;
	t->pi.min=Sys_T->tm_min;
	t->pi.sec=Sys_T->tm_sec;
	t->pi.day=Sys_T->tm_mday;
	t->pi.month=Sys_T->tm_mon+1;
	t->pi.year=1900 + Sys_T->tm_year;
}

void setFID(fcp *t)
{
	t->fid=id++;
}

int getFID(fcp *t)
{
	return (t->fid);
}

void setAID(fcp *t,int aid)
{
	t->aid=aid;
}

int getAID(fcp *t)
{
	return (t->aid);
}
void setRecordCount(fcp *t,int a)
{
	t->record=a;
}

int getRecordCount(fcp *t)
{
	return(t->record);
}

void setType(fcp *t,int a)
{
	t->type=a;
}

int getType(fcp *t)
{
	return(t->type);
}

void setATTR(fcp *t,int a)
{
	t->attr=a;
}

int getATTR(fcp *p)
{
	return(p->attr);
}


void setRid (fcp *p,rec *r)
{
r->rid=++(p->record);
}

int getRid(rec *r)
{
  return r->rid;
}

void setBuff(rec *r,char a[])
{
strcpy(r->databuffer,a);
}

char* getBuff(rec *r)
{
return r->databuffer;
}

int giveRead(fcp *p)
{
        
	p->attr=getATTR(p) | READ_WRITE_EXECUTE; 
	p->attr=getATTR(p) & READ;
	return(p->attr);
}
int giveWrite(fcp *p)
{
	p->attr=getATTR(p) | READ_WRITE_EXECUTE;
	p->attr=getATTR(p) & WRITE;
        return (p->attr);
}
int giveReadWriteExecute(fcp *p)
{
	p->attr=getATTR(p) | READ_WRITE_EXECUTE;
        return (p->attr);
}
int giveReadExecute(fcp *p)
{
	p->attr=getATTR(p) | READ_WRITE_EXECUTE;
	p->attr=getATTR(p) & READ_EXECUTE;
        return (p->attr);
}
int giveReadWrite(fcp *p)
{
	p->attr=getATTR(p) | READ_WRITE_EXECUTE;
	p->attr=getATTR(p) & READ_WRITE;
        return (p->attr);
}
int giveWriteExecute(fcp *p)
{
	p->attr=getATTR(p) | READ_WRITE_EXECUTE;
	p->attr=getATTR(p) & WRITE_EXECUTE;
        return (p->attr);
}
int giveExecute(fcp *p)
{
	p->attr=getATTR(p) | READ_WRITE_EXECUTE;
	p->attr=getATTR(p) & EXECUTE;
        return (p->attr); 
}
int giveNoAccess (fcp *p)
{
	
	p->attr=getATTR(p) & NO_ACCESS;
        return (p->attr);
}
