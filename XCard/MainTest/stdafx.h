// stdafx.h : ��׼ϵͳ�����ļ��İ����ļ���
// ���Ǿ���ʹ�õ��������ĵ�
// �ض�����Ŀ�İ����ļ�
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

// TODO: �ڴ˴����ó�����Ҫ������ͷ�ļ�
