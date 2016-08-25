
#include <Arduino.h>

#define MOT_PWM_A 3
#define MOT_PWM_B 11
#define MOT_BRK_A 8
#define MOT_BRK_B 9
#define MOT_DIR_A 12
#define MOT_DIR_B 13

int MOT_pa = 0;
int MOT_pb = 0;

void MOT_init() {
  pinMode(MOT_DIR_A, OUTPUT);
  digitalWrite(MOT_DIR_A, LOW);
  pinMode(MOT_PWM_A, OUTPUT);
  analogWrite(MOT_PWM_A, 0);
  pinMode(MOT_DIR_B, OUTPUT);
  digitalWrite(MOT_DIR_B, LOW);
  pinMode(MOT_PWM_B, OUTPUT);
  analogWrite(MOT_PWM_B, 0);
}

void MOT_setMot(int dir, int pwm, int p) {
  if (p>=0) digitalWrite(dir, LOW);
  else digitalWrite(dir, HIGH);
  analogWrite(pwm, abs(p));
}

void MOT_setL(int p) {
  p = constrain(p,-255,255);
  MOT_pb = p;
  MOT_setMot(MOT_DIR_B,MOT_PWM_B,p);
}

void MOT_setR(int p) {
  p = constrain(p,-255,255);
  MOT_pa = p;
  MOT_setMot(MOT_DIR_A,MOT_PWM_A,p);
}

int MOT_getL() {
  return MOT_pb;
}

int MOT_getR() {
  return MOT_pa;
}

void MOT_setMotors(int pL, int pR) {
  MOT_setL(pL);
  MOT_setR(pR);
}
