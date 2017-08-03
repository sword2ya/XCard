#include <QtGui>

#include <tchar.h>
#include <windows.h>
#include <time.h>

#include <string>
#include <set>
#include <vector>
#include <map>
using namespace std;

#include "appframe/ISocketSystem.h"
using namespace socketsystem;
#include "appframe/basetools/ITimerHelper.h"
using namespace basetools;

#include "DCommon.h"
#include "logging.h"

#include "Communicate/CSMessage.pb.h"

//#pragma comment(lib, "libprotobuf-lite.lib")
#pragma comment(lib, "libprotobufd.lib")


class IGlobalClient;
extern IGlobalClient* g_pGlobalClient;