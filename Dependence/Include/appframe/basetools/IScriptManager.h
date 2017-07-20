/********************************************************************
	created:	2011/11/16  19:30
	file base:	IScriptManager
	file ext:	h
	author:		
	
	purpose:	脚本管理器接口, 用来创建各种脚本对象
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
		* 获取对象名
		* 
		* @param param1 
		* @return 返回对象名字
		* @see 无
		*/	
		virtual LPCTSTR GetObjectName() = 0;
		
		/**
		* 设置对象名称
		* 
		* @param param1 对象的名称 
		* @return 无
		* @see 无
		*/	
		virtual BOOL SetObjectName(LPCTSTR szObjName) = 0;
	
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
		virtual IResScript2* GetResScript() = 0;		
				
		/**
		* 获取当前对象的父对象
		* 
		* @param param1 
		* @return 当前对象的父对象; 如果当前对象为根对象(root), 则返回null
		* @see 无
		*/	
	    virtual IResObject2* GetParentObject() = 0;
		
		//////////////////////////     子对象相关   /////////////////////
		
		/**
		* 创建新的子对象
		* 
		* @param param1 
		* @return 返回新创建的子对象
		* @see 无
		*/		   
		virtual IResObject2 *CreateChildObject() = 0;
			
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
		virtual IResObject2* GetSubObjectByName(LPCTSTR szObjectName) = 0;
		
		
		/**
		* 通过索引号获取子对象
		* 
		* @param param1  子对象的索引号. 这个值取值应该为[0, GetSubObjectCount() - 1]
		* @return 返回子对象引用. 如果索引值超出范围, 返回null
		* @see 无
		*/		   
		virtual IResObject2* GetSubObjectByIndex(DWORD dwIndex) = 0;

		/**
		* 删除子对象
		* 
		* @param param1  子对象的引用
		* @return 成功删除子对象, 返回true; 如果传入的对象不是本结点的子对象, 返回false.
		* @see 无
		*/		   
		virtual BOOL EraseChildObject(IResObject2 *pResObject) = 0;
		
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
		virtual LPCTSTR GetPropertyName(DWORD dwIndex) = 0;
		
		/**
		* 判断当前结点是否存在指定名称的属性
		* 
		* @param param1  属性的名称(不能为空串)		
		* @return  如果存在该名称的属性, 返回true, 否则返回false
		* @see 无
		*/		   
		virtual BOOL HasProperty(LPCTSTR szPropertyName) = 0;
		
		/**
		* 根据属性名称,删除指定的属性
		* 
		* @param param1  属性的名称(不能为空串)		
		* @return  如果成功删除属性, 返回true; 如果属性不存在返回false.
		* @see 无
		*/		   
		virtual BOOL EraseProperty(LPCTSTR szPropertyName) = 0;
		
		/**
		* 更改属性名称
		* 
		* @param param1  属性的旧名称(不能为空串)		
		* @param param2  属性的新名称(不能为空串)
		* @return  如果属性改名成功, 返回true; 属性不存在,或新旧属性名输入不合法, 新属性名已经存在, 返回false.
		* @see 无
		*/		   
		virtual BOOL RenameProperty(LPCTSTR szOldPropertyName, LPCTSTR szNewPropertyName) = 0; 
		
		/**
		* 获取属性值, 并以字符串的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 以字符串的形式返回属性值. 否则返回strDefaultVal
		* @see 无
		*/		   
		virtual LPCTSTR GetPropertyString(LPCTSTR szPropertyName, LPCTSTR szDefaultVal) = 0;
		
		/**
		* 获取属性值, 并以整数的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 整数形式返回; 否则返回iDefaultValue
		* @see 无
		*/		   
		virtual int GetPropertyInt(LPCTSTR szPropertyName, int iDefaultValue) = 0;

		/**
		* 获取属性值, 并以整数的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 整数形式返回; 否则返回iDefaultValue
		* @see 无
		*/		   
		virtual __int64 GetPropertyInt64(LPCTSTR szPropertyName, __int64 iDefaultValue) = 0;


		/**
		* 获取属性值, 并以浮点数的形式返回
		* 
		* @param param1  属性的名称				 
		* @return  如果能找到指定的属性, 浮点数形式返回; 否则返回fDefaultValue
		* @see 无
		*/		   
		virtual float GetPropertyFloat(LPCTSTR szPropertyName, float fDefaultValue) = 0;
	
		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        如果指定的属性名不存在则自动创建一个属性
		* @see 无
		*/		   
		virtual void SetPropertyString(LPCTSTR szPropertyName, LPCTSTR szValue) = 0;
		
		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* 
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        
		* @see 无
		*/		   
		virtual void SetPropertyInt(LPCTSTR szPropertyName, int iValue) = 0;
		
		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* 
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        
		* @see 无
		*/		   
		virtual void SetPropertyInt64(LPCTSTR szPropertyName, __int64 iValue) = 0;

		/**
		* 设置属性值
		* 如果指定的属性名不存在则自动创建一个属性
		* 
		* @param param1  属性的名称
		* @param param2  属性值				 
		* @return        
		* @see 无
		*/	   
		virtual void SetPropertyFloat(LPCTSTR szPropertyName, float fValue) = 0;
		
		
		/**
		* 获取指定的属性, 以整型数组形式返回		
		* 
		* @param param1  属性的名称
		* @return   如果属性不存在, 返回一个空的数组; 否则返回数组元素的个数
		* @see 无
		*/	   
		virtual int GetArrayInt(LPCTSTR szPropertyName, int *pIntArray, int iArraySize) = 0;
		
		/**
		* 获取指定的属性, 以浮点数组形式返回		
		* 
		* @param param1  属性的名称
		* @return   如果属性不存在, 返回一个空的数组; 否则返回数组元素的个数
		* @see 无
		*/	   
		virtual int GetArrayFloat(LPCTSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;

		/**
		* 以整型数组的形式, 写入一个属性		
		* 
		* @param param1  属性的名称
		* @param param2  包含整型属性值的数组
		* @return     
		* @see 无
		*/	   
		virtual void SetArrayProperty(LPCTSTR szPropertyName, int *pIntArray, int iArraySize ) = 0;
		
				/**
		* 以浮点型数组的形式, 写入一个属性		
		* 
		* @param param1  属性的名称
		* @param param2  包含整型属性值的数组
		* @return     
		* @see 无
		*/	   
		virtual void SetArrayProperty(LPCTSTR szPropertyName, float *pFloatArray, int iArraySize) = 0;


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
		virtual BOOL IsAncestorObject(IResObject2 *pAncestor) = 0;

		
		/**
		* 复制pSrcObject结点的属性
		*
		* @param param1   复制属性数据的源结点
		* @param param2   是否先将本结点的属性删除
		* @return         无
		* @see 无
		*/	
		virtual void CopyProperty(IResObject2 *pSrcObject, BOOL bDeleteSelfProperty) = 0;
};




