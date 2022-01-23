#ifndef _STD_AFX_H_
#define _STD_AFX_H_

#ifdef WIN32
#pragma warning(disable:4100)
#pragma warning(disable:4127)
#pragma warning(disable:4189)
#pragma warning(disable:4200)
#pragma warning(disable:4201)
#pragma warning(disable:4458)
#pragma warning(disable:4477)
#pragma warning(disable:4996)

#include <tchar.h>
#endif

#ifdef WIN32
#include <conio.h>
#include <winsock2.h>
#include <windows.h>
#endif

#include <locale.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <algorithm>

#include "CodeStd.h"
#include "MathStd.h"
#include "GlobalDef.h"
#include "CycleQueue.h"
#include "SplayTree.h"
#include "IJYBuffer.h"

#endif  //_STD_AFX_H_
