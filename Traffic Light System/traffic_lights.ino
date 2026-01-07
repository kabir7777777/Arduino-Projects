

void cycle1();
void cycle2();
void cycle3();
void cycle4();
void cycle5();
void cycle6();
void off();

unsigned long startMillis;
bool flashingGreen = false;

int redNS = 2;
int yellowNS = 3;
int greenNS = 4;

int redEW = 11;
int yellowEW = 12;
int greenEW = 13;

int interval1 = 3000;
int interval2 = 4000;
int interval3 = 5000;
int interval4 = 8000;
int interval5 = 9000;
int interval6 = 10000;

int cycleCount = 0;

bool maintenanceButton = false;
bool pedestrianButtonNSstate = false;
bool pedestrianButtonEWstate = false;

void setup() {
  Serial.begin(9600);
  startMillis = millis();

  pinMode(redNS, OUTPUT);
  pinMode(yellowNS, OUTPUT);
  pinMode(greenNS, OUTPUT);
  pinMode(redEW, OUTPUT);
  pinMode(yellowEW, OUTPUT);
  pinMode(greenEW, OUTPUT);
}

void loop() {
  unsigned long currentMillis = millis();

  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1023.0);
  voltage = round(voltage);

  if (voltage > 0) {
    if (voltage == 5 && (cycleCount == 4 || cycleCount == 5 || cycleCount == 6)) {
      pedestrianButtonEWstate = true;
    }
    if (voltage == 3 && (cycleCount == 1 || cycleCount == 2 || cycleCount == 3)) {
      pedestrianButtonNSstate = true;
    }
  }

  // Pedestrian timing logic
  if (pedestrianButtonNSstate && pedestrianButtonEWstate) {
    interval1 = 6000;
    interval2 = 7000;
    interval3 = 8000;
    interval4 = 14000;
    interval5 = 15000;
    interval6 = 16000;
  } 
  else if (pedestrianButtonEWstate) {
    interval1 = 6000;
    interval2 = 7000;
    interval3 = 8000;
    interval4 = 11000;
    interval5 = 12000;
    interval6 = 13000;
  } 
  else if (pedestrianButtonNSstate) {
    interval1 = 3000;
    interval2 = 4000;
    interval3 = 5000;
    interval4 = 11000;
    interval5 = 12000;
    interval6 = 13000;
  }

  // ✅ FIXED CONDITION
  if (!pedestrianButtonNSstate && !pedestrianButtonEWstate) {
    interval1 = 3000;
    interval2 = 4000;
    interval3 = 5000;
    interval4 = 8000;
    interval5 = 9000;
    interval6 = 10000;
  }

  // Maintenance button
  if (voltage == 2) {
    maintenanceButton = true;
  } else {
    maintenanceButton = false;
  }

  if (maintenanceButton) {
    off();
    if (!flashingGreen) {
      digitalWrite(greenEW, HIGH);
      delay(100);
      flashingGreen = true;
    } else {
      digitalWrite(redNS, HIGH);
      delay(100);
      flashingGreen = false;
    }
    off();
    return;
  }

  // Traffic light cycle
  if (currentMillis - startMillis <= interval1) {
    cycle1();
    cycleCount = 1;
  } 
  else if (currentMillis - startMillis <= interval2) {
    cycle2();
    cycleCount = 2;
  } 
  else if (currentMillis - startMillis <= interval3) {
    cycle3();
    cycleCount = 3;
    pedestrianButtonEWstate = false;
  } 
  else if (currentMillis - startMillis <= interval4) {
    cycle4();
    cycleCount = 4;
  } 
  else if (currentMillis - startMillis <= interval5) {
    cycle5();
    cycleCount = 5;
  } 
  else if (currentMillis - startMillis <= interval6) {
    cycle6();
    cycleCount = 6;
    pedestrianButtonNSstate = false;
  } 
  else {
    startMillis = currentMillis;
    cycleCount = 0;
  }
}

void cycle1() {
  off();
  digitalWrite(redNS, HIGH);
  digitalWrite(greenEW, HIGH);
}

void cycle2() {
  off();
  digitalWrite(yellowEW, HIGH);
  digitalWrite(redNS, HIGH);
}

void cycle3() {
  off();
  digitalWrite(redEW, HIGH);
  digitalWrite(redNS, HIGH);
}

void cycle4() {
  off();
  digitalWrite(greenNS, HIGH);
  digitalWrite(redEW, HIGH);
}

void cycle5() {
  off();
  digitalWrite(yellowNS, HIGH);
  digitalWrite(redEW, HIGH);
}

void cycle6() {
  off();
  digitalWrite(redNS, HIGH);
  digitalWrite(redEW, HIGH);
}

void off() {
  digitalWrite(redNS, LOW);
  digitalWrite(yellowNS, LOW);
  digitalWrite(greenNS, LOW);
  digitalWrite(redEW, LOW);
  digitalWrite(yellowEW, LOW);
  digitalWrite(greenEW, LOW);
}
