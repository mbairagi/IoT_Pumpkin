#include <Process.h>
#include "Maxbotix.h"
#include <aws_iot_mqtt.h>
#include <aws_iot_version.h>
#include "aws_iot_config.h"

#define redeyeleds 2
#define ylwmouthleds 3
#define whtmidmouthleds 4
#define bluoutermouthleds 5


Maxbotix rangeSensorAD(A0, Maxbotix::AN, Maxbotix::LV);


Process p;

aws_iot_mqtt_client myClient; // init iot_mqtt_client
char msg[32]; // read-write buffer
int rc = -100; // return value placeholder



void setup() {
  Bridge.begin();
  Serial.begin(9600);           // set up Serial library at 9600 bps
  Serial.println(F("test!"));

  pinMode(1, OUTPUT); 
  pinMode(2, OUTPUT); 
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  
  pinMode(redeyeleds, OUTPUT);
  pinMode(ylwmouthleds, OUTPUT);
  pinMode(whtmidmouthleds, OUTPUT);
  pinMode(bluoutermouthleds, OUTPUT);

 char curr_version[80];
  sprintf(curr_version, "AWS IoT SDK Version(dev) %d.%d.%d-%s\n", VERSION_MAJOR, VERSION_MINOR, VERSION_PATCH, VERSION_TAG);
  Serial.println(curr_version);
  // Set up the client
  if((rc = myClient.setup(AWS_IOT_CLIENT_ID)) != 0) {
    Serial.println("Setup failed!");
    Serial.println(rc);
  }
  // Load user configuration
  if((rc = myClient.config(AWS_IOT_MQTT_HOST, AWS_IOT_MQTT_PORT, AWS_IOT_ROOT_CA_PATH, AWS_IOT_PRIVATE_KEY_PATH, AWS_IOT_CERTIFICATE_PATH)) != 0) {
    Serial.println("Config failed!");
    Serial.println(rc);
  }
  // Use default connect: 60 sec for keepalive
  if((rc = myClient.connect()) != 0) {
    Serial.println("Connect failed!");
    Serial.println(rc);
  }

 }
 

void loop() { 
   int distsensor, i;
   long time;
   distsensor = 0;
   unsigned long start;
  
	funLEDonoff();
  
  Serial.println("Reading...");
  
  start = millis();
  Serial.print("AD: ");
  distsensor = rangeSensorAD.getRange();
  Serial.print(distsensor);
  Serial.print("cm - ");
  Serial.print(millis() - start);
  Serial.println("ms");
  
  Serial.println();
   
   if (distsensor <= 300) {
    funLEDonoff();
   } 

   
   if (distsensor > 300) {
     funLEDonoff();
	   // nobody there. one out of 200 times play one of the scary sounds (once every few minutes)
     i = random(200);
     if (i == 0) {
       i = random(3);
	   funLEDonoff();
       if (i == 0) {
           p.runShellCommand("madplay /mnt/sda1/1.mp3");
       } else if (i == 1) {
           p.runShellCommand("madplay /mnt/sda1/2.mp3");
       } else {
           p.runShellCommand("madplay /mnt/sda1/3.mp3");   
       }
     funLEDonoff();
     }
   } else if ((distsensor > 100) && (distsensor < 300)) {
  	        funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/4.mp3");
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/5.mp3");
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/6.mp3");   
            funLEDonoff();
   } else if ((distsensor > 50) && (distsensor < 100)) {
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/7.mp3"); 
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/8.mp3");
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/9.mp3");
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/10.mp3");   
            funLEDonoff();
   } else if (distsensor < 50) {
    
            sprintf(msg, "new object at distance %d", distsensor);
          // If distnace is under 50 cm, public message to the AWS IoT topic "topic1"
            if((rc = myClient.publish("topic1", msg, strlen(msg), 1, false)) != 0) {
            Serial.println("Publish failed!");
            Serial.println(rc);
            }
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/11.mp3");    
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/12.mp3");
            funLEDonoff();
            p.runShellCommand("madplay /mnt/sda1/13.mp3");
            funLEDonoff();
            
       } 
       
  funLEDonoff();
 }

   
void funLEDon () {
   //Serial.println("LED On");
   digitalWrite(redeyeleds, HIGH); 
	 digitalWrite(ylwmouthleds, HIGH); 
	 digitalWrite(whtmidmouthleds, HIGH); 
	 digitalWrite(bluoutermouthleds, HIGH); 
} 

void funLEDoff () {
   //Serial.println("LED Off");
   digitalWrite(redeyeleds, LOW); 
	 digitalWrite(ylwmouthleds, LOW); 
	 digitalWrite(whtmidmouthleds, LOW); 
	 digitalWrite(bluoutermouthleds, LOW); 
	 }

void funLEDonoff (){
  funLEDon();
  delay(200);
  funLEDoff();
  delay(200);
  funLEDon();
  delay(200);
  funLEDoff();
  delay(200);
  funLEDon();
  }
   
