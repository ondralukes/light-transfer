#include "light_recv.h"

unsigned int _delay;
unsigned int _waittime;

LightRecv::LightRecv(unsigned int d,unsigned int w,unsigned int chs){
      _delay = d;
      _waittime = w;
      _chsize = chs;
}

void LightRecv::config(){
  bool lowfirst;
  bool initdone = false;
  long vals[2] = {0,0};
  long num[2] = {0,0};
  long val;
  long val0;
  long val1;
  vals[0] += analogRead(A0);
  num[0]++;
  while(1){
    val = analogRead(A0);
    val0= vals[0]/num[0];
    if(abs(val0-val)>AUTOCALTRHD){
      if(!initdone){
        initdone = true;
        if(val>val0){
          vals[1] = val;
          num[1]++;
          lowfirst = true;
          } else {
            vals[1] = val;
          num[1]++;
          lowfirst = false;
            }
        } else {
          if(lowfirst){
            if(val>val0){
              if(num[1]<AUTOCALNUM){
              vals[1] += val;
              num[1]++;
              }
              }
            } else{
              if(val<val0){
                if(num[1]<AUTOCALNUM){
              vals[1] += val;
              num[1]++;
                }
              }
              }
          }
      } else {
        if(num[0]<AUTOCALNUM){
        vals[0] += val;
        num[0]++;
        }
        }
  if(num[0] == AUTOCALNUM&num[1] == AUTOCALNUM) break;
    }
  unsigned int low = lowfirst?(vals[0]/AUTOCALNUM):(vals[1]/AUTOCALNUM);
  unsigned int high = lowfirst?(vals[1]/AUTOCALNUM):(vals[0]/AUTOCALNUM);
  _minlight = low+(high-low)/2;
}
void LightRecv::readstr(char* buf, unsigned long size){
  int i = 0;
  int j = 0;
  bool zero = true;
  while(1){
  while(analogRead(A0)<_minlight);
  delayMicroseconds(1000);
  while(analogRead(A0)>_minlight);
    delay(_waittime);
    delay(_delay/2);
    j=0;
    if(i+_chsize>= size*8)break;
    zero = true;
    while(j<_chsize){
      if(analogRead(A0)>_minlight){
        buf[i/8] |= (1<<(7-(i%8)));
        zero = false;
        }
         i++;
         j++;
        delay(_delay);
      }
      if(zero){
        if(i==_chsize){
          i=0;
          } else{
          break;
          }
        }

  }
}
void LightRecv::waitforend(){
  unsigned long start = millis();
  while(millis()-start<_delay*_chsize){
     if(analogRead(A0)>_minlight){
      start=millis();
      }
    }
}
