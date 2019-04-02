/**
   (c) Copyright 2019 locha.io project developers
   Licensed under a MIT license, see LICENSE file in the root folder
   for a full text.
*/
#include <Arduino.h>
#include <SPI.h>
#include <string.h>
#include "radio.h"
#include "hal/hardware.h"
#include "lang/language.h"
#include <LoRa.h>
#include "packet.h"
#include "general_functions.h"
#include "routing_incoming.h"
#include "debugging.h"

using namespace std;

// para BLE
extern std::string txValue;
extern std::string rxValue;
// para LoRa
extern bool radio_Lora_receiving;
extern std::string txValue_Lora;
extern std::string rxValue_Lora;
extern char *id_node;


// Funcion para validar si un string es numerico
bool is_number(const std::string& s)
{
    return !s.empty() && std::find_if(s.begin(), 
        s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}

void process_Lora_incoming(){
  // se encarga de procesar la cadena recibida por Lora
  // no puede ser invocado desde Onreceive debido a un bug en la libreria Lora.h
  // https://www.bountysource.com/issues/70601319-calling-any-function-in-the-callback-method





String mensaje_recibido="";
 char* mensaje_recibido_char2;
  bool recibido=false;
  
  mensaje_recibido=rxValue_Lora.c_str();
 char mensaje_recibido_char[rxValue_Lora.size() + 1];
 rxValue_Lora.clear();  // se libera el buffer Lora
 radio_Lora_receiving=false;  //  se habilita para que se pueda recibir otro packet
 
  Serial.print(F("procesar packet recibido por LoRa:"));
  Serial.println(mensaje_recibido);
  
   strcpy(mensaje_recibido_char,mensaje_recibido.c_str());
packet_t packet_received=packet_deserialize(mensaje_recibido_char);



 // se verifica el header del mensaje recibido a ver si es un packet valido
      Serial.print(F("empiezo ..."));
    Serial.print(F("procesar packet recibido por LoRa en char:"));
          Serial.println(mensaje_recibido_char);
    
      Serial.print("recibi:");
      Serial.print("type:");
      Serial.print(convertir_packet_type_e_str(packet_received.header.type));
      Serial.print((String)packet_received.header.type);
       Serial.print("from:");
      Serial.print((String)packet_received.header.from);
      Serial.print("to:");
      Serial.print((String)packet_received.header.to);
       Serial.print("timestamp:");
      Serial.print((String)packet_received.header.timestamp);
      
       Serial.print("payload:");
      Serial.println((String)packet_received.body.payload);
        

        // se envia al BLE para efectos del demo
   txValue=((String)packet_received.body.payload).c_str();
        

        
        // se hace la parte de enrutamiento del packet
      //  process_received_packet(id_node,packet_received);
  
}


// recibe un paquete , es invocado via callback 
void onReceive(int packetSize) {
   // modificaciones para evitar el error de call back
   
   if (packetSize == 0) return; 
   
  
// char* mensaje_recibido_temp;
  char in_process;
uint8_t i;
if (!radio_Lora_receiving){
if (packetSize) {

  // se cambio packetsize por -1
  for (i = 0; i < packetSize-1; i++) {
    in_process=(char)LoRa.read();
   // se coloca en el Buffer Lora
      rxValue_Lora=rxValue_Lora+in_process;  
     
  }
  // se usa la variable boolean radio_Lora_receiving para indicar en el loop main que se puede procesar el contenido de rxValue_Lora
  // se hace de esta forma porque la libreria Lora.cpp tiene un bug y no permite invocar voids ni funciones dentro de onReceive
  radio_Lora_receiving=true;  
  
 
 
        

    Serial.println("saliendo...");
  }
  
}
}

// envía un paquete.
void radioSend(String _data) {
  // hay que verificar primero si el canal esta libre Listen before Talk
  Serial.print("voy a enviar el packet:");
  Serial.print(_data.c_str());
  LoRa.beginPacket();
  LoRa.print(_data.c_str());
  int done = LoRa.endPacket();
  Serial.print("enviado OK");
  if (done) {
    
    //LoRa.onReceive(onReceive);
    LoRa.receive();
  }
  // ..::HEADER::..
  // from:
  // to: from_phone
  // time: from_phone
  // ..::BODY::..
  // payload
}


// declaracion del radio Lora y su vinculacion via SPI
void task_radio(void *params) {

  DEBUG_PRINT(MSG_SCR);
  DEBUG_PRINT(" ");
  DEBUG_PRINT(MSG_INIT);
  DEBUG_PRINTLN(" ");

  SPI.begin(RAD_SCK, RAD_MISO, RAD_MOSI, RAD_CSS);
  LoRa.setPins(RAD_CSS, RAD_RST, RAD_DIO0);

  int rad_isInit = LoRa.begin(RAD_BAND, RAD_PABOOST);

  if (rad_isInit) {
    DEBUG_PRINT(MSG_OK);
  } else {
    DEBUG_PRINT(MSG_ERROR);
    // kill task by task handler
  }

  // al recibir ejecutar el callback onReceive()
  LoRa.onReceive(onReceive);
  // ponemos en modo recepcion.
  LoRa.receive();
// se deja en modo recibiendo el radio Lora
  while (1) {
    if (txValue_Lora.size() > 0) {
      DEBUG_PRINT("LoRa:");
      DEBUG_PRINTLN(txValue_Lora.c_str());

    }
    delay(10);
  }
}
