# MyHIDAPI

* https://github.com/Repy/myhidapi

## DESCRIPTION:

This is a small wrapper around HIDAPI.
I couldn't get other HIDAPI wrappers to work, so I wrote this one.
I'm using it to communicate with my keyboard, so it really only supports enough of the HIDAPI to do that.

This gem is a fork from the original work by Aaron Patterson ([@tenderlove](https://github.com/tenderlove)).

* **Original Repository:** https://github.com/tenderlove/myhidapi

## SUPPORTS

This gem works on the following platforms, leveraging the capabilities of the underlying HIDAPI library.

*   **Platforms**:
    *   Windows
    *   macOS
    *   Linux

*   **Device Types**:
    *   USB
    *   Bluetooth

## FEATURES/PROBLEMS:

* Incomplete
* No tests
* Seems to work (for me)

## SYNOPSIS:

```ruby
require 'myhidapi'

devices = MyHIDAPI.enumerate(0x0, 0x0)

for d in devices
    printf("0x%04x, 0x%04x, %s\n", d.vendor_id, d.product_id, d.product_string)
end

handle = MyHIDAPI.open(0x045e, 0x028e)

while true
    report_raw = handle.read_timeout(64, 500)
    data = report_raw.unpack("vvvvvb*")
    p data
end
```

## REQUIREMENTS:

This depends on **hidapi**.

## INSTALL:

First, install the **hidapi** library. Here are instructions for common platforms:

*   **Windows (using RubyInstaller with Devkit)**

    ```sh
    ridk exec pacman -S mingw-w64-ucrt-x86_64-hidapi
    ```

*   **macOS (using Homebrew)**

    ```sh
    brew install hidapi
    ```

*   **Ubuntu / Debian**

    ```sh
    sudo apt update
    sudo apt install libhidapi-dev
    ```

Once `hidapi` is installed, you can install this gem:

```sh
gem install myhidapi
```

## LICENSE:

(The MIT License)

Copyright (c) 2019 Aaron Patterson
Copyright (c) 2024 Repy

Permission is hereby granted, free of charge, to any person obtaining
a copy of this software and associated documentation files (the
'Software'), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be
included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
