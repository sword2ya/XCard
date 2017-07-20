/********************************************************************
	created:	2013/3/5  15:09
	file base:	IFileSystem
	file ext:	h
	author:		
	
	purpose:	文件系统
*********************************************************************/

#pragma once 

namespace basetools
{

class IFile;
class IFileFind;
		
class IFileSystem
{
public:

	//  访问模式
	enum EN_AccessMode{
		enRead = 1,
		enWrite ,		
		enReadWrite,
	};

	//  共享模式
	enum EN_ShareMode{
		enShareNone = 0,    
		enShareRead = 1,
		enShareWrite = 2,
		enShareDelete = 4,
	};


	//  创建模式
	enum EN_CreationDisposition{
		enCreateNew ,       // Creates a new file. The function fails if the specified file already exists.
		enCreateAlways,    // Creates a new file. If the file exists, the function overwrites the file and clears the existing attributes.
		enOpenExist,       //  Opens the file. The function fails if the file does not exist
		enOpenAlways,      //  Opens the file, if it exists. If the file does not exist, the function creates the file as if dwCreationDisposition were CREATE_NEW
		enTruncateExists,  //  Opens the file. Once opened, the file is truncated so that its size is zero bytes.
	};


public:

	//************************************
	// Method:    释放文件系统
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;



	//************************************
	// Method:    获取最后一次错误描述
	// Returns:   LPCTSTR                    错误描述
	// Qualifier:
	//************************************
	virtual LPCTSTR GetLastErrorDesc() = 0;


	//************************************
	// Method:    关联基准目录
	// Returns:   BOOL	                      是否成功关联
	// Parameter: LPCTSTR szBaseDir            基准目录
	//************************************
	virtual BOOL AttachBaseDirectory(LPCTSTR szBaseDir) = 0;


	//************************************
	// Method:    获取基准目录
	// Returns:   LPCTSTR	                    基准目录	
	//************************************
	virtual LPCTSTR GetBaseDirectory() = 0;


	//************************************
	// Method:    关联基准目录
	// Returns:   IFile*	                    被打开的文件对象. 使用完成后调用 IFile::Release()
	// Parameter: LPCSTR szRelatePath           被打开文件的相对路径. 完整路径为 (BasePath + '\\' + szRelatePath)
	// Parameter: BOOL bCreateDirIfNotExist     目录不存在时, 是否先创建目录
	// Parameter: DWORD dwDesiredAccess         访问模式, 取值于 EN_AccessMode  
	// Parameter: DWORD dwShareMode             共享模式,取值于 EN_ShareMode
	// Parameter: DWORD dwCreationDisposition   创建模式,取值于 EN_CreationDisposition
	//************************************
	virtual IFile* OpenFile(LPCTSTR szRelatePath, BOOL bCreateDirIfNotExist, EN_AccessMode enAccessMode, DWORD dwShareMode, EN_CreationDisposition enCreationDisposition) = 0;

	//************************************
	// Method:    检查文件是否存在
	// Returns:   BOOL                         文件是否存在
	// Parameter: LPCSTR szRelatePath          被创建文件的相对路径
	//************************************
	virtual BOOL IsFileExist(LPCTSTR szRelatePath) = 0;

	//************************************
	// Method:    删除文件
	// Returns:   BOOL                         是否成功删除文件
	// Parameter: LPCSTR szRelatePath          被删除文件的相对路径
	//************************************
	virtual BOOL RemoveFile(LPCTSTR szRelatePath) = 0;


	//************************************
	// Method:    创建目录. 
	// Returns:   BOOL                         是否成功创建目录
	// Parameter: LPCSTR szRelatePath          被创建目录的相对路径	
	// memo:      使用该方法会创建路径上的全部目录
	//************************************
	virtual BOOL CreateDirectory(LPCTSTR szRelatePath) = 0;

	//************************************
	// Method:    删除目录. 
	// Returns:   BOOL                         是否成功删除目录
	// Parameter: LPCSTR szRelatePath          被删除目录的相对路径	
	// Parameter: BOOL bRecurDelete            是否递归删除子目录. 如果为FALSE,且目录非空,则删除失败
	//************************************
	virtual BOOL RemoveDirectory(LPCTSTR szRelatePath, BOOL bRecurDelete) = 0;

