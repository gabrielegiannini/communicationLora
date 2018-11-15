#include <RH_RF95.h>

RH_RF95 rf95;

void setup(){
  Serial.begin(9600);
  while (!Serial) ; 
  if (!rf95.init()) /*e vero quando l inizializzazione di hardware e software per la comunicazione e andato a buon fine*/
    Serial.println("init failed");  
}

void loop(){
  Serial.println(rf95.available());  
  if (rf95.available()){/*vero se c'è un nuovo messaggio disponibile da essere letto tramite rf95.recv*/     
    uint8_t buf[RH_RF95_MAX_MESSAGE_LEN];
    uint8_t len = sizeof(buf);
     
    if (rf95.recv(buf, &len)){/*riceve un messaggio se ce ne sono da ricevere e ritorna true, altrimenti ritorna false*/
      Serial.print("got request: ");
      uint8_t dato=((int)*buf);
      Serial.println(dato);
      uint8_t data[] = "Dato ricevuto";
      rf95.send(data, sizeof(data));
      rf95.waitPacketSent();
      Serial.println("Sent a reply");   
    }else{
      Serial.println("recv failed");
    }
    
  }
}
