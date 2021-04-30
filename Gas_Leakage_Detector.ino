#include <SoftwareSerial.h>

//LPG Leakage Detection with Alarm, SMS Alert and Automatic Valve Shutdown
//by: Jen Beatrix Maristela

SoftwareSerial SIM808(9,10);
String textForSMS;
int data = 0; 
int smokeS = A1;
int Svalve = 13; 
int orangeled = 12;


String inputString;        // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

int Control_RX = A3; // RX and TX pin for the SoftWareSerial library.
int Control_TX = A2;

//volatile boolean svalve_Detect = false; // It is a variable to give delay time to Arduino.

SoftwareSerial Control(Control_RX, Control_TX); // Define the Rx and the Tx pins to communicate with Bluetooth Module.

String Name = "Control"; // Name your module and set the password for it.
int Password = 1111; //PASS:1234
String Uart = "9600,0,0";


 
void setup()
{
  //randomSeed(analogRead(0));
  Serial.begin(9600);
  SIM808.begin(9600);
  
  Control.begin(38400); // Begin HC-05 Bluetooth module to communicate.

  pinMode(smokeS, INPUT); 
  pinMode(Svalve, OUTPUT); 
  pinMode(orangeled,OUTPUT);
  digitalWrite(Svalve, LOW); 
}
 
void loop()
{
  data = analogRead(smokeS); 
  
  Serial.print("Smoke: "); 
  Serial.println(data);   
  
if (Serial.available()) {
    Control.write(Serial.read());
}

if (Control.available()) { // If HC-05 Bluetooth module is available, Commands() has proceeded.

    char c = Control.read();
    Serial.println(c); // Control the characters that are set by the app using the terminal.
    //Commands(c);
    Serial.write(c);
    }
 
if (data >= 150){
  digitalWrite(Svalve, HIGH);
  digitalWrite(orangeled, HIGH);
  Serial.println("Valve CLOSED");
  textForSMS = "\nGAS OR SMOKE DETECTED";
  Serial.println(textForSMS);
  //sendSMS(textForSMS);
  
  SIM808.println("AT+CMGF=1");                     // AT command to send SMS message
  delay(250);
  SIM808.println("AT+CMGS=\"+639235853916\"\r");  // recipient's mobile number, in international format
  delay(250);
  SIM808.println("WARNING: Gas Leakage detected");                         // message to send
  SIM808.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(250); 
  Serial.println("Message sent."); 
  
} 
 delay(500);
}
