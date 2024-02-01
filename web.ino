#include <WiFi.h>
#include <WebServer.h>

#define RXp2 16
#define TXp2 17


const char* ssid = "water";  
const char* password = "12345678"; 

WebServer server(80);


                             
String s1;
int s3;
int s2;
 
void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, RXp2, TXp2);
  delay(100);
               

  Serial.println("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
  delay(1000);
  Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected..!");
  Serial.print("Got IP: ");  Serial.println(WiFi.localIP());

  server.on("/", handle_OnConnect);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP server started");

}
void loop() {
  
  server.handleClient();
  
}

void handle_OnConnect() {
  s1 = Serial2.readString();
  s2 =s1.toInt();
  if(s2==4){
    s3=1;
  }
  else{
    s3 = 1+ s2;
  }
  
  server.send(200, "text/html", SendHTML(s2,s3));

}

void handle_NotFound(){
  server.send(404, "text/plain", "Not found");
}

  String SendHTML(int s2,int s3){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>ESP32 Weather Report</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;}\n";
  ptr +="p {font-size: 24px;color: #444444;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<div id=\"webpage\">\n";
  ptr +="<h1>ESP32 Weather Report</h1>\n";
  
  ptr +="<p>CURRENT SERIAL:";
  ptr +=s2;
  ptr +=".</p>";
  ptr +="<p>NEXT SERIAL: ";
  ptr +=s3;
  ptr +=".</p>";
  
  ptr +="</div>\n";
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}