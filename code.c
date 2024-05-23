#define BLYNK_TEMPLATE_ID "TMPL3xhq969ju"
#define BLYNK_TEMPLATE_NAME "Wheelchair Fall Detection IOT"
#define BLYNK_PRINT Serial
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>
#include <Blynk.h>
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#define BLYNK_AUTH_TOKEN "oAu1zirB9C-v8QRutJA3PhSkgUFaEiLr"
char auth[] = "oAu1zirB9C-v8QRutJA3PhSkgUFaEiLr";    
   // You should get Auth Token in the Blynk App.
char ssid[] = "FALL";                     
  // Your WiFi credentials.
char pass[] = "12345678";
int red = D5;
int green = D6;
int buzz = D7;
Adafruit_MPU6050 mpu;
void setup(void) 
{
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(red,OUTPUT);
  pinMode(green,OUTPUT);
  pinMode(buzz,OUTPUT);
  while (!Serial)
    delay(10);
 // will pause Zero, Leonardo, etc until serial console opens
  Serial.println("Adafruit MPU6050 test!");
  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");
  Serial.println("");
  delay(100);
}
void loop() {
Blynk.run();
  /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  /* Print out the values */
  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");
Blynk.virtualWrite(V0, a.acceleration.x);
Blynk.virtualWrite(V1, a.acceleration.y);
Blynk.virtualWrite(V2, temp.temperature);
  Serial.println("");
  delay(500);
if(a.acceleration.x > 5 || a.acceleration.x < -5 || a.acceleration.y >5 || a.acceleration.y < -5)
{
  analogWrite(red,255);
  analogWrite(buzz,255);
  analogWrite(green,0);
   Blynk.email("sampathirakeshreddy@gmail.com", "Alert", "Fall is Detected!! Please Help Me!");
    Blynk.logEvent("fall_alert","Fall is Detected!! Please Help Me!");
  delay(3000);
    analogWrite(red,0);
  analogWrite(buzz,0);
  analogWrite(green,255);
}
else
{
   analogWrite(red,0);
  analogWrite(buzz,0);
  analogWrite(green,255);
}
  
}
