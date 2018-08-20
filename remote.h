#ifndef REMOTE
#define REMOTE

#include <ESPAsyncWebServer.h>
#include <HTTPClient.h>
#include <AsyncJson.h>
#include "config.h"
#include "sensors.h"

// Use 60 seconds default timeout if not defined in config.h
#ifndef REMOTE_ENDPOINT_TIMEOUT
  #define REMOTE_ENDPOINT_TIMEOUT 60
#endif

HTTPClient http;

void setupRemote()
{
    // Create HTTP client to connect to remote
    http.begin(REMOTE_ENDPOINT_URI);
    // Keep TCP stream open if possible to reduce overhead.
    http.setReuse(true);
}

/** Read sensor data and post it to the remote.
 * 
 * loadSensorData() must be defined.
 * REMOTE_ENDPOINT_URI must be defined.
 * 
 * When this function is called in the context of an AsyncWebServerRequest, the request can be passed along and will
 * be correctly handled.
 * 
 * To post data outside the context of a response, simply pass NULL.
*/
int postRemote(AsyncWebServerRequest *request)
{
  http.addHeader("Content-Type", "application/json");
  DynamicJsonBuffer jsonBuffer;
  JsonObject &json = jsonBuffer.createObject();
  loadSensorData(&json);
  String poststring = String();
  json.printTo(poststring);
  Serial.println("HTTP POST to " + String(REMOTE_ENDPOINT_URI));
  Serial.println(poststring);
  int responseCode = http.POST(poststring);
  if (responseCode > 0)
  {
    String response = http.getString();
    Serial.println("Remote HTTP response:");
    Serial.println("HTTP: " + String(responseCode) + " " + response);
    if (request != NULL)
    {
      request->send(responseCode, "text/plain; charset=utf-8", response);
    }
  }
  else
  {
    Serial.println("Failed to send data to remote");
    Serial.println("HTTP: " + String(responseCode) + ": " + http.errorToString(responseCode));
    if (request != NULL)
    {
      request->send(responseCode);
    }
  }
  // End HTTP connection (but TCP connection should be reused)
  http.end();
  return responseCode;
}

/** Read sensor data and post it to the remote.
 * 
 * loadSensorData() must be defined.
 * REMOTE_ENDPOINT_URI must be defined.
 */
int postRemote() {
  return postRemote(NULL);
}
#endif