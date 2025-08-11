#ifndef MY_HIDAPI_UTIL_H
#define MY_HIDAPI_UTIL_H

#include "common.h"

#define BUF_SIZE 4096

static VALUE hidaping_wcstombs(wchar_t *str) {
    char buf[BUF_SIZE];
    int len;
    len = wcstombs(buf, str, BUF_SIZE);
    if (len > 0) {
        return rb_str_new(buf, len);
    } else {
        return Qnil;
    }
}

#endif // MY_HIDAPI_UTIL_H
