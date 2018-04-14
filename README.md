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
1. Fill in your WiFi SSID and PASSWORD (optional: Change the HOSTNAME)
1. Connect your DHT sensor to your ESP32 and set DHT_PIN in the program to the pin used
1. Connect your ESP32 to the computer
1. Select the correct serial port in Arduino IDE
1. Upload the program
1. Open the Serial Monitor to verify that everything runs correctly
1. Disconnect the ESP32 from the computer and connect it to a power supply for standalone operation

## License and disclaimer

The 3-Clause BSD License applies to this software, see the LICENSE file