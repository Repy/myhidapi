require 'hidaping'

devices = HIDAPING.enumerate(0x0, 0x0)

for d in devices
    printf("0x%04x, 0x%04x, %s\n", d.vendor_id, d.product_id, d.product_string)
end

handle = HIDAPING.open(0x057e, 0x2007)
handle.send_feature_report("\x01\x48\x00\x01\x40\x40\x00\x01\x40\x40\x00")

while true
    report_raw = handle.read_timeout(64, 500)
    data = report_raw.unpack("a17va*")
    p data[1]
end
