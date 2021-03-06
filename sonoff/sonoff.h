/*
  sonoff.h - Master header file for Sonoff-Tasmota

  Copyright (C) 2018  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _SONOFF_H_
#define _SONOFF_H_

#define D_PROGRAMNAME          "Sonoff-Tasmota"
#define D_AUTHOR               "Theo Arends"
//#define D_WEBLINK              "https://github.com/arendst/Sonoff-Tasmota"
#define D_WEBLINK              "https://bit.ly/tasmota"

/*********************************************************************************************\
 * Power Type
\*********************************************************************************************/

typedef unsigned long power_t;              // Power (Relay) type
#define POWER_MASK             0xffffffffUL // Power (Relay) full mask

/*********************************************************************************************\
 * Defines
\*********************************************************************************************/

// Changes to the following MAX_ defines will impact settings layout
#define MAX_RELAYS             8            // Max number of relays
#define MAX_LEDS               4            // Max number of leds
#define MAX_KEYS               4            // Max number of keys or buttons
#define MAX_SWITCHES           4            // Max number of switches
#define MAX_PWMS               5            // Max number of PWM channels
#define MAX_COUNTERS           4            // Max number of counter sensors
#define MAX_TIMERS             16           // Max number of Timers
#define MAX_PULSETIMERS        8            // Max number of supported pulse timers
#define MAX_FRIENDLYNAMES      4            // Max number of Friendly names
#define MAX_DOMOTICZ_IDX       4            // Max number of Domoticz device, key and switch indices
#define MAX_DOMOTICZ_SNS_IDX   12           // Max number of Domoticz sensors indices

#define MODULE                 SONOFF_BASIC // [Module] Select default model

#define MQTT_TOKEN_PREFIX      "%prefix%"   // To be substituted by mqtt_prefix[x]
#define MQTT_TOKEN_TOPIC       "%topic%"    // To be substituted by mqtt_topic, mqtt_grptopic, mqtt_buttontopic, mqtt_switchtopic

#define WIFI_HOSTNAME          "%s-%04d"    // Expands to <MQTT_TOPIC>-<last 4 decimal chars of MAC address>

#define CONFIG_FILE_SIGN       0xA5         // Configuration file signature
#define CONFIG_FILE_XOR        0x5A         // Configuration file xor (0 = No Xor)

#define HLW_PREF_PULSE         12530        // was 4975us = 201Hz = 1000W
#define HLW_UREF_PULSE         1950         // was 1666us = 600Hz = 220V
#define HLW_IREF_PULSE         3500         // was 1666us = 600Hz = 4.545A

#define MQTT_RETRY_SECS        10           // Minimum seconds to retry MQTT connection
#define APP_POWER              0            // Default saved power state Off
#define WS2812_MAX_LEDS        512          // Max number of LEDs

#define PWM_RANGE              1023         // 255..1023 needs to be devisible by 256
//#define PWM_FREQ               1000         // 100..1000 Hz led refresh
//#define PWM_FREQ               910          // 100..1000 Hz led refresh (iTead value)
#define PWM_FREQ               880          // 100..1000 Hz led refresh (BN-SZ01 value)

#define DEFAULT_POWER_DELTA    80           // Power change percentage
#define MAX_POWER_HOLD         10           // Time in SECONDS to allow max agreed power
#define MAX_POWER_WINDOW       30           // Time in SECONDS to disable allow max agreed power
#define SAFE_POWER_HOLD        10           // Time in SECONDS to allow max unit safe power
#define SAFE_POWER_WINDOW      30           // Time in MINUTES to disable allow max unit safe power
#define MAX_POWER_RETRY        5            // Retry count allowing agreed power limit overflow

#define STATES                 20           // State loops per second
#define IMMINENT_RESET_FACTOR  10           // Factor to extent button hold time for imminent Reset to default 40 seconds using KEY_HOLD_TIME of 40
#define SYSLOG_TIMER           600          // Seconds to restore syslog_level
#define SERIALLOG_TIMER        600          // Seconds to disable SerialLog
#define OTA_ATTEMPTS           5            // Number of times to try fetching the new firmware

#define INPUT_BUFFER_SIZE      255          // Max number of characters in (serial) command buffer
#define CMDSZ                  24           // Max number of characters in command
#define TOPSZ                  100          // Max number of characters in topic string
#define LOGSZ                  400          // Max number of characters in log
#define MIN_MESSZ              893          // Min number of characters in MQTT message

#ifdef USE_MQTT_TLS
  #define WEB_LOG_SIZE         2000         // Max number of characters in weblog
#else
  #define WEB_LOG_SIZE         4000         // Max number of characters in weblog
#endif

#define MAX_BACKLOG            30           // Max number of commands in backlog
#define MIN_BACKLOG_DELAY      2            // Minimal backlog delay in 0.1 seconds

#define SOFT_BAUDRATE          9600         // Default software serial baudrate
#define APP_BAUDRATE           115200       // Default serial baudrate
#define SERIAL_POLLING         100          // Serial receive polling in ms
#define MAX_STATUS             11           // Max number of status lines

/*
// Removed from esp8266 core since 20171105
#define min(a,b) ((a)<(b)?(a):(b))
#define max(a,b) ((a)>(b)?(a):(b))
*/

