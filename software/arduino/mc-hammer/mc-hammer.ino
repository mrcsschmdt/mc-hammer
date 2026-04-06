/*
  mc-hammer — pin map matches PLAN.md (draft). OLED: SSD1309 on hardware (I2C same wiring as typical SSD1306).
*/

#include <Wire.h>

// Position encoder (arm) — pins 2, 3
static const uint8_t PIN_ENC_POS_CLK = 2;
static const uint8_t PIN_ENC_POS_DT = 3;

// Force / interval knobs (KY-040)
static const uint8_t PIN_KNOB1_CLK = 4;
static const uint8_t PIN_KNOB1_DT = 5;
static const uint8_t PIN_KNOB1_SW = 6;
static const uint8_t PIN_KNOB2_CLK = 7;
static const uint8_t PIN_KNOB2_DT = 8;
static const uint8_t PIN_KNOB2_SW = 9;

static const uint8_t PIN_HIT = 10;
static const uint8_t PIN_ZERO = 11;
static const uint8_t PIN_PWR = 12;

// Stepper driver (STEP / DIR / EN on analog pins per PLAN)
static const uint8_t PIN_STEP = A0;
static const uint8_t PIN_DIR = A1;
static const uint8_t PIN_EN = A2;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);

  pinMode(PIN_ENC_POS_CLK, INPUT);
  pinMode(PIN_ENC_POS_DT, INPUT);

  pinMode(PIN_KNOB1_CLK, INPUT);
  pinMode(PIN_KNOB1_DT, INPUT);
  pinMode(PIN_KNOB1_SW, INPUT_PULLUP);
  pinMode(PIN_KNOB2_CLK, INPUT);
  pinMode(PIN_KNOB2_DT, INPUT);
  pinMode(PIN_KNOB2_SW, INPUT_PULLUP);

  pinMode(PIN_HIT, INPUT);
  pinMode(PIN_ZERO, INPUT_PULLUP);
  pinMode(PIN_PWR, INPUT);

  pinMode(PIN_STEP, OUTPUT);
  pinMode(PIN_DIR, OUTPUT);
  pinMode(PIN_EN, OUTPUT);
  digitalWrite(PIN_EN, HIGH);  // A4988: ENABLE active-low; start disabled

  Wire.begin();
}

void loop() {
  static uint32_t t = 0;
  if (millis() - t > 1000) {
    t = millis();
    Serial.print("HIT=");
    Serial.print(digitalRead(PIN_HIT));
    Serial.print(" ZERO=");
    Serial.print(digitalRead(PIN_ZERO));
    Serial.print(" PWR=");
    Serial.println(digitalRead(PIN_PWR));
  }

  digitalWrite(LED_BUILTIN, (millis() / 500) % 2);
}
