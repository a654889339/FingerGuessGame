#ifndef _ECS_DEF_H_
#define _ECS_DEF_H_

#include "JYVector.h"
#include <stdint.h>

typedef int32_t int_eid;

#define ERROR_EID -1
#define REGISTER_SYSTEM_COMPONENT(Sys, CList) Sys.SetComponentList(&CList)

#endif