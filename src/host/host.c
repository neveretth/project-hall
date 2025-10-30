#include "host.h"

#include <stdlib.h>

#include <fcntl.h>
#include <stdio.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

// #define BAUDRATE B9600
// #define BAUDRATE B38400
#define BAUDRATE B115200
#define MODEMDEVICE "/dev/ttyACM0"
#define _POSIX_SOURCE 1 /* POSIX compliant source */
#define FALSE 0
#define TRUE 1

struct __device_arduino _device;

int hall_read(float* buf) {
    return EXIT_SUCCESS;
}

int arduino_init() {
    struct __device_arduino _device;

    _device.fd = open(MODEMDEVICE, O_RDWR | O_NOCTTY);
    if (_device.fd < 0) {
        perror(MODEMDEVICE);
        exit(1);
    }

    tcgetattr(_device.fd, &_device.oldtio); /* save current port settings */

    bzero(&_device.newtio, sizeof(_device.newtio));

    cfsetispeed(&_device.newtio, BAUDRATE);
    cfsetospeed(&_device.newtio, BAUDRATE);

    // Enable NON CANONICAL Mode for Serial Port Comm
    _device.newtio.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);
    // Turn OFF software based flow control (XON/XOFF).
    _device.newtio.c_iflag &= ~(IXON | IXOFF | IXANY);

    // Turn ON  the receiver of the serial port (CREAD)
    _device.newtio.c_cflag |= CREAD | CLOCAL;
    // Turn OFF Hardware based flow control RTS/CTS
    _device.newtio.c_cflag &= ~CRTSCTS;

    // Set 8N1 (8 bits, no parity, 1 stop bit)
    _device.newtio.c_cflag &= ~PARENB; // No parity
    _device.newtio.c_cflag &= ~CSTOPB; // One stop bit
    _device.newtio.c_cflag &= ~CSIZE;
    _device.newtio.c_cflag |= CS8; // 8 bits (this might do the prev as well)

    _device.newtio.c_oflag &= ~OPOST; /*No Output Processing*/

    _device.newtio.c_cc[VMIN] = 20;
    _device.newtio.c_cc[VTIME] = 0;

    tcsetattr(_device.fd, TCSANOW, &_device.newtio);
  
    tcflush(_device.fd, TCIFLUSH);
  
    // TODO: actual syncing should be done here...
    printf("ARDUINO connection established.");
    printf("Baudrate: %i\n", BAUDRATE);
  
    return EXIT_SUCCESS;
}

int arduino_finalize() {
    tcflush(_device.fd, TCIFLUSH);
    tcsetattr(_device.fd, TCSANOW, &_device.oldtio);
    return EXIT_SUCCESS;
}
