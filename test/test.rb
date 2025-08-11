require 'hidaping'

devices = HIDAPING.enumerate(0x0, 0x0)

for d in devices
    printf("0x%04x, 0x%04x, %s\n", d.vendor_id, d.product_id, d.product_string)
end

if devices.length > 0
    handle = devices[0].open()

    report_raw = handle.read_timeout(64, 500)
    p report_raw
end
