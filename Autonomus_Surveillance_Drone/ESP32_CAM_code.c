#include "esp_camera.h"
#include <WiFi.h>
// Replace with your network
credentials
const char* ssid = "YOUR_SSID";
const char* password =
"YOUR_PASSWORD";
// Define camera model settings (e.g.,
for AI Thinker module)
#define
CAMERA_MODEL_AI_THINKER
#include "camera_pins.h"
WiFiServer server(80);
void setup() {
Serial.begin(115200);
// Connect to Wi-Fi
WiFi.begin(ssid, password);
while (WiFi.status() !=
WL_CONNECTED) {
delay(1000);
Serial.println("Connecting to
WiFi...");
}
Serial.println("Connected to WiFi");
// Start the camera
camera_config_t config;
config.ledc_channel =
LEDC_CHANNEL_0;
config.ledc_timer =
LEDC_TIMER_0;
config.pin_d0 = 0;
config.pin_d1 = 1;
config.pin_d2 = 2;
config.pin_d3 = 3;
config.pin_d4 = 4;
config.pin_d5 = 5;
config.pin_d6 = 6;
config.pin_d7 = 7;
config.pin_xclk = 21;
config.pin_pclk = 22;
config.pin_vsync = 25;
config.pin_href = 23;
config.pin_sscb_sda = 26;
config.pin_sscb_scl = 27;
config.pin_pwdn = -1;
config.pin_reset = -1;
config.xclk_freq_hz = 20000000;
config.pixel_format =
PIXFORMAT_JPEG;
if (esp_camera_init(&config) !=
ESP_OK) {
Serial.println("Camera
initialization failed!");
return;
}
// Start the server
server.begin();
Serial.print("Camera Stream Ready!
IP Address: ");
Serial.println(WiFi.localIP());
}
void loop() {
WiFiClient client =
server.available();
if (!client) {
return;
}
Serial.println("New Client
Connected");
// HTTP response header
client.println("HTTP/1.1 200 OK");
client.println("Content-Type:
multipart/x-mixed-replace;
boundary=frame");
client.println();
// Stream video
while (client.connected()) {
camera_fb_t *fb =
esp_camera_fb_get();
if (!fb) {
Serial.println("Frame buffer is
NULL");
return;
}
client.println("--frame");
client.println("Content-Type:
image/jpeg");
client.println("Content-Length: " +
String(fb->len));
client.println();
client.write(fb->buf, fb->len);
client.println();
esp_camera_fb_return(fb);
}
client.stop();
Serial.println("Client
Disconnected");
}

