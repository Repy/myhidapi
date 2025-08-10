# frozen_string_literal: true

require "mkmf"

append_cflags("-fvisibility=hidden")

pkg_config 'hidapi'
dir_config("hidapi")

create_makefile("myhidapi/myhidapi")
