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
    char act;
    int rdlen;
    int ctx;
    union __magnetic_rdg rdg;
    // rdlen = write(_device.fd, &msg,
    //               4); // write order to make sure the write is always a little
    //                   // ahead.. (sort of a cheap hack of a "buffer")
    while (getchar() != 'q') {
        hall_read(rdg.f32);
        _ping = ctx;
        printf("ctx: host->%i device->%i\n", ctx, _ping);
        printf("data: %f, %f, %f, %f\n", rdg.f32[0], rdg.f32[1], rdg.f32[2],
               rdg.f32[3]);
        ctx++;
    }

    return arduino_finalize();
}
