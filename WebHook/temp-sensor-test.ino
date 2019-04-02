// This #include statement was automatically added by the Particle IDE.
#include "Adafruit_DHT_Particle.h"

// Example testing sketch for various DHT humidity/temperature sensors
// Based from code implementation by ladyada, public domain

#define DHTPIN D2     // what pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11		// DHT 11 

// Connect pin 1 (on the left) of the sensor to 3V3 USB power dependent
// Connect pin 2 of the sensor to whatever your DHTPIN is
// Connect pin 4 (on the right) of the sensor to GROUND

DHT dht(DHTPIN, DHTTYPE);

void setup() {
	Serial.begin(9600); 
	Serial.println("DHT11 test!");
	Particle.publish("state", "DHT11 test start");

	dht.begin();
	delay(2000);
}

void loop() {

// Read temperature as Celsius
	float t = dht.getTempCelcius();

  
// Check if any reads failed and exit early (to try again).
	if (isnan(t)) {
		Serial.println("Failed to read from DHT sensor!");
		return;
	}

	
	Serial.print("Temp: "); 
	Serial.print(t);
	Serial.print("*C ");
	Serial.println(Time.timeStr());
	
	Particle.publish("readings", String::format("{\"Temp(°C)\": %4.2f}", t));       //publish to Web Console
	Particle.publish("temp", String(t), PRIVATE);                                   //publish to ThingSpeak
	delay(30000);
	
}