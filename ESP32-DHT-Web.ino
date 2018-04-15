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
#include "version.h"
#include "index.h"
#include "config.h"

// TCP server at port HTTP_PORT will respond to HTTP requests
AsyncWebServer server(HTTP_PORT);

// DHT sensor, the DHTesp library auto-detects the type.
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

void configureAP()
{
  if (WIFI_MODE == WIFI_AP || WIFI_MODE == WIFI_AP_STA)
  {
    Serial.println("\nAttempting to create WiFi access point " + String(AP_SSID) + "...");
    // Disable the default STA configuration.
    WiFi.enableAP(false);
    IPAddress ipaddress = IPAddress();
    IPAddress gateway = IPAddress();
    IPAddress netmask = IPAddress();
    if (!ipaddress.fromString(AP_IP_ADDRESS))
    {
      Serial.println("Could not parse AP_IP_GATEWAY");
      return;
    }
    if (!gateway.fromString(AP_IP_GATEWAY))
    {
      Serial.println("Could not parse AP_IP_ADDRESS");
      return;
    }
    if (!netmask.fromString(AP_IP_NETMASK))
    {
      Serial.println("Could not parse AP_IP_NETMASK");
      return;
    }
    // Try to enable the custom AP configuration
    if (!WiFi.softAP(AP_SSID, AP_PASSWORD))
    {
      Serial.println("Failed to configure AP. Check AP_SSID and AP_PASSWORD configuration.");
      // Disable AP on failure
      WiFi.enableAP(false);
      return;
    }
    Serial.println("Created WiFi AP: " + String(AP_SSID));
    if (!WiFi.softAPConfig(ipaddress, gateway, netmask))
    {
      Serial.println("Failed to configure AP network settings. Check AP_IP_ADDRESS, AP_IP_GATEWAY, and AP_IP_NETMASK configuration.");
      // Disable AP on failure      
      WiFi.enableAP(false);
      return;
    }
    Serial.println("AP IP address: " + String(AP_IP_ADDRESS));
  }
  else
  {
    // Disconnect and disable Access Point
    WiFi.softAPdisconnect(true);
    Serial.println("\nWiFi access point disabled.");
  }
}

void configureSTA()
{
  if (WIFI_MODE == WIFI_STA || WIFI_MODE == WIFI_AP_STA)
  {
    Serial.println("\nAttempting to connect to " + String(STA_SSID) + "...");
    WiFi.enableSTA(true);
    // Connect to WiFi network
    WiFi.begin(STA_SSID, STA_PASSWORD);
    long abort_time = millis() + STA_CONNECT_TIME;
    // Wait for connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        if (millis() > abort_time)
        {
          Serial.println("\nCould not connect to " + String(STA_SSID) + " within " + String(STA_CONNECT_TIME/1000) + " seconds.");
          return;
        }
        delay(500);
    }
    Serial.print("\nConnected to ");
    Serial.println(STA_SSID);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else
  {
    // Disconnect and disable Station
    WiFi.disconnect(true);
    Serial.println("\nWiFi Station disabled.");
  }
}

void startWiFi()
{
  WiFi.mode(WIFI_MODE);
  configureAP();
  configureSTA();
  Serial.println();
}

void setup(void)
{  
  // Serial interface for debugging.
  Serial.begin(115200);
  Serial.println("ESP32-DHT-Web version " + String(VERSION_NUMBER));
  // Initialise WiFi
  startWiFi();

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
  MDNS.addService("http", "tcp", HTTP_PORT);
  Serial.println("mDNS responder started");
}

// The main loop is unused, since our mDNS and HTTP servers are completely asynchronous.
void loop(void) { }

