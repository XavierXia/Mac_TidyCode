#ifndef __CLIB_MEMORY__H__
#define __CLIB_MEMORY__H__


// 智能指针
template<class TYPE>
class CAutoPointer
{
public:
	CAutoPointer(TYPE* pMemory) { m_pMemory=pMemory; }
	virtual~CAutoPointer() { if(m_pMemory!=NULL) { free(m_pMemory); m_pMemory=NULL; } }
	VOID SetPtr(TYPE* pMemory) { if(m_pMemory!=NULL) { free(m_pMemory); m_pMemory=NULL; } m_pMemory=pMemory; }
	BOOL IsNull() { return m_pMemory==NULL; }
	operator TYPE* () const { return m_pMemory; }
protected:
	TYPE* m_pMemory;
};



// 自动文件关闭类
template<class TYPE>
class CAutoFile
{
public:
	CAutoFile(TYPE* pFile) { m_pFile=pFile; }
	virtual~CAutoFile() { if(m_pFile!=NULL) { fclose(m_pFile); m_pFile=NULL; } }
	VOID SetFilePtr(FILE* pFile) { if(m_pFile!=NULL) { fclose(m_pFile); m_pFile=NULL; } m_pFile=pFile; }
	BOOL IsNull() { return m_pFile==NULL; }
	operator TYPE* () const { return m_pFile; }
protected:
	TYPE* m_pFile;
};


#endif
