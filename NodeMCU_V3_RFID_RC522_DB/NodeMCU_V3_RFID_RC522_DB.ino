/*
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # 
# RFID MFRC522 / RC522 Library : https://github.com/miguelbalboa/rfid # 
#                                                                     # 
#                 Installation :                                      # 
# NodeMCU ESP8266/ESP12E    RFID MFRC522 / RC522                      #
#         D2       <---------->   SDA/SS                              #
#         D5       <---------->   SCK                                 #
#         D7       <---------->   MOSI                                #
#         D6       <---------->   MISO                                #
#         GND      <---------->   GND                                 #
#         D1       <---------->   RST                                 #
#         3V/3V3   <---------->   3.3V                                #
# # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # # #
*/

#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <WiFiClientSecure.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <SPI.h>
#include <MFRC522.h>
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//
#include <Wire.h>
#include <Servo.h> 


#define SS_PIN D2  //--> SDA / SS is connected to pinout D2
#define RST_PIN D1  //--> RST is connected to pinout D1
MFRC522 mfrc522(SS_PIN, RST_PIN);  //--> Create MFRC522 instance.

#define ON_Board_LED 2  //--> Defining an On Board LED, used for indicators when the process of connecting to a wifi router

//----------------------------------------SSID and Password of your WiFi router-------------------------------------------------------------------------------------------------------------//
const char* ssid = "seedsphere"; //- CHANGE PATO
const char* password = "YssabelJane25*"; //- CHANGE PATO
// const char* ssid = "OPPO A96"; //- CHANGE PATO
// const char* password = "sheeshka"; //- CHANGE PATO
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

int readsuccess;
byte readcard[4];
char str[32] = "";
String StrUID;


int accessGrantedSize = 3;                                //The number of serial numbers
Servo lockServo;                //Servo for locking mechanism - CHANGE PATO
int lockPos = 15;               //Locked position limit
int unlockPos = 75;             //Unlocked position limit
boolean locked = true;
boolean locked1 = true;
int pos = 0;
int buzzerPin = D0;
int greenLEDPin = D8;
int redLEDPin = D3;


String getData = ""; //NEED
String payloadGet = ""; //NEED
String getData1 = ""; //NEED
String payloadGet1 = ""; //NEED
String URL_Server = "";
String Destination = "";
String host_or_IPv4 = "https://ucc-csd-bscs.com/";

HTTPClient http; //--> Declare object of class HTTPClient
WiFiClient client;