	//************************************
	// Method:    检查目录是否存在
	// Returns:   BOOL                         目录是否存在
	// Parameter: LPCSTR szRelatePath          被创建目录的相对路径		
	//************************************
	virtual BOOL IsDirectoryExist(LPCTSTR szRelatePath) = 0;
	
	//************************************
	// Method:    创建文件查找对象
	// Returns:   IFileFind*                    文件查找对象. 使用完成后需要调用IFileFind::Release()释放
	// Parameter: LPCSTR szRelatePath           开始查找的起始路径	
	//************************************
	virtual IFileFind * CreateFileFind(LPCTSTR szRelatePath) = 0;

	//************************************
	// Method:    获取文件被引用(打开)的次数 
	// Returns:   DWORD                         文件被引用的次数.
	// Parameter: LPCSTR szRelatePath           文件的相对路径   
	//    memo  :    此方法仅返回在本文件系统中引用的次数.  在其它文件系统中引用的次数,并不会记录
	//************************************
	virtual DWORD GetFileReferenceNums(LPCTSTR szRelatePath) = 0;
};

class IFile
{
public:
	enum EN_SeekMode
	{
		enBegin,
		enCurrent,
		enEnd,
	};


public:
	//************************************
	// Method:    释放文件
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;


	//************************************
	// Method:    读取文件数据
	// Returns:   BOOL                       发生错误返回0.  如果遇到文件尾,此值仍为非0,但 *pActualRead==0
	// Parameter: void * pBuffer             缓冲区    
	// Parameter: DWORD dwReadBytes          请求读取的数据量
	// Parameter: DWORD *pActualRead         如果此值不为NULL, 返回实际读取的字节数
	//************************************
	virtual BOOL Read(void *pBuffer, DWORD dwReadBytes, DWORD *pActualRead = NULL) = 0 ;

	
	//************************************
	// Method:    写入文件数据	
	// Returns:   BOOL	
	// Parameter: void * pBuffer             数据缓冲区
	// Parameter: DWORD dwWriteBytes         需要写入多少字节
	// Parameter: DWORD * pActualWrite       如果此值不为NULL, 返回实际写入的字节数
	//************************************
	virtual BOOL Write(const void *pBuffer, DWORD dwWriteBytes, DWORD *pActualWrite = NULL) = 0;


	//************************************
	// Method:    获取文件大	
	// Returns:   size_t                      文件大小
	// Qualifier:
	//************************************
	virtual size_t GetFileSize() = 0;


	//************************************
	// Method:    获取文件当前位置
	// Returns:   DWORD                      文件数据指针位置
	// Qualifier:
	//************************************
	virtual DWORD GetPosition() = 0;
	
	//************************************
	// Method:    跳跃位置
	// Returns:   BOOL                      是否成功 	
	// Parameter: int iOffset               位移                      
	// Parameter: EN_SeekMode enSeekMode    跳跃模式
	//     memo:      根据windows api的设定, 这个方法可以跳到文件尾之后的地方. 如果不调用Write(),文件大小不
	//            会产生变化; 一但调用了Write(),文件大小会增加至这个位置.
	//************************************
	virtual BOOL Seek(int iOffset, EN_SeekMode enSeekMode) = 0;

	//************************************
	// Method:    关闭文件
	// Returns:   	
	//************************************
	virtual void Close() = 0;

	//************************************
	// Method:    把当前位置设置文件结尾
	// Returns:   BOOL                      是否成功 	
	// Parameter: 
	//     memo:  
	//    
	//************************************
	virtual BOOL SetEndOfFile() = 0;
};


//  文件系统查找接口
class IFileFind
{
public:
	//************************************
	// Method:    释放
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;


	//************************************
	// Method:    GetFileName
	// Returns:   TCHAR *                  获取当前搜索到的文件名(或目录名), 不带路径
	// Qualifier:
	//************************************
	virtual LPCTSTR GetFileName() = 0;

	//************************************
	// Method:    是否为目录	
	// Returns:   BOOL                    返回TRUE为目录, 否则为文件
	// Qualifier:
	//************************************
	virtual BOOL IsDirectory() = 0;

	//************************************
	// Method:    是否为"." 或".."目录	
	// Returns:   BOOL                    返回TRUE为点目录
	// Qualifier:
	//************************************
	virtual BOOL IsDot() = 0;

