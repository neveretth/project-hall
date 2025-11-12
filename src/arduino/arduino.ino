#include <Wire.h>
#include "SparkFun_TMAG5273_Arduino_Library.h"

// #define BAUDRATE 9600
// #define BAUDRATE 38400
#define BAUDRATE 115200

enum {
    XDIM = 0,
    YDIM = 1,
    ZDIM = 2,
    TEMP = 3,
};

// sizeof is cursed too???
union __magnetic_rdg {
    float f32[4];
    char bytes[16];
};

union __data {
    int i32;
    char bytes[4];
};

union __data ctx = {.i32 = 0};

union __magnetic_rdg rdg;
union __magnetic_rdg dmp;

TMAG5273 sensor; // Initialize hall-effect sensor

// I2C default address
uint8_t i2cAddress = TMAG5273_I2C_ADDRESS_INITIAL;

void setup() {
    Wire.begin();
    Serial.begin(BAUDRATE);  
    sensor.setTemperatureEn(true);
    sensor.setConvAvg(TMAG5273_X32_CONVERSION);
    sensor.begin(i2cAddress, Wire); // Assume it works.
}

void loop() {
    // Checks if mag channels are on - turns on in setup
    if (Serial.available() >= 4) { 
        Serial.readBytes(dmp.bytes, 4); // Read and dump init sig
        // if(sensor.getMagneticChannel() != 0) {

            // Dump because why the fuck not.
            
            // sensor.getXData();
            rdg.f32[XDIM] = sensor.getXData();
            // sensor.getYData();
            rdg.f32[YDIM] = sensor.getYData();
            // sensor.getZData();
            rdg.f32[ZDIM] = sensor.getZData();
            // sensor.getTemp();
            rdg.f32[TEMP] = sensor.getTemp();
            
            Serial.write(dmp.bytes, 4);
            Serial.write(rdg.bytes, 16);
        // }
        // else {
        //     // Send back whatever was sent to the device.
        //     // Serial.write(dmp.bytes, 4);
        //     // Serial.write(dmp.bytes, 16);
        // }
        ctx.i32++;
    }

    return;
}
