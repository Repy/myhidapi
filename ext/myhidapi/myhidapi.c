#include "myhidapi.h"
#include "myhidapi_device.h"
#include "myhidapi_util.h"

VALUE mMyHIDAPI;

static VALUE enumerate(VALUE mod, VALUE vendor_id, VALUE product_id) {
    VALUE devices;
    struct hid_device_info *devs, *cur_dev;

    VALUE device_info_class = rb_path2class("MyHIDAPI::DeviceInfo");

    devices = rb_ary_new();
    devs = hid_enumerate(NUM2USHORT(vendor_id), NUM2USHORT(product_id));
    cur_dev = devs;
    while (cur_dev) {
        VALUE args[] = {INT2NUM(cur_dev->vendor_id),
                        INT2NUM(cur_dev->product_id),
                        rb_str_new2(cur_dev->path),
                        myhidapi_wcstombs(cur_dev->serial_number),
                        myhidapi_wcstombs(cur_dev->manufacturer_string),
                        myhidapi_wcstombs(cur_dev->product_string),
                        INT2NUM(cur_dev->usage),
                        INT2NUM(cur_dev->interface_number)};
        rb_ary_push(devices, rb_class_new_instance(8, args, device_info_class));
        cur_dev = cur_dev->next;
    }
    hid_free_enumeration(devs);

    return devices;
}

static VALUE rb_hid_open(VALUE mod, VALUE vid, VALUE pid) {
    hid_device *handle = hid_open(NUM2USHORT(vid), NUM2USHORT(pid), NULL);
    if (handle) {
        return create_myhidapi_handle(handle);
    } else {
        return Qfalse;
    }
}

static VALUE rb_hid_open_path(VALUE mod, VALUE path) {
    hid_device *handle = hid_open_path(StringValueCStr(path));
    if (handle) {
        return create_myhidapi_handle(handle);
    } else {
        return Qfalse;
    }
}

extern void Init_myhidapi(void) {
    mMyHIDAPI = rb_define_module("MyHIDAPI");
    rb_define_singleton_method(mMyHIDAPI, "enumerate", enumerate, 2);
    rb_define_singleton_method(mMyHIDAPI, "open", rb_hid_open, 2);
    rb_define_singleton_method(mMyHIDAPI, "open_path", rb_hid_open_path, 1);
    Init_myhidapi_device(mMyHIDAPI);
}
