#include <TinyGPSPlus.h>
#include <SoftwareSerial.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <WiFi.h>

#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

const char* ssid = "HIDDEN";
const char* password = "pungkursari";

WiFiServer server(80);

// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
// The pins for I2C are defined by the Wire-library. 
// On an arduino UNO:       A4(SDA), A5(SCL)
// On an arduino MEGA 2560: 20(SDA), 21(SCL)
// On an arduino LEONARDO:   2(SDA),  3(SCL), ...
#define OLED_RESET     -1 // Reset pin # (or -1 if sharing Arduino reset pin)
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);


/*
   This sample code demonstrates the normal use of a TinyGPSPlus (TinyGPSPlus) object.
   It requires the use of SoftwareSerial, and assumes that you have a
   4800-baud serial GPS device hooked up on pins 4(rx) and 3(tx).
*/
//2 kabel hitam
//3 kabel kuning
static const int RXPin = 4, TXPin = 2;
static const uint32_t GPSBaud = 9600;

// The TinyGPSPlus object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

#define stasiun 15
int prevLoc=0;

double latKor[] = {0,-6236481, -6224548, -6219036, -6217635, -6215510, -6213376,-6214897,-6212391,-6210488,-6202548,-6201346,-6200644,-6185963,-6155489,-6264360};
double lngKor[] = {0,106999124, 106979841, 106952463, 106940166, 106923299, 106899397,106870221,106860040,106849328,106822907,106819662,106815794,106810862,106801313,106982285};
String lokasi[] = {"null","bekasi","kranji","cakung","klender baru","buaran","klender","jatinegara","matraman","manggarai","sudirman","BNI City","karet","tanah abang","duri","kos-kosan"};

void setup()
{
      // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  // Menghubungkan ke WiFi
  // display.print("WIFI = ");
  // display.println(ssid);

  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    display.print(".");
    Serial.print(".");
  }
  display.print("IP: ");
  display.println(WiFi.localIP());
  display.display();
  server.begin();

  Serial.begin(115200);
  ss.begin(GPSBaud);

  // Serial.println(F("FullExample.ino"));
  // Serial.println(F("An extensive example of many interesting TinyGPSPlus features"));
  // Serial.print(F("Testing TinyGPSPlus library v. ")); Serial.println(TinyGPSPlus::libraryVersion());
  // Serial.println(F("by Mikal Hart"));
  // Serial.println();
  // Serial.println(F("Sats HDOP  Latitude   Longitude   Fix  Date       Time     Date Alt    Course Speed Card  Distance Course Card  Chars Sentences Checksum"));
  // Serial.println(F("           (deg)      (deg)       Age                      Age  (m)    --- from GPS ----  ---- to London  ----  RX    RX        Fail"));
  // Serial.println(F("----------------------------------------------------------------------------------------------------------------------------------------"));
}

void loop()
{

  
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("lat :");
  display.println(gps.location.lat(),6);
  display.print("long :");
  display.println(gps.location.lng(),6);

  printFloat(gps.location.lat(), gps.location.isValid(), 11, 6);
  printFloat(gps.location.lng(), gps.location.isValid(), 12, 6);
  Serial.println();
  String temp="";
  for(int i=0;i<=stasiun;i++){

      double difLat = gps.location.lat()*1000000-latKor[i];
      double difLng = gps.location.lng()*1000000-lngKor[i];
      temp += "<tr>";
      temp += "<td>";
      temp += lokasi[i];
      temp += "<td>";
      // temp += "<span id='difLat";
      // temp += i;
      // temp +="'>loading...</span>";
      // temp += difLat;
      temp += "</td>";
      temp += "<td>";
      // temp += "<span id='difLng";
      // temp += i;
      // temp +="'>loading...</span>";
      temp += difLng;
      temp += "</td>";
      temp += "</tr>";
    Serial.print("Lokasi - ");
    Serial.println(lokasi[i]);
    Serial.print("selisih Lat = ");
    Serial.println(difLat);
    Serial.print("selisih Lat = ");
    Serial.println(difLng);
    if((difLat>-500 && difLat<500) && (difLng>-500 && difLng<500))
    {
      prevLoc =i;
      Serial.print("KETEMU di lokasi - ");
      Serial.println(i);
    }
  }
  display.print("stasiun:");
  display.println(lokasi[prevLoc]);
  display.print("IP:");
  display.println(WiFi.localIP());
  smartDelay(1000);

  if (millis() > 5000 && gps.charsProcessed() < 10)
  {
    Serial.println(F("No GPS data received: check wiring"));
    display.println(F("No GPS"));
  }
  display.display();

  //WIFI
    WiFiClient client = server.available();   // Mendengarkan client yang masuk

  if (client) {                             // Jika ada client yang terhubung
    Serial.println("Client baru terhubung");
    String request = client.readStringUntil('\r');
    Serial.println(request);
    client.flush();
    // Menyusun halaman web yang akan ditampilkan
    String s = "HTTP/1.1 200 OK\r\nContent-Type: text/html\r\n\r\n<!DOCTYPE HTML>\r\n<html>\r\n";
    s+="<head><meta http-equiv=\"refresh\" content=\"30\"></head>\r\n";
    s+="<table style=\"width:100%\"><tr><th>Lokasi</th><th>Latitude</th><th>Longitude</th></tr><tr>\r\n";
    s+=temp;
    s+="</table>\r\n";
    // Mengirimkan halaman web ke client
    client.print(s);
    delay(1);
    Serial.println("Client terputus");
  }
  

}

// This custom version of delay() ensures that the gps object
// is being "fed".
static void smartDelay(unsigned long ms)
{
  unsigned long start = millis();
  do 
  {
    while (ss.available())
      gps.encode(ss.read());
  } while (millis() - start < ms);
}

static void printFloat(float val, bool valid, int len, int prec)
{
  if (!valid)
  {
    while (len-- > 1)
      Serial.print('*');
    Serial.print(' ');
  }
  else
  {
    Serial.print(val, prec);
    int vi = abs((int)val);
    int flen = prec + (val < 0.0 ? 2 : 1); // . and -
    flen += vi >= 1000 ? 4 : vi >= 100 ? 3 : vi >= 10 ? 2 : 1;
    for (int i=flen; i<len; ++i)
      Serial.print(' ');
  }
  smartDelay(0);
}

static void printInt(unsigned long val, bool valid, int len)
{
  char sz[32] = "*****************";
  if (valid)
    sprintf(sz, "%ld", val);
  sz[len] = 0;
  for (int i=strlen(sz); i<len; ++i)
    sz[i] = ' ';
  if (len > 0) 
    sz[len-1] = ' ';
  Serial.print(sz);
  smartDelay(0);
}

static void printDateTime(TinyGPSDate &d, TinyGPSTime &t)
{
  if (!d.isValid())
  {
    Serial.print(F("********** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d/%02d/%02d ", d.month(), d.day(), d.year());
    Serial.print(sz);
  }
  
  if (!t.isValid())
  {
    Serial.print(F("******** "));
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", t.hour(), t.minute(), t.second());
    Serial.print(sz);
  }

  printInt(d.age(), d.isValid(), 5);
  smartDelay(0);
}

static void printStr(const char *str, int len)
{
  int slen = strlen(str);
  for (int i=0; i<len; ++i)
    Serial.print(i<slen ? str[i] : ' ');
  smartDelay(0);
}