class IResScript2
{
public:
	enum ENCODE_MODE   // 编码模式
	{
		enAnsi,     // ansi字符串
		enUtf8,     // utf字符串
		//enUnicode,  // unicode字符串
	};

public:
		/**
		* 通过一个外部的XML文档, 创建出脚本.
		* 
		* @param param1 脚本文档.这个XML文档必须是之前用saveResScript()方法导出! 
		* @return 成功返回true, 失败返回false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResScript(LPCTSTR szFileName) = 0;

		
		/**
		* 通过一个字符串, 创建出脚本.
		* 
		* @param param1 脚本文档.这个XML文档必须是之前用GetResString()方法导出! 
		* @return 成功返回true, 失败返回false.
		* @see SaveResScript
		*/		
		virtual BOOL LoadResString(LPCTSTR szString) = 0;

		

		//************************************
		// Method:    GetScriptPath               获取脚本的磁盘路径. 
 		// Returns:   LPCTSTR                     脚本的磁盘路径.
		// memo:                                  这个路径在调用LoadResString(), 和SaveResScript(not NULL)后会被更新. 如果未调用过以上函数, 路径默认为空串("").
		//************************************
		virtual LPCTSTR GetScriptPath() = 0;


				
		//************************************
		// Method:    SetScriptPath               设置脚本的磁盘路径
		// Returns:   void
		//
		// Parameter: LPCTSTR szPath              脚本的磁盘路径.
		//************************************
		virtual void SetScriptPath(LPCTSTR szPath) = 0;


