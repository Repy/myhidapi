# MyHIDAPI

## DESCRIPTION

This is a small wrapper around HIDAPI.
I couldn't get other HIDAPI wrappers to work, so I wrote this one.
I'm using it to communicate with my keyboard, so it really only supports enough of the HIDAPI to do that.

## DESCRIPTION

* https://github.com/Repy/myhidapi

This gem is a fork from the original work by Aaron Patterson ([@tenderlove](https://github.com/tenderlove)).

* Original Repository: https://github.com/tenderlove/myhidapi

## SUPPORTS

This gem works on the following platforms, leveraging the capabilities of the underlying HIDAPI library.

*   **Platforms**:
    *   Windows
    *   macOS
    *   Linux

*   **Device Types**:
    *   USB
    *   Bluetooth

## FEATURES/PROBLEMS

* Incomplete
* No tests
* Seems to work (for me)

## SYNOPSIS

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

## REQUIREMENTS

This depends on **hidapi**.

## INSTALL

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

## LICENSE

The gem is available as open source under the terms of the [MIT License](LICENSE.md).
