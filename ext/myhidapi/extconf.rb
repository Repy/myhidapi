# frozen_string_literal: true

require "mkmf"

dir_config("hidapi")
pkg_config('hidapi')

if have_library('hidapi')
    libname = 'hidapi'
elsif have_library('hidapi-hidraw')
    libname = 'hidapi-hidraw'
elsif have_library('hidapi-libusb')
    libname = 'hidapi-libusb'
else
  abort 'you must have "libhidapi".'
end

if have_header('hidapi/hidapi.h')
    header = 'hidapi/hidapi.h'
elsif have_header('hidapi.h')
    header = 'hidapi.h'
else
  abort 'you must have "hidapi.h".'
end

create_header
create_makefile("myhidapi/myhidapi")
