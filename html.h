/***
 * Install the following libraries through zip-file from Github
 * - ESPAsyncTCP        (https://github.com/me-no-dev/ESPAsyncTCP)
 * - ESPAsyncWebServer  (https://github.com/me-no-dev/ESPAsyncWebServer)
 * 
 * This is for the webinterface for configuration
 ***/
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
AsyncWebServer server(80);
//const char* PARAM_INPUT_cityName = "input1";
const char* PARAM_INPUT_cityName = "Stadtname";
const char* PARAM_INPUT_mapLocation = "OPEN_WEATHER_MAP_LOCATION_ID";
const char* PARAM_INPUT_OWM_ID = "OPEN_WEATHER_MAP_APP_ID";
// HTML web page to handle 3 input fields (input1, input2, input3)
const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html><head>
  <title>ESP Input Form</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  </head><body>
  <form action="/get">
    Geben Sie hier den Stadtnamen ein: <input type="text" name="Stadtname">
    <input type="submit" value="Save & Submit">
  </form><br>   
  <form action="/get">
    OPEN_WEATHER_MAP_LOCATION_ID: <input type="text" name="OPEN_WEATHER_MAP_LOCATION_ID">
    <input type="submit" value="Save & Submit">
  </form><br>
  <form action="/get">
    OPEN_WEATHER_MAP_APP_ID: <input type="text" name="OPEN_WEATHER_MAP_APP_ID">
    <input type="submit" value="Save & Submit">
  </form>
</body></html>)rawliteral";

void notFound(AsyncWebServerRequest *request) {
  request->send(404, "text/plain", "Not found");
}
// ----- End of webinterface addon ------
// --------------------------------------
