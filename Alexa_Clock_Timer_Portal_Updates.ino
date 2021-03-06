/*****************  NEEDED TO MAKE NODEMCU WORK ***************************/
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ALLOW_INTERRUPTS 0
#define FASTLED_ESP8266_RAW_PIN_ORDER

/******************  WIFI MANAGER LIBRARIES *************************************/
#include <FS.h>
//#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>          //https://github.com/tzapu/WiFiManager
#include <ArduinoJson.h>          //https://github.com/bblanchon/ArduinoJson//this needs to be first, or it all crashes and burns...
/******************  LIBRARY SECTION *************************************/

#include <FastLED.h>        //https://github.com/FastLED/FastLED
#include <SimpleTimer.h>    //https://github.com/thehookup/Simple-Timer-Library
#include <PubSubClient.h>   //https://github.com/knolleary/pubsubclient
#include <ESP8266WiFi.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <ESP8266mDNS.h>    //if you get an error here you need to install the ESP8266 board manager 
#include <ArduinoOTA.h>     //ArduinoOTA is now included with the ArduinoIDE
#include <Espalexa.h>       //https://github.com/Aircoookie/Espalexa
#include <TimeLib.h>        //https://github.com/PaulStoffregen/Time/blob/master/TimeLib.h

/*****************  START USER CONFIG SECTION *********************************/
/*****************  START USER CONFIG SECTION *********************************/
/*****************  START USER CONFIG SECTION *********************************/
/*****************  START USER CONFIG SECTION *********************************/

#define DAYLIGHT_SAVINGS 1            // 1 = use daylight savings, 0 = don't use daylight savings
#define HOUR_MODE 0                   // 1 = use 12 hour time, 0 = use 24 hour time
#define RESET_PIN D5                  // connect this pin to ground to reset the wifimanager config

unsigned int localPort = 8888;  // local port to listen for UDP packets
time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);
WiFiUDP Udp;

//const int timeZone = 1;     // Central European Time
int timeZone = -5;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)

//define your default values here, if there are different values in config.json, they are overwritten.
char alexa_id1[20];
char alexa_id2[20];
char alexa_id3[20];
char alexa_id4[20];
char savedTimezone[6];
char r1[6];
char r2[6];
char r3[6];
char rT[6];
char g1[6];
char g2[6];
char g3[6];
char gT[6];
char b1[6];
char b2[6];
char b3[6];
char bT[6];
char savedEffect[20];
char savedTimer[20];
char savedBrightness[6];
char dayLightSavings[6];

String alexaString1;
String alexaString2;
String alexaString3;
String alexaString4;

#define USER_MQTT_CLIENT_NAME     "LED_Clock"           // Used to define MQTT topics, MQTT Client ID, and ArduinoOTA

#define ZONEONE                         1                   //ZONEONE is pin D1, 1 = zone used 0 = zone unused
#define FIRSTZONE_SECTIONS              7                   //Number of rows in your clock
#define FIRSTZONE_LEDS                  83                  //Number of LEDS total
#define FIRSTZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 

/*****************************    ROW AND COLUMN SETUP    *************************************/
/*****************************    ROW AND COLUMN SETUP     *************************************/

#if  FIRSTZONE_SECTIONS >= 1
#define ZONEONE_SECTION1_START            0           //starting LED for this zone
#define ZONEONE_SECTION1_END              10         //ending LED for this zone
#define ZONEONE_SECTION1_START_FIRE       1           //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION1_END_FIRE         1           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 2
#define ZONEONE_SECTION2_START            13           //starting LED for this zone
#define ZONEONE_SECTION2_END              23         //ending LED for this zone
#define ZONEONE_SECTION2_START_FIRE       1           //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION2_END_FIRE         1           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 3
#define ZONEONE_SECTION3_START            24           //starting LED for this zone
#define ZONEONE_SECTION3_END              34         //ending LED for this zone
#define ZONEONE_SECTION3_START_FIRE       1           //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION3_END_FIRE         1           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 4
#define ZONEONE_SECTION4_START            37           //starting LED for this zone
#define ZONEONE_SECTION4_END              47         //ending LED for this zone
#define ZONEONE_SECTION4_START_FIRE       1           //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION4_END_FIRE         1           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 5
#define ZONEONE_SECTION5_START            48           //starting LED for this zone
#define ZONEONE_SECTION5_END              58         //ending LED for this zone
#define ZONEONE_SECTION5_START_FIRE       1           //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION5_END_FIRE         1           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 6
#define ZONEONE_SECTION6_START            61           //starting LED for this zone
#define ZONEONE_SECTION6_END              71         //ending LED for this zone
#define ZONEONE_SECTION6_START_FIRE       1           //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION6_END_FIRE         1           //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 7
#define ZONEONE_SECTION7_START            72          //starting LED for this zone
#define ZONEONE_SECTION7_END              82        //ending LED for this zone
#define ZONEONE_SECTION7_START_FIRE       1          //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION7_END_FIRE         1          //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 8
#define ZONEONE_SECTION8_START            0          //starting LED for this zone
#define ZONEONE_SECTION8_END              100        //ending LED for this zone
#define ZONEONE_SECTION8_START_FIRE       1          //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION8_END_FIRE         1          //would you like fire to begin from this point? 0 = no 1 = yes
#endif

#if  FIRSTZONE_SECTIONS >= 9
#define ZONEONE_SECTION9_START            0          //starting LED for this zone
#define ZONEONE_SECTION9_END              100        //ending LED for this zone
#define ZONEONE_SECTION9_START_FIRE       1          //would you like fire to begin from this point? 0 = no 1 = yes
#define ZONEONE_SECTION9_END_FIRE         1          //would you like fire to begin from this point? 0 = no 1 = yes
#endif

/*****************  END USER CONFIG SECTION *********************************/
/*****************  END USER CONFIG SECTION *********************************/
/*****************  END USER CONFIG SECTION *********************************/
/*****************  END USER CONFIG SECTION *********************************/
/*****************  END USER CONFIG SECTION *********************************/

#define RESX 7                        // 7 columns
#define RESY 11                       // 11 rows
#define DIGITX 3                      // width of digits (3 pixels)
#define DIGITY 5                      // height of digits (5 pixels)
#define SECONDZONE_LEDS 300           // fake LED Zone to keep the ESP busy


/*****************  GENERAL VARIABLES  *************************************/
/*****************  GENERAL VARIABLES  *************************************/
/*****************  GENERAL VARIABLES  *************************************/
/*****************  GENERAL VARIABLES  *************************************/
/*****************  GENERAL VARIABLES  *************************************/


CRGBPalette16 gPal;
long oldTimeInSeconds = 0;
bool shouldSaveConfig = false;
long currentTimer = 0;
uint8_t mark = 0;
uint8_t gHue = 0;
uint8_t startPosition = 0;
uint8_t glitterChance = 250;
int chaseDelay = 1000;
int lastPosition = 1;
int raceSpeed = 12;
int BeatsPerMinute = 62;
uint8_t numberOfRainbows = 7;
int twinkleChance = 250;
int eyeChance = 248;
bool boot = true;
String effect = "Fill_Solid";
bool showLights = true;
int red1 = 255;
int green1 = 0;
int blue1 = 0;
int red2 = 0;
int green2 = 255;
int blue2 = 0;
int red3 = 0;
int green3 = 0;
int blue3 = 255;
int redT = 255;
int greenT = 255;
int blueT = 255;
int brightness = 100;
int displayMode = 1;
bool displayTimer = false;
int DST = 0;
byte notdigits[10][DIGITX * DIGITY] = {
  { 0, 0, 0,
    0, 1, 0,
    0, 1, 0,
    0, 1, 0,
    0, 0, 0
  },        // 0
  { 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 },        // 1
  { 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0 },        // 2
  { 0, 0, 0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 0, 0, 0 },        // 3
  { 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 1, 1, 0 },        // 4
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0 },        // 5
  { 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0 },        // 6
  { 0, 0, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 0 },        // 7
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0 },        // 8
  { 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 }         // 9
};

int grid[23] = { 5, 11, 12, 18, 29, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 53, 59, 60, 66, 77 };
static const char ntpServerName[] = "us.pool.ntp.org";


/*****************  DECLARATIONS  ****************************************/

WiFiClient espClient;
PubSubClient client(espClient);
SimpleTimer timer;
Espalexa espalexa;
ESP8266WebServer server(80);


void colorLightChanged1(EspalexaDevice* dev);
void colorLightChanged2(EspalexaDevice* dev);
void colorLightChanged3(EspalexaDevice* dev);
void colorLightChanged4(EspalexaDevice* dev);
EspalexaDevice* device1;
EspalexaDevice* device2;
EspalexaDevice* device3;
EspalexaDevice* device4;


boolean connectWifi();
boolean wifiConnected = false;

CRGB firstZone[FIRSTZONE_LEDS];
CRGB secondZone[SECONDZONE_LEDS];
const int Pin_firstZone = 5; //marked as D1 on the board
const int Pin_secondZone = 4; //marked as D2 on the board
int center_firstZone = 0;
int step_firstZone = -1;
int previousLED_firstZone = 0;


/*****************  WIFI CONFIG STUFF  ****************************************/
/*****************  WIFI CONFIG STUFF  ****************************************/
/*****************  WIFI CONFIG STUFF  ****************************************/
/*****************  WIFI CONFIG STUFF  ****************************************/
/*****************  WIFI CONFIG STUFF  ****************************************/

//callback notifying us of the need to save config
void saveConfigCallback () {
  Serial.println("Should save config");
  shouldSaveConfig = true;
}

