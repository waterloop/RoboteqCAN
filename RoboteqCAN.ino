//TODO: Look at examples on Pg.40 of Roboteq CAN manual

#include <SPI.h>
#include <mcp2515.h>

struct can_frame writingObject;
struct can_frame readObject;
struct can_frame writingObject1;
struct can_frame writingObject2;
struct can_frame writingObject3;
struct can_frame writingObject4;
MCP2515 mcp2515(10);

void setup() {

  writingObject.can_id  = 0x601;
  writingObject.can_dlc = 8;
  writingObject.data[0] = 0x02;
  writingObject.data[1] = 0x02;
  writingObject.data[2] = 0x00;
  writingObject.data[3] = 0x00;
  writingObject.data[4] = 0x20;
  writingObject.data[5] = 0x02;
  writingObject.data[6] = 0x64;
  
  
 for(int i = 7; i < 8; i++){
    writingObject.data[i] = 0x00; //32
  }

  writingObject1 = writingObject;
  writingObject2 = writingObject;
  writingObject3 = writingObject;
  writingObject4 = writingObject;

 writingObject1.data[4] = 0x64;
 writingObject2.data[4] = 0xB4;
 writingObject3.data[4] = 0x86;
 writingObject3.data[5] = 0x01;
 writingObject4.data[4] = 0xF4;
 writingObject4.data[5] = 0x01;

//    writingObject.can_id  = 0x601;
//    writingObject.can_dlc = 8;
//    writingObject.data[0] = 0x48;
//    writingObject.data[1] = 0x0D;
//    writingObject.data[2] = 0x21;
//    writingObject.data[3] = 0x02;
//    writingObject.data[4] = 0x0A;
// for(int i = 5; i < 8; i++){
//    writingObject.data[i] = 0x00;
//  }
  
  while (!Serial);
  Serial.begin(115200);
  SPI.begin();
  
  mcp2515.reset();
  mcp2515.setBitrate(CAN_1000KBPS);
  mcp2515.setNormalMode();
  
  Serial.println("Example: Write to CAN");
  mcp2515.sendMessage(&writingObject);
}
char myInput = '0';

void loop() {
  
  
  //DO NOT ADD SENDMESSAGE WITHIN LOOP
  //WE WANT TO TEST THE COMMAND A COUPLE TIMES, NOT CONSTANTLY

   if (Serial.available() > 0) {    // is a character available?
    myInput = Serial.read();       // get the character
    if(myInput == '1'){
      mcp2515.sendMessage(&writingObject1);
    }else if(myInput == '2'){
      mcp2515.sendMessage(&writingObject2);
    }else if(myInput == '3'){
      mcp2515.sendMessage(&writingObject3);
    }else if(myInput == '4'){
      mcp2515.sendMessage(&writingObject4);
    }
   }
   if (mcp2515.readMessage(&readObject) == MCP2515::ERROR_OK) {
      
    Serial.print(readObject.can_id, HEX); // print ID
    Serial.print(" "); 
    Serial.print(readObject.can_dlc, HEX); // print DLC
    Serial.print(" ");
    
    for (int i = 0; i< readObject.can_dlc; i++)  {  // print the data
        
      Serial.print(readObject.data[i], HEX);
      Serial.print(" ");

    }

    Serial.println();      
  }

}
