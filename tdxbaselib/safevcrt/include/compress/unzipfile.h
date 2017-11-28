#ifndef __UNZIPFILE__H__
#define __UNZIPFILE__H__
#if _MSC_VER > 1000
#pragma once
#endif
#define ZLIB_INTERNAL
#include "zlib.h"
#include "../collection/clibstr.h"
#include "../collection/coll.h"


// unz_global_info structure contain global data about the ZIPfile
// These data comes from the end of central dir
typedef struct __unz_global_info
{	uLong number_entry;         // total number of entries in the central dir on this disk
	uLong size_comment;         // size of the global comment of the zipfile
} unz_global_info;


// unz_file_info contain information about a file in the zipfile
typedef struct __unz_file_info
{	uLong version;              // version made by                 2 bytes
    uLong version_needed;       // version needed to extract       2 bytes
    uLong flag;                 // general purpose bit flag        2 bytes
    uLong compression_method;   // compression method              2 bytes
    uLong dosDate;              // last mod file date in Dos fmt   4 bytes
    uLong crc;                  // crc-32                          4 bytes
    uLong compressed_size;      // compressed size                 4 bytes 
    uLong uncompressed_size;    // uncompressed size               4 bytes 
    uLong size_filename;        // filename length                 2 bytes
    uLong size_file_extra;      // extra field length              2 bytes
    uLong size_file_comment;    // file comment length             2 bytes

    uLong disk_num_start;       // disk number start               2 bytes
    uLong internal_fa;          // internal file attributes        2 bytes
    uLong external_fa;          // external file attributes        4 bytes

    time32_t tmu_date;			// file modify datetime			   memory data
} unz_file_info;




class COMPRESS_IMP CUnzipFile
{
public:
	CUnzipFile();
	CUnzipFile(LPCTSTR lpszPath);
	virtual ~CUnzipFile();
	BOOL IsClosed();
	VOID Close();
	BOOL Open(LPCTSTR lpszPath);
	
	// Give the current position in uncompressed data
	ULONG Tell();

	// return TRUE if the end of file was reached,FALSE elsewhere 
	BOOL IsEOF();

	// Get the global comment string of the ZipFile,in the szComment buffer.
	// uSizeBuf is the size of the szComment buffer.
	// return the number of byte copied
	int GetGlobalComment(char* szComment,uLong uSizeBuf);

	// Read extra field from the current file(opened by OpenCurrentFile)
	// This is the local-header version of the extra field(sometimes,there is
	// more info in the local-header version than in the central-header)
	// 
	// if buf==NULL,it return the size of the local extra field
	// 
	// if buf!=NULL,len is the size of the buffer,the extra header is copied in buf.
	//   the return value is the number of bytes copied in buf
	int GetLocalExtrafield(VOID* buf,UINT len);

	// Get Info about the current file
	// if file_info structure will contain somes info about
	//	    the current file
	// if szFileName!=NULL,the filemane string will be copied in szFileName
	//			(fileNameBufferSize is the size of the buffer)
	// if extraField!=NULL,the extra field information will be copied in extraField
	//			(extraFieldBufferSize is the size of the buffer).
	//			This is the Central-header version of the extra field
	// if szComment!=NULL,the comment string of the file will be copied in szComment
	//			(commentBufferSize is the size of the buffer)
	BOOL GetCurrentFileInfo(unz_file_info* file_info,LPSTR szFileName=NULL,
		uLong fileNameBufferSize=0,VOID *extraField=NULL,uLong extraFieldBufferSize=0,
		LPSTR szComment=NULL,uLong commentBufferSize=0);

	// Write info about the ZipFile in the *pglobal_info structure.
	// No preparation of the structure is needed
	VOID GetGlobalInfo(unz_global_info & global_info);

	



	//////////////////////////////////////////////////////////////////////////
	// Unzip package allow you browse the directory of the zipfile

	// Set the current file of the zipfile to the first file.
	BOOL GoToFirstFile();

	// Set the current file of the zipfile to the next file.
	//   return TRUE if there is no problem
	//   return FALSE if the actual file was the latest.
	BOOL GoToNextFile();

	// Try locate the file szFileName in the zipfile.
	// For the iCaseSensitivity signification,see unzStringFileNameCompare
	// return value :
	// TRUE if the file is found. It becomes the current file.
	// FALSE if the file is not found
	BOOL LocateFile(LPCTSTR pszFileName,BOOL bCaseSensitive=FALSE);

	// Open for reading data the current file in the zipfile.
	BOOL OpenCurrentFile();

	// Close the file in zip opened with OpenCurrentFile
	// throw badCrc error if all the file was read but the CRC is not good
	BOOL CloseCurrentFile();

