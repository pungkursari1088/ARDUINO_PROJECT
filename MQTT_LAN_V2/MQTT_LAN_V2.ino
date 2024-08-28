#include <WiFi.h>
#include <WebServer.h>
#include <EEPROM.h>
#include <Arduino.h>
#include <Ethernet.h>
#include <FS.h>
#include <SPIFFS.h>
#include <SPI.h>
#include <AsyncTCP.h>
#include <ESPAsyncWebServer.h>

const byte LATCH = 5; 
const byte DATA  = 19;
const byte CLOCK = 18; 
const byte chips = 18;

const int outputD1 = 32;
const int outputD2 = 33;
const int outputD3 = 25;
const int outputD4 = 26;
int DO[4] = {32,33,25,26};

const char* input_parameter1 = "output";
const char* input_parameter2 = "state";

static unsigned long lastMillis;
static unsigned long frameCount;
static unsigned int framesPerSecond;
const int seconds = 1;

unsigned long previousMillis = 0;
unsigned long interval = 8640;
unsigned long currentTime = millis();
unsigned long previousTime = 0; 
const long timeoutTime = 100;

unsigned long previousMillis2=0;
const long interval2=5000;

unsigned long lastTime = 0;
unsigned long timerDelay = 50;

int last_second;

#define EEPROM_SIZE 512
int address = 0; // EEPROM address where data is stored
int data[4]; // Array to store the read data
int ipArray[4];  // Array to hold the IP address as integers
// String checkboxState[32];

// Define the SSID and Password for the AP mode
// const char* ssid = "ESP32-AP";
// const char* password = "123456789";
const char* ssid = "DJAWADWIPA";
const char* password = "Siemens88";

// Set a static IP address
// IPAddress local_IP(192, 168, 1, 1);
// IPAddress gateway(192, 168, 1, 1);
// IPAddress subnet(255, 255, 255, 0);

// Create a WebServer object on port 80
AsyncWebServer server(80);

// Variable to store the text input from the HTML form
String inputText = "";
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP32 WEB SERVER</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p {font-size: 3.0rem;}
    body {max-width: 600px; margin:0px auto; padding-bottom: 25px;}
    button {
            font-size: 20px;
            padding: 15px 30px;
            margin: 20px;
            border-radius: 10px;
            border: none;
            cursor: pointer;
        }
        .on {
            background-color: #4CAF50; /* Green */
            color: white;
        }
        .off {
            background-color: #f44336; /* Red */
            color: white;
        }
        .status {
            font-size: 18px;
            margin-top: 10px;
        }
  </style>
</head>
<body>
  <h2>ESP32 WEB SERVER</h2>
  %BUTTONPLACEHOLDER%
  <button class="off" onclick="controlOutput('off1')">Output 1 OFF</button>
<script>
  function controlOutput(input) {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (xhttp.readyState === 4 && xhttp.status === 200) {
                    console.log(xhttp.responseText); // Menampilkan hasil permintaan ke konsol
                }
            };
            xhttp.open("GET", "/action?output=" + input, true);
            xhttp.send();
        }
</script>
</body>
</html>
)rawliteral";

void setup() {
  // Start Serial for debugging
  Serial.begin(115200);
  for(int i=0;i<4;i++){
    pinMode(DO[i],OUTPUT);
    digitalWrite(DO[i], HIGH);
  }

  // Read data from EEPROM
    EEPROM.begin(EEPROM_SIZE); // Initialize EEPROM
    for (int i = 0; i < 4; i++) {
        EEPROM.get(address + i * sizeof(int), data[i]); // Read data from EEPROM
    }
    EEPROM.end(); // Free the EEPROM resources

    if (!SPIFFS.begin(true)) {
    Serial.println("An Error has occurred while mounting SPIFFS");
    return;
  }

  // Load saved checkbox states
  // loadCheckboxState();

  //SETTING IP ADDRESS ETHERNET
  // byte mac[] = {0x02, 0xCB, 0xE3, 0xBB, 0xDB, 0xEC}; //ganti beda2
  // IPAddress ip(data[0],data[1],data[2],data[3]); //ganti beda2
  // IPAddress gateway(data[0],data[1],data[2], 1);
  // IPAddress subnet(255, 255, 255, 0);
  // EthernetClient net;

  // Configure the ESP32 as an AP
  // WiFi.softAPConfig(local_IP, gateway, subnet);
  // WiFi.softAP(ssid, password);

  // Sambungkan ke WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Menghubungkan ke WiFi...");
  }
  Serial.println("Terhubung ke WiFi!");
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());

  Serial.println("Access Point Started");
  Serial.print("IP Address: ");
  Serial.println(WiFi.softAPIP());

  // Set up URL routes
  // Route for root / web page
  server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });
  // server.on("/submit", HTTP_POST, handleSubmit);
  // server.on("/reset", HTTP_POST, espReset);
  // server.on("/checkbox", HTTP_POST, [](){
  //   saveCheckboxState();
  //   server.send(200, "text/html", htmlContent());
  // });

  server.on("/action", HTTP_GET, [] (AsyncWebServerRequest *request) {
    unsigned long currentMillis = millis();
    String inputMessage1;
    if (request->hasParam(input_parameter1)){
      inputMessage1 = request->getParam(input_parameter1)->value();
      if(inputMessage1=="off1"){
        digitalWrite(DO[0],LOW);
        Serial.println("DO 1 OFF");
        if(currentMillis - previousMillis2 >=interval2){
          digitalWrite(DO[0],HIGH);
          Serial.println("DO 1 ON");
          previousMillis2 = currentTime;
        }
      }
    }
    else {
      inputMessage1 = "No message sent";
    }
    request->send(200, "text/plain", "OK");
  });
  // // Send a GET request to <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  // server.on("/update", HTTP_GET, [] (AsyncWebServerRequest *request) {
  //   String inputMessage1;
  //   String inputMessage2;
  //   // GET input1 value on <ESP_IP>/update?output=<inputMessage1>&state=<inputMessage2>
  //   if (request->hasParam(input_parameter1) && request->hasParam(input_parameter2)) {
  //     inputMessage1 = request->getParam(input_parameter1)->value();
  //     inputMessage2 = request->getParam(input_parameter2)->value();
  //     digitalWrite(inputMessage1.toInt(), inputMessage2.toInt());
  //   }
  //   else {
  //     inputMessage1 = "No message sent";
  //     inputMessage2 = "No message sent";
  //   }
  //   Serial.print("GPIO: ");
  //   Serial.print(inputMessage1);
  //   Serial.print(" - Set to: ");
  //   Serial.println(inputMessage2);
  //   request->send(200, "text/plain", "OK");
  // });
  // Start the server
  server.begin();
}

void loop() {
  // Handle client requests
  server.begin();
}