void configPortal()
{

  Serial.println("mounting FS...");
  if (SPIFFS.begin())
  {
    Serial.println("mounted file system");
    if (SPIFFS.exists("/color1.json"))
    {
      //file exists, reading and loading
      Serial.println("reading color1 file");
      File color1 = SPIFFS.open("/color1.json", "r");
      if (color1)
      {
        Serial.println("opened color1 file ");
        size_t size = color1.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        color1.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success())
        {
          Serial.println("\nparsed json");

          strcpy(r1, json["r1"]);
          red1 = atoi( r1 );

          strcpy(g1, json["g1"]);
          green1 = atoi( g1 );

          strcpy(b1, json["b1"]);
          blue1 = atoi( b1 );

          strcpy(savedBrightness, json["savedBrightness"]);
          brightness = atoi( savedBrightness );

        }
        else
        {
          Serial.println("failed to load json color1");
        }
      }
    }
    if (SPIFFS.exists("/color2.json"))
    {
      //file exists, reading and loading
      Serial.println("opened color2 file ");
      File color2 = SPIFFS.open("/color2.json", "r");
      if (color2)
      {
        Serial.println("opened color2 file");
        size_t size = color2.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        color2.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success())
        {
          Serial.println("\nparsed json");

          strcpy(r2, json["r2"]);
          red2 = atoi( r2 );

          strcpy(g2, json["g2"]);
          green2 = atoi( g2 );


          strcpy(b2, json["b2"]);
          blue2 = atoi( b2 );

          strcpy(savedEffect, json["savedEffect"]);
          effect = String((char *)savedEffect);
        }
        else
        {
          Serial.println("failed to load json color2");
        }
      }
    }
    if (SPIFFS.exists("/color3.json"))
    {
      //file exists, reading and loading
      Serial.println("reading color3 file");
      File color3 = SPIFFS.open("/color3.json", "r");
      if (color3)
      {
        Serial.println("opened color3 file");
        size_t size = color3.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        color3.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success())
        {
          Serial.println("\nparsed json");

          strcpy(r3, json["r3"]);
          red3 = atoi( r3 );

          strcpy(g3, json["g3"]);
          green3 = atoi( g3 );

          strcpy(b3, json["b3"]);
          blue3 = atoi( b3 );


          boot = false;
        }
        else
        {
          Serial.println("failed to load json color3");
        }
      }
    }
    if (SPIFFS.exists("/timer.json"))
    {
      //file exists, reading and loading
      Serial.println("reading timer file");
      File timer = SPIFFS.open("/timer.json", "r");
      if (timer)
      {
        Serial.println("opened timer file");
        size_t size = timer.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        timer.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success())
        {
          Serial.println("\nparsed json");

          strcpy(rT, json["rT"]);
          redT = atoi( rT );

          strcpy(gT, json["gT"]);
          greenT = atoi( gT );

          strcpy(bT, json["bT"]);
          blueT = atoi( bT );

          strcpy(savedTimer, json["savedTimer"]);
          currentTimer = atoi( savedTimer );

          strcpy(dayLightSavings, json["dayLightSavings"]);
          DST = atoi( dayLightSavings );

        }
        else
        {
          Serial.println("failed to load json timer");
        }
      }
    }
    if (SPIFFS.exists("/config.json"))
    {
      //file exists, reading and loading
      Serial.println("reading config file");
      File configFile = SPIFFS.open("/config.json", "r");
      if (configFile)
      {
        Serial.println("opened config file");
        size_t size = configFile.size();
        // Allocate a buffer to store contents of the file.
        std::unique_ptr<char[]> buf(new char[size]);
        configFile.readBytes(buf.get(), size);
        DynamicJsonBuffer jsonBuffer;
        JsonObject& json = jsonBuffer.parseObject(buf.get());
        json.printTo(Serial);
        if (json.success())
        {
          Serial.println("\nparsed json");
          strcpy(alexa_id1, json["alexa_id1"]);
          alexaString1 = String((char *)alexa_id1);
          strcpy(alexa_id2, json["alexa_id2"]);
          alexaString2 = String((char *)alexa_id2);
          strcpy(alexa_id3, json["alexa_id3"]);
          alexaString3 = String((char *)alexa_id3);
          strcpy(alexa_id4, json["alexa_id4"]);
          alexaString4 = String((char *)alexa_id4);
          strcpy(savedTimezone, json["savedTimezone"]);
        }
        else
        {
          Serial.println("failed to load json config");
        }
      }
    }
  }
  else
  {
    Serial.println("failed to mount FS");
  }
  //end read
  // The extra parameters to be configured (can be either global or just in the setup)
  // After connecting, parameter.getValue() will get you the configured value
  // id/name placeholder/prompt default length
  WiFiManagerParameter custom_alexa_id1("ID1", "Main Clock Invocation Name", alexa_id1, 20);
  WiFiManagerParameter custom_alexa_id2("ID2", "Color2/Effect Invocation Name", alexa_id2, 20);
  WiFiManagerParameter custom_alexa_id3("ID3", "Color3/Mod Invocation Name", alexa_id3, 20);
  WiFiManagerParameter custom_alexa_id4("ID4", "Timer Invocation Name", alexa_id4, 20);
  WiFiManagerParameter custom_savedTimezone("Timezone", "Timezone (EST -5)", savedTimezone, 20);

  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  WiFiManager wifiManager;

  //set config save notify callback
  wifiManager.setSaveConfigCallback(saveConfigCallback);

  //add all your parameters here
  wifiManager.addParameter(&custom_alexa_id1);
  wifiManager.addParameter(&custom_alexa_id2);
  wifiManager.addParameter(&custom_alexa_id3);
  wifiManager.addParameter(&custom_alexa_id4);
  wifiManager.addParameter(&custom_savedTimezone);

  //reset settings - for testing
  if (digitalRead(RESET_PIN) == LOW)
  {
    wifiManager.resetSettings();
  }

  if (!wifiManager.autoConnect("Clock Setup")) {
    Serial.println("failed to connect and hit timeout");
    delay(3000);
    //reset and try again, or maybe put it to deep sleep
    ESP.reset();
    delay(5000);
  }

  //if you get here you have connected to the WiFi
  Serial.println("connected...");

  //read updated parameters
  strcpy(alexa_id1, custom_alexa_id1.getValue());
  strcpy(alexa_id2, custom_alexa_id2.getValue());
  strcpy(alexa_id3, custom_alexa_id3.getValue());
  strcpy(alexa_id4, custom_alexa_id4.getValue());
  strcpy(savedTimezone, custom_savedTimezone.getValue());

  //save the custom parameters to FS
  if (shouldSaveConfig) {
    Serial.println("saving config");
    DynamicJsonBuffer jsonBuffer;
    JsonObject& json = jsonBuffer.createObject();
    json["alexa_id1"] = alexa_id1;
    json["alexa_id2"] = alexa_id2;
    json["alexa_id3"] = alexa_id3;
    json["alexa_id4"] = alexa_id4;
    json["savedTimezone"] = savedTimezone;

    File configFile = SPIFFS.open("/config.json", "w");
    if (!configFile) {
      Serial.println("failed to open config file for writing");
    }

    json.printTo(Serial);
    json.printTo(configFile);
    configFile.close();
    //end save
  }
}




/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/
/*****************  GLOBAL LIGHT FUNCTIONS  *******************************/


void chase()
{
  if (startPosition == 5)
  {
    startPosition = 0;
  }
  else
  {
    startPosition++;
  }
  timer.setTimeout(chaseDelay, chase);
}

void checkIn()
{
  client.publish(USER_MQTT_CLIENT_NAME"/checkIn", "OK");
  timer.setTimeout(120000, checkIn);
}