		//************************************
		// Method:    SaveResScript                               将内部数据保存成一个XML文件. 
		// FullName:  basetools::IResScript2::SaveResScript
		// Access:    virtual public 
		// Returns:   BOOL                                        保存是否成功
		// Qualifier:
		// Parameter: LPCTSTR szFileName                          保存路径. 如果这个参数为NULL, 则使用GetScriptPath()的值; 如果GetScriptPath()的值为空串, 则保存失败.
		//************************************
		virtual BOOL SaveResScript(LPCTSTR szFileName) = 0;

		/**
		* 将内部数据保存成一个XML文件. 
		* 这个文档可能通过LoadResScript()重新加载
		*
		* @param param1  XML脚本文档.  
		* @return 返回一个XML数据字符串.
		* @see LoadResScript
		*/		
		virtual LPCTSTR GetResString() = 0;

		
		/**
		* 获取文档的根对象 
		* 每个子对象都必须放在根对象下面.
		*
		* @param param1    
		* @return 返回XML数据文档的根对象.
		* @see 无
		*/		
		virtual IResObject2* GetResObjectRoot() = 0;
		
		
		/**
		* 访问指定ID的资源对象		
		*
		* @param param1 结点对象的唯一ID    
		* @return 如果该结点存在, 返回该结点对象; 否则返回null.
		* @see 无
		*/		
	    virtual IResObject2* GetResObject(DWORD dwID) = 0;
	

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
		virtual LPCTSTR GetLastErrorMsg() = 0;

		/**
		* 释放脚本
		*
		* @param param1 
		* @return        
		* @see 无
		*/	
		virtual void Release() = 0;



		//************************************
		// Method:    获取文件编码类型
		// Returns:    basetools::IResScript::ENCODE_MODE        文件编码类型. 对于一个新创建的IResScript对象,默认值为enAnsi
		// memo:       这个函数返回的是文件编码.  跟内在中的数据无关
		//             对于Unicode模式的库, 在内存中的数据会根据情况,从ansi或utf8转换为unicode.
		//             对于多字节模式的库, 内在中的数据格式跟文件格式一致.
		//          
		//************************************
		virtual ENCODE_MODE GetFileEncode() = 0;

		

		//************************************
		// Method:    设置文件的编码类型
		// Returns:    
		// memo:       
		//************************************


		//************************************
		// Method:    SetFileEncode                             设置文件的编码类型
		// FullName:  basetools::IResScript2::SetFileEncode   
		// Access:    virtual public 
		// Returns:   BOOL                                      编码转换是否成功
		// Qualifier:
		// Parameter: ENCODE_MODE enMode
		//      memo:                                        (1)   先用这个函数设置好编码类型后, 随后调用 SetName, SetPoperty等方法时, 需要使用对应的编码进行操作.
	    //                                                   (2)   调用这个这个函数后, 当前的数据会进行编码转换(Unicode版本不会有变化, 只有保存到文件才会进行编码转换) .
		//                                                   
		//************************************
		virtual BOOL SetFileEncode(ENCODE_MODE enMode) = 0;



		//************************************
		// Method:    SetFileEncrypt                  设置文件加密模式.  
		// Access:    virtual public 
		// Returns:   void
		// Qualifier:
		// Parameter: BOOL bEncrypt                   是否需要加密.   默认值FALSE
		// memo:                                      先用这个函数设置好加密类型, 再调用SaveResScript()来保存出对应的文件
		//                                        如果调用过LoadResScript(), 这个标记会根据文件类型作出改变
		//************************************
		virtual void SetFileEncrypt(BOOL bEncrypt) = 0;


		//************************************
		// Method:    GetFileEncrypt                   获取文件的加密模式
		// Access:    virtual public 
		// Returns:   BOOL                             文件的加密模式
		// Qualifier:
		//************************************
		virtual BOOL GetFileEncrypt() = 0;


		//************************************
		// Method:    ResortObjectID                    重排全部对象结点的ID , 从dwStartID开始分配		
		// Access:    virtual public 
		// Returns:   BOOL                              重排是否成功 
		// Qualifier:
		// Parameter: DWORD dwStartID                   新的起始ID
		//************************************
		virtual BOOL ResortObjectID(DWORD dwStartID = 0) = 0;
};



};   // namespace