#include "light_recv.h"

LightRecv lr(15,30,16);
int minlight = 0;
void setup() {
  Serial.begin(9600);
  Serial.println("Autoconfig...");
  lr.config();
  char buf[256];
  memset(buf,0,256);
  Serial.println("Waiting...");
  lr.waitforend();
  Serial.println("Reading...");
  lr.readstr(&buf[0],256);
  int i=0;
  while(buf[i] != '\0'){
    Serial.print(buf[i]&0xff,HEX);
    Serial.print(" ");
    i++;
  }
  Serial.println();
  Serial.println(buf);
}

void loop() {
}
