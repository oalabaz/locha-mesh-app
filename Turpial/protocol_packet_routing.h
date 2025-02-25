/**
 * @file protocol_packet_routing.h
 * @author locha.io project developers (dev@locha.io)
 * @brief 
 * @version 0.1
 * @date 2019-04-24
 * 
 * @copyright Copyright (c) 2019 locha.io project developers
 * @license MIT license, see LICENSE file for details
 * 
  */
#ifndef PROTOCOL_PACKET_ROUTING_H 
#define PROTOCOL_PACKET_ROUTING_H

#include <Arduino.h>
#include "hal/hardware.h"
#include "memory_def.h"
#include "packet.h"
#include "SQLite.h"


void protocol_incoming_PACKET_ROUTING_HELLO(char id_node[SIZE_IDNODE], packet_t packet_temporal, int RSSI_recibido, int SNR_recibido, sqlite3 *db);

/**
 * @brief 
 * 
 * @param id_node 
 * @param packet_temporal 
 */
void protocol_incoming_PACKET_ROUTING_JOIN(char id_node[SIZE_IDNODE], packet_t packet_temporal);

/**
 * @brief 
 * 
 * @param id_node 
 * @param packet_temporal 
 */
void protocol_incoming_PACKET_ROUTING_GOSSIP(char id_node[SIZE_IDNODE], packet_t packet_temporal);

/**
 * @brief 
 * 
 * @param id_node 
 * @param packet_temporal 
 */
void protocol_incoming_PACKET_ROUTING_ROUTE(char id_node[SIZE_IDNODE], packet_t packet_temporal);

/**
 * @brief 
 * 
 * @param id_node 
 * @param packet_temporal 
 */
void protocol_incoming_PACKET_ROUTING_BYE(char id_node[SIZE_IDNODE], packet_t packet_temporal);

/**
 * @brief 
 * 
 * @param id_node 
 * @param packet_temporal 
 */
void protocol_incoming_PACKET_ROUTING(char id_node[SIZE_IDNODE], packet_t packet_temporal, int RSSI_recibido, int SNR_recibido,sqlite3 *db);

#endif // PROTOCOL_PACKET_ROUTING_H