void choosePattern()
{
  if (showLights == true)
  {
    if (effect == "Color_Chase")
    {
      RGB_firstZone();
    }
    if (effect == "Color_Glitter")
    {
      ColorGlitter_firstZone(glitterChance);
    }
    if (effect == "Single_Race")
    {
      SingleRace_firstZone();
    }
    if (effect == "Double_Crash")
    {
      Crash_firstZone();
    }
    if (effect == "Rainbow")
    {
      Rainbow_firstZone();
    }
    if (effect == "Blocked_Colors")
    {
      Blocked_firstZone();
    }
    if (effect == "BPM")
    {
      BPM_firstZone();
    }
    if (effect == "Twinkle")
    {
      Twinkle_firstZone();
    }
    if (effect == "Fill_Solid")
    {
      Solid_firstZone();
    }
    if (effect == "Ripple")
    {
      Ripple_firstZone();
    }
  }
  if (showLights == false)
  {
    fill_solid(firstZone, FIRSTZONE_LEDS, CRGB::Black);
  }
  secondZone_doStuff();
}

/*********************** TIME FUNCTIONS ***************************/
/*********************** TIME FUNCTIONS ***************************/
/*********************** TIME FUNCTIONS ***************************/
/*********************** TIME FUNCTIONS ***************************/
/*********************** TIME FUNCTIONS ***************************/

void displayTime()
{
  time_t t = now();                                                   // store current time in variable t to prevent changes while updating
  choosePattern();
  if (HOUR_MODE == 0) {
    if (hourFormat12(t) >= 10)
    {
      showDigit(1, 2, 10);
    }
    else
    {
      showDigit(0, 2, 10);
    }
    showDigit((hourFormat12(t) % 10), 6, 10);
  } else if (HOUR_MODE == 1) {
    showDigit(hour(t) / 10, 2, 10);
    showDigit(hour(t) % 10, 6, 10);
  }
  showDigit((minute(t) / 10), 2, 4);
  showDigit((minute(t) % 10), 6, 4);
}

void showTimer()
{
  //unfinsihed function... basically when timer is called add that number of ms to now(), then in this function subtract now() from the saved timer value (also save the timer in SPIFFS) to calculate the time left on the timer.
  long timeInSeconds = (currentTimer - now());
  int timeInMinutes = timeInSeconds / 60;
  choosePattern();
  if (currentTimer < now())
  {
    displayTimer = false;
  }
  else if (timeInMinutes < 60)
  {
    showDigit((timeInMinutes / 10), 2, 10);
    showDigit((timeInMinutes % 10), 6, 10);
    showDigit(((timeInSeconds % 60) / 10), 2, 4);
    showDigit(((timeInSeconds % 60) % 10), 6, 4);
    Serial.print("Timer is ");
    Serial.print((timeInMinutes / 10));
    Serial.print((timeInMinutes % 10));
    Serial.print(":");
    Serial.print((timeInSeconds % 60) / 10);
    Serial.println((timeInSeconds % 60) % 10);
  }
  else
  {
    showDigit(0, 2, 10);
    showDigit(1, 6, 10);
    showDigit(((timeInMinutes - 60) / 10), 2, 4);
    showDigit(((timeInMinutes - 60) % 10), 6, 4);
    Serial.print("Timer is ");
    Serial.print("0");
    Serial.print("1");
    Serial.print(":");
    Serial.print(((timeInMinutes - 60) / 10));
    Serial.println(((timeInMinutes - 60) % 10));
  }
}

void showDigit(byte digit, byte x, byte y)
{
  for (byte i = 0; i < 15; i++) {
    if (notdigits[digit][i] == 1) setPixel(x + (i - ((i / DIGITX) * DIGITX)) - 2, y - (i / DIGITX));
  }
}

void setPixel(byte x, byte y)
{
  byte pixel = 0;
  int colorMode = 1;
  if (x < RESX && y < RESY) {
    if ((x % 2) == 0) pixel = x + (x * RESY) + y;
    else pixel = ((x + 1) * RESY) - y + x;
    if (colorMode == 1) firstZone[pixel] = CRGB::Black;
    else firstZone[pixel] = CRGB::Black;
  }
}

void gridRemove()
{
  for (int i = 0; i < 23; i++)
  {
    firstZone[grid[i]] = CRGB::Black;
  }
}

/*********************** NTP CLOCK FUNCTIONS ***************************/
/*********************** NTP CLOCK FUNCTIONS ***************************/
/*********************** NTP CLOCK FUNCTIONS ***************************/
/*********************** NTP CLOCK FUNCTIONS ***************************/
/*********************** NTP CLOCK FUNCTIONS ***************************/
/*********************** NTP CLOCK FUNCTIONS ***************************/

const int NTP_PACKET_SIZE = 48; // NTP time is in the first 48 bytes of message
byte packetBuffer[NTP_PACKET_SIZE]; //buffer to hold incoming & outgoing packets

time_t getNtpTime()
{
  IPAddress ntpServerIP; // NTP server's ip address

  while (Udp.parsePacket() > 0) ; // discard any previously received packets
  Serial.println("Transmit NTP Request");
  // get a random server from the pool
  WiFi.hostByName(ntpServerName, ntpServerIP);
  Serial.print(ntpServerName);
  Serial.print(": ");
  Serial.println(ntpServerIP);
  sendNTPpacket(ntpServerIP);
  uint32_t beginWait = millis();
  while (millis() - beginWait < 1500) {
    int size = Udp.parsePacket();
    if (size >= NTP_PACKET_SIZE) {
      Serial.println("Receive NTP Response");
      Udp.read(packetBuffer, NTP_PACKET_SIZE);  // read packet into the buffer
      unsigned long secsSince1900;
      // convert four bytes starting at location 40 to a long integer
      secsSince1900 =  (unsigned long)packetBuffer[40] << 24;
      secsSince1900 |= (unsigned long)packetBuffer[41] << 16;
      secsSince1900 |= (unsigned long)packetBuffer[42] << 8;
      secsSince1900 |= (unsigned long)packetBuffer[43];
      return secsSince1900 - 2208988800UL + timeZone * SECS_PER_HOUR;
    }
  }
  Serial.println("No NTP Response :-(");
  return 0; // return 0 if unable to get the time
}

