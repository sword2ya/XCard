/********************************************************************
	created:	2011/11/16  19:30
	file base:	IScriptManager
	file ext:	h
	author:		
	
	purpose:	�ű��������ӿ�, �����������ֽű�����
*********************************************************************/

#pragma once

namespace basetools
{

class IResScript2;
class IResObject2;


class IResObject2
{
public:

		/**
		* ��ȡ������
		* 
		* @param param1 
		* @return ���ض�������
		* @see ��
		*/	
		virtual LPCTSTR GetObjectName() = 0;
		
		/**
		* ���ö�������
		* 
		* @param param1 ��������� 
		* @return ��
		* @see ��
		*/	
		virtual BOOL SetObjectName(LPCTSTR szObjName) = 0;
	
		/**
		* ��ȡ����ID
		* 
		* @param param1 
		* @return �����ڽű��ڵ�ΨһID
		* @see ��
		*/	
		virtual DWORD GetID() = 0;
		
		/**
		* ��ȡ��Ӧ�Ľű�����
		* 
		* @param param1 
		* @return ���ض�Ӧ�Ľű�����
		* @see ��IResScript
		*/	
		virtual IResScript2* GetResScript() = 0;		
				
		/**
		* ��ȡ��ǰ����ĸ�����
		* 
		* @param param1 
		* @return ��ǰ����ĸ�����; �����ǰ����Ϊ������(root), �򷵻�null
		* @see ��
		*/	
	    virtual IResObject2* GetParentObject() = 0;
		
		//////////////////////////     �Ӷ������   /////////////////////
		
		/**
		* �����µ��Ӷ���
		* 
		* @param param1 
		* @return �����´������Ӷ���
		* @see ��
		*/		   
		virtual IResObject2 *CreateChildObject() = 0;
			
		/**
		* ��ȡ�Ӷ�����Ŀ
		* 
		* @param param1 
		* @return �����Ӷ������Ŀ
		* @see ��
		*/		   
		virtual DWORD GetSubObjectCount() = 0;
	
		/**
		* ͨ����������ȡ�Ӷ���(��Сд����)
		* 
		* @param param1  �Ӷ��������
		* @return �����Ӷ�������. ����޷�ƥ��, ����null. ���ж��ͬ���Ӷ���, ���ص�һ��
		* @see ��
		*/		   
		virtual IResObject2* GetSubObjectByName(LPCTSTR szObjectName) = 0;
		
		
		/**
		* ͨ�������Ż�ȡ�Ӷ���
		* 
		* @param param1  �Ӷ����������. ���ֵȡֵӦ��Ϊ[0, GetSubObjectCount() - 1]
		* @return �����Ӷ�������. �������ֵ������Χ, ����null
		* @see ��
		*/		   
		virtual IResObject2* GetSubObjectByIndex(DWORD dwIndex) = 0;

		/**
		* ɾ���Ӷ���
		* 
		* @param param1  �Ӷ��������
		* @return �ɹ�ɾ���Ӷ���, ����true; �������Ķ����Ǳ������Ӷ���, ����false.
		* @see ��
		*/		   
		virtual BOOL EraseChildObject(IResObject2 *pResObject) = 0;
		
		//////////////////////////    �����������   /////////////////////
		
		/**
		* ��ȡ�������������Ŀ
		* 
		* @param param1  
		* @return  ���ر������������Ŀ
		* @see ��
		*/		   
		virtual DWORD GetPropertyCount() = 0;
			
		/**
		* ��ȡ���������������
		* 
		* @param param1  ���Ե�����
		* @return  ���ض�Ӧ����������. ���������Ч, ���ؿ��ַ���("").
		* @see ��
		*/		   
		virtual LPCTSTR GetPropertyName(DWORD dwIndex) = 0;
		
		/**
		* �жϵ�ǰ����Ƿ����ָ�����Ƶ�����
		* 
		* @param param1  ���Ե�����(����Ϊ�մ�)		
		* @return  ������ڸ����Ƶ�����, ����true, ���򷵻�false
		* @see ��
		*/		   
		virtual BOOL HasProperty(LPCTSTR szPropertyName) = 0;
		
