#include <Arduino.h>

constexpr uint8_t L1 = 13, L2 = 12, R1 = 11, R2 = 10;

enum Dir : int8_t { REV = -1, STOP = 0, FWD = 1 };

inline void setMotor(uint8_t a, uint8_t b, Dir d) {
  digitalWrite(a, d == FWD);
  digitalWrite(b, d == REV);
}

inline void drive(Dir left, Dir right) {
  setMotor(L1, L2, left);
  setMotor(R1, R2, right);
}

inline bool isSpeedCmd(char c) { return (c >= '0' && c <= '9') || c == 'q'; }

void setup() {
  pinMode(L1, OUTPUT);
  pinMode(L2, OUTPUT);
  pinMode(R1, OUTPUT);
  pinMode(R2, OUTPUT);
  drive(STOP, STOP);
  Serial.begin(9600);
}

void handle(char c) {
  if (isSpeedCmd(c))
    return;
  switch (c) {
  case 'F':
    drive(FWD, FWD);
    break;
  case 'B':
    drive(REV, REV);
    break;
  case 'L':
    drive(STOP, FWD);
    break;
  case 'R':
    drive(FWD, STOP);
    break;
  case 'G':
    drive(FWD, STOP);
    break;
  case 'I':
    drive(STOP, FWD);
    break;
  case 'H':
    drive(REV, STOP);
    break;
  case 'J':
    drive(STOP, REV);
    break;
  case 'S':
  case 'D':
    drive(STOP, STOP);
    break;
  case 'W':
  case 'w':
  case 'U':
  case 'u':
  case 'V':
  case 'v':
  case 'X':
  case 'x':
    break;
  default:
    drive(STOP, STOP);
    break;
  }
}

void loop() {
  while (Serial.available())
    handle((char)Serial.read());
}