// send an NTP request to the time server at the given address
void sendNTPpacket(IPAddress &address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12] = 49;
  packetBuffer[13] = 0x4E;
  packetBuffer[14] = 49;
  packetBuffer[15] = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  Udp.beginPacket(address, 123); //NTP requests are to port 123
  Udp.write(packetBuffer, NTP_PACKET_SIZE);
  Udp.endPacket();
}

/*****************  SETUP FUNCTION  ****************************************/
/*****************  SETUP FUNCTION  ****************************************/
/*****************  SETUP FUNCTION  ****************************************/
/*****************  SETUP FUNCTION  ****************************************/
/*****************  SETUP FUNCTION  ****************************************/


void setup() {
  Serial.begin(115200);
  pinMode(RESET_PIN, INPUT_PULLUP);
  configPortal();
  int tempInt = atoi( savedTimezone );
  timeZone = tempInt + DST;
  FastLED.addLeds<WS2812B, Pin_firstZone, FIRSTZONE_COLOR_ORDER>(firstZone, FIRSTZONE_LEDS);
  FastLED.addLeds<WS2812B, Pin_secondZone, FIRSTZONE_COLOR_ORDER>(secondZone, SECONDZONE_LEDS);
  FastLED.setDither( 0 );
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  wifiConnected = true;
  if (wifiConnected) {
    server.on("/", HTTP_GET, []() {
      server.send(200, "text/plain", "This is an example index page your server may send.");
    });
    server.on("/test", HTTP_GET, []() {
      server.send(200, "text/plain", "This is a second subpage you may have.");
    });
    server.onNotFound([]() {
      if (!espalexa.handleAlexaApiCall(server.uri(), server.arg(0))) //if you don't know the URI, ask espalexa whether it is an Alexa control request
      {
        //whatever you want to do with 404s
        server.send(404, "text/plain", "Not found");
      }
    });

    device1 = new EspalexaDevice(alexaString1, colorLightChanged1, EspalexaDeviceType::color);
    device2 = new EspalexaDevice(alexaString2, colorLightChanged2, EspalexaDeviceType::color);
    device3 = new EspalexaDevice(alexaString3, colorLightChanged3, EspalexaDeviceType::color);
    device4 = new EspalexaDevice(alexaString4, colorLightChanged4, EspalexaDeviceType::color);
    espalexa.addDevice(device1);
    espalexa.addDevice(device2);
    espalexa.addDevice(device3);
    espalexa.addDevice(device4);

    device1->setValue(brightness);
    device1->setColor(red1, green1, blue1);
    setEffect();
    device2->setColor(red2, green2, blue2);
    device3->setValue(127);
    device3->setColor(red3, green3, blue3);
    device4->setValue(0);

    espalexa.begin(&server);
  }
  else
  {
    delay(5000);
    ESP.restart();
  }
  Udp.begin(localPort);
  setSyncProvider(getNtpTime);
  setSyncInterval(300);
  ArduinoOTA.setHostname(USER_MQTT_CLIENT_NAME);
  ArduinoOTA.begin();
  gPal = HeatColors_p;
  if (currentTimer > now())
  {
    displayTimer = true;
  }
  timer.setTimeout(10000, chase);
  timer.setTimeout(120000, checkIn);
}

/*****************  MAIN LOOP  ****************************************/
/*****************  MAIN LOOP  ****************************************/
/*****************  MAIN LOOP  ****************************************/
/*****************  MAIN LOOP  ****************************************/
/*****************  MAIN LOOP  ****************************************/


void loop()
{
  espalexa.loop();
  ArduinoOTA.handle();

  timer.run();
  EVERY_N_MILLISECONDS( 20 )
  {
    gHue++;
  }
  if (displayTimer == true)
  {
    showTimer();
    gridRemove();
    FastLED[0].showLeds(brightness);
  }
  else
  {
    displayTime();
    gridRemove();
    FastLED[0].showLeds(brightness);
  }
  FastLED[1].showLeds(brightness);
}

/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/

void colorLightChanged1(EspalexaDevice* d)
{
  int brightnessCommand = d->getValue();
  Serial.println("Got Data for device 1");
  if (brightnessCommand == 0)
  {
    showLights = false;
  }
  else
  {
    showLights = true;
  }
  brightness = brightnessCommand;
  red1 = d->getR();
  green1 = d->getG();
  blue1 = d->getB();

  itoa(brightnessCommand, savedBrightness, 10);
  itoa(red1, r1, 10);
  itoa(green1, g1, 10);
  itoa(blue1, b1, 10);
  Serial.println("saving position");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["r1"] = r1;
  json["g1"] = g1;
  json["b1"] = b1;
  json["savedBrightness"] = savedBrightness;
  File storedFile = SPIFFS.open("/color1.json", "w");
  if (!storedFile)
  {
    Serial.println("failed to open config file for writing");
  }
  json.printTo(Serial);
  json.printTo(storedFile);
  storedFile.close();
}