//-----------------------------------------------------------------------------------------------SETUP--------------------------------------------------------------------------------------//
void setup() {
  Serial.begin(115200); //--> Initialize serial communications with the PC
  SPI.begin();      //--> Init SPI bus
  mfrc522.PCD_Init(); //--> Init MFRC522 card
  lockServo.attach(D3);
  lockServo.write(lockPos);         //Move servo into locked position
  pinMode(greenLEDPin,OUTPUT); //--> On Board LED port Direction output
  pinMode(redLEDPin,OUTPUT); //--> On Board LED port Direction output
  delay(500);

  WiFi.begin(ssid, password); //--> Connect to your WiFi router
  Serial.println("");
    
  pinMode(ON_Board_LED,OUTPUT); 
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off Led On Board

  //----------------------------------------Wait for connection
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    //----------------------------------------Make the On Board Flashing LED on the process of connecting to the wifi router.
    digitalWrite(ON_Board_LED, LOW);
    delay(250);
    digitalWrite(ON_Board_LED, HIGH);
    delay(250);
  }
  digitalWrite(ON_Board_LED, HIGH); //--> Turn off the On Board LED when it is connected to the wifi router.
  //----------------------------------------If successfully connected to the wifi router, the IP Address that will be visited is displayed in the serial monitor
  Serial.println("");
  Serial.print("Successfully connected to : ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Please tag a card or keychain to see the UID !");
  Serial.println("");
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//-----------------------------------------------------------------------------------------------LOOP---------------------------------------------------------------------------------------//
void loop() {
  // put your main code here, to run repeatedly
  readsuccess = getid();

  if(readsuccess) {  
  digitalWrite(ON_Board_LED, LOW);
    String UIDresultSend, postData;
    UIDresultSend = StrUID;
   
    //Post Data
    postData = "UIDresult=" + UIDresultSend;
    std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    client->setInsecure(); //don't use SSL certificate

    // Your_Host_or_IP = Your pc or server IP, example : 192.168.0.0 , if you are a windows os user, open cmd, then type ipconfig then look at IPv4 Address.
    // http.begin(client, "http://192.168.68.115/NodeMCU_RC522_Mysql/getUID.php");  //Specify request destination
    http.begin(*client, "https://ucc-csd-bscs.com/HRS/admin/getUID.php");  //Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded"); //Specify content-type header
   
    int httpCode = http.POST(postData);   //Send the request
    String payload = http.getString();    //Get the response payload

    Serial.println(UIDresultSend);
    Serial.println(postData);
    Serial.println(httpCode);   //Print HTTP return code
    Serial.println(payload);    //Print request response payload
    checkAccess (UIDresultSend);     //Check if the identified tag is an allowed to open tag

    //ROOM 1
    int id_1 = 1; //--> ID in Database 
    getData = "ID=" + String(id_1); //ID=0
    Destination = "HRS/GetData.php";
    URL_Server = host_or_IPv4 + Destination;

    // std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    // client->setInsecure(); //don't use SSL certificate

    http.begin(*client, URL_Server); //--> Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

    int httpCodeGet = http.POST(getData); //--> Send the request
    payloadGet = http.getString(); //--> Get the response payload from server
    Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. For more information see here : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
    Serial.println(httpCodeGet); //--> Print HTTP return code
    Serial.print("Returned data from Server : ");
    Serial.println(payloadGet); //--> Print request response payload  
    // delay(10000);

    //ROOM 2
    int id_2 = 2; //--> ID in Database 
    getData1 = "ID=" + String(id_2); //ID=0
    Destination = "HRS/GetData1.php";
    URL_Server = host_or_IPv4 + Destination;

    // std::unique_ptr<BearSSL::WiFiClientSecure>client(new BearSSL::WiFiClientSecure);
    // client->setInsecure(); //don't use SSL certificate

    http.begin(*client, URL_Server); //--> Specify request destination
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");    //Specify content-type header

    int httpCodeGet1 = http.POST(getData1); //--> Send the request
    payloadGet1 = http.getString(); //--> Get the response payload from server
    Serial.print("Response Code : "); //--> If Response Code = 200 means Successful connection, if -1 means connection failed. For more information see here : https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
    Serial.println(httpCodeGet1); //--> Print HTTP return code
    Serial.print("Returned data from Server : ");
    Serial.println(payloadGet1); //--> Print request response payload  
    // delay(10000);
    
    http.end();  //Close connection
    delay(3000);
  digitalWrite(ON_Board_LED, HIGH);
  }


}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------
void checkAccess (String UIDresultSend)    //Function to check if an identified tag is registered to allow access
{
  boolean granted = false;
  boolean granted1 = false;
  String accessGranted[2] = {payloadGet, payloadGet1};  //RFID serial numbers to grant access to //- CHANGE PATO
  for (int i=0; i <= (accessGrantedSize-1); i++)    //Runs through all tag ID numbers registered in the array
  {
    if(accessGranted[i] == UIDresultSend)            //If a tag is found then open/close the lock
    {
      Serial.println ("Access Granted");
      tone(buzzerPin, 3000, 800);
      delay(500);
      noTone(buzzerPin);

      if(accessGranted[0] == UIDresultSend)            //If a tag is found then open/close the lock
      {
        Serial.println("Room 101");
        granted = true;
        if (locked == true)         //If the lock is closed then open it
        {
          // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees - CHANGE PATO
          //   // in steps of 1 degree
          //   lockServo.write(pos);              // tell servo to go to position in variable 'pos'
          //   //delay(15);                       // waits 15ms for the servo to reach the position
          // }
            Serial.println("DOOR IS OPEN");
            Serial.println("LIGHTS ON");
            digitalWrite(greenLEDPin, HIGH);    //Green LED sequence
            // lockServo.write(unlockPos);
            locked = false;
        }
        else if (locked == false)   //If the lock is open then close it
        {
          // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees - CHANGE PATO
          //   lockServo.write(pos);              // tell servo to go to position in variable 'pos'
          //   //delay(15);                       // waits 15ms for the servo to reach the position
          // }
            Serial.println("DOOR IS CLOSE");
            Serial.println("LIGHTS OFF");
            digitalWrite(greenLEDPin, LOW);
            // lockServo.write(lockPos);
            locked = true;
        }
      }


      if(accessGranted[1] == UIDresultSend)            //If a tag is found then open/close the lock
      {
        Serial.println("Room 102");
        granted1 = true;
        if (locked1 == true)         //If the lock is closed then open it
        {
          // for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees - CHANGE PATO
          //   // in steps of 1 degree
          //   lockServo.write(pos);              // tell servo to go to position in variable 'pos'
          //   //delay(15);                       // waits 15ms for the servo to reach the position
          // }
            Serial.println("DOOR IS OPEN");
            Serial.println("LIGHTS ON");
            digitalWrite(redLEDPin, HIGH);    //Green LED sequence
            // lockServo.write(unlockPos);
            locked1 = false;
        }
        else if (locked1 == false)   //If the lock is open then close it
        {
          // for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees - CHANGE PATO
          //   lockServo.write(pos);              // tell servo to go to position in variable 'pos'
          //   //delay(15);                       // waits 15ms for the servo to reach the position
          // }
            Serial.println("DOOR IS CLOSE");
            Serial.println("LIGHTS OFF");
            digitalWrite(redLEDPin, LOW);
            // lockServo.write(lockPos);
            locked1 = true;
        }
      }
    }
  }
  if (granted == false)     //If the tag is not found
  {
    Serial.println ("Card is not exist");
    Serial.println("LIGHTS OFF");
    tone(buzzerPin, 300, 1000);
    delay(500);
    noTone(buzzerPin);
  }
  
}

//----------------------------------------Procedure for reading and obtaining a UID from a card or keychain---------------------------------------------------------------------------------//
int getid() {  
  if(!mfrc522.PICC_IsNewCardPresent()) {
    return 0;
  }
  if(!mfrc522.PICC_ReadCardSerial()) {
    return 0;
  }
 
  
  Serial.print("THE UID OF THE SCANNED CARD IS : ");
  
  for(int i=0;i<4;i++){
    readcard[i]=mfrc522.uid.uidByte[i]; //storing the UID of the tag in readcard
    array_to_string(readcard, 4, str);
    StrUID = str;
  }
  mfrc522.PICC_HaltA();
  return 1;
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//

//----------------------------------------Procedure to change the result of reading an array UID into a string------------------------------------------------------------------------------//
void array_to_string(byte array[], unsigned int len, char buffer[]) {
    for (unsigned int i = 0; i < len; i++)
    {
        byte nib1 = (array[i] >> 4) & 0x0F;
        byte nib2 = (array[i] >> 0) & 0x0F;
        buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
        buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
    }
    buffer[len*2] = '\0';
}
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------//