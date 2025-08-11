#ifndef MY_HIDAPI_DEVICE_H
#define MY_HIDAPI_DEVICE_H

#include "common.h"

VALUE create_myhidapi_handle(hid_device *handle);
void Init_myhidapi_device(VALUE mMyHIDAPI);

#endif // MY_HIDAPI_DEVICE_H