	//************************************
	// Method:    获取当前文件的路径  (不带文件名)	
	// Returns:   BOOL                     是否成功获取
	// Parameter: TCHAR * szPath           路径
	// Parameter: int iBufLen              缓冲区长度  
	//************************************
	virtual BOOL GetFilePath(TCHAR *szPath, int iBufLen) = 0;


	//************************************
	// Method:    打开文件进行读写
	// Returns:   IFile*                   打开文件	
	// Parameter: DWORD dwAccessMode       访问模式, 取值IFileSystem::EN_AccessMode
	// Parameter: DWORD dwShareMode        共享模式, 取值IFileSystem::EN_ShareMode
	//            BOOL bTruncateExists     此参数为TRUE, 则打开时会清除文件内容
	//      memo: 如果当前搜索目标是个目录 , 则返回NULL. 或者打开失败也是返回NULL
	//************************************
	virtual IFile* OpenFile(IFileSystem::EN_AccessMode enAccessMode, DWORD dwShareMode, BOOL bTruncateExists) = 0;


	//************************************
	// Method:    创建子目录的查询
	// Returns:   IFileFind*               子目录的查询. 使用完成后,需要调用Release()释放接口
	//    memo:   (1)  如果当前搜索目标是个文件,则返回NULL	
	//************************************
	virtual IFileFind* CreateSubDirectorySearch() = 0;


	//************************************
	// Method:    查找下一个文件或者目录	
	// Returns:   BOOL                     是否有下一个文件(目录)
	//************************************
	virtual BOOL FindNext() = 0;

};

//  zip助手 
class IZipHelper
{
public:
	
	//************************************
	// Method:    zip压缩一个目录	
	// Returns:   BOOL                       是否成功
	// Qualifier:  
	// Parameter: IFile * pZipFile           目标ZIP文件
	// Parameter: IFileSystem *pSrcFS        源文件系统
	// Parameter: LPCTSTR szSrcPath          需要压缩的源路径, 在文件系统中的相对路径. 如果从文件系统的当前目录开始压力,这个参数传_T("")
	//      memo:  (1) pZipFile 不要放在szSrcPath路径中, 否则压缩时, 可能会读取到目标文件自身,造成异常.
	//             (2) pZipFile不要求是本文件系统产生的对象
	//************************************
	virtual BOOL ZipDirectory(IFile *pZipFile, IFileSystem *pSrcFS, LPCTSTR szSrcPath = _T("")) = 0;


	//************************************
	// Method:    解压缩一个目录	
	// Returns:   BOOL                       是否成功
	// 
	// Parameter: IFileSystem * pDstFS       目标文件系统
	// Parameter: LPCTSTR szDstPath          在目标文件系统上的路径
	// Parameter: IFile * pSrcZipFile        源ZIP文件
	// Parameter: LPCTSTR szPassword         密码. 如果没有密码, 传NULL, 不要传""
	//      memo:  (1) pZipFile不要求是本文件系统产生的对象
	//             (2) pZipFile 不要放在szSrcPath路径中, 否则压缩时, 可能会读取到目标文件自身,造成异常.
	//************************************
	virtual BOOL UnzipDirectory(IFileSystem *pDstFS, LPCTSTR szDstPath, IFile *pSrcZipFile, LPCTSTR szPassword) = 0;

	//************************************
	// Method:    使用ZIP包中的文件校验目录	
	// Returns:   BOOL                       如果ZIP中的内容跟目录内容一致,返回TRUE; 否则返回FALSE
	// Qualifier:  
	// Parameter: IFileSystem *pDstFS        目标文件系统
	// Parameter: IFile * pZipFile           目标ZIP文件
	// Parameter: LPCTSTR szSrcPath          需要压缩的源路径
	// Parameter: LPCTSTR szPassword         密码. 如果没有密码, 传NULL, 不要传""
	//      memo:  (1) pZipFile不要求是本文件系统产生的对象
	//             (2) pZipFile 不要放在szSrcPath路径中, 否则压缩时, 可能会读取到目标文件自身,造成异常.
	//************************************
	virtual BOOL VerifyDirectory(IFileSystem *pDstFS, LPCTSTR szDstPath, IFile *pSrcZipFile, LPCTSTR szPassword) = 0;

	//************************************
	// Method:    获取最后一次错误描述
	// Returns:   LPCTSTR                    错误描述
	// Qualifier:
	//************************************
	virtual LPCTSTR GetLastErrorDesc() = 0;

	//************************************
	// Method:    释放
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;
};


};