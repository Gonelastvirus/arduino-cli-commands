#include <HTTPClient.h>
#include <Arduino_JSON.h>
#include <HardwareSerial.h>
#include <WiFi.h>
#include <WiFiManager.h>
HardwareSerial MySerial(2);
int node;
double temp;
double hum;
String readings;

void setup()
{
	Serial.begin(115200);
	WiFiManager manager;
	bool success = manager.autoConnect("SmartAG", "password");
	if (!success)
	{
		Serial.println("Failed to connect");
	}
	else
	{
		Serial.println("Connected");
	}
	MySerial.begin(115200, SERIAL_8N1, 16);
}

void loop()
{

	while (MySerial.available())
	{
		String RxdChar = MySerial.readString();
		JSONVar myObject = JSON.parse(RxdChar);
		node = myObject["node"];
		temp = myObject["temp"];
		hum = myObject["hum"];
		// convert string into json
		JSONVar jsonReadings;
		jsonReadings["node"] = node;
		jsonReadings["temp"] = temp;
		jsonReadings["hum"] = hum;
		readings = JSON.stringify(jsonReadings);
		Serial.println(readings); // printing json
		send();
	}
}
void send()
{
	const char *server = "http://api.thingspeak.com/update";
	String my_Api_key = "1QK63KXC70LIR6VM";
	WiFiClient wifiClient;
	HTTPClient http;
	http.begin(wifiClient, server);
	// Specify content-type header
	http.addHeader("Content-Type", "application/x-www-form-urlencoded");
	String httpRequestData = "api_key=" + my_Api_key + "&field1=" + String(node) + "&field2=" + String(hum) + "&field3=" + String(temp);
	int httpResponseCode = http.POST(httpRequestData);
}
