# ESP32 DHT Web

Web view for a DHT temperature and humidity sensor connected to an ESP32.

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