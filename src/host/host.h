#ifndef __HALL_HOST_H
#define __HALL_HOST_H

#include <termios.h>

union __magnetic_rdg {
    float f32[4];
    char bytes[sizeof(float) * 4]; // TODO: is this bad form?
};

struct __device_arduino {
    int fd;
    struct termios oldtio;
    struct termios newtio;
};

extern struct __device_arduino _device;
extern int _ping;

// Reading with no math operations performed, raw data...
// This should be the building block of most of the stuff.
int hall_read(float* buf);

int arduino_init();
int arduino_finalize();

#endif
