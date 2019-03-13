#define DELAY 15
#define CAL 30
#define WAIT 30
#define CHUNK_SIZE 16

char buf[] = "This website uses cookies. By using this website you accept the use of cookies. ";

void setup() {
  Serial.begin(9600);
  pinMode(3,OUTPUT);
  
}

void loop() {
  long size = strlen(buf);
  int i = 0;
  char sig;
  while(i/8<=size){
    digitalWrite(3,HIGH);
    delay(CAL);
    digitalWrite(3,LOW);
    delay(WAIT);
    while(1){
      sig = buf[i/8]&(1<<(7-(i%8)));
      digitalWrite(3,sig!=0);
      delay(DELAY);
      i++;
      if(i%CHUNK_SIZE==0)break;
    }
    digitalWrite(3,LOW);
  }
  digitalWrite(3,HIGH);
  delay(DELAY*CALMUL);
  digitalWrite(3,LOW);
  delay(DELAY*WAITMUL);
  delay(DELAY*CHUNK_SIZE);
}
