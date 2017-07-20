/********************************************************************
	created:	2011/11/16  19:30
	file base:	IScriptManager
	file ext:	h
	author:		
	
	purpose:	�ű��������ӿ�, �����������ֽű�����
*********************************************************************/

#pragma once

class IResScript;
class IResObject;
class IScriptManager;

class IResObject
{
public:
		/**
		* ��ȡ������
		* 
		* @param param1 
		* @return ���ض�������
		* @see ��
		*/	
		virtual LPCSTR GetObjectName() = 0;
		
		/**
		* ���ö�������
		* 
		* @param param1 ��������� 
		* @return ��
		* @see ��
		*/	
		virtual BOOL SetObjectName(LPCSTR szObjName) = 0;
	
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
		virtual IResScript* GetResScript() = 0;		
				
		/**
		* ��ȡ��ǰ����ĸ�����
		* 
		* @param param1 
		* @return ��ǰ����ĸ�����; �����ǰ����Ϊ������(root), �򷵻�null
		* @see ��
		*/	
	    virtual IResObject* GetParentObject() = 0;
		
		//////////////////////////     �Ӷ������   /////////////////////
		
		/**
		* �����µ��Ӷ���
		* 
		* @param param1 
		* @return �����´������Ӷ���
		* @see ��
		*/		   
		virtual IResObject *CreateChildObject() = 0;
			
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
		virtual IResObject* GetSubObjectByName(LPCSTR szObjectName) = 0;
		
		
		/**
		* ͨ�������Ż�ȡ�Ӷ���
		* 
		* @param param1  �Ӷ����������. ���ֵȡֵӦ��Ϊ[0, GetSubObjectCount() - 1]
		* @return �����Ӷ�������. �������ֵ������Χ, ����null
		* @see ��
		*/		   
		virtual IResObject* GetSubObjectByIndex(DWORD dwIndex) = 0;

		/**
		* ɾ���Ӷ���
		* 
		* @param param1  �Ӷ��������
		* @return �ɹ�ɾ���Ӷ���, ����true; �������Ķ����Ǳ������Ӷ���, ����false.
		* @see ��
		*/		   
		virtual BOOL EraseChildObject(IResObject *pResObject) = 0;
		
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
		virtual LPCSTR GetPropertyName(DWORD dwIndex) = 0;
		
		/**
		* �жϵ�ǰ����Ƿ����ָ�����Ƶ�����
		* 
		* @param param1  ���Ե�����(����Ϊ�մ�)		
		* @return  ������ڸ����Ƶ�����, ����true, ���򷵻�false
		* @see ��
		*/		   
		virtual BOOL HasProperty(LPCSTR szPropertyName) = 0;
		
		/**
		* ������������,ɾ��ָ��������
		* 
		* @param param1  ���Ե�����(����Ϊ�մ�)		
		* @return  ����ɹ�ɾ������, ����true; ������Բ����ڷ���false.
		* @see ��
		*/		   
		virtual BOOL EraseProperty(LPCSTR szPropertyName) = 0;
		
		/**
		* ������������
		* 
		* @param param1  ���Եľ�����(����Ϊ�մ�)		
		* @param param2  ���Ե�������(����Ϊ�մ�)
		* @return  ������Ը����ɹ�, ����true; ���Բ�����,���¾����������벻�Ϸ�, ���������Ѿ�����, ����false.
		* @see ��
		*/		   
		virtual BOOL RenameProperty(LPCSTR szOldPropertyName, LPCSTR szNewPropertyName) = 0; 
		
		/**
		* ��ȡ����ֵ, �����ַ�������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ���ַ�������ʽ��������ֵ. ���򷵻�strDefaultVal
		* @see ��
		*/		   
		virtual LPCSTR GetPropertyString(LPCSTR szPropertyName, LPCSTR szDefaultVal) = 0;
		
		/**
		* ��ȡ����ֵ, ������������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ������ʽ����; ���򷵻�iDefaultValue
		* @see ��
		*/		   
		virtual int GetPropertyInt(LPCSTR szPropertyName, int iDefaultValue) = 0;

		/**
		* ��ȡ����ֵ, ���Ը���������ʽ����
		* 
		* @param param1  ���Ե�����				 
		* @return  ������ҵ�ָ��������, ��������ʽ����; ���򷵻�fDefaultValue
		* @see ��
		*/		   
		virtual float GetPropertyFloat(LPCSTR szPropertyName, float fDefaultValue) = 0;
	
		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        ���ָ�������������������Զ�����һ������
		* @see ��
		*/		   
		virtual void SetPropertyString(LPCSTR szPropertyName, LPCSTR szValue) = 0;
		
		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* 
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        
		* @see ��
		*/		   
		virtual void SetPropertyInt(LPCSTR szPropertyName, int iValue) = 0;
		
