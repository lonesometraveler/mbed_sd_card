#ifndef _SD_H__
#define _SD_H__

#include "mbed.h"
#include "FATFileSystem.h"
#include "SDBlockDevice.h"

#define MOUNT_PATH    "fs"
#define SD_READ       "r"
#define SD_WRITE      "w"
#define SD_APPEND     "a"
#define SD_READ_WRITE "r+"

class SD {

public:
	/**
     * @brief constructor.
     *
     * @param PinNames for SPI pins
     */
	SD(PinName mosi, PinName miso, PinName clk, PinName cs);

     /**
     * @brief prints out file names in the default directory.
     */
     void listDirectory(void);

	/**
     * @brief formats SD card.
     *
     * @return error | 0 = success, negative numbers for failure
     */
	int format(void);

	/**
     * @brief mount file system.
     *
     * @return error | 0 = success, negative numbers for failure
     */
	int mount(void);

	/**
     * @brief write data to a new file (if already exists, erase the old content).
     *
     * @param file path
     * @param data to write
     * @parm size of element in data
     * @param length of data
     *
     * @return size or -1 for error
     */
     int write(const char* filePath, uint8_t* data, size_t size, int length);

     /**
     * @brief append data to an existing file.
     *
     * @param file path
     * @param data to write
     * @parm size of element in data
     * @param length of data
     *
     * @return size or -1 for error
     */
     int append(const char* filePath, uint8_t* data, size_t size, int length);

	/**
     * @brief read a file from a specified address.
     *
     * @param file path
     * @parm offset for fseek
     * @parm data buffer
     * @parm size of data buffer's element
     * @parm number of element to read
     *
     * @return size or -1 for error
     */
     int read(const char* filePath, int offset, void* buff, size_t size, int length);

private:
     FATFileSystem fs;
	SDBlockDevice bd;
};

#endif
