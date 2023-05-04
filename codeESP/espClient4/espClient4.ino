#include <WebSocketsClient.h>
#include <SocketIoClient.h>
SocketIoClient socketIO;
uint64_t messageTimestamp;

void messageEventHandler(const char * payload, size_t length) {
 Serial.printf("got message: %s\n", payload);
}

void setup() {
 WiFi.begin("HT", "Thiet123");
 Serial.print("Connecting");
 
 while (WiFi.status() != WL_CONNECTED)
 {
  delay(500);
  Serial.print(".");
 }
 
 Serial.println();

 Serial.print("Connected, IP address: ");
 Serial.println(WiFi.localIP());

  // server address, port and URL
  socketIO.begin("the ip address or domain", 3005);
  // event handler for the event message
  socketIO.on("reply",messageEvenetHandler);
}



void loop() {  
  socketIO.loop();
  uint64_t now = millis();
  if(now - messageTimestamp > 6000) {
    messageTimestamp = now;
    // Send event     
  socketIO.emit("message", "\"this is a message from the client\"");   
  }    
}
