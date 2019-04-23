/*****************  NEEDED TO MAKE NODEMCU WORK ***************************/
#define FASTLED_INTERRUPT_RETRY_COUNT 0
#define FASTLED_ESP8266_RAW_PIN_ORDER
#define ESPALEXA_ASYNC

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
#define HOUR_MODE 0                 // 1 = use 12 hour time, 0 = use 24 hour time

WiFiUDP Udp;
unsigned int localPort = 8888;  // local port to listen for UDP packets
time_t getNtpTime();
void digitalClockDisplay();
void printDigits(int digits);
void sendNTPpacket(IPAddress &address);
//const int timeZone = 1;     // Central European Time
const int timeZone = -5 + DAYLIGHT_SAVINGS;  // Eastern Standard Time (USA)
//const int timeZone = -4;  // Eastern Daylight Time (USA)
//const int timeZone = -8;  // Pacific Standard Time (USA)
//const int timeZone = -7;  // Pacific Daylight Time (USA)


#define USER_SSID                 "YOUR_WIFI_SSID"
#define USER_PASSWORD             "YOUR_WIFI_PASSWORD"
#define USER_MQTT_SERVER          "UNUSED"
#define USER_MQTT_PORT            1883
#define USER_MQTT_USERNAME        "UNUSED"
#define USER_MQTT_PASSWORD        "UNUSED"
#define USER_MQTT_CLIENT_NAME     "LED_Grid_Project"           // Used to define MQTT topics, MQTT Client ID, and ArduinoOTA


#define ZONEONE                         1                   //ZONEONE is pin D1, 1 = zone used 0 = zone unused
#define FIRSTZONE_SECTIONS              7                   //Number of roof sections setup below
#define FIRSTZONE_LEDS                  83                  //Number of LEDS in this zone 
#define FIRSTZONE_COLOR_ORDER           GRB                 //Color orders, can be RGB, RBG, GRB, GBR, BRG, BGR 

/*****************************    ZONEONE ROOF SETUP    *************************************/
/*****************************    ZONEONE ROOF SETUP    *************************************/

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
#define LED_COUNT (RESX * RESY) + 6   // total number of leds
#define SECONDZONE_LEDS 300           // fake LED Zone


/***********************  WIFI AND MQTT SETUP *****************************/
/***********************  DON'T CHANGE THIS INFO *****************************/

const char* ssid = USER_SSID ;
const char* password = USER_PASSWORD ;
const char* mqtt_server = USER_MQTT_SERVER ;
const int mqtt_port = USER_MQTT_PORT ;
const char *mqtt_user = USER_MQTT_USERNAME ;
const char *mqtt_pass = USER_MQTT_PASSWORD ;
const char *mqtt_client_name = USER_MQTT_CLIENT_NAME ;

/*****************  DECLARATIONS  ****************************************/

WiFiClient espClient;
PubSubClient client(espClient);
SimpleTimer timer;
Espalexa espalexa;

void colorLightChanged1(uint8_t brightness, uint32_t rgb);
void colorLightChanged2(uint8_t brightness, uint32_t rgb);
void colorLightChanged3(uint8_t brightness, uint32_t rgb);
boolean connectWifi();
boolean wifiConnected = false;

CRGB firstZone[FIRSTZONE_LEDS];
CRGB secondZone[SECONDZONE_LEDS];
const int Pin_firstZone = 5; //marked as D1 on the board
const int Pin_secondZone = 4; //marked as D1 on the board
int center_firstZone = 0;
int step_firstZone = -1;
int previousLED_firstZone = 0;




/*****************  GENERAL VARIABLES  *************************************/

CRGBPalette16 gPal;
int glitterFrequency = 100;
int lightningChance = 65280;
int firesize = 40;
int SPARKING = 85;
int COOLING =  120;
bool gReverseDirection = false;
uint8_t mark = 0;
uint8_t gHue = 0;
uint8_t startPosition = 0;
uint8_t glitterChance = 250;
int chaseDelay = 1000;
int lastPosition = 1;
int lightning = 1;
int raceSpeed = 12;
int BeatsPerMinute = 62;
uint8_t numberOfRainbows = 7;
int twinkleChance = 250;
int eyeChance = 248;
bool boot = true;
String effect = "Fill_Solid";
bool showGlitter = false;
bool showLightning = false;
bool audioEffects = false;
bool showLights = true;
byte red1 = 255;
byte green1 = 0;
byte blue1 = 0;
byte red2 = 0;
byte green2 = 255;
byte blue2 = 0;
byte red3 = 0;
byte green3 = 0;
byte blue3 = 255;
byte redG = 255;
byte greenG = 255;
byte blueG = 255;
byte brightness = 100;
char charPayload[50];
int locatorLED = 0;
char MQTT_locatorLED[50];
int locatorDelay = 1000;
byte displayMode = 1;
byte notdigits[10][DIGITX * DIGITY] = {
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },        // 0
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


