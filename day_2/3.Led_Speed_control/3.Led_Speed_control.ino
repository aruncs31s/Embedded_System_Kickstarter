// source : https://randomnerdtutorials.com/esp32-web-server-arduino-ide/
#include <WiFi.h>

// change the credential according to your needs
const char *ssid = "802.11";
const char *psswd = "12345678p";

// Set portnumber to 80
WiFiServer server(80);

String header;

int delay_time = 1000;
String current_led_status = "off";
int LED_BUILTIN = 2;

unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 2000;

void setup()
{
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  // Connecting to Wi-Fi
  Serial.print("Connecting to WiFi");
  WiFi.begin(ssid, psswd);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(100);
    Serial.print(".");
  }
  Serial.println("Connected!");

  server.begin();

}

void loop(){
  WiFiClient client = server.available();
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());


if (client) {
 currentTime = millis();
    previousTime = currentTime;
    Serial.println("New Client.");          
    String currentLine = "";                
    while (client.connected() && currentTime - previousTime <= timeoutTime) {  
      currentTime = millis();
      if (client.available()) {             
      char c = client.read();             
        Serial.write(c);                    
        header += c;
        if (c == '\n') {                    
          if (currentLine.length() == 0) {
            client.println("HTTP/1.1 200 OK");
            client.println("Content-type:text/html");
            client.println("Connection: close");
            client.println();
            
          v
            client.println("<!DOCTYPE html><html>");
            client.println("<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
            client.println("<link rel=\"icon\" href=\"data:,\">");
            client.println("<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}");
            client.println(".button { background-color: #4CAF50; border: none; color: white; padding: 16px 40px;");
            client.println("text-decoration: none; font-size: 30px; margin: 2px; cursor: pointer;}");
            client.println(".button2 {background-color: #555555;}</style></head>");
            
            client.println("<body><h1>BUILTIN Led Control</h1>");
            
            client.println("<p>BUILTIN LED  - State " + current_led_status + "</p>");
            if (current_led_status=="off") {
              client.println("<p><a href=\"/02/on\"><button class=\"button\">ON</button></a></p>");
            } else {
              client.println("<p><a href=\"/02/off\"><button class=\"button button2\">OFF</button></a></p>");
            } 
            client.println("<p><a href=\"/02/plus\"><button class=\"button\">Plus</button></a></p>");
            client.println("<p><a href=\"/02/minus\"><button class=\"button button2\">Minua</button></a></p>");

              
            client.println("</body></html>");
            
            client.println();
            break;
          } else {
          currentLine = "";
          }
        } else if (c != '\r') { 
          currentLine += c;     
        }
      }
    }
    header = "";
    client.stop();
    Serial.println("Client disconnected.");
    Serial.println("");

  }
    delay(delay_time);

}