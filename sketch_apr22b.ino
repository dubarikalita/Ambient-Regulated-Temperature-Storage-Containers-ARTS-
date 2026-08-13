#include <LiquidCrystal.h>
#include <math.h>

// ---------- PIN DEFINITIONS ----------

#define NTC_PIN A0

#define UP_BUTTON 2
#define DOWN_BUTTON 3
#define SET_BUTTON 4

#define BUZZER_PIN 5
#define FAN_PIN 6

// LCD: RS, E, D4, D5, D6, D7
LiquidCrystal lcd(12, 11, 10, 9, 8, 7);

// ---------- TEMPERATURE SETTINGS ----------

float targetTemp = 35.0;

const float MIN_TARGET = 20.0;
const float MAX_TARGET = 40.0;
const float CRITICAL_TEMP = 40.0;

// NTC parameters
const float BETA = 3950.0;
const float R0 = 10000.0;
const float T0 = 298.15;

// ---------- SETUP ----------

void setup() {

  lcd.begin(16, 2);

  pinMode(UP_BUTTON, INPUT_PULLUP);
  pinMode(DOWN_BUTTON, INPUT_PULLUP);
  pinMode(SET_BUTTON, INPUT_PULLUP);

  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(FAN_PIN, OUTPUT);

  analogWrite(FAN_PIN, 0);
  noTone(BUZZER_PIN);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Automatic Temp");
  lcd.setCursor(0, 1);
  lcd.print("Control System");

  delay(2000);

  lcd.clear();
}

// ---------- READ NTC TEMPERATURE ----------

float readTemperature() {

  int adcValue = analogRead(NTC_PIN);

  if (adcValue <= 0 || adcValue >= 1023) {
    return 0;
  }

  // Calculate thermistor resistance
  float resistance =
      R0 * (1023.0 / adcValue - 1.0);

  // Beta equation
  float temperature =
      1.0 /
      (1.0 / T0 +
       log(resistance / R0) / BETA);

  // Kelvin to Celsius
  temperature -= 273.15;

  return temperature;
}

// ---------- CALCULATE FAN SPEED ----------

int calculateFanSpeed(float temperature) {

  int speed;

  if (temperature <= targetTemp - 5) {

    speed = 0;

  }
  else if (temperature <= targetTemp) {

    speed = map(
      temperature * 10,
      (targetTemp - 5) * 10,
      targetTemp * 10,
      0,
      50
    );

  }
  else if (temperature <= targetTemp + 5) {

    speed = map(
      temperature * 10,
      targetTemp * 10,
      (targetTemp + 5) * 10,
      50,
      100
    );

  }
  else {

    speed = 100;

  }

  return constrain(speed, 0, 100);
}

// ---------- BUTTON CONTROL ----------

void handleButtons() {

  // UP
  if (digitalRead(UP_BUTTON) == LOW) {

    targetTemp++;

    if (targetTemp > MAX_TARGET) {
      targetTemp = MAX_TARGET;
    }

    delay(200);
  }

  // DOWN
  if (digitalRead(DOWN_BUTTON) == LOW) {

    targetTemp--;

    if (targetTemp < MIN_TARGET) {
      targetTemp = MIN_TARGET;
    }

    delay(200);
  }

  // SET
  if (digitalRead(SET_BUTTON) == LOW) {

    lcd.clear();

    lcd.setCursor(0, 0);
    lcd.print("Target Temp:");

    lcd.setCursor(0, 1);
    lcd.print(targetTemp, 1);
    lcd.print((char)223);
    lcd.print("C");

    delay(1000);

    lcd.clear();
  }
}

// ---------- MAIN LOOP ----------

void loop() {

  handleButtons();

  float temperature = readTemperature();

  int fanSpeed = calculateFanSpeed(temperature);

  // Convert 0-100% to Arduino PWM 0-255
  int pwmValue = map(fanSpeed, 0, 100, 0, 255);

  analogWrite(FAN_PIN, pwmValue);

  // ---------- BUZZER ----------

  if (temperature >= CRITICAL_TEMP) {

    tone(BUZZER_PIN, 1000);

  } else {

    noTone(BUZZER_PIN);
  }

  // ---------- LCD ----------

  lcd.setCursor(0, 0);
  lcd.print("Temp: ");
  lcd.print(temperature, 1);
  lcd.print((char)223);
  lcd.print("C   ");

  lcd.setCursor(0, 1);
  lcd.print("Fan Speed: ");
  lcd.print(fanSpeed);
  lcd.print("%   ");

  delay(300);
}
