#include <SocketIoClient.h>
#include<ESP8266WiFi.h>
#include<Arduino.h>
#define USER_SERIAL Serial 

SocketIoClient socket;
const char* ssid = "HT";
const char* pass = "Thiet123";
void setup() {
  pinMode(2, OUTPUT);
  USER_SERIAL.begin(115200);
  searchWifi();
  initWiFi();
  socket.on("message", handleMessage);
  socket.on("light_on",handleMessage);
  socket.emit("message","hello from esp");
  socket.begin("192.168.0.102",3000);
  
 
  
}

void loop() {
  digitalWrite(2,LOW);
  digitalWrite(2,HIGH);
  socket.loop();

  
}
void handleMessage(const char* message, size_t length){
  USER_SERIAL.println(message);
}

  void initWiFi(){
      WiFi.mode(WIFI_STA);
      WiFi.hostname("ESP-host");
      WiFi.setPhyMode(WIFI_PHY_MODE_11G);
      WiFi.enableInsecureWEP(true);
      WiFi.begin(ssid,pass);
      while(WiFi.status() != WL_CONNECTED){
        USER_SERIAL.print(".");
        delay(1000);
      }
      USER_SERIAL.print("");
      USER_SERIAL.println("WiFi connected");
      USER_SERIAL.print("IP Address: ");
      USER_SERIAL.println(WiFi.localIP());
      WiFi.setAutoReconnect(true);
      WiFi.persistent(true);
  
  
  }
 void searchWifi(){
  int numberOfNetwork = WiFi.scanNetworks();
  USER_SERIAL.println("-----");
  for ( int i = 0; i< numberOfNetwork;i++){
    USER_SERIAL.print("Network name: ");
    USER_SERIAL.println(WiFi.SSID(i));
    USER_SERIAL.print("Signal Strength: ");
    USER_SERIAL.println(WiFi.RSSI(i));
    USER_SERIAL.println("-------------");
  }
}
