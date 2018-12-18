
//USER CONFIGURED SECTION START//
int holdTime = 1500;
#define wifi_ssid "xxxx" //enter your WIFI SSID
#define wifi_password "xxxxx" //enter your WIFI Password
char mqtt_server[64] = ""; // These defaults may be overwritten with values saved by the web interface
char mqtt_port[6] = "1883";
char mqtt_user[32] = "DVES_USER";
char mqtt_password[32] = "DVES_PASS";
char versionno[8] = "0.7.18";
char mcuHostName[64]; 
char mqtt_client_name[64] = "CeilingLightMCU"; // Client connections can't have the same connection name
bool Mqttconnected = 0 ;
//USER CONFIGURED SECTION END//

/*****************  DECLARATIONS  ****************************************/

WiFiClient espClient;
PubSubClient client(espClient);
SimpleTimer timer;

//#define espName  "CPL";
/*****************  GLOBAL VARIABLES  ************************************/


const int FrontLeft = 4; 
const int FrontMiddle = 16; 
const int FrontRight = 17; 
const int MiddleLeft = 13; 
const int MiddleRight = 5; 
const int BackLeft = 14; 
const int BackMiddle = 27; 
const int BackRight = 26; 
const int ambientPin = 15; 
const int switchPin = 22;

int FrontLeft_Bright = 0;
int FrontMiddle_Bright = 0;
int FrontRight_Bright = 0;
int MiddleLeft_Bright = 0;
int MiddleRight_Bright = 0;
int BackLeft_Bright = 0;
int BackMiddle_Bright = 0;
int BackRight_Bright = 0;
int Master_Bright = 0;

int freq = 800;
int resolution = 8;

bool boot = true;

long buttonHold = 0;
long startPress = 0;
bool pressed = false;

bool lightsOn = false;
WiFiServer telnetServer(23);
WiFiClient telnetClient;
//ESP8266HTTPUpdateServer httpUpdater;


char wifiConfigAP[19]; 
char wifiConfigPass[9];                          // AP config password, always 8 chars + NUL
bool shouldSaveConfig = false;                   // Flag to save json config to SPIFFS
const char LED_STYLE[] = "<style>button{background-color:#03A9F4;}body{width:60%;margin:auto;}</style>";

WiFiClient wifiClient;
WebServer webServer(80);


int brightness_index = 0;
int cycleTime = 0;
int brightness_values[] = { 15, 95, 170, 255 };

const char *getDeviceID() {
  char *identifier = new char[30];
  strcpy(identifier, mqtt_client_name);
  strcat_P(identifier, PSTR("-"));

  char cidBuf[7];
  sprintf(cidBuf, "%06X", ESP.getEfuseMac());
  strcat_P(identifier, cidBuf);

  return identifier;
}

void debuglineprint(String debugText)
{ // Debug output line of text to our debug targets
  String debugTimeText = "[+" + String(float(millis()) / 1000, 3) + "s] " + debugText;
  Serial.print(debugTimeText);
  Serial.print(debugTimeText);
  Serial.flush();
  
}


/*****************  SYSTEM FUNCTIONS  *************************************/
