// PIR Motion Sensor Automatic Light
// Components: Arduino UNO, PIR sensor, Relay

const int PIR_PIN = 2;
const int RELAY_PIN = 8;

// Assumes an active-LOW relay module
const int RELAY_ON = LOW;
const int RELAY_OFF = HIGH;

unsigned long lastMotionTime = 0;
const unsigned long lightDelay = 10000; // 10 seconds

bool lightIsOn = false;

void setup() {
  Serial.begin(9600);

  pinMode(PIR_PIN, INPUT);
  pinMode(RELAY_PIN, OUTPUT);

  digitalWrite(RELAY_PIN, RELAY_OFF);

  Serial.println("PIR Automatic Light System Started");
}

void loop() {
  int pirState = digitalRead(PIR_PIN);

  if (pirState == HIGH) {
    lastMotionTime = millis();

    if (!lightIsOn) {
      Serial.println("Motion detected: Light ON");
      lightIsOn = true;
    }

    digitalWrite(RELAY_PIN, RELAY_ON);
  }

  if (lightIsOn &&
      millis() - lastMotionTime >= lightDelay) {

    digitalWrite(RELAY_PIN, RELAY_OFF);
    lightIsOn = false;

    Serial.println("No motion: Light OFF");
  }

  delay(100);
}