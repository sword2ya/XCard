#include <QtGui>

#include <tchar.h>
#include <windows.h>
#include <time.h>

#include <string>
using namespace std;

#include "appframe/ISocketSystem.h"
using namespace socketsystem;
#include "appframe/basetools/ITimerHelper.h"
using namespace basetools;

#include "logging.h"


class IGlobalClient;
extern IGlobalClient* g_pGlobalClient;