// This #include statement was automatically added by the Spark IDE.
#include "application.h"
//#include "Adafruit_GFX.h"
#include "Adafruit_SSD1306.h"

/* ============== MAIN =====================*/

//Use I2C with OLED RESET pin on D4
#define OLED_RESET D4
Adafruit_SSD1306 oled(OLED_RESET);

unsigned long previousMillis;
unsigned long interval = 30000;

int surf(String args);
void urlDecode(String &input);
int id;
char s_id[5] = "0";

void setup() {
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3D);  
  oled.clearDisplay();
  oled.setTextSize(1);
  oled.setTextColor(WHITE);
  oled.setCursor(0,0);
  oled.println("Up next,\nsurf report!");
  oled.display(); // show splashscreen
  Spark.function("surf",surf);
}

void loop() {
  unsigned long currentMillis = millis();

  if(currentMillis - previousMillis > interval) {
    previousMillis = currentMillis;
    snprintf(s_id,sizeof(s_id),"%d",id);
    Spark.publish("refresh",s_id);
  }
}

int surf(String args) {
  urlDecode(args);

  int idx = args.indexOf("/");
  String myid = args.substring(0,idx);
  String mydata = args.substring(idx+1);

  char idbuf[5];
  myid.toCharArray(idbuf, sizeof(idbuf));
  id = atoi(idbuf);
  
  String name;
  switch (id) {
    case 2456: 
    name = "Playa Guiones";
    break;
    case 362: 
    name = "Higgins Beach";
    break;
    case 852: 
    name = "Old Orchard Beach";
    break;
    case 401:
    name = "Topsail Island";
    break;
    case 650: 
    name = "Carolina Beach";
    break;
  }

  oled.clearDisplay();
  oled.setCursor(0,0);

  mydata.replace('/','\n');
  oled.println(name);
  oled.println(mydata);

  oled.display();
  return 1;
}

void urlDecode(String &input)
{
  input.trim();
  input.replace("%20", " ");
  input.replace("+", " ");
  input.replace(".", "mph");
  input.replace("@", "ft ");
  input.replace("_", "");
  input.replace("%21", "Today: ");
  input.replace("%7E", "Tomorrow: ");
  input.replace("%22", "\"");
  input.replace("%23", "#");
  input.replace("%24", "$");
  input.replace("%25", "%");
  input.replace("%26", "&");
  input.replace("%27", "\'");
  input.replace("%28", "(");
  input.replace("%29", ")");
  input.replace("%30", "*");
  input.replace("%31", "+");
  input.replace("%2C", ",");
  input.replace("%2E", ".");
  input.replace("%2F", "/");
  input.replace("%2C", ",");
  input.replace("%3A", ":");
  input.replace("%3A", ";");
  input.replace("%3C", "<");
  input.replace("%3D", "=");
  input.replace("%3E", ">");
  input.replace("%3F", "?");
  input.replace("%40", "@");
  input.replace("%5B", "[");
  input.replace("%5C", "\\");
  input.replace("%5D", "]");
  input.replace("%5E", "^");
  input.replace("%5F", "-");
  input.replace("%60", "`");
}
