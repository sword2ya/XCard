/********************************************************************
	created:	2011/11/16  19:30
	file base:	IScriptManager
	file ext:	h
	author:		
	
	purpose:	脚本管理器接口, 用来创建各种脚本对象
*********************************************************************/

#pragma once

class IResScript;
class IResObject;
class IScriptManager;

class IResObject
{
public:
		/**
		* 获取对象名
		* 
		* @param param1 
		* @return 返回对象名字
		* @see 无
		*/	
		virtual LPCSTR GetObjectName() = 0;
		
		/**
		* 设置对象名称
		* 
		* @param param1 对象的名称 
		* @return 无
		* @see 无
		*/	
		virtual BOOL SetObjectName(LPCSTR szObjName) = 0;
	
		/**
		* 获取对象ID
		* 
		* @param param1 
		* @return 对象在脚本内的唯一ID
		* @see 无
		*/	
		virtual DWORD GetID() = 0;
		
		/**
		* 获取对应的脚本对象
		* 
		* @param param1 
		* @return 返回对应的脚本对象
		* @see 无IResScript
		*/	
		virtual IResScript* GetResScript() = 0;		
				
		/**
		* 获取当前对象的父对象
		* 
		* @param param1 
		* @return 当前对象的父对象; 如果当前对象为根对象(root), 则返回null
		* @see 无
		*/	
	    virtual IResObject* GetParentObject() = 0;
		
		//////////////////////////     子对象相关   /////////////////////
		
		/**
		* 创建新的子对象
		* 
		* @param param1 
		* @return 返回新创建的子对象
		* @see 无
		*/		   
		virtual IResObject *CreateChildObject() = 0;
			
		/**
		* 获取子对象数目
		* 
		* @param param1 
		* @return 返回子对象的数目
		* @see 无
		*/		   
		virtual DWORD GetSubObjectCount() = 0;
	
		/**
		* 通过对象名获取子对象(大小写敏感)
		* 
		* @param param1  子对象的名称
		* @return 返回子对象引用. 如果无法匹配, 返回null. 如有多个同名子对象, 返回第一个
		* @see 无
		*/		   
		virtual IResObject* GetSubObjectByName(LPCSTR szObjectName) = 0;
		
		
		/**
		* 通过索引号获取子对象
		* 
		* @param param1  子对象的索引号. 这个值取值应该为[0, GetSubObjectCount() - 1]
		* @return 返回子对象引用. 如果索引值超出范围, 返回null
		* @see 无
		*/		   
		virtual IResObject* GetSubObjectByIndex(DWORD dwIndex) = 0;

		/**
		* 删除子对象
		* 
		* @param param1  子对象的引用
		* @return 成功删除子对象, 返回true; 如果传入的对象不是本结点的子对象, 返回false.
		* @see 无
		*/		   
		virtual BOOL EraseChildObject(IResObject *pResObject) = 0;
		
		//////////////////////////    对象属性相关   /////////////////////
		
		/**
		* 获取本对象的属性数目
		* 
		* @param param1  
		* @return  返回本对象的属性数目
		* @see 无
		*/		   
		virtual DWORD GetPropertyCount() = 0;
			
		/**
		* 获取本对象的属性名称
		* 
		* @param param1  属性的索引
		* @return  返回对应的属性名称. 如果索引无效, 返回空字符串("").
		* @see 无
		*/		   
		virtual LPCSTR GetPropertyName(DWORD dwIndex) = 0;
		
		/**
		* 判断当前结点是否存在指定名称的属性
		* 
		* @param param1  属性的名称(不能为空串)		
		* @return  如果存在该名称的属性, 返回true, 否则返回false
		* @see 无
		*/		   
		virtual BOOL HasProperty(LPCSTR szPropertyName) = 0;
		
		/**
		* 根据属性名称,删除指定的属性
		* 
		* @param param1  属性的名称(不能为空串)		
		* @return  如果成功删除属性, 返回true; 如果属性不存在返回false.
		* @see 无
		*/		   
		virtual BOOL EraseProperty(LPCSTR szPropertyName) = 0;
		
		/**
		* 更改属性名称
		* 
		* @param param1  属性的旧名称(不能为空串)		
		* @param param2  属性的新名称(不能为空串)
		* @return  如果属性改名成功, 返回true; 属性不存在,或新旧属性名输入不合法, 新属性名已经存在, 返回false.
		* @see 无
		*/		   
		virtual BOOL RenameProperty(LPCSTR szOldPropertyName, LPCSTR szNewPropertyName) = 0; 
		
		/**
		* 获取属性值, 并以字符串的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 以字符串的形式返回属性值. 否则返回strDefaultVal
		* @see 无
		*/		   
		virtual LPCSTR GetPropertyString(LPCSTR szPropertyName, LPCSTR szDefaultVal) = 0;
		
		/**
		* 获取属性值, 并以整数的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 整数形式返回; 否则返回iDefaultValue
		* @see 无
		*/		   
		virtual int GetPropertyInt(LPCSTR szPropertyName, int iDefaultValue) = 0;

