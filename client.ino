#include <SPI.h>
#include <RH_RF95.h>
RH_RF95 rf95;

void setup(){
  
  Serial.begin(9600);
  while (!Serial) ; 
  if (!rf95.init())
    Serial.println("init failed");
  
}

void loop(){
  
  Serial.println("Sending to rf95_server"); 
  uint8_t data[] = "Hello World!";
  rf95.send(data,sizeof(data));
  rf95.waitPacketSent();
  uint8_t buf[RH_RF95_MAX_MESSAGE_LEN]; //definisco i Byte del buf
  uint8_t len = sizeof(buf);
  
  if (rf95.waitAvailableTimeout(3000)){ 
    if (rf95.recv(buf, &len)){
      Serial.print("got reply: ");
      Serial.println((char*)buf);   
    }else{
      Serial.println("recv failed");
    }
  }else{
    Serial.println("No reply, is rf95_server running?");
  }
  delay(3000);
}
