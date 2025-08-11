# frozen_string_literal: true

require_relative "hidaping/hidaping.so"

module HIDAPING

  class DeviceInfo
    attr_reader :vendor_id, :product_id, :path, :serial_number, :manufacturer_string, :product_string, :usage, :interface_number

    def initialize vendor_id, product_id, path, serial_number, manufacturer_string, product_string, usage, interface_number
      @vendor_id           = vendor_id
      @product_id          = product_id
      @path                = path
      @serial_number       = serial_number
      @manufacturer_string = manufacturer_string
      @product_string      = product_string
      @usage               = usage
      @interface_number    = interface_number
    end

    def open
      HIDAPING.open vendor_id, product_id
    end
  end

end
