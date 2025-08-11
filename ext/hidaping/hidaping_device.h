#ifndef MY_HIDAPI_DEVICE_H
#define MY_HIDAPI_DEVICE_H

#include "common.h"

VALUE create_hidaping_handle(hid_device *handle);
void Init_hidaping_device(VALUE mHIDAPING);

#endif // MY_HIDAPI_DEVICE_H
