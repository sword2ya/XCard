#include "stdafx.h"
#include "ModalExporter.h"
#include "GlobalClient.h"


void * GetModuleInterface(const char* szInterfaceName)
{
	if (strcmp(szInterfaceName, "IGlobalClient") == 0)
	{
		g_pGlobalClient = new CGlobalClient;
		return g_pGlobalClient;		
	}
	return NULL;
}