		/**
		* ��������ֵ
		* ���ָ�������������������Զ�����һ������
		* 
		* @param param1  ���Ե�����
		* @param param2  ����ֵ				 
		* @return        
		* @see ��
		*/	   
		virtual void SetPropertyFloat(LPCSTR szPropertyName, float fValue) = 0;
		
		
		/**
		* ��ȡָ��������, ������������ʽ����		
		* 
		* @param param1  ���Ե�����
		* @return   ������Բ�����, ����һ���յ�����; ���򷵻�����Ԫ�صĸ���
		* @see ��
		*/	   
		virtual int GetArrayInt(LPCSTR szPropertyName, int *pIntArray, int iArraySize) = 0;
		
		/**
		* ��ȡָ��������, �Ը���������ʽ����		
		* 
		* @param param1  ���Ե�����
		* @return   ������Բ�����, ����һ���յ�����; ���򷵻�����Ԫ�صĸ���
		* @see ��
		*/	   
		virtual int GetArrayFloat(LPCSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;

		/**
		* �������������ʽ, д��һ������		
		* 
		* @param param1  ���Ե�����
		* @param param2  ������������ֵ������
		* @return     
		* @see ��
		*/	   
		virtual void SetArrayProperty(LPCSTR szPropertyName, int *pIntArray, int iArraySize ) = 0;
		
				/**
		* �Ը������������ʽ, д��һ������		
		* 
		* @param param1  ���Ե�����
		* @param param2  ������������ֵ������
		* @return     
		* @see ��
		*/	   
		virtual void SetArrayProperty(LPCSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;


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
		virtual BOOL IsAncestorObject(IResObject *pAncestor) = 0;

		
		/**
		* ����pSrcObject��������
		*
		* @param param1   �����������ݵ�Դ���
		* @param param2   �Ƿ��Ƚ�����������ɾ��
		* @return         ��
		* @see ��
		*/	
		virtual void CopyProperty(IResObject *pSrcObject, BOOL bDeleteSelfProperty) = 0;
};




class IResScript
{
public:
		/**
		* ͨ��һ���ⲿ��XML�ĵ�, �������ű�.
		* 
		* @param param1 �ű��ĵ�.���XML�ĵ�������֮ǰ��saveResScript()��������! 
		* @return �ɹ�����true, ʧ�ܷ���false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResScript(LPCSTR szFileName) = 0;

		
		/**
		* ͨ��һ���ַ���, �������ű�.
		* 
		* @param param1 �ű��ĵ�.���XML�ĵ�������֮ǰ��GetResString()��������! 
		* @return �ɹ�����true, ʧ�ܷ���false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResString(LPCSTR szString) = 0;

		
		/**
		* ���ڲ����ݱ����һ��XML�ļ�. 
		* ����ĵ�����ͨ��LoadResScript()���¼���
		*
		* @param param1  XML�ű��ĵ�.  
		* @return ����һ��XML�����ĵ�.
		* @see LoadResScript
		*/		
		virtual BOOL SaveResScript(LPCSTR szFileName) = 0;

		/**
		* ���ڲ����ݱ����һ��XML�ļ�. 
		* ����ĵ�����ͨ��LoadResScript()���¼���
		*
		* @param param1  XML�ű��ĵ�.  
		* @return ����һ��XML�����ַ���.
		* @see LoadResScript
		*/		
		virtual LPCSTR GetResString() = 0;

		
		/**
		* ��ȡ�ĵ��ĸ����� 
		* ÿ���Ӷ��󶼱�����ڸ���������.
		*
		* @param param1    
		* @return ����XML�����ĵ��ĸ�����.
		* @see ��
		*/		
		virtual IResObject* GetResObjectRoot() = 0;
		
		
		/**
		* ����ָ��ID����Դ����		
		*
		* @param param1 �������ΨһID    
		* @return ����ý�����, ���ظý�����; ���򷵻�null.
		* @see ��
		*/		
	    virtual IResObject* GetResObject(DWORD dwID) = 0;
	

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
		virtual LPCSTR GetLastErrorMsg() = 0;

		/**
		* �ͷŽű�
		*
		* @param param1 
		* @return        
		* @see ��
		*/	
		virtual void Release() = 0;


};



class IScriptManager
{
public:
	virtual IResScript* CreateResScript(DWORD dwStartID) = 0;

	virtual void Release() = 0;
};