void colorLightChanged2(EspalexaDevice* d)
{
  Serial.println("Got Data for device 2");
  fill_solid(firstZone, FIRSTZONE_LEDS, CRGB::Black);
  int brightnessPercent = d->getPercent();
  if (brightnessPercent > 0 && brightnessPercent <= 10)
  {
    effect = "Fill_Solid";
  }
  if (brightnessPercent > 10 && brightnessPercent <= 20)
  {
    effect = "Color_Chase";
  }
  if (brightnessPercent > 20 && brightnessPercent <= 30)
  {
    effect = "Color_Glitter";
  }
  if (brightnessPercent > 30 && brightnessPercent <= 40)
  {
    effect = "Single_Race";
  }
  if (brightnessPercent > 40 && brightnessPercent <= 50)
  {
    effect = "Double_Crash";
  }
  if (brightnessPercent > 50 && brightnessPercent <= 60)
  {
    effect = "Rainbow";
  }
  if (brightnessPercent > 60 && brightnessPercent <= 70)
  {
    effect = "Blocked_Colors";
  }
  if (brightnessPercent > 70 && brightnessPercent <= 80)
  {
    effect = "BPM";
  }
  if (brightnessPercent > 80 && brightnessPercent <= 90)
  {
    effect = "Twinkle";
  }
  if (brightnessPercent > 90 && brightnessPercent <= 100)
  {
    effect = "Ripple";
  }
  red2 = d->getR();
  green2 = d->getG();
  blue2 = d->getB();
  itoa(red2, r2, 10);
  itoa(green2, g2, 10);
  itoa(blue2, b2, 10);
  effect.toCharArray(savedEffect, effect.length() + 1);
  Serial.println("saving position");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["savedEffect"] = savedEffect;
  json["r2"] = r2;
  json["g2"] = g2;
  json["b2"] = b2;
  File storedFile = SPIFFS.open("/color2.json", "w");
  if (!storedFile)
  {
    Serial.println("failed to open config file for writing");
  }
  json.printTo(Serial);
  json.printTo(storedFile);
  storedFile.close();
}

void colorLightChanged3(EspalexaDevice* d)
{
  Serial.println("Got Data for device 3");
  int brightnessCommand = d->getValue();
  int intPayload = map(brightnessCommand, 0, 255, 0, 500);
  if (effect == "Double_Crash" || effect == "Single_Race")
  {
    raceSpeed = (intPayload / 20);
  }
  if (effect == "BPM")
  {
    BeatsPerMinute = (intPayload / 4);
  }
  if (effect == "Color_Chase" || effect == "Blocked_Colors")
  {
    chaseDelay = (intPayload * 5);
    if (chaseDelay < 100)
    {
      chaseDelay = 100;
    }
  }
  if (effect == "Color_Glitter")
  {
    glitterChance = (intPayload / 2);
  }
  if (effect == "Rainbow")
  {
    numberOfRainbows = (intPayload / 30);
  }
  if (effect == "Twinkle")
  {
    twinkleChance = map(intPayload, 0, 500, 0, 255);
  }
  red3 = d->getR();
  green3 = d->getG();
  blue3 = d->getB();

  itoa(red3, r3, 10);
  itoa(green3, g3, 10);
  itoa(blue3, b3, 10);
  Serial.println("saving position");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["r3"] = r3;
  json["g3"] = g3;
  json["b3"] = b3;
  File storedFile = SPIFFS.open("/color3.json", "w");
  if (!storedFile)
  {
    Serial.println("failed to open config file for writing");
  }
  json.printTo(Serial);
  json.printTo(storedFile);
  storedFile.close();
}

void colorLightChanged4(EspalexaDevice* d)
{
  Serial.println("Got Data for device 4");
  int percent = d->getPercent();
  long newTimer = percent * 60;
  currentTimer = now() + newTimer;

  redT = d->getR();
  greenT = d->getG();
  blueT = d->getB();

  if (redT > greenT + blueT)
  {
    DST = 1;
    int tempInt = atoi( savedTimezone );
    timeZone = tempInt + DST;
  }
  if (blueT > greenT + redT)
  {
    DST = 0;
    int tempInt = atoi( savedTimezone );
    timeZone = tempInt + DST;
  }
  itoa(redT, rT, 10);
  itoa(green3, gT, 10);
  itoa(blueT, bT, 10);
  itoa(currentTimer, savedTimer, 10);
  itoa(DST, dayLightSavings, 10);
  Serial.println("saving position");
  DynamicJsonBuffer jsonBuffer;
  JsonObject& json = jsonBuffer.createObject();
  json["rT"] = rT;
  json["gT"] = gT;
  json["bT"] = bT;
  json["savedTimer"] = savedTimer;
  json["dayLightSavings"] = dayLightSavings;
  File storedFile = SPIFFS.open("/timer.json", "w");
  if (!storedFile)
  {
    Serial.println("failed to open config file for writing");
  }
  json.printTo(Serial);
  json.printTo(storedFile);
  storedFile.close();
  displayTimer = true;
}

void setEffect()
{
  if (effect == "Fill_Solid")
  {
    device2->setValue(13);
  }
  else if (effect == "Color_Chase")
  {
    device2->setValue(39);
  }
  else if (effect == "Color_Glitter")
  {
    device2->setValue(65);
  }
  else if (effect == "Single_Race")
  {
    device2->setValue(90);
  }
  else if (effect == "Double_Crash")
  {
    device2->setValue(116);
  }
  else if (effect == "Rainbow")
  {
    device2->setValue(142);
  }
  else if (effect == "Blocked_Colors")
  {
    device2->setValue(169);
  }
  else if (effect == "BPM")
  {
    device2->setValue(194);
  }
  else if (effect == "Twinkle")
  {
    device2->setValue(220);
  }
  else if (effect == "Ripple")
  {
    device2->setValue(246);
  }
  if (DST == 1)
  {
    device3->setColor(253, 0, 0);
  }
  else if (DST == 0)
  {
    device3->setColor(0, 0, 253);
  }
}

/*****************  firstZone Animations  ****************************************/
/*****************  firstZone Animations  ****************************************/
/*****************  firstZone Animations  ****************************************/
/*****************  firstZone Animations  ****************************************/
/*****************  firstZone Animations  ****************************************/


