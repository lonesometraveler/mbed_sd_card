#include "SD.h"

SD::SD(PinName mosi, PinName miso, PinName clk, PinName cs): 
    bd(mosi, miso, clk, cs),
    fs(MOUNT_PATH) {}

void SD::listDirectory() {
    DIR* dir = opendir(MOUNT_PATH);
    struct dirent* dent;
    while ((dent = readdir(dir)) != NULL) {
        printf("%s\r\n", dent->d_name);
    }
    closedir(dir);
}

int SD::format(void) {
    return FATFileSystem::format(&bd);
}

int SD::mount() { 
    return fs.mount(&bd);
}

int SD::write(const char* filePath, uint8_t* data, size_t size, int length) {
    FILE* f = fopen(filePath, SD_WRITE);
    if (f == NULL) { return -1; }

    int result = fwrite(data, size, length, f);
    fclose(f);
    return result;
}

int SD::append(const char* filePath, uint8_t* data, size_t size, int length) {
    FILE* f = fopen(filePath, SD_APPEND);
    if (f == NULL) { return -1; }

    int result = fwrite(data, size, length, f);
    fclose(f);
    return result;
}

int SD::read(const char* filePath, int offset, void* buff, size_t size, int length) {
    FILE* f = fopen(filePath, SD_READ);
    if (f == NULL) { return -1; }

    fseek(f, offset, SEEK_SET);
    int result = fread(buff, size, length, f);
    fclose(f);
    return result;
}
