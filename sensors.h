#ifndef SENSORS
#define SENSORS

#include <AsyncJson.h>
#include <DHTesp.h>
#include "config.h"

#ifdef DHT_PIN
  // DHT sensor, the DHTesp library auto-detects the type.
  DHTesp dht;
#endif

#ifdef PIR_PIN
  portMUX_TYPE mux = portMUX_INITIALIZER_UNLOCKED;
  volatile bool pir_status;
  volatile bool pir_change_handled;
  volatile long pir_since;


  void pir_isr()
  {
    portENTER_CRITICAL(&mux);
    pir_change_handled = false;
    pir_since = millis();
    // This is probably not the best idea during an ISR... maybe register separate ISRs for RISING and FALLING?
    // Direct access to the GPIO memory would be much better in terms of speed,
    // but might cause problems when using different versions of the ESP32 chip, maybe.
    pir_status = digitalRead(PIR_PIN);
    portEXIT_CRITICAL(&mux);
  }
#endif

void setupSensors()
{
  #ifdef DHT_PIN
    // Enable the DHT sensor.
    dht.setup(DHT_PIN, DHTesp::AUTO_DETECT);
  #endif
  #ifdef PIR_PIN
    pinMode(PIR_PIN, INPUT);
    attachInterrupt(digitalPinToInterrupt(PIR_PIN), pir_isr, CHANGE);
    // Manually call the interrupt once to initialise the data:
    pir_isr();
  #endif
}

/* Read sensor values and set them in the passed JSON object.
*/
void loadSensorData(JsonObject *json)
{
  // Store data in the JSON object
  (*json)["uptime_ms"] = (unsigned long)millis();
  #ifdef DHT_PIN
    JsonObject& dhtJSON = json->createNestedObject("dht");
    // Read temperature and humidity from the DHT sensor
    TempAndHumidity data = dht.getTempAndHumidity();
    if (!isnan(data.temperature))
    {
      dhtJSON["temperature"] = data.temperature;
    }
    else
    {
      Serial.println("Could not read temperature!");
    }
    if (!isnan(data.humidity))
    {
      dhtJSON["humidity"] = data.humidity;
    }
    else 
    {
      Serial.println("Could not read humidity!");
    }
  #endif
  #ifdef PIR_PIN
    JsonObject& pirJSON = json->createNestedObject("pir");
    pirJSON["status"] = pir_status;
    pirJSON["since_ms"] = pir_since;
  #endif
}

/* Check sensors that use REMOTE_ENDPOINT_SEND_ON_CHANGE */
bool sensorsChanged() {
  bool result = false;
  #ifdef PIR_PIN
    portENTER_CRITICAL(&mux);
    result |= !pir_change_handled;
    portEXIT_CRITICAL(&mux);
  #endif
  return result;
}

void sensorChangesHandled() {
  #ifdef PIR_PIN
    portENTER_CRITICAL(&mux);
    // Uncomment this to debug the PIR sensor
    //digitalWrite(LED_BUILTIN, pir_status);
    pir_change_handled = true;
    portEXIT_CRITICAL(&mux);
  #endif
}
#endif
