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

union __magnetic_rdg rdg;
union __magnetic_rdg dmp;

TMAG5273 sensor; // Initialize hall-effect sensor

// I2C default address
uint8_t i2cAddress = TMAG5273_I2C_ADDRESS_INITIAL;

void setup() {
    Wire.begin();
    Serial.begin(BAUDRATE);  
    sensor.setTemperatureEn(true);
    
    // TODO: yeah okay we _should_ verify this,
    // but I don't really care to be frank.
    sensor.begin(i2cAddress, Wire); // Assume it works.
    
    // TODO: check to see if these change anything significantly...
    sensor.setXYAxisRange(TMAG5273_RANGE_40MT);
    sensor.setZAxisRange(TMAG5273_RANGE_40MT);
    // sensor.setXYAxisRange(TMAG5273_RANGE_80MT);
    // sensor.setZAxisRange(TMAG5273_RANGE_80MT);
    sensor.setGlitchFilter(TMAG5273_GLITCH_ON);
    sensor.setLowPower(TMAG5273_LOW_NOISE_MODE);
    
    // Readings give average of 32 sensor polls
    sensor.setConvAvg(TMAG5273_X32_CONVERSION);
}

void loop() {
    if (Serial.available() >= 4) { 
        // Save ping to verify connection between device and host.
        Serial.readBytes(dmp.bytes, 4);
        
        // sensor.getMagneticChannel();
        // can be used to check status, but we don't care.
        
        rdg.f32[XDIM] = sensor.getXData();
        rdg.f32[YDIM] = sensor.getYData();
        rdg.f32[ZDIM] = sensor.getZData();
        // rdg.f32[TEMP] = 0.0;
        rdg.f32[TEMP] = sensor.getTemp();
        
        Serial.write(dmp.bytes, 4);
        Serial.write(rdg.bytes, 16);
    }

    return;
}
