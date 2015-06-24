
#include "xe/tracetype.h"

#include <cstdio>

static const char *strs[] = 
{
    "XE_INFO",
    "XE_WARN",
    "XE_ERROR",
    "XE_FATAL",
    "XE_CIN",
    "XE_COUT",
};

static char unk[100];

const char *xe_trace_type_str(XeTraceType type)
{
    int i = (int)type;

    if (i < 0 || i > (int)XE_COUT)
    {
        sprintf(unk, "Unknown trace type %d", i);
        return unk;
    }

    return strs[i];
}

