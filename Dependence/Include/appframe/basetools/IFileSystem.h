/********************************************************************
	created:	2013/3/5  15:09
	file base:	IFileSystem
	file ext:	h
	author:		
	
	purpose:	�ļ�ϵͳ
*********************************************************************/

#pragma once 

namespace basetools
{

class IFile;
class IFileFind;
		
class IFileSystem
{
public:

	//  ����ģʽ
	enum EN_AccessMode{
		enRead = 1,
		enWrite ,		
		enReadWrite,
	};

	//  ����ģʽ
	enum EN_ShareMode{
		enShareNone = 0,    
		enShareRead = 1,
		enShareWrite = 2,
		enShareDelete = 4,
	};


	//  ����ģʽ
	enum EN_CreationDisposition{
		enCreateNew ,       // Creates a new file. The function fails if the specified file already exists.
		enCreateAlways,    // Creates a new file. If the file exists, the function overwrites the file and clears the existing attributes.
		enOpenExist,       //  Opens the file. The function fails if the file does not exist
		enOpenAlways,      //  Opens the file, if it exists. If the file does not exist, the function creates the file as if dwCreationDisposition were CREATE_NEW
		enTruncateExists,  //  Opens the file. Once opened, the file is truncated so that its size is zero bytes.
	};


public:

	//************************************
	// Method:    �ͷ��ļ�ϵͳ
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;



	//************************************
	// Method:    ��ȡ���һ�δ�������
	// Returns:   LPCTSTR                    ��������
	// Qualifier:
	//************************************
	virtual LPCTSTR GetLastErrorDesc() = 0;


	//************************************
	// Method:    ������׼Ŀ¼
	// Returns:   BOOL	                      �Ƿ�ɹ�����
	// Parameter: LPCTSTR szBaseDir            ��׼Ŀ¼
	//************************************
	virtual BOOL AttachBaseDirectory(LPCTSTR szBaseDir) = 0;


	//************************************
	// Method:    ��ȡ��׼Ŀ¼
	// Returns:   LPCTSTR	                    ��׼Ŀ¼	
	//************************************
	virtual LPCTSTR GetBaseDirectory() = 0;


	//************************************
	// Method:    ������׼Ŀ¼
	// Returns:   IFile*	                    ���򿪵��ļ�����. ʹ����ɺ���� IFile::Release()
	// Parameter: LPCSTR szRelatePath           �����ļ������·��. ����·��Ϊ (BasePath + '\\' + szRelatePath)
	// Parameter: BOOL bCreateDirIfNotExist     Ŀ¼������ʱ, �Ƿ��ȴ���Ŀ¼
	// Parameter: DWORD dwDesiredAccess         ����ģʽ, ȡֵ�� EN_AccessMode  
	// Parameter: DWORD dwShareMode             ����ģʽ,ȡֵ�� EN_ShareMode
	// Parameter: DWORD dwCreationDisposition   ����ģʽ,ȡֵ�� EN_CreationDisposition
	//************************************
	virtual IFile* OpenFile(LPCTSTR szRelatePath, BOOL bCreateDirIfNotExist, EN_AccessMode enAccessMode, DWORD dwShareMode, EN_CreationDisposition enCreationDisposition) = 0;

	//************************************
	// Method:    ����ļ��Ƿ����
	// Returns:   BOOL                         �ļ��Ƿ����
	// Parameter: LPCSTR szRelatePath          �������ļ������·��
	//************************************
	virtual BOOL IsFileExist(LPCTSTR szRelatePath) = 0;

	//************************************
	// Method:    ɾ���ļ�
	// Returns:   BOOL                         �Ƿ�ɹ�ɾ���ļ�
	// Parameter: LPCSTR szRelatePath          ��ɾ���ļ������·��
	//************************************
	virtual BOOL RemoveFile(LPCTSTR szRelatePath) = 0;


	//************************************
	// Method:    ����Ŀ¼. 
	// Returns:   BOOL                         �Ƿ�ɹ�����Ŀ¼
	// Parameter: LPCSTR szRelatePath          ������Ŀ¼�����·��	
	// memo:      ʹ�ø÷����ᴴ��·���ϵ�ȫ��Ŀ¼
	//************************************
	virtual BOOL CreateDirectory(LPCTSTR szRelatePath) = 0;

	//************************************
	// Method:    ɾ��Ŀ¼. 
	// Returns:   BOOL                         �Ƿ�ɹ�ɾ��Ŀ¼
	// Parameter: LPCSTR szRelatePath          ��ɾ��Ŀ¼�����·��	
	// Parameter: BOOL bRecurDelete            �Ƿ�ݹ�ɾ����Ŀ¼. ���ΪFALSE,��Ŀ¼�ǿ�,��ɾ��ʧ��
	//************************************
	virtual BOOL RemoveDirectory(LPCTSTR szRelatePath, BOOL bRecurDelete) = 0;

