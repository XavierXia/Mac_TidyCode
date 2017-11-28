#ifndef __DBF__H__
#define __DBF__H__
#include "../safevcrt.h"

// 当前类需要使用1字节对齐
#pragma pack(1)


#ifndef TRUE
	#define TRUE				1				// 真定义
	#define FALSE				0				// 假定义
#endif

#define		LOCK_F_OFFSET		0x40000000l		// 锁文件的锁偏移
#define		LOCK_C_OFFSET		1000000000l		// 锁记录的锁偏移
#define		LOCK_FILE_LEN		0x3fffffffl		// 加锁的时候锁文件的长度


#define		DBFIDX_LAYER		6				// DBF索引层数
#define		DBFIDX_ROOT			1				// 索引根
#define		DBFIDX_BRANCH		0				// 索引分支
#define		DBFIDX_OVERFLOW		-2				// 索引溢出
#define		READ_IDX_ERR		-3				// 索引读错误
#define		SEEK_IDX_ERR		-4				// 索引指针移动错误
#define		KEYWORD_ERR			-5				// 索引关键字错误
#define     MAX_FLD_NUM         20				// 最大字段数
#define     CH_SPACE            0x20			// 空格字符

#define		SUCCESS				0				// 成功标志
#define     SUCCEED             0				// 成功标志
#define		FAIL                -1				// 失败标志

#define		APPEND_DBF   	    -1l				// 追加记录

#define		SEEK_DBF_ERR		-1l				// 数据库指针移动错误
#define		READ_DBF_ERR		-2l				// 数据库读错误
#define		WRITE_DBF_ERR		-3l				// 数据库写错误
#define		REC_NUMBER_ERR		-4l				// 数据库记录数错误
#define     OPEN_DBF_ERR        -5l				// 数据库打开错误
#define     ALLOC_DBF_ERR       -6l				// 数据内存分配错误
#define     DBF_DESTROYED       -7l				// 数据库结构损坏错误
#define     DBF_INCOMPATIBLE    -8l				// 数据库格式不兼容错误

#define		DBF_LOCK_WAIT_TIME	10				// 数据库锁定延迟
#define     DBF_IDX_BLOCK_SIZE  0x200			// 数据库块大小


typedef struct tagDBFTAGHEADER
{  LONG           root;                        // -1 means unknown 
   LONG           free_list;                   // start of the free list (-1 if none) 
   ULONG          version;                     // used multi-user only 
   SHORT          key_len;                     // Key Length 
   char           type_code;                   // 0x01 Uniq; 0x08 For Clause; 0x32 Compact; 0x80 Compound 
   char           signature;                   // unused
// char           dummy2[482];                 // unused
   char           dummy3[4];                   // unused
   SHORT          descending;                  // 1 = descending, 0 = ascending 
   SHORT          filter_pos;                  // not used, == to expr_len 
   SHORT          filter_len;                  // length of filter clause 
   SHORT          expr_pos;                    // not used, == to 0  
   SHORT          expr_len;                    // length of expression 
// char           expr_pool[512];              // expression and filter pool 
} DBFTAGHEADER;


typedef struct tagDBFKEYDATA
{  LONG  num;								   //
   char  value[1];							   // The key size is variable
} DBFKEYDATA;


// the following structure is used only on the leaf nodes of the tree structure
typedef struct tagDBFNODEHEADER
{  SHORT            free_space;                // # bytes available in node 
   ULONG            rec_num_mask;              // record number mask 
   char             dup_byte_cnt;              // duplicate byte mask count 
   char             trail_byte_cnt;            // Trailing byte mask count 
   char             rec_num_len;               // # bits used for record number 
   char             dup_cnt_len;               // # bits used for duplicate count 
   char             trail_cnt_len;             // # bits used for trail count 
   char             info_len;                  // # bytes for holding record number, 
} DBFNODEHEADER;

typedef struct tagDBFBLOCKHEADER
{  SHORT      node_attribute;                  // 0=index, 1=root, 2=leaf
   SHORT      n_keys;                          // DBFBLOCK Image starts here
   LONG       left_node;                       // -1 if not present
   LONG       right_node;                      // -1 if not present
} DBFBLOCKHEADER;

typedef struct tagDBFBLOCK
{  DBFTAGHEADER* tag;                          // header
   SHORT key_on;                               // The current key within the block
   SHORT cur_trail_cnt;                        // current value used for seeking 
   SHORT cur_dup_cnt;                          // current value used for seeking 
   SHORT dup_pos;                              // bit offset into the info for the duplicate data 
   SHORT trail_pos;                            // bit offset into the info for the trail data 
   SHORT rec_pos;                              // bit offset into the info for the record # data 
   char  *cur_pos;                             // current position into the data (starts at end) 
   SHORT built_on;                             // the 'current' key value (i.e. key really 'on') 
   char  *built_pos;                           // position where built on 
   DBFKEYDATA* built_key;                      //
   DBFBLOCKHEADER header;                      //
   DBFNODEHEADER node_hdr;                     // only if the block is a leaf
   char data[1];                               // the remaining data
} DBFBLOCK;

