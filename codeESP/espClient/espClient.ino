//#include <WiFi.h>
//#include <SocketIoClient.h>
//
//const char* ssid = "HT";
//const char* password = "Thiet123";
//const char* serverUrl = "http://localhost:3000/"; // ví dụ: http://localhost:3000
//
//WiFiClient client;
//SocketIoClient socketIO;
//
//void setup() {
//  Serial.begin(9600);
//  WiFi.begin(ssid, password);
//  while (WiFi.status() != WL_CONNECTED) {
//    delay(1000);
//    Serial.println("Connecting to WiFi...");
//  }
//  Serial.println("Connected to WiFi");
//
//  socketIO.begin(serverUrl, client); // kết nối tới server
//  socketIO.on("connect", onConnect); // đăng ký hàm xử lý sự kiện connect
//}
//
//void loop() {
//  if (WiFi.status() == WL_CONNECTED) {
//    socketIO.loop(); // xử lý các sự kiện socket
//    delay(1000);
//
//    // Gửi dữ liệu lên server
//    int sensorValue = analogRead(A0);
//    char data[50];
//    sprintf(data, "{\"sensorValue\":%d}", sensorValue);
//    socketIO.emit("sensorData", data);
//  }
//}
#include <ESP8266WiFi.h>
#include <SocketIoClient.h>

const char* ssid = "HT";
const char* password = "Thiet123";
const char* serverUrl = "http://localhost:3000/"; // ví dụ: http://localhost:3000

WiFiClient client;
SocketIoClient socketIO;

void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Sử dụng thư viện ESP8266HTTPClient thay vì thư viện WiFiClient
  socketIO.begin(serverUrl, &client); // kết nối tới server

  // Đăng ký hàm xử lý sự kiện connect
  socketIO.on("connect", []() {
    Serial.println("Connected to server");
  });
}

void loop() {
  if (WiFi.status() == WL_CONNECTED) {
    socketIO.loop(); // xử lý các sự kiện socket
    delay(1000);

    // Gửi dữ liệu lên server
    int sensorValue = 99;
    char data[50];
    sprintf(data, "{\"sensorValue\":%d}", sensorValue);

    // Sử dụng phương thức emit có tham số là const char* để phù hợp với ESP8266
    socketIO.emit("sensorData", (const char*) data);
  }
}

void onConnect() {
  Serial.println("Connected to server");
}
