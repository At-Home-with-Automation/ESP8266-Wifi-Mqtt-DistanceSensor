/*
  SimpleMQTTClient.ino
  The purpose of this exemple is to illustrate a simple handling of MQTT and Wifi connection.
  Once it connects successfully to a Wifi network and a MQTT broker, it subscribe to a topic and send a message to it.
  It will also send a message delayed 5 seconds later.
*/
#define TRIGPIN 12
#define ECHOPIN 14
#include "EspMQTTClient.h"

EspMQTTClient client(
  "WiFi Access Point",
  "Password",
  "Broker IP",  // MQTT Broker server ip
  "Username",   // Can be omitted if not needed
  "Password",   // Can be omitted if not needed
  "Car Distance",     // Client name that uniquely identify your device
  1883              // The MQTT port, default to 1883. this line can be omitted
);

float duration, distance;

void setup()
{
  Serial.begin(115200);

  // Optional functionalities of EspMQTTClient
  client.enableDebuggingMessages(); // Enable debugging messages sent to serial output
  client.enableHTTPWebUpdater(); // Enable the web updater. User and password default to values of MQTTUsername and MQTTPassword. These can be overridded with enableHTTPWebUpdater("user", "password").
  client.enableOTA(); // Enable OTA (Over The Air) updates. Password defaults to MQTTPassword. Port is the default OTA port. Can be overridden with enableOTA("password", port).
  client.enableLastWillMessage("TestClient/lastwill", "I am going offline");  // You can activate the retain flag by setting the third parameter to true
};

// This function is called once everything is connected (Wifi and MQTT)
// WARNING : YOU MUST IMPLEMENT IT IF YOU USE EspMQTTClient
void onConnectionEstablished()
//{
  // Subscribe to "mytopic/test" and display received message to Serial
//  client.subscribe("mytopic/test", [](const String & payload) {
//    Serial.println(payload);
//  };
//{
  // Subscribe to "mytopic/wildcardtest/#" and display received message to Serial
//  client.subscribe("mytopic/wildcardtest/#", [](const String & topic, const String & payload) {
//    Serial.println("(From wildcard) topic: " + topic + ", payload: " + payload);
//  };

  // Publish a message to "mytopic/test"
//  client.publish("Garden/Equipment/TankLevels", "This is a message"); // You can activate the retain flag by setting the third parameter to true

  // Execute delayed instructions
 // client.executeDelayed(5 * 1000, []() {
  //  client.publish("mytopic/wildcardtest/test123", "This is a message sent 5 seconds later");
//  };


{
  pinMode(ECHOPIN,INPUT);
  pinMode(TRIGPIN,OUTPUT);
}

void loop()
{
  client.loop();
 

  digitalWrite (TRIGPIN,LOW);
  delayMicroseconds(2);

  digitalWrite(TRIGPIN,HIGH);
  delayMicroseconds(20);


  digitalWrite(TRIGPIN,LOW);

  duration = pulseIn(ECHOPIN,HIGH);

  distance = (duration / 2) * 0.343;
  float value = distance/10;

  if (value <= 160.00) {

  Serial.print("distance: ");
  Serial.print(distance/10);
  }
  
  delay(100);

  String topic("Garage/Sensor/Wall Sensor");
  
  String valueStr(value);
  if (value <= 160.00) {
    boolean result = client.publish("Garage/Sensor/Wall Sensor", valueStr);
}

}
  
