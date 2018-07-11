#include <WiFiType.h>
// Hostname to use for mDNS resolution.
#define HOSTNAME "esp32"

// Pin where the DHT sensor is connected.
#define DHT_PIN 23

// WiFi mode configuration (uncomment exactly one)
//#define WIFI_MODE WIFI_OFF    // No WiFi at all. (Mainly for debugging purposes)
//#define WIFI_MODE WIFI_AP     // Access point mode (Create own WiFi network)
//#define WIFI_MODE WIFI_STA    // Station mode (Connect to WiFi network)
#define WIFI_MODE WIFI_AP_STA // Both Access point and station


// WiFi STA configuration
#define STA_SSID "........"
#define STA_PASSWORD "........"
#define STA_CONNECT_TIME 60000 // Abort attempts to connect to STA after so many milliseconds

// WiFi AP configuration
#define AP_SSID "ESP32DHTWeb"         // 1 - 63 characters
#define AP_PASSWORD "secretive"       // 8 - 63 characters (Use NULL to create an unsecured network)
#define AP_IP_ADDRESS "10.0.0.1"      // IP address of the device on it's own WiFi network
#define AP_IP_GATEWAY "10.0.0.1"      // Gateway address of the device's WiFi network. Normally identical to AP_IP_ADDRESS
#define AP_IP_NETMASK "255.255.255.0" // Netmask of the device's WiFi network

// HTTP configuration
#define HTTP_PORT 80  // Port number to use for HTTP server

// Remote configuration
// Endpoint URL to post the data to. Uncomment the next line to enable this functionality.
//#define REMOTE_ENDPOINT_URI "https://httpbin.org/post"
// Interval in seconds
#define REMOTE_ENDPOINT_INTERVAL 60