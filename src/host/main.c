#include <stdlib.h>

#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

// #define BAUDRATE B9600
// #define BAUDRATE B38400 // Man what the fuck
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

volatile int STOP = FALSE;

union __magnetic_rdg {
    float f32[4];
    char bytes[sizeof(float) * 4]; // TODO: is this bad form?
};

int main() {
    int fd, c;
    struct termios oldtio, newtio;

    fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror(MODEMDEVICE);
        exit(1);
    }

    tcgetattr(fd, &oldtio); /* save current port settings */

    bzero(&newtio, sizeof(newtio));

    cfsetispeed(&newtio, BAUDRATE);
    cfsetospeed(&newtio, BAUDRATE);

    // Enable NON CANONICAL Mode for Serial Port Comm
    newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // Turn OFF software based flow control (XON/XOFF).
    newtio.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Turn ON  the receiver of the serial port (CREAD)
    newtio.c_cflag |= CREAD | CLOCAL;
    // Turn OFF Hardware based flow control RTS/CTS
    newtio.c_cflag &= ~CRTSCTS;

    // Set 8N1 (8 bits, no parity, 1 stop bit)
    newtio.c_cflag &= ~PARENB; // No parity
    newtio.c_cflag &= ~CSTOPB; // One stop bit
    newtio.c_cflag &= ~CSIZE;
    newtio.c_cflag |= CS8; // 8 bits (this might do the prev as well)

    newtio.c_oflag &= ~OPOST; /*No Output Processing*/

    newtio.c_cc[VMIN] = 20;
    newtio.c_cc[VTIME] = 0;

    tcsetattr(fd, TCSANOW, &newtio);

    printf("baudrate: %i\n", BAUDRATE);
    printf("Exit with char q.\n");
    int ctx = 0;
    char act;
    int rdlen;
    int ctx_dev;
    union __magnetic_rdg rdg;

    // Right now this relies on some good timing... but it definitely can be
    // made better (look for a sequence, reset when found...)

    tcflush(fd, TCIFLUSH);

    
    int msg = 0xbeef; // Junk to send
    rdlen = write(fd, &msg,
                  4); // write order to make sure the write is always a little
                      // ahead.. (sort of a cheap hack of a "buffer")
    
    // VMIN is important to get her in the mood.
    while (getchar() != 'q') {
        rdlen = read(fd, &ctx_dev, 4);
        rdlen = read(fd, &rdg, 16);
        printf("ctx: host->%i device->%i\n", ctx, ctx_dev);
        printf("data: %f, %f, %f, %f\n", rdg.f32[0], rdg.f32[1], rdg.f32[2],
               rdg.f32[3]);
        ctx++;
        rdlen = write(fd, &msg, 4);
    }
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &oldtio);
    return EXIT_SUCCESS;
}
