#include <CAN.h>
#include <Access_Point.h>

/* --------------------- Definitions and static variables ------------------ */

twai_general_config_t g_config;
twai_timing_config_t t_config;
twai_filter_config_t f_config;

/* --------------------------- Tasks and Functions -------------------------- */

void Init_CAN(){

  //Initialize configuration structures using macro initializers
  g_config = TWAI_GENERAL_CONFIG_DEFAULT(GPIO_NUM_37, GPIO_NUM_36, TWAI_MODE_NORMAL);   //Platine
  t_config = TWAI_TIMING_CONFIG_25KBITS();
  f_config = TWAI_FILTER_CONFIG_ACCEPT_ALL();
  

  // Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK)
  {
    printf("Driver installed\n");
  }
  else
  {
    printf("Failed to install driver\n");
    return;
  }
  // Start TWAI driver
  if (twai_start() == ESP_OK)
  {
    printf("Driver started\n");
  }
  else
  {
    printf("Failed to start driver\n");
    return;
  }
}


void twai_receive_task()
{
    printf("twai_receive_task: while Loop\n");

    twai_message_t message;

    if(twai_receive(&message, 1000) == ESP_OK){
    printf("0x%03x :", message.identifier);
    printf("0x%03x :", message.data_length_code);
    if (!(message.rtr))
    {
      for (int i = 0; i < message.data_length_code; i++)
      {
        printf("0x%02x ", message.data[i]);
      }
      printf("\n");
    }

    uint8_t a = (message.identifier >> 24) & 0xFF;  //a
    uint8_t b = (message.identifier >> 16)& 0xFF;   //b
    uint8_t c = (message.identifier >> 8) & 0xFF;   //c
    uint8_t d = message.identifier & 0xFF;          //d
    
    vector<uint8_t> identifier = {
         static_cast<uint8_t>(a),
         static_cast<uint8_t>(b),
         static_cast<uint8_t>(c),
         static_cast<uint8_t>(d)};

     vector<uint8_t> frameLength = {message.data_length_code};

     vector<uint8_t> data = {
         static_cast<uint8_t>(message.data[0]),
         static_cast<uint8_t>(message.data[1]),
         static_cast<uint8_t>(message.data[2]),
         static_cast<uint8_t>(message.data[3]),
         static_cast<uint8_t>(message.data[4]),
         static_cast<uint8_t>(message.data[5]),
         static_cast<uint8_t>(message.data[6]),
         static_cast<uint8_t>(message.data[7])};

    
    vector<uint8_t> extFlag = {0x00};
    vector<uint8_t> rtrFlag = {0x00};

    if ((unsigned char)message.extd == 1)
    {
      extFlag = {0x01};
    } else {
      extFlag = {0x00};
    }

    if((unsigned char)message.rtr == 1)
    {
      rtrFlag = {0x01};
    } else {
      rtrFlag = {0x00};
    }

    CANFrame CanFrameReceived;
    
    CanFrameReceived.identifier = identifier;
    CanFrameReceived.frameLength = frameLength;
    CanFrameReceived.data = data;
    CanFrameReceived.extFlag = extFlag;
    CanFrameReceived.rtrFlag = rtrFlag;

    sendReceivedCANData(CanFrameReceived);

    }else{
      printf("Failed to receive message\n");
      return;
    }
}


void twai_transmit_task(twai_message_t message){
  
  // Queue message for transmission
  if (twai_transmit(&message, pdMS_TO_TICKS(1000)) == ESP_OK)
  {
    printf("Message queued for transmission\n");
  } else {
    printf("Failed to queue message for transmission\n");
  }

  printf("Transmitting Message\n");
        
  printf("0x%04x :", message.identifier);
  printf("0x%02x :", message.data_length_code);
  for (int i = 0; i < message.data_length_code; i++)
  {
    printf("0x%02x ", message.data[i]);
  }
  cout << endl;

  vTaskDelay(2000);
}


int convertVectorToUInt32(const vector<uint8_t>& vec) { 
    
    uint32_t result = 0;
    
    for (size_t i = 0; i < vec.size(); i++) { 
        result = (result << 8) | vec[i]; 
    } 
        
    return result; 
}


void Change_CAN_Speed(uint8_t *data){

  if(data[0] == '1' && data[1] == 'M'){
    t_config = TWAI_TIMING_CONFIG_1MBITS();
    printf("\nCAN-Speed changed to 1Mbit/s\n");
  } else if(data[0] == '8'){
    t_config = TWAI_TIMING_CONFIG_800KBITS();
    printf("\nCAN-Speed changed to 800Kbit/s\n");
  } else if(data[0] == '5' && data[2] == '0'){
    t_config = TWAI_TIMING_CONFIG_500KBITS();
    printf("\nCAN-Speed changed to 500Kbit/s\n");
  } else if(data[0] == '2' && data[2] == '0'){
    t_config = TWAI_TIMING_CONFIG_250KBITS();
    printf("\nCAN-Speed changed to 250Kbit/s\n");
  } else if(data[0] == '1' && data[1] == '2'){
    t_config = TWAI_TIMING_CONFIG_125KBITS();
    printf("\nCAN-Speed changed to 125Kbit/s\n");
  } else if(data[0] == '1' && data[2] == '0'){
    t_config = TWAI_TIMING_CONFIG_100KBITS();
    printf("\nCAN-Speed changed to 100Kbit/s\n");
  } else if(data[0] == '5' && data[1] == '0'){
    t_config = TWAI_TIMING_CONFIG_50KBITS();
    printf("\nCAN-Speed changed to 50Kbit/s\n");
  } else if(data[0] == '2' && data[1] == '5'){
    t_config = TWAI_TIMING_CONFIG_25KBITS();
    printf("\nCAN-Speed changed to 25Kbit/s\n");
  }else{
    t_config = TWAI_TIMING_CONFIG_25KBITS();
    printf("\nDefault CAN-Speed\n");
  }

  //Stop the TWAI driver
  if (twai_stop() == ESP_OK) {
    printf("Driver stopped\n");
  } else {
    printf("Failed to stop driver\n");
    return;
  }

  //Uninstall the TWAI driver
  if (twai_driver_uninstall() == ESP_OK) {
    printf("Driver uninstalled\n");
  } else {
    printf("Failed to uninstall driver\n");
    return;
  }

  // Install TWAI driver
  if (twai_driver_install(&g_config, &t_config, &f_config) == ESP_OK)
  {
    printf("Driver installed\n");
  }
  else
  {
    printf("Failed to install driver\n");
    return;
  }
  // Start TWAI driver
  if (twai_start() == ESP_OK)
  {
    printf("Driver started\n");
  }
  else
  {
    printf("Failed to start driver\n");
    return;
  }
}
