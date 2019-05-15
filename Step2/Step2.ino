
// only runs once on boot
void setup() {
  // Initializing serial port for debugging purposes
  Serial.begin(115200);
  delay(10);

  Serial.println("Hello World!");
}

// runs over and over again
void loop() {
  Serial.println("Byl jsem zde. Fantomas.");
}
