##Accelerometer (ADXL 335)
#include <math.h>
const int x_out = A1; /* connect x_out of module to A1 of UNO board */
const int y_out = A2; /* connect y_out of module to A2 of UNO board */
const int z_out = A3; /* connect z_out of module to A3 of UNO board */
void setup() {
Serial.begin(9600);
}
void loop() {
int x_adc_value, y_adc_value, z_adc_value;
double x_g_value, y_g_value, z_g_value;
double roll, pitch, yaw;
x_adc_value = analogRead(x_out); /* Digital value of voltage on x_out pin */
y_adc_value = analogRead(y_out); /* Digital value of voltage on y_out pin */
z_adc_value = analogRead(z_out); /* Digital value of voltage on z_out pin */
Serial.print("x = ");
Serial.print(x_adc_value);
Serial.print("\t\t");
Serial.print("y = ");
Serial.print(y_adc_value);
Serial.print("\t\t");
Serial.print("z = ");
Serial.print(z_adc_value);
Serial.print("\t\t");
delay(1000);
x_g_value = ( ( ( (double)(x_adc_value * 5)/1024) - 1.65 ) / 0.330 ); /* Acceleration in
x-direction in g units */
delay(1000);
y_g_value = ( ( ( (double)(y_adc_value * 5)/1024) - 1.65 ) / 0.330 ); /* Acceleration in ydirection
in g units */
delay(1000);
z_g_value = ( ( ( (double)(z_adc_value * 5)/1024) - 1.80 ) / 0.330 ); /* Acceleration in zdirection
in g units */
delay(1000);
roll = ( ( (atan2(y_g_value,z_g_value) * 180) / 3.14 ) + 180 ); /* Formula for roll */
pitch = ( ( (atan2(z_g_value,x_g_value) * 180) / 3.14 ) + 180 ); /* Formula for pitch */
//yaw = ( ( (atan2(x_g_value,y_g_value) * 180) / 3.14 ) + 180 ); /* Formula for yaw */
Serial.print("Roll = ");
Serial.print(roll);
Serial.print("\t");
Serial.print("Pitch = ");
Serial.print(pitch);
Serial.print("\n\n");
delay(1000);
}

##GPS
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
void setup()
{
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
delay(100);
}
void loop()
{
if (Serial.available()>0)
switch(Serial.read())
{
case 's':
SendMessage();
break;
case 'd':
DialCall();
break;
}
if (mySerial.available()>0)
Serial.write(mySerial.read());
}
void SendMessage()
{
mySerial.println("AT+CMGF=1\r"); //Sets the GSM Module in Text Mode
delay(1000); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"8825413527\"\r"); // Replace x with mobile number
delay(1000);
mySerial.println("I am SMS from GSM");// The SMS text you want to send
delay(100);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(1000);
}
void DialCall()
{
mySerial.println("ATD8248469940;"); // ATDxxxxxxxxxx; -- watch out here for semicolon at the
end!!
delay(100);
}

##GSM
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11); // TX, RX
void setup()
{
// Open serial communications and wait for port to open:
Serial.begin(9600);
Serial.println("Calling through GSM Modem");
// set the data rate for the SoftwareSerial port
mySerial.begin(9600);
delay(2000);
mySerial.println("ATD8825413527;");
Serial.println("Called ATD8825413527");
}
void loop() // run over and over
{
// print response over serial port
if (mySerial.available())
Serial.write(mySerial.read());
}
##Impact Sensor
int button=2;//Define pin for the OUT pin of the sensor
#define BUZ 7
#include <SoftwareSerial.h>
SoftwareSerial mySerial(10, 11);
void setup() {
pinMode(button,INPUT);//Set the sensor pin as INPUT
Serial.begin(9600);//Set baud rate for serial communication
Serial.println("Hello!");//print no collision
mySerial.begin(9600); // Setting the baud rate of GSM Module
Serial.begin(9600); // Setting the baud rate of Serial Monitor (Arduino)
delay(100);
pinMode(BUZ, OUTPUT);
}
void loop()
{
if(digitalRead(button)==LOW)//If switch is not pressed
{
Serial.println("Collision");//print collision
delay(3);
Page17
SendMessage();
Serial.write(mySerial.read());
buzzzzz();
exit(0);
}
else if(digitalRead(button)==HIGH)//If switch is pressed
{
Serial.println("No Collision");//print collision
delay(100);
}
else
Serial.println("No Data");
delay(100);
}
void buzzzzz()
{
while(true){
digitalWrite(BUZ, HIGH);
}
}
void SendMessage()
{
mySerial.println("AT+CMGF=1"); //Sets the GSM Module in Text Mode
delay(500); // Delay of 1000 milli seconds or 1 second
mySerial.println("AT+CMGS=\"8248469940\"\r"); // Replace x with mobile number
delay(500);
mySerial.println("I am dying please help me");// The SMS text you want to send
delay(500);
mySerial.println((char)26);// ASCII code of CTRL+Z
delay(100);
}