/*****************  SYSTEM FUNCTIONS  *************************************/
/*****************  SYSTEM FUNCTIONS  *************************************/
/*****************  SYSTEM FUNCTIONS  *************************************/
/*****************  SYSTEM FUNCTIONS  *************************************/
/*****************  SYSTEM FUNCTIONS  *************************************/

boolean connectWifi() {
  boolean state = true;
  int i = 0;

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  Serial.println("");
  Serial.println("Connecting to WiFi");

  // Wait for connection
  Serial.print("Connecting...");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
    if (i > 40) {
      state = false; break;
    }
    i++;
  }
  Serial.println("");
  if (state) {
    Serial.print("Connected to ");
    Serial.println(ssid);
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());
  }
  else {
    Serial.println("Connection failed.");
  }
  return state;
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
  FastLED.addLeds<WS2812B, Pin_firstZone, FIRSTZONE_COLOR_ORDER>(firstZone, FIRSTZONE_LEDS);
  FastLED.addLeds<WS2812B, Pin_secondZone, FIRSTZONE_COLOR_ORDER>(secondZone, SECONDZONE_LEDS);
  //FastLED.setDither( 0 );
  WiFi.setSleepMode(WIFI_NONE_SLEEP);
  WiFi.mode(WIFI_STA);
  wifiConnected = connectWifi();
  if (wifiConnected)
  {
    espalexa.addDevice("LED Grid", colorLightChanged1);
    espalexa.addDevice("Grid Color 2", colorLightChanged2);
    espalexa.addDevice("Grid Color 3", colorLightChanged3);
    espalexa.begin();
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
  choosePattern();
  displayTime();
  gridRemove();
  FastLED[0].showLeds(brightness);
  FastLED[1].showLeds(brightness);
}

/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/
/*****************  ALEXA CALLBACKS  ****************************************/

void colorLightChanged1(uint8_t brightnessCommand, uint32_t rgb)
{
  Serial.println("Got Data for Grid1");
  Serial.println(brightnessCommand);
  if (brightnessCommand == 0)
  {
    showLights = false;
  }
  else
  {
    showLights = true;
  }
  brightness = brightnessCommand;
  red1 = (rgb >> 16) & 0xFF;
  green1 = (rgb >>  8) & 0xFF;
  blue1 = rgb & 0xFF;
  Serial.println(showLights);
}

void colorLightChanged2(uint8_t brightnessCommand, uint32_t rgb)
{
  Serial.println("Got Data for Grid2");
  Serial.println(brightnessCommand);
  fill_solid(firstZone, FIRSTZONE_LEDS, CRGB::Black);
  int brightnessPercent = espalexa.toPercent(brightnessCommand);
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
  red2 = (rgb >> 16) & 0xFF;
  green2 = (rgb >>  8) & 0xFF;
  blue2 = rgb & 0xFF;
  Serial.println(showLights);
}

void colorLightChanged3(uint8_t brightnessCommand, uint32_t rgb)
{
  Serial.println("Got Data for Grid3");
  Serial.println(brightnessCommand);
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
  red3 = (rgb >> 16) & 0xFF;
  green3 = (rgb >>  8) & 0xFF;
  blue3 = rgb & 0xFF;
  Serial.println(showLights);
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
  for ( int mark = 0; mark < FIRSTZONE_LEDS; mark += 30)
  {
    for ( int i = 0; i < 9; i++)
    {
      if (startPosition == 0 || startPosition == 1)
      {
        if (i + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + mark] = CRGB(red1, green1, blue1);
        }
        if (i + 10 + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + 10 + mark] = CRGB(red2, green2, blue2);
        }
        if (i + 20 + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + 20 + mark] = CRGB(red3, green3, blue3);
        }
      }
      if (startPosition == 2 || startPosition == 3)
      {
        if (i + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + mark] = CRGB(red2, green2, blue2);
        }
        if (i + 10 + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + 10 + mark] = CRGB(red3, green3, blue3);
        }
        if (i + 20 + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + 20 + mark] = CRGB(red1, green1, blue1);
        }
      }
      if (startPosition == 4 || startPosition == 5)
      {
        if (i + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + mark] = CRGB(red3, green3, blue3);
        }
        if (i + 10 + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + 10 + mark] = CRGB(red1, green1, blue1);
        }
        if (i + 20 + mark <= FIRSTZONE_LEDS)
        {
          firstZone[i + 20 + mark] = CRGB(red2, green2, blue2);
        }
      }
    }
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

void Locator_firstZone()
{
  if (locatorLED <= FIRSTZONE_LEDS)
  {
    fill_solid(firstZone, FIRSTZONE_LEDS, CRGB::Black);
    firstZone[locatorLED] = CRGB(red1, green1, blue1);
  }
}

