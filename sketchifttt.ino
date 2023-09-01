#include <WiFiNINA.h>

char ssid[] = SECRET_SSID;
char pass[] = SECRET_PASSWORD;

WiFiClient client;

char HOST_NAME[] = "maker.ifttt.com";
String PATH_NAME   = "/trigger/Sunlight/with/key/lutvWDDoGPU_Y4JrLg_g1q7aLo7R7kp9nvCZONokwck"; 
String queryString = "?value1=";

#define LDR A0
int light_amount = 0;

void setup() {
  WiFi.begin(ssid, pass);
  Serial.begin(9600);
  while (!Serial);

  client_setup();
}

void loop() {
  light_amount = analogRead(LDR);
  Serial.println(light_amount);
    String data = queryString + String(light_amount);
    client_setup();
    if(light_amount < 900)
    {
      client.println("GET " + PATH_NAME + data + " -> Their is Sunlight" " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println();
  
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
      }
  
      client.stop();
      Serial.println();
      Serial.println("Disconnected");
    }
    
    else
    {
      client.println("GET " + PATH_NAME + data + " -> No Sunlight" " HTTP/1.1");
      client.println("Host: " + String(HOST_NAME));
      client.println("Connection: close");
      client.println();
  
      while (client.connected()) {
        if (client.available()) {
          char c = client.read();
          Serial.print(c);
        }
      }
  
      client.stop();
      Serial.println();
      Serial.println("Disconnected");
    }
    
  delay(5000); // Adjust the delay as needed
}

void client_setup()
{
  if (client.connect(HOST_NAME, 80)) {
    Serial.println("Connected to server");
  } else {
    Serial.println("Connection failed");
  }
}
