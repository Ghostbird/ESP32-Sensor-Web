# ESP32 Sensor Web

Web view for sensors connected to an ESP32.

*Note:* The repository as is, is programmed for a DHT-11 or DHT-22 sensor (tested with both). However, it is not about the DHT sensor. If you modify the sensors.h file and the index.h webpage, it will work for any sensors that can be connected to an ESP32.

## Setup Arduino IDE

1. Install [ESP32 support](https://github.com/espressif/arduino-esp32#installation-instructions)
1. Install the required libraries:
    * DHTesp by beegee_tokyo through Arduino IDE's Library Manager
    * [ESPAsyncTCP](https://github.com/me-no-dev/ESPAsyncTCP)
    * [ESPAsyncWebServer](https://github.com/me-no-dev/ESPAsyncWebServer)

## Running

1. Download the repository
1. Open the .ino file in Arduino IDE
1. Connect your DHT sensor to your ESP32
1. Set the WiFi, HTTP and sensor connection configuration in config.h
1. Connect your ESP32 to the computer
1. Select the correct serial port in Arduino IDE
1. Upload the program
1. Open the Serial Monitor to verify that everything runs correctly
1. Disconnect the ESP32 from the computer and connect it to a power supply for standalone operation

## Changelog

### Version 0.3.1

* Bugfix: Make INO file name match the repository name to avoid Arduino IDE errors.

### Version 0.3

* Feature: All sensor specific code has been moved to a separate file `sensors.h`. This means that the main .ino program does not need any modifications to work with other sensors than the DHT-11 or DHT-22.
* Feature: Configurable periodic posts to a remote URL.
    While this library was originally written to support systems that periodically request data from this server,
    it now also supports system that only offer an endpoint where the data can be periodically HTTP POSTed.

### Version 0.2.1

* Bugfix: Serial interface no longer prints that it is attempting to connect to the configured STA_SSID when WiFi is not in STA mode.
* Bugfix: mDNS now advertises the http server on the configured HTTP_PORT instead of port 80.

### Version 0.2

* Add version numbering
* Move configuration to separate file
* Add WiFi mode configuration
  * Disable, customise and/or secure the WiFi access point
  * Disable the WiFi station

### Version 0.1

* First release

## License and disclaimer

The 3-Clause BSD License applies to this software, see the LICENSE file
