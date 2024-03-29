#include <Arduino.h>
#include <vector>
#include <iostream>

#include "driver/twai.h"
#include <Wifi.h>

using namespace std;

/* --------------------------- Tasks and Functions -------------------------- */
void Init_CAN();
void twai_receive_task();                           
void twai_transmit_task(twai_message_t message);

void Change_CAN_Speed(uint8_t *data);

int convertVectorToUInt32(const vector<uint8_t> &vec);