typedef struct tagDBFFLDINFO
{	char          name[10];                    // node type
	char          null1;                       // fixed to 0x00
	char          type;                        // field type
	SHORT         offset;                      // field offset in a record
	char          null2[2];                    // null chars
	BYTE          wid;                         // field length
	char          dec;                         // point number length
	char          null3[14];                   // used by system
} DBFFLDINFO;

typedef struct tagDBH_Head
{
      char			id;                         // .DBF标识
      char			year,month,day;             // 文件最后修改日期
      LONG			RecNum;                     // 总记录数
      SHORT			HeadLen;                    // .DBF头文件长度(length of DBF head)
      SHORT			RecLen;                     // 记录长度(length of each record)
      char*			RecBuf;                     // 记录Buffer指针
      DBFFLDINFO*	Field;                      // 字段结构
      SHORT			FieldNum;                   // 字段数
      SHORT			fpt;                        // DBF句柄
      LONG			NowRec;                     // 当前记录号
      char			null[4];                    // null char in the info. unit
      SHORT			fptfpt;                     // .FPT句柄
      SHORT			fptflag;                    // .FPT标志
      SHORT			fptreclen;                  // .FPT中记录长度
      SHORT			fptcdx;                     // .CDX句柄
      DBFTAGHEADER* tag_index;
      DBFBLOCK*     block;
} DBH_Head;

typedef struct tagDBFIDXFILEHEADER
{	LONG      root;
    LONG      ff;
    LONG      new_node;
    SHORT     key_len;
} DBFIDXFILEHEADER;

typedef struct tagIDXNODEHEADER
{     char    flag;
      char    zero1;
      char    item_num;
      char    zero2;
      LONG    left_node;
      LONG    right_node;
} IDXNODEHEADER;

typedef struct tagIDX_Head
{	SHORT				fpt;
	DBFIDXFILEHEADER	head;
	char*				buf;
	SHORT				cur;
} IDX_Head;

typedef struct tagNDXHEAD
{	char     raddr[4];         // the relative address of root node
	char     hl[4];            // label of boot node,normally 0xFFFFFFFF
	char     total[4];         // total number of nodes
	char     keylen[2];        // length of index key word
	char     keytype;          // 0 if key word is char.type,else 1
	char     exp[100];         // index expresiion
} NDXHEAD;

typedef struct tagNDXNODE
{	char    type;              // node type 
	char    c1;                // normally 0 
	char    ndxnum;            // valide number of index items 
	char    c2;                // normally 0 
	ULONG   preptr;		       // pre_pointer of the node,0xFFFFFFFF if no pre_node 
	ULONG   postptr;		   // post_pointer of the node,0xFFFFFFFF if no post_node 
	char    item[500];         // index item 
} NDXNODE;

typedef struct tagNDXLEVEL
{	char        id;				// id this level is valide or invaid
	SHORT       lastbv;			//
	SHORT       endbv;			//
	SHORT       bv;				// boundary value for this level
	SHORT       ioffs;			// index item offs in this block node
//	NDXNODE		lnd;			// hold node for this level
} NDXLEVEL;

typedef struct tagNDXREC
{	char        id;				// if valid,ptr is record no indexed out,else it's pointer to node
	SHORT       SeqNo;			// 
	char        kw[20];			// pointer to key word needed to index
	LONG        ptr;            // pointer to next block node or record no */
} NDXREC;







#define  BaseDataTop(DBH)		ReadDbf(DBH,1l)
#define  BaseDataBottom(DBH)    ReadDbf(DBH,GetDbfRecNum(DBH))

