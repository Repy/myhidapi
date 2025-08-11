require 'myhidapi'

devices = MyHIDAPI.enumerate(0x0, 0x0)

for d in devices
    puts d.product_string , d.vendor_id, d.product_id
end

# dev = devices.find { |dev| dev.product_string == "Realforce 108U" }

handle = MyHIDAPI.open(1118, 654)

p handle

handle.set_nonblocking(1)

while true
    buf = handle.read_timeout(100, 500)
    p buf
end
