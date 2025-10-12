union data {
    int i32;
    char bytes[4];
};

union data ctx = {.i32 = 0};
// TODO: Local memory is cursed?
// When I try to have a write based on local memory, it sends junk?
union data buf = {.i32 = 0};

union data wrt[2];

// Init function (I would assume) (Run once at init.)
void setup() {
    Serial.begin(9600);
    // digitalWrite(LED_BUILTIN, HIGH);
    return;
}

void loop() {
    // delay(1000);

    if (Serial.available() >= 4) {
        Serial.readBytes(buf.bytes, 4); // collect them
        
        Serial.write(ctx.bytes, 4);
        Serial.write(buf.bytes, 4);
        ctx.i32++;
    }
    return;
}