LITEDBF_IMP LONG  OpenBase(DBH_Head* DBHptr,const char* filename,LONG access);
LITEDBF_IMP LONG  CloseBase(DBH_Head* DBHptr);
LITEDBF_IMP LONG  CheckBase(DBH_Head* DBHptr);
LITEDBF_IMP LONG  CheckBaseEx(DBH_Head* DBHptr);
LITEDBF_IMP LONG  LockDbf(DBH_Head* DBHptr,LONG rec);
LITEDBF_IMP LONG  UnlockDbf(DBH_Head* DBHptr,LONG rec);
LITEDBF_IMP LONG  LockBase(DBH_Head* DBHptr);
LITEDBF_IMP LONG  UnlockBase(DBH_Head* DBHptr);
LITEDBF_IMP LONG  LockIndex(LONG idx_fpt);
LITEDBF_IMP LONG  UnlockIndex(LONG idx_fpt);
LITEDBF_IMP LONG  GetDbfRecNum(DBH_Head* DBHptr);
LITEDBF_IMP LONG  ReadDbfNow(DBH_Head* DBHptr);
LITEDBF_IMP LONG  ReadDbf(DBH_Head* DBHptr,LONG rec);
LITEDBF_IMP LONG  ReadDbfN(DBH_Head* DBHptr,char* str,LONG rec,LONG rec_num);
LITEDBF_IMP LONG  CopyRecInBuf(DBH_Head* DBHptr,char* str,LONG rec);
LITEDBF_IMP LONG  WriteDbfNow(DBH_Head* DBHptr);
LITEDBF_IMP LONG  WriteDbf(DBH_Head* DBHptr,LONG rec);
LITEDBF_IMP LONG  WriteIndex(LONG idx_fpt,char* keyword,LONG rec);
LITEDBF_IMP LONG  GetFieldSeq(DBH_Head* DBHptr,char* fname);
LITEDBF_IMP LONG  GetFieldStr(DBH_Head* DBHptr,char* fname,char* vari);
LITEDBF_IMP LONG  GetFieldSeq2(DBH_Head* DBHptr,char* fname);
LITEDBF_IMP LONG  GetFieldStr2(DBH_Head* DBHptr,char* fname,char* vari);
LITEDBF_IMP LONG  Skip(LONG n,DBH_Head* DBH);
LITEDBF_IMP void  formatstr(char* buf,char* vari,LONG type,LONG width,LONG dec);
LITEDBF_IMP LONG  PrevFieldStr(DBH_Head* DBHptr,char* fname,char* vari);
LITEDBF_IMP LONG  PrevFieldStrLeft(DBH_Head* DBHptr,char* fname,char* vari);
LITEDBF_IMP LONG  GetMemoStr(DBH_Head* DBHptr,char* fname,char* buffer);
LITEDBF_IMP SHORT reverse_short(SHORT val);
LITEDBF_IMP LONG  reverse_long(LONG val);
LITEDBF_IMP LONG  CdxTop(DBH_Head* DBHptr,char* tag_name);
LITEDBF_IMP LONG  CdxBottom(DBH_Head* DBHptr,char* tag_name);
LITEDBF_IMP LONG  CdxSeek(DBH_Head* DBHptr,char* tag_name,char* key,LONG descending);
LITEDBF_IMP LONG  CdxSeekDouble(DBH_Head* DBHptr,char* tag_name,double key,LONG descending);
LITEDBF_IMP LONG  CdxContinue(DBH_Head* DBHptr,char* key,LONG descending);
LITEDBF_IMP LONG  CdxContinueDouble(DBH_Head* DBHptr,double key,LONG descending);
LITEDBF_IMP LONG  IdxSeek_c(int fpt,char* keyword,LONG* rec,LONG maxcount);
LITEDBF_IMP LONG  IdxSeek_f(int fpt,char* keyword,LONG* rec,LONG maxcount);
LITEDBF_IMP LONG  IdxSeek_double(int fpt,double keyword,LONG* rec,LONG maxcount);
LITEDBF_IMP void  set_secret(void);
LITEDBF_IMP void  clr_secret(void);
LITEDBF_IMP char* AllocRecbuf(DBH_Head* DBHptr);
LITEDBF_IMP LONG  ReadDbfNowToBuf(DBH_Head* DBHptr,char* RecBuf);
LITEDBF_IMP LONG  GetFieldStrFromBuf(DBH_Head* DBHptr,char* fname,char* vari,char* RecBuf);
LITEDBF_IMP LONG  OpenIdx(IDX_Head* IDXptr,char* filename,LONG access);
LITEDBF_IMP LONG  CloseIdx(IDX_Head* IDXptr);
LITEDBF_IMP LONG  IdxSeek(IDX_Head* IDXptr,char* keyword);
LITEDBF_IMP LONG  IdxContinue(IDX_Head* IDXptr,char* keyword);
LITEDBF_IMP LONG  IdxSeekDouble(IDX_Head* IDXptr,double keyword);
LITEDBF_IMP LONG  IdxContinueDouble(IDX_Head* IDXptr,double keyword);
LITEDBF_IMP LONG  MemGetDbfRecNum(DBH_Head* DBHptr,char* buf);
LITEDBF_IMP LONG  MemReadDbf(DBH_Head* DBHptr,LONG rec,char* buf);
LITEDBF_IMP LONG  MemReadDbfNow(DBH_Head* DBHptr,char* buf);
LITEDBF_IMP LONG  MemSkip(LONG step,DBH_Head* DBHptr,char* buf);


#pragma pack()

#endif
