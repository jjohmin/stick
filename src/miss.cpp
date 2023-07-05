#include "miss.h"

#include <MPU9250.h>
#include <math.h>
#include "vec.h"
#include "pins.h"

#define GYRO_OFFSET_X 42
#define GYRO_OFFSET_Y 45
#define GYRO_OFFSET_Z 28

#define ACCEL_OFFSET_X 5583
#define ACCEL_OFFSET_Y 3458
#define ACCEL_OFFSET_Z 10169

using Accel = Vec<float>;

static constexpr const uint8_t GYRO_FS_SEL = MPU9250_GYRO_FS_2000;
static constexpr const float GYRO_LSB_DPS = float(1 << 15) / (250 << GYRO_FS_SEL); /* LSB/dps */
static constexpr const uint8_t ACCEL_FS_SEL = MPU9250_ACCEL_FS_16;
static constexpr const float ACCEL_LSB_G = float(1 << 15) / (2 << ACCEL_FS_SEL); /* LSB/g */
static constexpr const float MISS_THRESHOLD = 1600; // dg/dt
static constexpr const unsigned long BUZZER_TOGGLE_INTERVAL = 500;

static MPU9250 mpu;
static bool is_missed;
static bool is_first = true;

static constexpr inline
float accel_raw2g(int16_t a) { return a / ACCEL_LSB_G; }

static
void mpu_setup() {
    Wire.begin();
    Wire.setClock(400000);

    if (!mpu.testConnection()) {
        Serial.println("mpu testConnection failed!");
    }

    mpu.reset();
    mpu.initialize();

    /* GYRO INIT */ {
        mpu.setFullScaleGyroRange(GYRO_FS_SEL);
        mpu.setXGyroOffsetUser(GYRO_OFFSET_X);
        mpu.setYGyroOffsetUser(GYRO_OFFSET_Y);
        mpu.setZGyroOffsetUser(GYRO_OFFSET_Z);
    }

    /* ACCEL INIT */ {
        mpu.setFullScaleAccelRange(ACCEL_FS_SEL);
        mpu.setXAccelOffset(ACCEL_OFFSET_X);
        mpu.setYAccelOffset(ACCEL_OFFSET_Y);
        mpu.setZAccelOffset(ACCEL_OFFSET_Z);
    }

    /* DLPF*/ {
        mpu.setAccelDLPFMode(6);
    }
}

void miss_begin() {
    mpu_setup();
    pinMode(PIN_BUTTON, INPUT_PULLUP);
    pinMode(LED_BUILTIN, OUTPUT);
}

    // Serial.print(ax); Serial.print(' ');
    // Serial.print(ay); Serial.print(' ');
    // Serial.print(az); Serial.print(' ');
    // Serial.println();
    // delay(100);

static
Accel make_accel_vector(int16_t ax, int16_t ay, int16_t az) {
    return {
        accel_raw2g(ax),  
        accel_raw2g(ay),
        accel_raw2g(az),
    };
}

static inline
bool button_is_pressed() {
    return !digitalRead(PIN_BUTTON);
}

static
void imu_polling() {
    static Accel prev_vec;
    static unsigned long prev_us;

    int16_t _ax, _ay, _az;
    mpu.getAcceleration(&_ax, &_ay, &_az);
    auto curr_us = micros();
    auto curr_vec = make_accel_vector(_ax, _ay, _az);

    if (is_first) {
        is_first = false;
        prev_vec = curr_vec;
        prev_us = curr_us;
        return;
    }

    auto diff_vec = curr_vec - prev_vec;
    auto diff_us = curr_us - prev_us;

    auto delta = diff_vec.get_size() * 1e6f / diff_us;
    Serial.println(delta);

    if (delta >= MISS_THRESHOLD) {
        is_missed = true;
    }

    prev_us = curr_us;
    prev_vec = curr_vec;
}

static
void when_missed() {
    static unsigned long miss_prev_ms;
    static bool toggle_first = true;
    if (button_is_pressed()) {
        noTone(PIN_BUZZER);
        miss_reset();
        toggle_first = true;
        return;
    }

    if (toggle_first) {
        toggle_first = false;
        miss_prev_ms = millis() - BUZZER_TOGGLE_INTERVAL * 2;
    }

    auto curr_us = millis();
    if (curr_us - miss_prev_ms < BUZZER_TOGGLE_INTERVAL * 2) return;
    miss_prev_ms = curr_us;
    tone(PIN_BUZZER, 400, BUZZER_TOGGLE_INTERVAL);
}

void miss_loop() {
    if (!is_missed) imu_polling();
    if (is_missed) when_missed();
}

bool miss_is_cane() {
    return is_missed;
}

void miss_reset() {
    is_first = true;
    is_missed = false;
}