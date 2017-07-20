
#pragma once 

#define SafeRelease(p) if(p) {(p)->Release(); (p) = NULL;}