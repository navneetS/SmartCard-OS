int id=1,incr=0;
int node[31];
struct prop_info
{
unsigned int day:5,month:4,year:11,hr:5,min:6,sec:6;
};

typedef struct Record
{
unsigned int rid:4;
char databuffer[32];
struct Record *next;
}rec;

typedef struct fblk	 
{
unsigned int fid;
unsigned int aid:5;
struct fblk *pp;
struct fblk *cp;
struct fblk *sp;
struct fblk *nex;
unsigned int type:1;
unsigned int sfid:5;
struct prop_info pi;
unsigned int attr:6;
unsigned int record:4;
rec *FIRST;
}fcp;


typedef struct s
{
unsigned int sw2:8,sw1:8;
}status;

   /* MACRO OF ERROR CODES*/

#define NFQ 0x9000              /* No further qualification */
#define ERRDATA 0x6281		/* Part of returned data may be corrupted */
#define BYTELTLE 0x6282		/* End of file/record reached before reading Le bytes*/ 
#define IFILE 0x6283	        /* Selected file invalidated */
#define FCIUNSTR 0x6284		/*FCI not formatted according to 1.1.5 */
#define NFG 0x6200		/*No information given */
#define FILECOMP 0x6381		/*File filled up by the last write */
#define NVMEMUNCH 0x6400	/*Nonvolatile Memory unchanged*/
#define MEMERR 0x6581		/*Memory failure */
#define NLOGCHNL 0x6881		/*Logical channel not supported **/
#define NSECMSG 0x6882		/*Secure messaging not supported */
#define NCMDFSTR 0x6981		/*Command incompatible with file structure */
#define NSECST 0x6982		/*Security status not satisfied */
#define AUMTDBLK 0x6983		/*Authentication method blocked */
#define NIREFDATA 0x6984	/*Referenced data invalidated */
#define NCONDUSE 0x6985 	/*Conditions of use not satisfied */
#define NCMD 0x6986		/*Command not allowed (no current EF) */
#define EXPSMDATAOBJ 0x6987	/*Expected SM data objects missing */
#define NSMDATAOBJ 0x6988 	/*SM data objects incorrect */
#define NPARDATA 0x6A80		/*Incorrect parameters in the data field*/ 
#define NFUNC 0x6A81		/*Function not supported */
#define NFILE 0x6A82		/*File not found */
#define NREC 0x6A83		/*Record not found */
#define NEMFILE 0x6A84 		/*Not enough memory space in the file*/
#define NLCTLV 0x6A85		/*Lc inconsistent with TLV structure */
#define NPARP1P2 0x6A86		/*Incorrect parameters P1-P2*/ 
#define NLCP1P2 0x6A87		/*Lc inconsistent with P1-P2*/ 
#define NREFDATA 0x6A88 	/*Referenced data not found */

/*MACROS RISTRICTING LENGTH/TYPE*/
#define MAX_RECORD_LIMIT 15
#define EF 0
#define MF 1


/**MACRO OF ACCESS RIGHT*/
#define NO_ACCESS 0x38
#define EXECUTE 0x39
#define WRITE 0x3A
#define WRITE_EXECUTE 0x3B
#define READ 0x3C
#define READ_EXECUTE 0x3D
#define READ_WRITE 0x3E
#define READ_WRITE_EXECUTE 0x3F

