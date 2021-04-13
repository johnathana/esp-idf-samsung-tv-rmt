# ESP-IDF Samsung TV Infrared

Component for Espressif [ESP-IDF](https://github.com/espressif/esp-idf) development framework.


## How to use

### ESP32

Clone this repository:

```Shell
cd ~/idf-libs
git clone git@github.com:johnathana/esp-idf-samsung-tv-rmt.git
```

Add path to components in your project CMakeLists.txt:

```CMake
list(APPEND EXTRA_COMPONENT_DIRS "~/idf-libs/esp-idf-samsung-tv-rmt")
```

Example code:

```C
#include "ir_samsung_tv.h"

ir_samsung_t ir_samsung_config = {
    .channel = RMT_CHANNEL_0,
    .gpio    = GPIO_NUM_12
};

// setup once
ir_samsung_tv_init();
// send volume up
ir_samsung_tv_send(TV_SAMSUNG_VOL_UP);
```

## Credits

- [haxplore](https://github.com/haxplore), developer of the https://github.com/haxplore/ESP32_RMT_IRLib