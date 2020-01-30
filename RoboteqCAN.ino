//!G 1 500 
//{Command, Motor ID, int32(-1000<N<1000)} ;-> Refer to pg.18
//TODO:

#include <SPI.h>
#include <mcp2515.h>

struct can_frame writingObject;
struct can_frame readObject;
MCP2515 mcp2515(10);


void setup() {

  writingObject.can_id  = 0x1;
  writingObject.can_dlc = 8;
  writingObject.data[0] = 0x8E;
  writingObject.data[1] = 0x87;
  writingObject.data[2] = 0x32;
  writingObject.data[3] = 0xFA;
  writingObject.data[4] = 0x26;
  writingObject.data[5] = 0x8E;
  writingObject.data[6] = 0xBE;
  writingObject.data[7] = 0x86;

 
  
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_125KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
  mcp2515.sendMessage(&writingObject);
}

void loop() {
  
  
  //DO NOT ADD SENDMESSAGE WITHIN LOOP
  //WE WANT TO TEST THE COMMAND A COUPLE TIMES, NOT CONSTANTLY

  
   if (mcp2515.readMessage(&readObject) == MCP2515::ERROR_OK) {
      
    Serial.print(readObject.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(readObject.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i<readObject.can_dlc; i++)  {  // print the data
        
      Serial.print(readObject.data[i],HEX);
      Serial.print(" ");

    }

    Serial.println();      
  }

}