	//************************************
	// Method:    ���Ŀ¼�Ƿ����
	// Returns:   BOOL                         Ŀ¼�Ƿ����
	// Parameter: LPCSTR szRelatePath          ������Ŀ¼�����·��		
	//************************************
	virtual BOOL IsDirectoryExist(LPCTSTR szRelatePath) = 0;
	
	//************************************
	// Method:    �����ļ����Ҷ���
	// Returns:   IFileFind*                    �ļ����Ҷ���. ʹ����ɺ���Ҫ����IFileFind::Release()�ͷ�
	// Parameter: LPCSTR szRelatePath           ��ʼ���ҵ���ʼ·��	
	//************************************
	virtual IFileFind * CreateFileFind(LPCTSTR szRelatePath) = 0;

	//************************************
	// Method:    ��ȡ�ļ�������(��)�Ĵ��� 
	// Returns:   DWORD                         �ļ������õĴ���.
	// Parameter: LPCSTR szRelatePath           �ļ������·��   
	//    memo  :    �˷����������ڱ��ļ�ϵͳ�����õĴ���.  �������ļ�ϵͳ�����õĴ���,�������¼
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
	// Method:    �ͷ��ļ�
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;


	//************************************
	// Method:    ��ȡ�ļ�����
	// Returns:   BOOL                       �������󷵻�0.  ��������ļ�β,��ֵ��Ϊ��0,�� *pActualRead==0
	// Parameter: void * pBuffer             ������    
	// Parameter: DWORD dwReadBytes          �����ȡ��������
	// Parameter: DWORD *pActualRead         �����ֵ��ΪNULL, ����ʵ�ʶ�ȡ���ֽ���
	//************************************
	virtual BOOL Read(void *pBuffer, DWORD dwReadBytes, DWORD *pActualRead = NULL) = 0 ;

	
	//************************************
	// Method:    д���ļ�����	
	// Returns:   BOOL	
	// Parameter: void * pBuffer             ���ݻ�����
	// Parameter: DWORD dwWriteBytes         ��Ҫд������ֽ�
	// Parameter: DWORD * pActualWrite       �����ֵ��ΪNULL, ����ʵ��д����ֽ���
	//************************************
	virtual BOOL Write(const void *pBuffer, DWORD dwWriteBytes, DWORD *pActualWrite = NULL) = 0;


	//************************************
	// Method:    ��ȡ�ļ���	
	// Returns:   size_t                      �ļ���С
	// Qualifier:
	//************************************
	virtual size_t GetFileSize() = 0;


	//************************************
	// Method:    ��ȡ�ļ���ǰλ��
	// Returns:   DWORD                      �ļ�����ָ��λ��
	// Qualifier:
	//************************************
	virtual DWORD GetPosition() = 0;
	
	//************************************
	// Method:    ��Ծλ��
	// Returns:   BOOL                      �Ƿ�ɹ� 	
	// Parameter: int iOffset               λ��                      
	// Parameter: EN_SeekMode enSeekMode    ��Ծģʽ
	//     memo:      ����windows api���趨, ����������������ļ�β֮��ĵط�. ���������Write(),�ļ���С��
	//            ������仯; һ��������Write(),�ļ���С�����������λ��.
	//************************************
	virtual BOOL Seek(int iOffset, EN_SeekMode enSeekMode) = 0;

	//************************************
	// Method:    �ر��ļ�
	// Returns:   	
	//************************************
	virtual void Close() = 0;

	//************************************
	// Method:    �ѵ�ǰλ�������ļ���β
	// Returns:   BOOL                      �Ƿ�ɹ� 	
	// Parameter: 
	//     memo:  
	//    
	//************************************
	virtual BOOL SetEndOfFile() = 0;
};


//  �ļ�ϵͳ���ҽӿ�
class IFileFind
{
public:
	//************************************
	// Method:    �ͷ�
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;


	//************************************
	// Method:    GetFileName
	// Returns:   TCHAR *                  ��ȡ��ǰ���������ļ���(��Ŀ¼��), ����·��
	// Qualifier:
	//************************************
	virtual LPCTSTR GetFileName() = 0;

	//************************************
	// Method:    �Ƿ�ΪĿ¼	
	// Returns:   BOOL                    ����TRUEΪĿ¼, ����Ϊ�ļ�
	// Qualifier:
	//************************************
	virtual BOOL IsDirectory() = 0;

	//************************************
	// Method:    �Ƿ�Ϊ"." ��".."Ŀ¼	
	// Returns:   BOOL                    ����TRUEΪ��Ŀ¼
	// Qualifier:
	//************************************
	virtual BOOL IsDot() = 0;

	//************************************
	// Method:    ��ȡ��ǰ�ļ���·��  (�����ļ���)	
	// Returns:   BOOL                     �Ƿ�ɹ���ȡ
	// Parameter: TCHAR * szPath           ·��
	// Parameter: int iBufLen              ����������  
	//************************************
	virtual BOOL GetFilePath(TCHAR *szPath, int iBufLen) = 0;