void Ripple_firstZone()
{
  for (int i = 0; i < FIRSTZONE_LEDS; i++)
  {
    firstZone[i] = CRGB((red2 / 2), (green2 / 2), (blue2 / 1));
  }
  switch (step_firstZone)
  {
    case -1:
      center_firstZone = random16(FIRSTZONE_LEDS);
      step_firstZone = 0;
      break;
    case 0:
      firstZone[center_firstZone] = CRGB(red1, green1, blue1);
      step_firstZone ++;
      break;
    case 12:
      step_firstZone = -1;
      break;
    default:                                                             // Middle of the ripples.
      firstZone[(center_firstZone + step_firstZone + FIRSTZONE_LEDS) % FIRSTZONE_LEDS] += CRGB((red1 / (step_firstZone * 5)), (green1 / (step_firstZone * 5)), (blue1 / (step_firstZone * 5)));
      firstZone[(center_firstZone - step_firstZone + FIRSTZONE_LEDS) % FIRSTZONE_LEDS] += CRGB((red1 / (step_firstZone * 5)), (green1 / (step_firstZone * 5)), (blue1 / (step_firstZone * 5)));
      step_firstZone ++;
      break;
  }
}

void RGB_firstZone()
{
  if (startPosition < 6)
  {
    for (int pixel = startPosition + 1; pixel < FIRSTZONE_LEDS; pixel += 6)
    {
      if (pixel <= FIRSTZONE_LEDS)
      {
        firstZone[pixel] = CRGB(red1, green1, blue1);
      }
    }
    for (int pixel = startPosition + 3; pixel < FIRSTZONE_LEDS; pixel += 6)
    {
      if (pixel <= FIRSTZONE_LEDS)
      {
        firstZone[pixel] = CRGB(red2, green2, blue2);
      }
    }
    for (int pixel = startPosition + 5; pixel < FIRSTZONE_LEDS; pixel += 6)
    {
      if (pixel <= FIRSTZONE_LEDS)
      {
        firstZone[pixel] = CRGB(red3, green3, blue3);
      }
    }
  }
  if (startPosition == 1)
  {
    firstZone[0] = CRGB(red3, green3, blue3);
  }
  if (startPosition == 2)
  {
    firstZone[1] = CRGB(red3, green3, blue3);
  }
  if (startPosition == 3)
  {
    firstZone[2] = CRGB(red3, green3, blue3);
    firstZone[0] = CRGB(red2, green2, blue2);
  }
  if (startPosition == 4)
  {
    firstZone[3] = CRGB(red3, green3, blue3);
    firstZone[1] = CRGB(red2, green2, blue2);
  }
  if (startPosition == 5)
  {
    firstZone[4] = CRGB(red3, green3, blue3);
    firstZone[2] = CRGB(red2, green2, blue2);
    firstZone[0] = CRGB(red1, green1, blue1);
  }
}

void ColorGlitter_firstZone( fract8 chanceOfGlitter)
{

  if (startPosition == 0)
  {
    if ( random8() < chanceOfGlitter)
    {
      firstZone[ random16(FIRSTZONE_LEDS) ] = CRGB(red1, green1, blue1);
    }
  }
  if (startPosition == 1)
  {
    if ( random8() < chanceOfGlitter)
    {
      firstZone[ random16(FIRSTZONE_LEDS) ] = CRGB(red2, green2, blue2);
    }
  }
  if (startPosition == 2)
  {
    if ( random8() < chanceOfGlitter)
    {
      firstZone[ random16(FIRSTZONE_LEDS) ] = CRGB(red3, green3, blue3);
    }
  }
  if (startPosition == 3)
  {
    if ( random8() < chanceOfGlitter)
    {
      firstZone[ random16(FIRSTZONE_LEDS) ] = CRGB(red1, green1, blue1);
    }
  }
  if (startPosition == 4)
  {
    if ( random8() < chanceOfGlitter)
    {
      firstZone[ random16(FIRSTZONE_LEDS) ] = CRGB(red2, green2, blue2);
    }
  }
  if (startPosition == 5)
  {
    if ( random8() < chanceOfGlitter)
    {
      firstZone[ random16(FIRSTZONE_LEDS) ] = CRGB(red3, green3, blue3);
    }
  }
}

void SingleRace_firstZone()
{
  int pos = beatsin16( raceSpeed, 0, FIRSTZONE_LEDS);
  if (pos > previousLED_firstZone)
  {
    firstZone[pos] = CRGB(red1, green1, blue1);
    firstZone[0] =  CRGB(red1, green1, blue1);
    previousLED_firstZone = pos;

  }
  if (pos < previousLED_firstZone)
  {
    firstZone[pos] = CRGB(red2, green2, blue2);
    previousLED_firstZone = pos;
  }

}

void Crash_firstZone()
{
#ifdef ZONEONE_SECTION1_START
  int pos_SECTION1 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION1_END - ZONEONE_SECTION1_START) );
  firstZone[ZONEONE_SECTION1_START + pos_SECTION1] = CRGB(red1, green1, blue1);
  firstZone[ZONEONE_SECTION1_END - pos_SECTION1] = CRGB(red2, green2, blue2);
#endif

#ifdef ZONEONE_SECTION2_START
  int pos_SECTION2 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION2_END - ZONEONE_SECTION2_START) );
  firstZone[ZONEONE_SECTION2_START + pos_SECTION2] = CRGB(red2, green2, blue2);
  firstZone[ZONEONE_SECTION2_END - pos_SECTION2] = CRGB(red1, green1, blue1);
#endif

#ifdef ZONEONE_SECTION3_START
  int pos_SECTION3 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION3_END - ZONEONE_SECTION3_START) );
  firstZone[ZONEONE_SECTION3_START + pos_SECTION3] = CRGB(red1, green1, blue1);
  firstZone[ZONEONE_SECTION3_END - pos_SECTION3] = CRGB(red2, green2, blue2);
#endif

