#include <SoftwareSerial.h>
SoftwareSerial SIM808(9,10);
String textForSMS;
int data = 0; 
int Smokes = A1;
int Solenoidvalve = 13; 
int orangeled = 12;

//String inputString;        // a string to hold incoming data
//boolean stringComplete = false;  // whether the string is complete

int Control_RX = A3; 
int Control_TX = A2;

//SoftwareSerial Control(Control_RX, Control_TX); // Define the Rx and the Tx pins to communicate with Bluetooth Module.
//
//String Name = "Control"; // Name your module and set the password for it.
//int Password = 1111; //PASS:1234
//String Uart = "9600,0,0";


 
void setup()
{
  Serial.begin(9600);
  SIM808.begin(9600);
  
  //Control.begin(38400); // Begin HC-05 Bluetooth module to communicate.

  pinMode(Smokes, INPUT); 
  pinMode(Solenoidvalve, OUTPUT); 
  pinMode(orangeled,OUTPUT);
  digitalWrite(Solenoidvalve, LOW); 
}
 
void loop()
{
  data = analogRead(Smokes); 
  Serial.print("Smoke: "); 
  Serial.println(data);   
  
if (Serial.available()) {
    Control.write(Serial.read());
}

//if (Control.available()) { // If HC-05 Bluetooth module is available, Commands() has proceeded.
//
//    char c = Control.read();
//    Serial.println(c); // Control the characters that are set by the app using the terminal.
//    //Commands(c);
//    Serial.write(c);
//    }
 
if (data >= 150){
  digitalWrite(Solenoidvalve, HIGH);
  digitalWrite(orangeled, HIGH);
  Serial.println("Valve CLOSED");
  textForSMS = "\nGAS OR SMOKE DETECTED";
  Serial.println(textForSMS);
  //sendSMS(textForSMS);
  
  SIM808.println("AT+CMGF=1");                     
  delay(250);
  SIM808.println("AT+CMGS=\"+639235853916\"\r");  
  delay(250);
  SIM808.println("WARNING: Gas Leakage detected");                         
  SIM808.println((char)26);                        // End AT command with a ^Z, ASCII code 26
  delay(250); 
  Serial.println("Message sent."); 
  
} 
 delay(500);
}

//void Change_BluetoothModule_Defaults() { 
//
//  Control.print("AT+NAME"); // Change the name.
//  Control.println(Name);
//  Serial.print("Name is changed: ");
//  Serial.println(Name);
//  delay(2000);
//  Control.print("AT+PSWD"); // Change the password.
//  Control.println(Password);
//  Serial.print("Password is changed: ");
//  Serial.println(Password);
//  delay(2000);
//  Control.print("AT+UART"); // Change the baud rate. If the Bluetooth module is a HC-05, the default value of the baud rate is 38400.
//  Control.println(Uart);
//  Serial.print("Baud rate is set: ");
//  Serial.println(Uart);
//  delay(2000);
//  Serial.println("Task is completed."); // You can see whether the task is completed correctly or not using the terminal.
//}

//void serialEvent() {
//  while (Control.available()) {
//    // get the new byte:
//    int inChar = Control.read();
//    // add it to the inputString:
//    inputString += inChar;
//    // if the incoming character is a newline, set a flag
//    // so the main loop can do something about it:
//    if (inChar == '\n') {
//      stringComplete = true;
//    }
//  }
}