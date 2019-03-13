#ifndef LIGHT_RECV
#define LIGHT_RECV
#if ARDUINO >= 100
    #include "Arduino.h"
#else
    #include "WProgram.h"
#endif

#define AUTOCALTRHD 5
#define AUTOCALNUM 30

class LightRecv {
  public:
    LightRecv(unsigned int d,unsigned int w,unsigned int chs);
    void config();
    void readstr(char* buf,unsigned long size);
    void waitforend();
  private:
    unsigned int _delay;
    unsigned int _waittime;
    unsigned int _chsize;
    int _minlight;
};
#endif