	//************************************
	// Method:    ���ļ����ж�д
	// Returns:   IFile*                   ���ļ�	
	// Parameter: DWORD dwAccessMode       ����ģʽ, ȡֵIFileSystem::EN_AccessMode
	// Parameter: DWORD dwShareMode        ����ģʽ, ȡֵIFileSystem::EN_ShareMode
	//            BOOL bTruncateExists     �˲���ΪTRUE, ���ʱ������ļ�����
	//      memo: �����ǰ����Ŀ���Ǹ�Ŀ¼ , �򷵻�NULL. ���ߴ�ʧ��Ҳ�Ƿ���NULL
	//************************************
	virtual IFile* OpenFile(IFileSystem::EN_AccessMode enAccessMode, DWORD dwShareMode, BOOL bTruncateExists) = 0;


	//************************************
	// Method:    ������Ŀ¼�Ĳ�ѯ
	// Returns:   IFileFind*               ��Ŀ¼�Ĳ�ѯ. ʹ����ɺ�,��Ҫ����Release()�ͷŽӿ�
	//    memo:   (1)  �����ǰ����Ŀ���Ǹ��ļ�,�򷵻�NULL	
	//************************************
	virtual IFileFind* CreateSubDirectorySearch() = 0;


	//************************************
	// Method:    ������һ���ļ�����Ŀ¼	
	// Returns:   BOOL                     �Ƿ�����һ���ļ�(Ŀ¼)
	//************************************
	virtual BOOL FindNext() = 0;

};

//  zip���� 
class IZipHelper
{
public:
	
	//************************************
	// Method:    zipѹ��һ��Ŀ¼	
	// Returns:   BOOL                       �Ƿ�ɹ�
	// Qualifier:  
	// Parameter: IFile * pZipFile           Ŀ��ZIP�ļ�
	// Parameter: IFileSystem *pSrcFS        Դ�ļ�ϵͳ
	// Parameter: LPCTSTR szSrcPath          ��Ҫѹ����Դ·��, ���ļ�ϵͳ�е����·��. ������ļ�ϵͳ�ĵ�ǰĿ¼��ʼѹ��,���������_T("")
	//      memo:  (1) pZipFile ��Ҫ����szSrcPath·����, ����ѹ��ʱ, ���ܻ��ȡ��Ŀ���ļ�����,����쳣.
	//             (2) pZipFile��Ҫ���Ǳ��ļ�ϵͳ�����Ķ���
	//************************************
	virtual BOOL ZipDirectory(IFile *pZipFile, IFileSystem *pSrcFS, LPCTSTR szSrcPath = _T("")) = 0;


	//************************************
	// Method:    ��ѹ��һ��Ŀ¼	
	// Returns:   BOOL                       �Ƿ�ɹ�
	// 
	// Parameter: IFileSystem * pDstFS       Ŀ���ļ�ϵͳ
	// Parameter: LPCTSTR szDstPath          ��Ŀ���ļ�ϵͳ�ϵ�·��
	// Parameter: IFile * pSrcZipFile        ԴZIP�ļ�
	// Parameter: LPCTSTR szPassword         ����. ���û������, ��NULL, ��Ҫ��""
	//      memo:  (1) pZipFile��Ҫ���Ǳ��ļ�ϵͳ�����Ķ���
	//             (2) pZipFile ��Ҫ����szSrcPath·����, ����ѹ��ʱ, ���ܻ��ȡ��Ŀ���ļ�����,����쳣.
	//************************************
	virtual BOOL UnzipDirectory(IFileSystem *pDstFS, LPCTSTR szDstPath, IFile *pSrcZipFile, LPCTSTR szPassword) = 0;

	//************************************
	// Method:    ʹ��ZIP���е��ļ�У��Ŀ¼	
	// Returns:   BOOL                       ���ZIP�е����ݸ�Ŀ¼����һ��,����TRUE; ���򷵻�FALSE
	// Qualifier:  
	// Parameter: IFileSystem *pDstFS        Ŀ���ļ�ϵͳ
	// Parameter: IFile * pZipFile           Ŀ��ZIP�ļ�
	// Parameter: LPCTSTR szSrcPath          ��Ҫѹ����Դ·��
	// Parameter: LPCTSTR szPassword         ����. ���û������, ��NULL, ��Ҫ��""
	//      memo:  (1) pZipFile��Ҫ���Ǳ��ļ�ϵͳ�����Ķ���
	//             (2) pZipFile ��Ҫ����szSrcPath·����, ����ѹ��ʱ, ���ܻ��ȡ��Ŀ���ļ�����,����쳣.
	//************************************
	virtual BOOL VerifyDirectory(IFileSystem *pDstFS, LPCTSTR szDstPath, IFile *pSrcZipFile, LPCTSTR szPassword) = 0;

	//************************************
	// Method:    ��ȡ���һ�δ�������
	// Returns:   LPCTSTR                    ��������
	// Qualifier:
	//************************************
	virtual LPCTSTR GetLastErrorDesc() = 0;

	//************************************
	// Method:    �ͷ�
	// Returns:   void	                     	
	//************************************
	virtual void Release() = 0;
};


};