//enum ws2812NeopixelbusFeature { NEO_RGB, NEO_GRB, NEO_BRG, NEO_RBG, NEO_3LED, NEO_RGBW, NEO_GRBW };  // Doesn't work
#define NEO_RGB                0            // Neopixel RGB leds
#define NEO_GRB                1            // Neopixel GRB leds
#define NEO_BRG                2            // Neopixel BRG leds
#define NEO_RBG                3            // Neopixel RBG leds
#define NEO_3LED               4            // Placeholder to test for 4 led types
#define NEO_RGBW               5            // Neopixel RGBW leds
#define NEO_GRBW               6            // Neopixel GRBW leds

#define MQTT_PUBSUBCLIENT      1            // Mqtt PubSubClient library
#define MQTT_TASMOTAMQTT       2            // Mqtt TasmotaMqtt library based on esp-mqtt-arduino
#define MQTT_ESPMQTTARDUINO    3            // Mqtt esp-mqtt-arduino library by Ingo Randolf

/*********************************************************************************************\
 * Enumeration
\*********************************************************************************************/

enum WeekInMonthOptions {Last, First, Second, Third, Fourth};
enum DayOfTheWeekOptions {Sun=1, Mon, Tue, Wed, Thu, Fri, Sat};
enum MonthNamesOptions {Jan=1, Feb, Mar, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec};
enum HemisphereOptions {North, South};
enum GetDateAndTimeOptions { DT_LOCAL, DT_UTC, DT_RESTART, DT_UPTIME };

enum LoggingLevels {LOG_LEVEL_NONE, LOG_LEVEL_ERROR, LOG_LEVEL_INFO, LOG_LEVEL_DEBUG, LOG_LEVEL_DEBUG_MORE, LOG_LEVEL_ALL};

enum WifiConfigOptions {WIFI_RESTART, WIFI_SMARTCONFIG, WIFI_MANAGER, WIFI_WPSCONFIG, WIFI_RETRY, WIFI_WAIT, MAX_WIFI_OPTION};

enum SwitchModeOptions {TOGGLE, FOLLOW, FOLLOW_INV, PUSHBUTTON, PUSHBUTTON_INV, PUSHBUTTONHOLD, PUSHBUTTONHOLD_INV, PUSHBUTTON_TOGGLE, MAX_SWITCH_OPTION};

enum LedStateOptions {LED_OFF, LED_POWER, LED_MQTTSUB, LED_POWER_MQTTSUB, LED_MQTTPUB, LED_POWER_MQTTPUB, LED_MQTT, LED_POWER_MQTT, MAX_LED_OPTION};

enum EmulationOptions {EMUL_NONE, EMUL_WEMO, EMUL_HUE, EMUL_MAX};

enum TopicOptions { CMND, STAT, TELE, nu1, RESULT_OR_CMND, RESULT_OR_STAT, RESULT_OR_TELE };

enum ExecuteCommandPowerOptions { POWER_OFF, POWER_ON, POWER_TOGGLE, POWER_BLINK, POWER_BLINK_STOP, power_nu1, POWER_OFF_NO_STATE, POWER_ON_NO_STATE, power_nu2, POWER_SHOW_STATE };

enum PowerOnStateOptions { POWER_ALL_OFF, POWER_ALL_ON, POWER_ALL_SAVED_TOGGLE, POWER_ALL_SAVED, POWER_ALL_ALWAYS_ON, POWER_ALL_OFF_PULSETIME_ON };

enum ButtonStates {PRESSED, NOT_PRESSED};

enum SettingsParmaIndex {P_HOLD_TIME, P_MAX_POWER_RETRY, P_MAX_PARAM8};

enum DomoticzSensors {DZ_TEMP, DZ_TEMP_HUM, DZ_TEMP_HUM_BARO, DZ_POWER_ENERGY, DZ_ILLUMINANCE, DZ_COUNT, DZ_VOLTAGE, DZ_CURRENT, DZ_AIRQUALITY, DZ_MAX_SENSORS};

enum Ws2812ClockIndex { WS_SECOND, WS_MINUTE, WS_HOUR, WS_MARKER };
enum Ws2812Color { WS_RED, WS_GREEN, WS_BLUE };
enum LightTypes {LT_BASIC, LT_PWM1, LT_PWM2, LT_PWM3, LT_PWM4, LT_PWM5, LT_PWM6, LT_PWM7, LT_NU8, LT_NU9, LT_NU10, LT_WS2812, LT_RGBW, LT_RGBWC};
enum LichtSubtypes {LST_NONE, LST_SINGLE, LST_COLDWARM, LST_RGB, LST_RGBW, LST_RGBWC};
enum LichtSchemes {LS_POWER, LS_WAKEUP, LS_CYCLEUP, LS_CYCLEDN, LS_RANDOM, LS_MAX};

enum XsnsFunctions {FUNC_INIT, FUNC_LOOP, FUNC_EVERY_50_MSECOND, FUNC_EVERY_SECOND, FUNC_PREP_BEFORE_TELEPERIOD, FUNC_JSON_APPEND, FUNC_WEB_APPEND, FUNC_SAVE_BEFORE_RESTART,
                    FUNC_COMMAND, FUNC_MQTT_SUBSCRIBE, FUNC_MQTT_INIT, FUNC_MQTT_DATA, FUNC_SET_POWER, FUNC_SHOW_SENSOR};

const uint8_t kDefaultRfCode[9] PROGMEM = { 0x21, 0x16, 0x01, 0x0E, 0x03, 0x48, 0x2E, 0x1A, 0x00 };

/*********************************************************************************************\
 * Extern global variables
\*********************************************************************************************/

extern uint8_t light_device;  // Light device number

#endif  // _SONOFF_H_