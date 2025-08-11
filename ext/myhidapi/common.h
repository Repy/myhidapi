#ifndef MY_HIDAPI_COMMON_H
#define MY_HIDAPI_COMMON_H

#include "extconf.h"

#if defined(HAVE_HIDAPI_H)
#include <hidapi.h>
#elif defined(HAVE_HIDAPI_HIDAPI_H)
#include <hidapi/hidapi.h>
#else
#error "No suitable header found"
#endif

#include <ruby.h>
#include <stdlib.h>

#endif // MY_HIDAPI_COMMON_H
