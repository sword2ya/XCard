// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件
//

#pragma once

#include "targetver.h"

#include <windows.h>
#include <stdio.h>
#include <tchar.h>

#include <vector>
#include <list>
#include <map>
#include <set>

using namespace std;


#include "gtest\gtest.h"
#pragma comment(lib, "gtestd.lib")

#include "ModalLoader.h"
#include "appframe/ISocketSystem.h"
#include "appframe/basetools/ITimerHelper.h"
#include "appframe/basetools/BaseExportMain.h"
using namespace socketsystem;
using namespace basetools;

#include "IGlobalClient.h"

#include "UtilMacro.h"

#define Trace(x) {stringstream s; s<<x;  fprintf(stdout, s.str().c_str() ); fprintf(stdout, "\n");}
#define Error(x) {stringstream s; s<<x;  fprintf(stderr, s.str().c_str() ); fprintf(stderr, "\n");}
#define Warning(x) {stringstream s; s<<x;  fprintf(stderr, s.str().c_str() ); fprintf(stderr, "\n");}

// TODO: 在此处引用程序需要的其他头文件