		/**
		* 获取属性值, 并以浮点数的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 浮点数形式返回; 否则返回fDefaultValue
		* @see 无
		*/		   
		virtual float GetPropertyFloat(LPCSTR szPropertyName, float fDefaultValue) = 0;
	
		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        如果指定的属性名不存在则自动创建一个属性
		* @see 无
		*/		   
		virtual void SetPropertyString(LPCSTR szPropertyName, LPCSTR szValue) = 0;
		
		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* 
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        
		* @see 无
		*/		   
		virtual void SetPropertyInt(LPCSTR szPropertyName, int iValue) = 0;
		
		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* 
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        
		* @see 无
		*/	   
		virtual void SetPropertyFloat(LPCSTR szPropertyName, float fValue) = 0;
		
		
		/**
		* 获取指定的属性, 以整型数组形式返回		
		* 
		* @param param1  属性的名称
		* @return   如果属性不存在, 返回一个空的数组; 否则返回数组元素的个数
		* @see 无
		*/	   
		virtual int GetArrayInt(LPCSTR szPropertyName, int *pIntArray, int iArraySize) = 0;
		
		/**
		* 获取指定的属性, 以浮点数组形式返回		
		* 
		* @param param1  属性的名称
		* @return   如果属性不存在, 返回一个空的数组; 否则返回数组元素的个数
		* @see 无
		*/	   
		virtual int GetArrayFloat(LPCSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;

		/**
		* 以整型数组的形式, 写入一个属性		
		* 
		* @param param1  属性的名称
		* @param param2  包含整型属性值的数组
		* @return     
		* @see 无
		*/	   
		virtual void SetArrayProperty(LPCSTR szPropertyName, int *pIntArray, int iArraySize ) = 0;
		
				/**
		* 以浮点型数组的形式, 写入一个属性		
		* 
		* @param param1  属性的名称
		* @param param2  包含整型属性值的数组
		* @return     
		* @see 无
		*/	   
		virtual void SetArrayProperty(LPCSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;


		/**
		* 清除结点的全部属性		
		* 
		* @param param1  		
		* @return     
		* @see 无
		*/	   
		virtual void ClearAllPropertys() = 0;
		
		/**
		* 清除结点的全部子对象		
		* 
		* @param param1  		
		* @return     
		* @see 无
		*/	   
		virtual void ClearAllChildren() = 0;

		
		/**
		* 测试pAncestor是否本结点的祖先
		*
		* @param param1   祖先结点
		* @return         如果pAncestor为祖先结点, 返回TRUE; 否则返回FALSE
		* @see 无
		*/	
		virtual BOOL IsAncestorObject(IResObject *pAncestor) = 0;

		
		/**
		* 复制pSrcObject结点的属性
		*
		* @param param1   复制属性数据的源结点
		* @param param2   是否先将本结点的属性删除
		* @return         无
		* @see 无
		*/	
		virtual void CopyProperty(IResObject *pSrcObject, BOOL bDeleteSelfProperty) = 0;
};




class IResScript
{
public:
		/**
		* 通过一个外部的XML文档, 创建出脚本.
		* 
		* @param param1 脚本文档.这个XML文档必须是之前用saveResScript()方法导出! 
		* @return 成功返回true, 失败返回false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResScript(LPCSTR szFileName) = 0;

		
		/**
		* 通过一个字符串, 创建出脚本.
		* 
		* @param param1 脚本文档.这个XML文档必须是之前用GetResString()方法导出! 
		* @return 成功返回true, 失败返回false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResString(LPCSTR szString) = 0;

		
		/**
		* 将内部数据保存成一个XML文件. 
		* 这个文档可能通过LoadResScript()重新加载
		*
		* @param param1  XML脚本文档.  
		* @return 返回一个XML数据文档.
		* @see LoadResScript
		*/		
		virtual BOOL SaveResScript(LPCSTR szFileName) = 0;

		/**
		* 将内部数据保存成一个XML文件. 
		* 这个文档可能通过LoadResScript()重新加载
		*
		* @param param1  XML脚本文档.  
		* @return 返回一个XML数据字符串.
		* @see LoadResScript
		*/		
		virtual LPCSTR GetResString() = 0;

		
		/**
		* 获取文档的根对象 
		* 每个子对象都必须放在根对象下面.
		*
		* @param param1    
		* @return 返回XML数据文档的根对象.
		* @see 无
		*/		
		virtual IResObject* GetResObjectRoot() = 0;
		
		
		/**
		* 访问指定ID的资源对象		
		*
		* @param param1 结点对象的唯一ID    
		* @return 如果该结点存在, 返回该结点对象; 否则返回null.
		* @see 无
		*/		
	    virtual IResObject* GetResObject(DWORD dwID) = 0;
	

		/**
		* 获得本脚本当前最大的结点ID
		*
		* @param param1 
		* @return 当前脚本最大的流水号. 再新建结点的话, 它的ID就是这个值 + 1;
		* @see 无
		*/	
		virtual DWORD GetMaxID() = 0;
	
	
		/**
		* 获取错误字符串. 在操作错误后根据这个接口, 让外部程序提出处理方式.
		*
		* @param param1 
		* @return        返回最后一次的错误信息
		* @see 无
		*/	
		virtual LPCSTR GetLastErrorMsg() = 0;

		/**
		* 释放脚本
		*
		* @param param1 
		* @return        
		* @see 无
		*/	
		virtual void Release() = 0;


};



class IScriptManager
{
public:
	virtual IResScript* CreateResScript(DWORD dwStartID) = 0;

	virtual void Release() = 0;
};