/**
   (c) Copyright 2019 locha.io project developers
   Licensed under a MIT license, see LICENSE file in the root folder
   for a full text.

   Rutinas para debugging de la app
*/

#ifndef DEBUGGING_H 
#define DEBUGGING_H

#include <Arduino.h>
#include "hardware.h"
#include "general_functions.h"
#include "debugging.h"
#include "boards_def.h"
#include "memory_def.h"
#include "packet.h"
#include "route.h"
#include "language_es.h"


extern char* id_node;
extern packet_t Buffer_packet;
extern rutas_t routeTable[MAX_ROUTES];
extern nodo_t vecinos[MAX_NODES];
extern message_queue_t mensajes_salientes[MAX_MSG_QUEUE];
extern uint8_t total_vecinos;
extern uint8_t total_rutas; 
extern uint8_t total_mensajes_salientes; 

#ifdef DEBUG
  #define DEBUG_BEGIN(x)                Serial.begin (x)
  #define DEBUG_PRINT(x)                Serial.print (x)
  #define DEBUG_WRITE(x)                Serial.write (x)
  #define DEBUG_PRINT_DEC(x)            Serial.print (x, DEC)
  #define DEBUG_PRINT_HEX(x)            Serial.print (x, HEX)
  #define DEBUG_PRINTLN(x)              Serial.println (x)
  #define DEBUG_PRINT_STR(x)            Serial.print (F(x))
  #define DEBUG_PRINTLN_STR(x)          Serial.println (F(x))
#else
  #define DEBUG_BEGIN(x)
  #define DEBUG_PRINT(x)
  #define DEBUG_WRITE(x)
  #define DEBUG_PRINT_DEC(x)
  #define DEBUG_PRINT_HEX(x)
  #define DEBUG_PRINTLN(x)
  #define DEBUG_PRINT_STR(x)
  #define DEBUG_PRINTLN_STR(x)
#endif


uint8_t show_debugging_info(struct nodo_t (&vecinos)[MAX_NODES], uint8_t &total_vecinos);



#endif // DEBUGGING_H
