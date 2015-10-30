# IoT_Pumpkin

here is final project:
https://www.youtube.com/watch?v=aAMmTdFi28M

Brief:
The IoT pumpkin will sense distance of the nearest object and play Mp3 clips and blink LED lights based on the distance. Once object comes very close i.e. <30 cms, it will use AWS IoT services to send email to owner (instead of email, you can configure AWS IoT Topic to send SMS, invoke Lambda, insert records in Dynamo db etc). 
This fun project is to showcase how to connect simple IoT device to AWS IoT and help educate on understanding capabilities of Arduino Yun and AWS IoT.  

I followed Arduino tutorial from Lady Ada at 
https://learn.adafruit.com/halloween-pumpkin/overview
I appreciate her efforts to build this project. It was very helpful.
This project uses Arduino Uno and Wave Sheild and speakers to play .wave files.  Since I am planning to showcase fun IoT project,  I am using Arduino Yun, I thought of using Yun’s inbuilt MicroSD card and attache external speaker to Yun’s USB. This makes the project lot simpler and no need to solder anything.

What you need:
Arduino Yun
Maxbotix Ultrasonic Rangefinder - LV-EZ1
Seven diffused Red 10mm LED - two for eyes and four for mouth
Hook-up Wire
Three 47 ohm resistor and one 150 ohm resistor

You can get those things at amazon.com or Adafruit.com
Plastic pumpkin
USB Speaker
AWS account
MP3 clips (please make sure its in mono format and not stereo, I couldn’t get stereo files working for some reason)

Setup:
Install AWS IOT and setup Arduino Yun as per instructions here 
https://github.com/aws/aws-iot-device-sdk-arduino-yun


Update Yun to play sound files:

In order to play sound files, yun needs to be updated with komod-usb-audio and modplay. Here are the instructions to install those updates on yun.

open an ssh session to the yun, and type:

opkg update
opkg install kmod-usb-audio
opkg install madplay


Connect Sensor:
The maxbotix Sensor is easy to use. Connect three wires: Power, Ground and Analog signal as shown.
https://learn.adafruit.com/system/assets/assets/000/008/138/original/projects_sonarprep.jpg?
Connec other end of wires to Yun analog board
Ground goes to Yun analog ground pin
Power goes to 5v power and 
Analog goes to analog in 1
Connect LEDs:
Connect LEDs and resistors are per this diagram 
https://learn.adafruit.com/system/assets/assets/000/008/149/original/projects_pumpkinleds.gif?1396861359
Connect USB speaker to the Yun USB out
Load Mp3 files to MicroSD card and insert the card into. Create nine MP3 files, name the 1.mp3, 2.mp3 so on, make sure those files are in Mono format and not Stereo. You can convert your files to mono using online tools such as http://audio.online-convert.com/convert-to-mp3

Create AWS IoT thing https://aws.amazon.com/iot/
Download certificates when prompted. The certificates needs to be kept at .\cert directory of your project.
Download source code:
Download IoT pumpkin source code to your yun samples directory, as per AWS IoT SDK install instructions, its user/Documents/Arduino/libraries/AWS-IoT-Arduino-Yun-Library/examples/<your directory>
Update cert files locations:
You need three certs: AWS root can be downloaded from https://www.symantec.com/content/en/us/enterprise/verisign/roots/VeriSign-Class%203-Public-Primary-Certification-Authority-G5.pem
Rename it to root-CA.cert
Edit and update aws_iot_config.h file with your IOT information and certificate names
// Copy and paste your configuration into this file
//===============================================================
#define AWS_IOT_MQTT_HOST "XXXXXXXX.iot.us-west-2.amazonaws.com"
// your endpoint
#define AWS_IOT_MQTT_PORT 8883
// your port
#define AWS_IOT_CLIENT_ID      "myYun"
// your client ID
#define AWS_IOT_MY_THING_NAME "myYun"
// your thing name
#define AWS_IOT_ROOT_CA_FILENAME "root-CA.crt"
// your root-CA filename
#define AWS_IOT_CERTIFICATE_FILENAME "mything.pem.crt"
// your certificate filename
#define AWS_IOT_PRIVATE_KEY_FILENAME "mything.pem.key"
// your private key filename
//===============================================================
thing and topic name, in this project Topic name is Topic1 but you can create your own Thing and then topic to trigger Lambda function, SNS, S3 etc.

My apologies, the instructions are bit rough, I did not have much free time for this project. I just wanted to show how easy it is to use AWS IoT with Ardunio Yun and create amazing IoT projects.
Please let me know if you have any questions.
Hopefully Christmas lights will be lot smarter this year :-). 