		/**
		* ������������,ɾ��ָ��������
		* 
		* @param param1  ���Ե�����(����Ϊ�մ�)		
		* @return  ����ɹ�ɾ������, ����true; ������Բ����ڷ���false.
		* @see ��
		*/		   
		virtual BOOL EraseProperty(LPCTSTR szPropertyName) = 0;
		
		/**
		* ������������
		* 
		* @param param1  ���Եľ�����(����Ϊ�մ�)		
		* @param param2  ���Ե�������(����Ϊ�մ�)
		* @return  ������Ը����ɹ�, ����true; ���Բ�����,���¾����������벻�Ϸ�, ���������Ѿ�����, ����false.
		* @see ��
		*/		   
		virtual BOOL RenameProperty(LPCTSTR szOldPropertyName, LPCTSTR szNewPropertyName) = 0; 
		
		/**
		* ��ȡ����ֵ, �����ַ�������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ���ַ�������ʽ��������ֵ. ���򷵻�strDefaultVal
		* @see ��
		*/		   
		virtual LPCTSTR GetPropertyString(LPCTSTR szPropertyName, LPCTSTR szDefaultVal) = 0;
		
		/**
		* ��ȡ����ֵ, ������������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ������ʽ����; ���򷵻�iDefaultValue
		* @see ��
		*/		   
		virtual int GetPropertyInt(LPCTSTR szPropertyName, int iDefaultValue) = 0;

		/**
		* ��ȡ����ֵ, ������������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ������ʽ����; ���򷵻�iDefaultValue
		* @see ��
		*/		   
		virtual __int64 GetPropertyInt64(LPCTSTR szPropertyName, __int64 iDefaultValue) = 0;


		/**
		* ��ȡ����ֵ, ���Ը���������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ��������ʽ����; ���򷵻�fDefaultValue
		* @see ��
		*/		   
		virtual float GetPropertyFloat(LPCTSTR szPropertyName, float fDefaultValue) = 0;
	
		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        ���ָ�������������������Զ�����һ������
		* @see ��
		*/		   
		virtual void SetPropertyString(LPCTSTR szPropertyName, LPCTSTR szValue) = 0;
		
		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* 
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        
		* @see ��
		*/		   
		virtual void SetPropertyInt(LPCTSTR szPropertyName, int iValue) = 0;
		
		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* 
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        
		* @see ��
		*/		   
		virtual void SetPropertyInt64(LPCTSTR szPropertyName, __int64 iValue) = 0;

		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* 
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        
		* @see ��
		*/	   
		virtual void SetPropertyFloat(LPCTSTR szPropertyName, float fValue) = 0;
		
		
		/**
		* ��ȡָ��������, ������������ʽ����		
		* 
		* @param param1  ���Ե�����
		* @return   ������Բ�����, ����һ���յ�����; ���򷵻�����Ԫ�صĸ���
		* @see ��
		*/	   
		virtual int GetArrayInt(LPCTSTR szPropertyName, int *pIntArray, int iArraySize) = 0;
		