#ifdef ZONEONE_SECTION4_START
  int pos_SECTION4 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION4_END - ZONEONE_SECTION4_START) );
  firstZone[ZONEONE_SECTION4_START + pos_SECTION4] = CRGB(red2, green2, blue2);
  firstZone[ZONEONE_SECTION4_END - pos_SECTION4] = CRGB(red1, green1, blue1);
#endif

#ifdef ZONEONE_SECTION5_START
  int pos_SECTION5 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION5_END - ZONEONE_SECTION5_START) );
  firstZone[ZONEONE_SECTION5_START + pos_SECTION5] = CRGB(red1, green1, blue1);
  firstZone[ZONEONE_SECTION5_END - pos_SECTION5] = CRGB(red2, green2, blue2);
#endif

#ifdef ZONEONE_SECTION6_START
  int pos_SECTION6 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION6_END - ZONEONE_SECTION6_START) );
  firstZone[ZONEONE_SECTION6_START + pos_SECTION6] = CRGB(red2, green2, blue2);
  firstZone[ZONEONE_SECTION6_END - pos_SECTION6] = CRGB(red1, green1, blue1);
#endif

#ifdef ZONEONE_SECTION7_START
  int pos_SECTION7 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION7_END - ZONEONE_SECTION7_START) );
  firstZone[ZONEONE_SECTION7_START + pos_SECTION7] = CRGB(red1, green1, blue1);
  firstZone[ZONEONE_SECTION7_END - pos_SECTION7] = CRGB(red2, green2, blue2);
#endif

#ifdef ZONEONE_SECTION8_START
  int pos_SECTION8 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION8_END - ZONEONE_SECTION8_START) );
  firstZone[ZONEONE_SECTION8_START + pos_SECTION8] = CRGB(red2, green2, blue2);
  firstZone[ZONEONE_SECTION8_END - pos_SECTION8] = CRGB(red1, green1, blue1);
#endif

#ifdef ZONEONE_SECTION9_START
  int pos_SECTION9 = beatsin16( raceSpeed, 0, (ZONEONE_SECTION9_END - ZONEONE_SECTION9_START) );
  firstZone[ZONEONE_SECTION9_START + pos_SECTION9] = CRGB(red1, green1, blue1);
  firstZone[ZONEONE_SECTION9_END - pos_SECTION9] = CRGB(red2, green2, blue2);
#endif

}

void Rainbow_firstZone()
{
  fill_rainbow( firstZone, FIRSTZONE_LEDS, gHue, numberOfRainbows);
}

void Blocked_firstZone()
{
  if (startPosition == 0 || startPosition == 1)
  {
    fill_solid(firstZone, FIRSTZONE_LEDS, CRGB(red1, green1, blue1));
  }
  if (startPosition == 2 || startPosition == 3)
  {
    fill_solid(firstZone, FIRSTZONE_LEDS, CRGB(red2, green2, blue2));
  }
  if (startPosition == 4 || startPosition == 5)
  {
    fill_solid(firstZone, FIRSTZONE_LEDS, CRGB(red3, green3, blue3));
  }
}

void BPM_firstZone()
{
  if ((red1 * 2) > (green1 + blue1))
  {
    CRGBPalette16 palette_firstZone = LavaColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < FIRSTZONE_LEDS; i++)
    {
      firstZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((green1 * 2) > (red1 + blue1))
  {
    CRGBPalette16 palette_firstZone = ForestColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < FIRSTZONE_LEDS; i++)
    {
      firstZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((blue1 * 2) > (green1 + red1))
  {
    CRGBPalette16 palette_firstZone = CloudColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < FIRSTZONE_LEDS; i++)
    {
      firstZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((blue1 * 2) == (green1 + red1))
  {
    CRGBPalette16 palette_firstZone = PartyColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < FIRSTZONE_LEDS; i++)
    {
      firstZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
}

void Twinkle_firstZone()
{
  fadeToBlackBy( firstZone, FIRSTZONE_LEDS, 80);
  for ( int i = 0; i < FIRSTZONE_LEDS; i++)
  {
    if (i <= FIRSTZONE_LEDS)
    {
      if (random8() > twinkleChance)
      {
        firstZone[i] = CRGB( red1, green1, blue1);
      }
      else
      {
        firstZone[i] = CRGB( 150, 100, 40);
      }
    }
  }
}

void Eyes_firstZone()
{
  unsigned int chance = random8();
  if ( chance > eyeChance)
  {
    unsigned int eye = random16(FIRSTZONE_LEDS);
    firstZone[eye] = CRGB(red1, green1, blue1);
    firstZone[eye - 4] = CRGB(red1, green1, blue1);
  }
  if ( chance > 39)
  {
    fadeToBlackBy( firstZone, FIRSTZONE_LEDS, 10);
  }
}

void secondZone_doStuff()
{
  if ((red1 * 2) > (green1 + blue1))
  {
    CRGBPalette16 palette_firstZone = LavaColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < SECONDZONE_LEDS; i++)
    {
      secondZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((green1 * 2) > (red1 + blue1))
  {
    CRGBPalette16 palette_firstZone = ForestColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < SECONDZONE_LEDS; i++)
    {
      secondZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((blue1 * 2) > (green1 + red1))
  {
    CRGBPalette16 palette_firstZone = CloudColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < SECONDZONE_LEDS; i++)
    {
      secondZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
  if ((blue1 * 2) == (green1 + red1))
  {
    CRGBPalette16 palette_firstZone = PartyColors_p;
    uint8_t beat = beatsin16( BeatsPerMinute, 64, 255);
    for ( int i = 0; i < SECONDZONE_LEDS; i++)
    {
      secondZone[i] = ColorFromPalette(palette_firstZone, gHue + (i * 2), beat - gHue + (i * 10));
    }
  }
}

void Solid_firstZone()
{
  fill_solid(firstZone, FIRSTZONE_LEDS, CRGB(red1, green1, blue1));
}


