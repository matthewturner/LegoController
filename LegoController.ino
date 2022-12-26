#include <L293.h>

const byte MotorLeftEnablePin = 3;
const byte MotorLeftForwardPin = 6;
const byte MotorLeftReversePin = 4;
const byte MotorRightEnablePin = 9;
const byte MotorRightForwardPin = 7;
const byte MotorRightReversePin = 8;

const byte SwitchPin = 12;

L293 leftMotor(MotorLeftEnablePin, MotorLeftForwardPin, MotorLeftReversePin);
L293 rightMotor(MotorRightEnablePin, MotorRightForwardPin, MotorRightReversePin);

void setup() {
  Serial.begin(9600);

  pinMode(SwitchPin, INPUT_PULLUP);

  Serial.println("Setup complete. Looping...");
}

void loop() {
  if (digitalRead(SwitchPin) == HIGH) {
    int leftSpeed = readSpeed(A0);
    applySpeed(leftMotor, leftSpeed);
  
    int rightSpeed = readSpeed(A1);
    applySpeed(rightMotor, rightSpeed);
  }
  else {
    leftMotor.stop();
    rightMotor.stop();
  }
}

void applySpeed(L293 motor, int speed)
{
  if (speed == 0)
  {
    motor.stop();
  }
  else
  {
    if (speed > 0)
    {
      motor.forward(speed);
    }
    else
    {
      motor.back(abs(speed));
    }
  }
}

int readSpeed(int pin)
{
  int setting = analogRead(pin);
  int mappedSetting = map(setting, 0, 1023, -250, 250);
  if (mappedSetting > -50 && mappedSetting < 50)
  {
    return 0;
  }
  return mappedSetting;
}
