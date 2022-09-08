/**The MIT License (MIT)
Copyright (c) 2015 by Daniel Eichhorn
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
See more at http://blog.squix.ch
*/

#include <simpleDSTadjust.h>

// Setup

#define WIFI_SSID "WIFI"
#define WIFI_PASS "wifiPASSWORD"
#define WIFI_HOSTNAME "ThingPulse-weather-station-color"




const int UPDATE_INTERVAL_SECS = 15 * 60; // Update every 10 minutes
const int SLEEP_INTERVAL_SECS = 0;   // Going to Sleep after idle times, set 0 for dont sleep


// OpenWeatherMap Settings
// Sign up here to get an API key: https://docs.thingpulse.com/how-tos/openweathermap-key/
String OPEN_WEATHER_MAP_APP_ID = "xxxxxxxxxxxxxxxxxxxxxxxxxxxx";
/*
Go to https://openweathermap.org/find?q= and search for a location. Go through the
result set and select the entry closest to the actual location you want to display 
data for. It'll be a URL like https://openweathermap.org/city/2657896. The number
at the end is what you assign to the constant below.
*/

String OPEN_WEATHER_MAP_LOCATION_ID = "999999";
String DISPLAYED_CITY_NAME = "location";

/*
Arabic -> ar, Bulgarian -> bg, Catalan -> ca, Czech -> cz, German -> de, Greek -> el,
English -> en, Persian (Farsi) -> fa, Finnish -> fi, French -> fr, Galician -> gl,
Croatian -> hr, Hungarian -> hu, Italian -> it, Japanese -> ja, Korean -> kr,
Latvian -> la, Lithuanian -> lt, Macedonian -> mk, Dutch -> nl, Polish -> pl,
Portuguese -> pt, Romanian -> ro, Russian -> ru, Swedish -> se, Slovak -> sk,
Slovenian -> sl, Spanish -> es, Turkish -> tr, Ukrainian -> ua, Vietnamese -> vi,
Chinese Simplified -> zh_cn, Chinese Traditional -> zh_tw.
*/
String OPEN_WEATHER_MAP_LANGUAGE = "de";
const uint8_t MAX_FORECASTS = 10;

// Adjust according to your language
const String WDAY_NAMES[] = {"So.", "Mo.", "Di.", "Mi.", "Do.", "Fr.", "Sa."};
const String MONTH_NAMES[] = {"JAN", "FEB", "MAR", "APR", "MAI", "JUN", "JUL", "AUG", "SEP", "OKT", "NOV", "DEZ"};
const String MOON_PHASES[] = {"Neumond", "zun.Sichelmond", "1. Viertel", "zun.Dreiviertelmond",
                              "Vollmond", "abn.Dreiviertelmond", "3. Viertel", "abn.Sichelmond"};

#define UTC_OFFSET +3       //UTC +3  OESZ  Osteuropäische Sommerzeit Athen     AB 30. Okt 2022 -->  UTC +2 OEZ Osteuropäische Zeit
//#define UTC_OFFSET +2       //UTC +2  OESZ  Osteuropäische Sommerzeit München     AB 30. Okt 2022 -->  UTC +1 OEZ Osteuropäische Zeit

struct dstRule StartRule = {"CEST", Last, Sun, Mar, 2, 3600}; // Central European Summer Time = UTC/GMT +2 hours
struct dstRule EndRule = {"CET", Last, Sun, Oct, 2, 0};       // Central European Time = UTC/GMT +1 hour

// Settings for Boston
// #define UTC_OFFSET -5
// struct dstRule StartRule = {"EDT", Second, Sun, Mar, 2, 3600}; // Eastern Daylight time = UTC/GMT -4 hours
// struct dstRule EndRule = {"EST", First, Sun, Nov, 1, 0};       // Eastern Standard time = UTC/GMT -5 hour

// values in metric or imperial system?
const boolean IS_METRIC = true;

// Change for 12 Hour/ 24 hour style clock
bool IS_STYLE_12HR = false;

// change for different ntp (time servers)
#define NTP_SERVERS "0.ch.pool.ntp.org", "1.ch.pool.ntp.org", "2.ch.pool.ntp.org"
// #define NTP_SERVERS "us.pool.ntp.org", "time.nist.gov", "pool.ntp.org"



// Pins for the ILI9341
#define TFT_DC D2
#define TFT_CS D1
#define TFT_LED D8

#define HAVE_TOUCHPAD
#define TOUCH_CS D3
#define TOUCH_IRQ  D4


/***************************
 * End Settings
 **************************/
