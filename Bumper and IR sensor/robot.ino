int switchState;
int buttonStateL;
int buttonStateR;

int fwdSpeed = 12000;
int revSpeed = 6000;

int outputLeft;
int outputRight;

int leftButton = 3;
int rightButton = 2;

int fwdPinL = 5;
int revPinL = 6;

int fwdPinR = 11;
int revPinR = 10;

int sensorL;
int sensorR;
int sensorPinL = 8;
int sensorPinR = 9;

int switchButton = 7;
bool switchBool = true;

int reverse(int time) {
  analogWrite(fwdPinL, 0);
  analogWrite(fwdPinR, 0);

  analogWrite(revPinL, revSpeed);
  analogWrite(revPinR, revSpeed);

  delay(time);

  analogWrite(revPinL, 0);
  analogWrite(revPinR, 0);
}

int off() {
  analogWrite(revPinL, 0);
  analogWrite(revPinR, 0);
  analogWrite(fwdPinL, 0);
  analogWrite(fwdPinR, 0);
}

void setup() {
  Serial.begin(9600);

  pinMode(sensorPinL, INPUT);
  pinMode(sensorPinR, INPUT);
  pinMode(leftButton, INPUT);
  pinMode(rightButton, INPUT);
  pinMode(switchButton, INPUT);

  pinMode(fwdPinL, OUTPUT);
  pinMode(revPinL, OUTPUT);
  pinMode(fwdPinR, OUTPUT);
  pinMode(revPinR, OUTPUT);

  analogWrite(revPinL, 0);
  analogWrite(revPinR, 0);
  analogWrite(fwdPinL, fwdSpeed);
  analogWrite(fwdPinR, fwdSpeed);
}

void loop() {
  buttonStateL = digitalRead(leftButton);
  buttonStateR = digitalRead(rightButton);
  switchState = digitalRead(switchButton);
  sensorL = digitalRead(sensorPinL);
  sensorR = digitalRead(sensorPinR);

  if (switchState == HIGH) {
    switchBool = !switchBool;
    delay(200); // debounce
  }

  if (switchBool) {
    if (buttonStateL == HIGH) {
      turnLeft();
    } else if (buttonStateR == HIGH) {
      turnRight();
    } else {
      goForward();
    }
    delay(50);
  } else {
    if (sensorL == 1 && sensorR == 1) {
      off();
      analogWrite(fwdPinL, fwdSpeed);
      analogWrite(revPinR, fwdSpeed);
      delay(1400);

      off();
      analogWrite(revPinL, revSpeed);
      analogWrite(revPinR, revSpeed);
      delay(600);

      off();
    } 
    else if (sensorL == 1) {
      analogWrite(fwdPinR, fwdSpeed);
      analogWrite(fwdPinL, 0);
    } 
    else if (sensorR == 1) {
      analogWrite(fwdPinL, fwdSpeed);
      analogWrite(fwdPinR, 0);
    } 
    else {
      goForward();
    }
  }
}

int turnRight() {
  reverse(1500);
  off();
  analogWrite(fwdPinL, fwdSpeed);
  delay(1000);
  off();
}

int turnLeft() {
  Serial.println("Left");
  reverse(1500);
  off();
  analogWrite(fwdPinR, fwdSpeed);
  delay(1000);
  off();
}

int goForward() {
  off();
  analogWrite(fwdPinL, fwdSpeed);
  analogWrite(fwdPinR, fwdSpeed);
}
