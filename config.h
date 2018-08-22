#include <WiFiType.h>
// Hostname to use for mDNS resolution.
#define HOSTNAME "esp32"

// Pin where the DHT sensor is connected. (comment to disable)
#define DHT_PIN 22

// Pin where the PIR sensor is connected. (comment to disable)
#define PIR_PIN 27

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
#define AP_PASSWORD "secretive"       // 8 - 63 characters. Use NULL (without quotes) to create an unsecured network
#define AP_IP_ADDRESS "10.0.0.1"      // IP address of the device on it's own WiFi network
#define AP_IP_GATEWAY "10.0.0.1"      // Gateway address of the device's WiFi network. Normally identical to AP_IP_ADDRESS
#define AP_IP_NETMASK "255.255.255.0" // Netmask of the device's WiFi network

// HTTP configuration
#define HTTP_PORT 80  // Port number to use for HTTP server

// Remote configuration
// Endpoint URL to post the data to. Uncomment to enable this functionality.
//#define REMOTE_ENDPOINT_URI "https://httpbin.org/post"
/* Transmission timing controls:
 * Note that REMOTE_ENDPOINT_INTERVAL and REMOTE_ENDPOINT_SEND_ON_CHANGE can both be active!
 * In this case a transmission on change will reset the INTERVAL
 * If INTERVAL is not defined, the SEND_ON_CHANGE may still be used to send only on changes.
 */
// Interval in seconds
#define REMOTE_ENDPOINT_INTERVAL 60
// For some sensors (e.g. PIR) it is desirable to send an update immediately on change.
#define REMOTE_ENDPOINT_SEND_ON_CHANGE