		/**
		* ��ȡָ��������, �Ը���������ʽ����		
		* 
		* @param param1  ���Ե�����
		* @return   ������Բ�����, ����һ���յ�����; ���򷵻�����Ԫ�صĸ���
		* @see ��
		*/	   
		virtual int GetArrayFloat(LPCTSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;

		/**
		* �������������ʽ, д��һ������		
		* 
		* @param param1  ���Ե�����
		* @param param2  ������������ֵ������
		* @return     
		* @see ��
		*/	   
		virtual void SetArrayProperty(LPCTSTR szPropertyName, int *pIntArray, int iArraySize ) = 0;
		
				/**
		* �Ը������������ʽ, д��һ������		
		* 
		* @param param1  ���Ե�����
		* @param param2  ������������ֵ������
		* @return     
		* @see ��
		*/	   
		virtual void SetArrayProperty(LPCTSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;


		/**
		* �������ȫ������		
		* 
		* @param param1  		
		* @return     
		* @see ��
		*/	   
		virtual void ClearAllPropertys() = 0;
		
		/**
		* �������ȫ���Ӷ���		
		* 
		* @param param1  		
		* @return     
		* @see ��
		*/	   
		virtual void ClearAllChildren() = 0;

		
		/**
		* ����pAncestor�Ƿ񱾽�������
		*
		* @param param1   ���Ƚ��
		* @return         ���pAncestorΪ���Ƚ��, ����TRUE; ���򷵻�FALSE
		* @see ��
		*/	
		virtual BOOL IsAncestorObject(IResObject2 *pAncestor) = 0;

		
		/**
		* ����pSrcObject��������
		*
		* @param param1   �����������ݵ�Դ���
		* @param param2   �Ƿ��Ƚ�����������ɾ��
		* @return         ��
		* @see ��
		*/	
		virtual void CopyProperty(IResObject2 *pSrcObject, BOOL bDeleteSelfProperty) = 0;
};




class IResScript2
{
public:
	enum ENCODE_MODE   // ����ģʽ
	{
		enAnsi,     // ansi�ַ���
		enUtf8,     // utf�ַ���
		//enUnicode,  // unicode�ַ���
	};

public:
		/**
		* ͨ��һ���ⲿ��XML�ĵ�, �������ű�.
		* 
		* @param param1 �ű��ĵ�.���XML�ĵ�������֮ǰ��saveResScript()��������! 
		* @return �ɹ�����true, ʧ�ܷ���false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResScript(LPCTSTR szFileName) = 0;

		
		/**
		* ͨ��һ���ַ���, �������ű�.
		* 
		* @param param1 �ű��ĵ�.���XML�ĵ�������֮ǰ��GetResString()��������! 
		* @return �ɹ�����true, ʧ�ܷ���false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResString(LPCTSTR szString) = 0;

		

		//************************************
		// Method:    GetScriptPath               ��ȡ�ű��Ĵ���·��. 
 		// Returns:   LPCTSTR                     �ű��Ĵ���·��.
		// memo:                                  ���·���ڵ���LoadResString(), ��SaveResScript(not NULL)��ᱻ����. ���δ���ù����Ϻ���, ·��Ĭ��Ϊ�մ�("").
		//************************************
		virtual LPCTSTR GetScriptPath() = 0;


				
		//************************************
		// Method:    SetScriptPath               ���ýű��Ĵ���·��
		// Returns:   void
		//
		// Parameter: LPCTSTR szPath              �ű��Ĵ���·��.
		//************************************
		virtual void SetScriptPath(LPCTSTR szPath) = 0;


		//************************************
		// Method:    SaveResScript                               ���ڲ����ݱ����һ��XML�ļ�. 
		// FullName:  basetools::IResScript2::SaveResScript
		// Access:    virtual public 
		// Returns:   BOOL                                        �����Ƿ�ɹ�
		// Qualifier:
		// Parameter: LPCTSTR szFileName                          ����·��. ����������ΪNULL, ��ʹ��GetScriptPath()��ֵ; ���GetScriptPath()��ֵΪ�մ�, �򱣴�ʧ��.
		//************************************
		virtual BOOL SaveResScript(LPCTSTR szFileName) = 0;

		/**
		* ���ڲ����ݱ����һ��XML�ļ�. 
		* ����ĵ�����ͨ��LoadResScript()���¼���
		*
		* @param param1  XML�ű��ĵ�.  
		* @return ����һ��XML�����ַ���.
		* @see LoadResScript
		*/		
		virtual LPCTSTR GetResString() = 0;

		
		/**
		* ��ȡ�ĵ��ĸ����� 
		* ÿ���Ӷ��󶼱�����ڸ���������.
		*
		* @param param1    
		* @return ����XML�����ĵ��ĸ�����.
		* @see ��
		*/		
		virtual IResObject2* GetResObjectRoot() = 0;
		
		
		/**
		* ����ָ��ID����Դ����		
		*
		* @param param1 �������ΨһID    
		* @return ����ý�����, ���ظý�����; ���򷵻�null.
		* @see ��
		*/		
	    virtual IResObject2* GetResObject(DWORD dwID) = 0;
	

		/**
		* ��ñ��ű���ǰ���Ľ��ID
		*
		* @param param1 
		* @return ��ǰ�ű�������ˮ��. ���½����Ļ�, ����ID�������ֵ + 1;
		* @see ��
		*/	
		virtual DWORD GetMaxID() = 0;
	
	
		/**
		* ��ȡ�����ַ���. �ڲ���������������ӿ�, ���ⲿ�����������ʽ.
		*
		* @param param1 
		* @return        �������һ�εĴ�����Ϣ
		* @see ��
		*/	
		virtual LPCTSTR GetLastErrorMsg() = 0;

		/**
		* �ͷŽű�
		*
		* @param param1 
		* @return        
		* @see ��
		*/	
		virtual void Release() = 0;



		//************************************
		// Method:    ��ȡ�ļ���������
		// Returns:    basetools::IResScript::ENCODE_MODE        �ļ���������. ����һ���´�����IResScript����,Ĭ��ֵΪenAnsi
		// memo:       ����������ص����ļ�����.  �������е������޹�
		//             ����Unicodeģʽ�Ŀ�, ���ڴ��е����ݻ�������,��ansi��utf8ת��Ϊunicode.
		//             ���ڶ��ֽ�ģʽ�Ŀ�, �����е����ݸ�ʽ���ļ���ʽһ��.
		//          
		//************************************
		virtual ENCODE_MODE GetFileEncode() = 0;

		

		//************************************
		// Method:    �����ļ��ı�������
		// Returns:    
		// memo:       
		//************************************


		//************************************
		// Method:    SetFileEncode                             �����ļ��ı�������
		// FullName:  basetools::IResScript2::SetFileEncode   
		// Access:    virtual public 
		// Returns:   BOOL                                      ����ת���Ƿ�ɹ�
		// Qualifier:
		// Parameter: ENCODE_MODE enMode
		//      memo:                                        (1)   ��������������úñ������ͺ�, ������ SetName, SetPoperty�ȷ���ʱ, ��Ҫʹ�ö�Ӧ�ı�����в���.
	    //                                                   (2)   ����������������, ��ǰ�����ݻ���б���ת��(Unicode�汾�����б仯, ֻ�б��浽�ļ��Ż���б���ת��) .
		//                                                   
		//************************************
		virtual BOOL SetFileEncode(ENCODE_MODE enMode) = 0;



		//************************************
		// Method:    SetFileEncrypt                  �����ļ�����ģʽ.  
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: BOOL bEncrypt                   �Ƿ���Ҫ����.   Ĭ��ֵFALSE
		// memo:                                      ��������������úü�������, �ٵ���SaveResScript()���������Ӧ���ļ�
		//                                        ������ù�LoadResScript(), �����ǻ�����ļ����������ı�
		//************************************
		virtual void SetFileEncrypt(BOOL bEncrypt) = 0;


		//************************************
		// Method:    GetFileEncrypt                   ��ȡ�ļ��ļ���ģʽ
		// Access:    virtual public 
		// Returns:   BOOL                             �ļ��ļ���ģʽ
		// Qualifier:
		//************************************
		virtual BOOL GetFileEncrypt() = 0;


		//************************************
		// Method:    ResortObjectID                    ����ȫ���������ID , ��dwStartID��ʼ����		
		// Access:    virtual public 
		// Returns:   BOOL                              �����Ƿ�ɹ� 
		// Qualifier:
		// Parameter: DWORD dwStartID                   �µ���ʼID
		//************************************
		virtual BOOL ResortObjectID(DWORD dwStartID = 0) = 0;
};



};   // namespace