	// Read bytes from the current file(opened by OpenCurrentFile)
	// buf contain buffer where data must be copied
	// len the size of buf.
	// 
	// return the number of byte copied if somes bytes are copied
	// return 0 if the end of file was reached
	int ReadCurrentFile(VOID* buf,UINT len);



protected:
	// standard stream file
	class COMPRESS_IMP CStdInFile
	{
	public:
		CStdInFile();
		virtual~CStdInFile();
		BOOL Open(LPCTSTR pszFileName);
		VOID SeekToOffset(uLong uOffset);
		VOID Close();
		BOOL IsClosed();
		LPCTSTR GetFilePath();
		uLong Read(VOID* lpBuf,uLong nCount);
		BOOL Write(const VOID* lpBuf,uLong nCount);
		uLong GetLength();
	protected:
		TCHAR m_szFileName[MAX_PATH];
		FILE* m_fpFile;
	};

	// unz_file_info_interntal contain internal info about a file in zipfile
	struct unz_file_info_internal
	{	uLong offset_curfile;		// relative offset of local header 4 bytes
	};

	// file_in_zip_read_info_s contain internal information about a file in zipfile,
	// when reading and decompress it
	struct file_in_zip_read_info
	{	char* read_buffer;					// internal buffer for compressed data
		z_stream stream;					// zLib stream structure for inflate
		uLong pos_in_zipfile;				// position in byte on the zipfile,for fseek
		uLong stream_initialised;   		// flag set if stream structure is initialised
		uLong offset_local_extrafield;		// offset of the local extra field
		uInt  size_local_extrafield;		// size of the local extra field
		uLong pos_local_extrafield;			// position in the local extra field in read
		uLong crc32;						// crc32 of all data uncompressed
		uLong crc32_wait;           		// crc32 we must obtain after decompress all
		uLong rest_read_compressed; 		// number of byte to be decompressed
		uLong rest_read_uncompressed;		// number of byte to be obtained after decomp
		uLong compression_method;			// compression method(0==store)
		uLong byte_before_the_zipfile;		// byte before the zipfile,(>0 for sfx)
	};
protected:
	VOID free_m_pfile_in_zip_read();
	VOID alloc_m_pfile_in_zip_read();
	int StringFileNameCompare(LPCSTR pszFileName1,LPCSTR pszFileName2,BOOL bCaseSensitive=FALSE);
	VOID CheckForError(int err);
	VOID ThrowError(LONG err);
	static VOID myfree(VOID* opaque,VOID* address);
	static VOID* myalloc(VOID* opaque,UINT items,UINT size);
protected:
	BOOL unzlocal_GetCurrentFileInfoInternal( unz_file_info & file_info,
		unz_file_info_internal & file_info_internal,LPSTR szFileName,
		uLong fileNameBufferSize,VOID *extraField,uLong extraFieldBufferSize,
		LPSTR szComment,uLong commentBufferSize);
	VOID unzlocal_DosDateToTmuDate(unz_file_info & file_info);
	BOOL unzlocal_CheckCurrentFileCoherencyHeader(uInt & iSizeVar,uLong & offset_local_extrafield,uLong & size_local_extrafield);
	uLong unzlocal_SearchCentralDir();
	VOID unzlocal_getLong(uLong & pX);
	VOID unzlocal_getShort(uLong & pX);
	VOID unzlocal_getByte(int & pi);
protected:
	CStdInFile m_ZipFile;								// io structore of the zipfile
	unz_global_info m_gi;       						// public global information
	uLong m_byte_before_the_zipfile;					// byte before the zipfile,(>0 for sfx)
	uLong m_num_file;									// number of the current file in the zipfile
	uLong m_pos_in_central_dir;							// pos of the current file in the central dir
	uLong m_current_file_ok;							// flag about the usability of the current file
	uLong m_central_pos;								// position of the beginning of the central dir
	uLong m_size_central_dir;							// size of the central directory
	uLong m_offset_central_dir;							// offset of start of central directory with respect to the starting disk number
	unz_file_info m_cur_file_info;						// public info about the current file in zip
	unz_file_info_internal m_cur_file_info_internal;	// private info about it
    file_in_zip_read_info* m_pfile_in_zip_read;			// structure about the current file if we are decompressing it
	LONG m_nLastError;									// last error code
	BOOL m_bDetectZlibMemoryLeaks;						// specify whether to control memory allocation and freeing by zlib library
														// strongly suggested to set it to TRUE(default)
	TListPtr m_lstZlibMemorys;							// memory blocks
};

#endif
