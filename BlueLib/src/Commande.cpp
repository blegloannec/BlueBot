
#include <Arduino.h>
#include "Moteurs.h"

int CMD_fabInt(byte b0, byte b1) {
  return int(b0)|(int(b1)<<8);
}

void CMD_recvOrdre() {
  byte c[3];
  int p,pf,d;
  if (Serial1.available()>=3) {
    Serial1.readBytes((char*)c,3);
    /*if (c[0]=='m') {
      MOT_setMotors(CMD_fabInt(c[1],c[2]),CMD_fabInt(c[3],c[4]));
      }
    else if (c[0]=='o') {
      long V = ODO_getL();
      Serial.write((uint8_t*)&V,4);
      V = ODO_getR();
      Serial.write((uint8_t*)&V,4);
      }
    else if (c[0]=='r') ODO_reset();
    */
    if (c[0]=='D') {
      p = 2*(c[1]-127);
      if (abs(p)<30) p = 0;
      d = 127-c[2];
      if (abs(d)<15) pf = p;
      else pf = int(float(p)*(1.-2.*float(abs(d))/127.));
      if (p*d>=0) MOT_setMotors(pf,p);
      else MOT_setMotors(p,pf);
    }
    else if (c[0]=='S') {
      p = c[1];
      if (p<50) p = 0;
      if (0<=c[2] && c[2]<64) {
        pf = int(float(p)*(-1.+2.*float(c[2])/64.));
        MOT_setMotors(-p,-pf);
      }
      else if (64<=c[2] && c[2]<128) {
        pf = int(float(p)*(1.-2.*float(c[2]-64)/64.));
        MOT_setMotors(-pf,-p);
      }
      else if (128<=c[2] && c[2]<192) {
        pf = int(float(p)*(-1.+2.*float(c[2]-128)/64.));
        MOT_setMotors(p,pf);
      }
      else {
        pf = int(float(p)*(1.-2.*float(c[2]-192)/64.));
        MOT_setMotors(pf,p);
      }
    }
  }
}
