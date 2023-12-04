#ifndef _TOOLS_H
#define _TOOLS_H

#include "common.h"

extern long getFileSize(FILE *fp);
//ÔÝÍ£³ÌÐò
extern void pause(const char *str, ...);
extern void getpwd(char *pwd, int pwdlen);

#endif

