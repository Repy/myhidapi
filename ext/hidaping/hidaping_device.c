#include "hidaping_device.h"
#include "hidaping.h"
#include "hidaping_util.h"

#define BUF_SIZE 4096

VALUE cHIDAPINGHandle;

static void dealloc(void *ptr) {
    hid_device *handle = (hid_device *)ptr;
    hid_close(handle);
}

static const rb_data_type_t hidaping_handle_type = {
    "HIDAPING/Handle",
    {
        0,
        dealloc,
        0,
    },
    0,
    0,
#ifdef RUBY_TYPED_FREE_IMMEDIATELY
    RUBY_TYPED_FREE_IMMEDIATELY,
#endif
};

VALUE create_hidaping_handle(hid_device *handle) {
    return TypedData_Wrap_Struct(cHIDAPINGHandle, &hidaping_handle_type, handle);
}

static VALUE rb_hid_write(VALUE self, VALUE str) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    int written = hid_write(handle, (unsigned char *)StringValuePtr(str), RSTRING_LEN(str));

    if (written >= 0) {
        return INT2NUM(written);
    } else {
        return Qfalse;
    }
}

static VALUE rb_hid_set_nonblocking(VALUE self, VALUE val) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    if (!hid_set_nonblocking(handle, NUM2INT(val))) {
        return Qtrue;
    } else {
        return Qnil;
    }
}

static VALUE rb_hid_read(VALUE self, VALUE size) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    unsigned char *buf = xcalloc(NUM2SIZET(size), sizeof(unsigned char));
    int read = hid_read(handle, buf, NUM2SIZET(size));

    VALUE ret;
    if (read > 0) {
        ret = rb_str_new((char *)buf, read);
    } else {
        ret = Qnil;
    }

    xfree(buf);
    return ret;
}

static VALUE rb_hid_read_timeout(VALUE self, VALUE size, VALUE timeout_ms) {
    hid_device *handle;
    unsigned char *buf;
    int read;
    VALUE ret;

    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    buf = xcalloc(NUM2SIZET(size), sizeof(unsigned char));

    read = hid_read_timeout(handle, buf, NUM2SIZET(size), NUM2INT(timeout_ms));

    if (read > 0) {
        ret = rb_str_new((char *)buf, read);
    } else {
        ret = Qnil;
    }
    xfree(buf);
    return ret;
}

static VALUE rb_hid_send_feature_report(VALUE self, VALUE str) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    int written =
        hid_send_feature_report(handle, (unsigned char *)StringValuePtr(str), RSTRING_LEN(str));

    if (written >= 0) {
        return INT2NUM(written);
    } else {
        return Qfalse;
    }
}

static VALUE rb_hid_get_feature_report(VALUE self, VALUE report_id, VALUE size) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    int buf_size = NUM2SIZET(size);
    unsigned char *buf = xcalloc(buf_size, sizeof(unsigned char));
    int read = hid_get_feature_report(handle, buf, buf_size);

    VALUE ret;
    if (read > 0) {
        ret = rb_str_new((char *)buf, read);
    } else {
        ret = Qnil;
    }

    xfree(buf);
    return ret;
}

static VALUE rb_manufacturer(VALUE self) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    wchar_t buffer[BUF_SIZE];
    hid_get_manufacturer_string(handle, buffer, BUF_SIZE);

    return hidaping_wcstombs(buffer);
}

static VALUE rb_product(VALUE self) {
    hid_device *handle;
    TypedData_Get_Struct(self, hid_device, &hidaping_handle_type, handle);

    wchar_t buffer[BUF_SIZE];
    hid_get_product_string(handle, buffer, BUF_SIZE);

    return hidaping_wcstombs(buffer);
}

void Init_hidaping_device(VALUE mHIDAPING) {
    cHIDAPINGHandle = rb_define_class_under(mHIDAPING, "Handle", rb_cObject);
    rb_undef_alloc_func(cHIDAPINGHandle);
    rb_define_method(cHIDAPINGHandle, "write", rb_hid_write, 1);
    rb_define_method(cHIDAPINGHandle, "read", rb_hid_read, 1);
    rb_define_method(cHIDAPINGHandle, "read_timeout", rb_hid_read_timeout, 2);
    rb_define_method(cHIDAPINGHandle, "set_nonblocking", rb_hid_set_nonblocking, 1);
    rb_define_method(cHIDAPINGHandle, "send_feature_report", rb_hid_send_feature_report, 1);
    rb_define_method(cHIDAPINGHandle, "get_feature_report", rb_hid_get_feature_report, 2);
    rb_define_method(cHIDAPINGHandle, "manufacturer", rb_manufacturer, 0);
    rb_define_method(cHIDAPINGHandle, "product", rb_product, 0);
}
