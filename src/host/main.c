#include "host.h"

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// TODO: good lord there's a lot I need to learn about error handling on device
// stuff like this... because this is all terrible...

int main() {

    int err = arduino_init();

    if (err == EXIT_FAILURE) {
        printf("Error initializing arduino!");
        return EXIT_FAILURE;
    }

    printf("Exit with char q.\n");
    int ctx = 0;
    char act;
    int rdlen;
    int ctx_dev;
    union __magnetic_rdg rdg;
    int msg = 0xbeef; // Junk to send
    rdlen = write(_device.fd, &msg,
                  4); // write order to make sure the write is always a little
                      // ahead.. (sort of a cheap hack of a "buffer")
    while (getchar() != 'q') {
        rdlen = read(_device.fd, &ctx_dev, 4);
        rdlen = read(_device.fd, &rdg, 16);
        printf("ctx: host->%i device->%i\n", ctx, ctx_dev);
        printf("data: %f, %f, %f, %f\n", rdg.f32[0], rdg.f32[1], rdg.f32[2],
               rdg.f32[3]);
        ctx++;
        rdlen = write(_device.fd, &msg, 4);
    }

    return arduino_finalize();
}
