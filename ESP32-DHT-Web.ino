#include <DHTesp.h>
#include <AsyncWebSocket.h>
#include <StringArray.h>
#include <SPIFFSEditor.h>
#include <ESPAsyncWebServer.h>
#include <AsyncEventSource.h>
#include <WebAuthentication.h>
#include <WebResponseImpl.h>
#include <AsyncJson.h>
#include <WebHandlerImpl.h>
#include <WiFi.h>
#include <ESPmDNS.h>
#include "index.h"

// Hostname to use for mDNS resolution.
#define HOSTNAME "esp32"

// Pin where the DHT sensor is connected.
#define DHT_PIN 23

// WiFi configuration
#define SSID "..."
#define PASSWORD "..."

// TCP server at port 80 will respond to HTTP requests
AsyncWebServer server(80);

// DHT sensor, the DHT esp library auto-detects the type.
DHTesp dht;

void handleNotFound(AsyncWebServerRequest *request)
{
  // Reply with an HTTP 404 status code and a small human readable message.
  request->send(404, "text/plain; charset=utf-8", request->url() + " not found!");
}

void handleRoot(AsyncWebServerRequest *request)
{
  // Reply with INDEX_HTML, which is the home page included through index.h
  request->send(200, "text/html; charset=utf-8", INDEX_HTML);
}

void handleSensor(AsyncWebServerRequest *request)
{
  // Create a JSON response
  AsyncJsonResponse * response = new AsyncJsonResponse();
  // Add access control header so sensor data can be loaded by third party sites.
  response->addHeader("Access-Control-Allow-Origin", "*");
  // Get the root JSON object
  JsonObject& root = response->getRoot();
  // Read temperature and humidity from the DHT sensor
  TempAndHumidity data = dht.getTempAndHumidity();
  // Store data in the JSON object
  root["temperature"] = data.temperature;
  root["humidity"] = data.humidity;
  root["uptime"] = millis();
  // Calculate and set the Content-Length for the response after we've made all required modifications.
  response->setLength();
  // Send the JSON data to the client.
  request->send(response);
}

void setup(void)
{  
  // Serial interface for debugging.
  Serial.begin(115200);

  // Connect to WiFi network
  WiFi.begin(SSID, PASSWORD);
  Serial.println("");

  // Wait for connection
  while (WiFi.status() != WL_CONNECTED) {
      delay(500);
      Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(SSID);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  // Set up mDNS responder
  while (!MDNS.begin(HOSTNAME)) {
      // Retry every 5 seconds on failure.
      Serial.println("Error setting up MDNS responder!");
      delay(5000);
  }

  // Start DHT sensor
  dht.setup(DHT_PIN);

  // Configure the HTTP server
  // Add Server header
  DefaultHeaders::Instance().addHeader("Server","ESP Async Web Server");
  // Add homage to Terry Pratchett
  DefaultHeaders::Instance().addHeader("X-Clacks-Overhead", "GNU Terry Pratchett");
  // Add HTTP routes
  server.onNotFound(handleNotFound);
  server.on("/", HTTP_GET, handleRoot);
  server.on("/sensor", HTTP_GET, handleSensor);
  // Start HTTP server
  server.begin();
  Serial.println("HTTP server started");

  // Advertise HTTP server using mDNS Service Discovery
  MDNS.addService("http", "tcp", 80);
  Serial.println("mDNS responder started");
}

// The main loop is unused, since our mDNS and HTTP servers are completely asynchronous.
void loop(void) { }

