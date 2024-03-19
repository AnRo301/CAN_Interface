#include <Arduino.h>
#include <vector>
#include <driver/gpio.h>
#include <sstream>
#include <iostream>

#include "Access_Point.h"
#include "CAN.h"

#include "driver/twai.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/semphr.h"
#include "esp_err.h"

using namespace std;


// /* --------------------------- Tasks and Functions -------------------------- */

void setup() {

  Serial.begin(9600);
  Serial.begin(115200);

  Init_AP();    //Init Access Points

  Init_WS();    // WebSocket-Handling

  Init_CAN();   // CAN

}

void loop() {
 
  twai_receive_task();

  WS_Handling();

}
