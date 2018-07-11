#ifndef SENSORS
#define SENSORS

#include <AsyncJson.h>
#include <DHTesp.h>
#include "config.h"

// DHT sensor, the DHTesp library auto-detects the type.
DHTesp dht;

void setupSensors()
{
    // Enable the DHT sensor.
    dht.setup(DHT_PIN);
}

/* Read sensor values and set them in the passed JSON object.
*/
void loadSensorData(JsonObject *json)
{

  // Read temperature and humidity from the DHT sensor
  TempAndHumidity data = dht.getTempAndHumidity();
  // Store data in the JSON object
  (*json)["uptime_ms"] = (unsigned long)millis();
  if (!isnan(data.temperature))
  {
    (*json)["temperature"] = data.temperature;
  }
  else
  {
    Serial.println("Could not read temperature!");
  }
  if (!isnan(data.humidity))
  {
    (*json)["humidity"] = data.humidity;
  }
  else 
  {
    Serial.println("Could not read humidity!");
  }
}

#endif