// This #include statement was automatically added by the Spark IDE.
#include "application.h"
//#include "Adafruit_GFX.h"
#include "LiquidCrystal.h"

/* ============== MAIN =====================*/

LiquidCrystal *lcd;
unsigned long previousMillis;
unsigned long interval = 1800000;

int surf(String args);
void urlDecode(String &input);
int id;
char s_id[5] = "0";

void setup() {
  lcd = new LiquidCrystal(D0, D1, D2, D3, D4, D5);
  // set up the LCD's number of columns and rows:
  lcd->begin(20, 4);
  // Print a message to the LCD.
  lcd->clear();
  lcd->print("Up Next,Surf Report!");

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
  char c;
  char d = '/';
  int i;
  int current_line = 1;
  int current_col = 0;
  lcd->clear();

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
  
  lcd->setCursor(0,0);
  lcd->print(name);

  for( i = 0; i < mydata.length(); i++ ) {
      c = mydata.charAt(i);
        if( c == d ) {
          current_line++;
          current_col = 0;
      } else {
          lcd->setCursor(current_col,current_line);
          lcd->print(c);
          current_col++;
      }
  }

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
