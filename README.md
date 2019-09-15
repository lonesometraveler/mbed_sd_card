# SD card device

SD card library for mbed projects.

### Prerequisites

- mbed OS 5


### Installation

Add this library to a mbed project.

```
mbed add https://github.com/lonesometraveler/mbed_sd_card.git
```

### mbed app json

Enable the storage feature and SD component in mbed_app.json. Here is an example for ```LPC1768```. For more info on ```Storage```, see [the mbed official documentation](https://os.mbed.com/docs/mbed-os/v5.13/reference/storage.html).

```
"target_overrides": {
    "LPC1768": {
         "target.features_add": ["STORAGE"],
         "target.components_add": ["SD"],
    }
}
```


## Usage

### Initialization

Pass SPI pins to the constructor.

```c++
SD sd(MOSI, MISO, CLK, CS);
```

### Mount

Call ```mount```. This returns ```0``` for success and a negative number for failure. 

```c++
int result = sd.mount();
```

### Write

```write``` writes data to a new file. If already exists, it erases the old content. This function returns size of written data or a negative number in case of failure.

```c++
int result = sd.write(FILE_PATH, buffer, sizeof buffer[0], length);
```

### Append

```append``` appends data to an existing file. This function returns size of written data or a negative number in case of failure.

```c++
int result = sd.append(FILE_PATH, buffer, sizeof buffer[0], length);
```

### Read

```read``` reads data from a specified address. This function returns size of read data or a negative number in case of failure.

```c++
int result = sd.read(FILE_PATH, address, buffer, sizeof buffer[0], length);
```

## Example

```c++
#include "mbed.h"
#include "SD.h"

SD sd(MBED_CONF_SD_SPI_MOSI, MBED_CONF_SD_SPI_MISO, MBED_CONF_SD_SPI_CLK, MBED_CONF_SD_SPI_CS);
const char* FILE_PATH = "/fs/text.txt";

int main() {

    sd.mount();

    char* text1 = "The world is in my head. ";
    char* text2 = "My body is in the world.";
    char buffer[64];

    int size = sd.write(FILE_PATH, text1, sizeof(char), strlen(text1));
    size > 0 
    	? printf("wrote %d chars\r\n", size)
    	: printf("error\r\n");

    size = sd.read(FILE_PATH, 0, buffer, sizeof(char), 64);
    size > 0
    	? printf("read: %s\r\n", buffer)
    	: printf("error\r\n");

    size = sd.append(FILE_PATH, text2, sizeof(char), strlen(text2));
    size > 0 
    	? printf("appended %d chars\r\n", size)
    	: printf("error\r\n");

    size = sd.read(FILE_PATH, 0, buffer, sizeof(char), 64);
    size > 0
    	? printf("read: %s\r\n", buffer)
    	: printf("error\r\n");
}
```
