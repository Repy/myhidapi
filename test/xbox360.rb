require 'myhidapi'

devices = MyHIDAPI.enumerate(0x0, 0x0)

for d in devices
    printf("0x%04x, 0x%04x, %s\n", d.vendor_id, d.product_id, d.product_string)
end

handle = MyHIDAPI.open(0x045e, 0x028e)

while true
    report_raw = handle.read_timeout(64, 500)
    data = report_raw.unpack("vvvvvSb*")
    p data
end
