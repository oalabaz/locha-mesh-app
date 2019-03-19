/**
   (c) Copyright 2019 locha.io project developers
   Licensed under a MIT license, see LICENSE file in the root folder
   for a full text.
*/
#include <Arduino.h>
#include <string.h> 
#include "hardware.h"
#include "general_functions.h"
#include "packet.h"
#include "route.h"

extern char id_node[16];
extern packet_t Buffer_packet;


// se incluyen los eventos para externos para cada tipo de packet_t
extern int routing_incoming_PACKET_HELLO(char id_node[16], packet_t packet_received);
extern int routing_incoming_NET_BYE(char id_node[16], packet_t packet_received);
extern int routing_incoming_NET_JOIN(char id_node[16], packet_t packet_received);
extern int routing_incoming_NET_ROUTE(char id_node[16], packet_t packet_received);
extern int routing_incoming_PACKET_ACK(char id_node[16], packet_t packet_received);
extern int routing_incoming_PACKET_GOSSIP(char id_node[16], packet_t packet_received);
extern int routing_incoming_PACKET_MSG(char id_node[16], packet_t packet_received);
extern int routing_incoming_PACKET_TXN(char id_node[16], packet_t packet_received);
extern int routing_incoming_PACKET_NOTDELIVERED(char id_node[16], packet_t packet_received);


radioPacket::radioPacket(packet_t packet)
{
  packet = packet;
  header = packet.header;
  body = packet.body;
}

radioPacket::~radioPacket()
{
  // destructor
}

void radioPacket::deserialize()
{
  uint8_t rpta;
  switch (header.type)
  {
  case EMPTY:
  case JOIN:
      routing_incoming_NET_JOIN(id_node, Buffer_packet);
      break;
  case BYE:
      routing_incoming_NET_BYE(id_node, Buffer_packet);
      break;
  case ROUTE:
      routing_incoming_NET_ROUTE(id_node, Buffer_packet);
      break;
  case ACK:
      routing_incoming_PACKET_ACK(id_node, Buffer_packet);
      break;
  case MSG:
     routing_incoming_PACKET_MSG(id_node, Buffer_packet);
     break;
  case HELLO:
   routing_incoming_PACKET_HELLO(id_node, Buffer_packet);
      break;
  case GOSSIP:
   routing_incoming_PACKET_GOSSIP(id_node, Buffer_packet);
      break;
  case NOT_DELIVERED:
   routing_incoming_PACKET_NOTDELIVERED(id_node, Buffer_packet);
      break;
  default:
    break;
  }
}


packet_type_e convertir_str_packet_type_e(String type_recibido){
  packet_type_e rpta=EMPTY;
  if (type_recibido==F("ACK")) return ACK;
  if (type_recibido==F("JOIN")) return JOIN;
  if (type_recibido==F("BYE")) return BYE;
  if (type_recibido==F("ROUTE")) return ROUTE;
  if (type_recibido==F("HELLO")) return HELLO;
  if (type_recibido==F("GOSSIP")) return GOSSIP;
  if (type_recibido==F("NOT_DELIVERED")) return NOT_DELIVERED;
  return rpta;
}


packet_t create_packet(char* id_node, packet_type_e type, char* from, char* to, char* payload){
   
      packet_header_t header;
      packet_body_t body;

      header.type=type;
      copy_array_locha(id_node, header.from, 16);
      copy_array_locha(to, header.to, 16);
      header.timestamp=millis();
      copy_array_locha(payload, body.payload, 240);
      packet_t new_packet;
      new_packet.header=header;
      new_packet.body=body;
    return new_packet;
}
