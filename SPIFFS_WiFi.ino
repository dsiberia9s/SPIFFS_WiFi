#include <M5Stack.h>
#include <WiFi.h>
#include "SPIFFS.h"
#include "FS.h"

char * WiFiAuto(int timeout = 5000) {
  timeout = (timeout < 1000) ? 1000 : timeout;
  File file;
  char * WiFiSSID;
  char * WiFiPswd;
  const char * path;
  bool r = false;
  WiFi.disconnect(true);
  delay(100);
  for (int i = 0; i < WiFi.scanNetworks(); i++) {
    File root = SPIFFS.open("/");
    file = root.openNextFile();
    while (file) {
      if (!file.isDirectory()) {
        String WiFiSSID_ = WiFi.SSID(i);
        WiFiSSID = new char[WiFiSSID_.length() + 1];
        strcpy(WiFiSSID, WiFiSSID_.c_str());
        path = file.name();
        if ((strstr(path, WiFiSSID) != NULL) && strstr(file.name(), ".wifi")) {
          r = true;
        }
        if (r) break;
      }
      file = root.openNextFile();
    }
    root.close();
    if (r) break;
  }
  if (r) {
    file = SPIFFS.open(path);
    String WiFiPswd_ = "";
    while (file.available()){
      char ch = file.read();
      if (ch == 0x0A) break;
      WiFiPswd_ += ch;
    }
    file.close();
    WiFiPswd = new char[WiFiPswd_.length() + 1];
    strcpy(WiFiPswd, WiFiPswd_.c_str());
    WiFi.begin((char *)WiFiSSID, (char *)WiFiPswd);
    delete WiFiPswd;
    int s = 250;
    for (int i = 0; i < timeout; i += s) {
      if (WiFi.status() == WL_CONNECTED) return WiFiSSID;
      delay(s);
    }
  }
  return NULL;
}

void setup() {
  M5.begin();
  M5.Lcd.setTextSize(2);
  SPIFFS.begin(true);
  M5.Lcd.println("Searching Wi-Fi,\nplease wait...");
  char * ssid = WiFiAuto(); 
  if (ssid) {
    M5.Lcd.println("Connectid to ");
    M5.Lcd.println(ssid);
    M5.Lcd.println(WiFi.localIP());
  } else {
    M5.Lcd.println("Can't connect to WiFi network :(\nTry to REBOOT device");
  }
}

void loop() {

}
