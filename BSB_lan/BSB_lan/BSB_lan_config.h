/************************************************************************************/
/************************************************************************************/
/* Settings -   BEGIN                                                               */
/************************************************************************************/
/************************************************************************************/
/*
 * if defined the URL has to contain the defined passkey as first element
 * e.g.
 * http://192.168.1,50/1234/                - to view the help
 * http://192.168.1.50/1234/K               - to list all categories
 * http://192.168.1.50/1234/8700/8740/8741  - to list parameters 8700, 8740 and 8741 in one request
*/

#define PASSKEY  "1234"

/* display web interface in German language; remove definement for English */

#define LANG_DE

/* enable /X URL command to reset Arduino - might not work on older boards */

//#define RESET

/* select your heating system (default may work for other systems) */

//#define THISION
//#define FUJITSU          // for FUJITSU Wärmepumpe
//#define BROETJE
//#define BROETJE_SOB
//#define BROETJE_BSW      // so far only for handling parameters 6800-6819

/*
 * Define the pin for one wire temperature sensors
*/
//#define ONE_WIRE_BUS 3

// Activate DHT temperature/humidity sensors
#define DHT_BUS 2,3

/*
 *  Enter a MAC address and IP address for your controller below.
 *  The IP address will be dependent on your local network:
*/
byte mac[] = { 0x00, 0x80, 0x41, 0x19, 0x69, 0x90 };

/*
 * Initialize the Ethernet server library
 * with the IP address and port you want to use
 * (port 80 is default for HTTP):
*/
IPAddress ip(192,168,1,50);
EthernetServer server(80);

// Software Serial needs special pins for RX: 10-13, 50-53, 62(A8)-69(A15)
// W5100 ethernet shield uses the following pins: 10, 50-53
// use BSB bus(68,69,7) to define device as RGT2
BSB bus(68,69);

// Protect these pins from accidental GPIO access
byte exclude_GPIO[] = {10, 11, 12, 13, 50, 51, 52, 53, 62, 63, 64, 65, 66, 67, 68, 69};

// If set to 1, all messages on the bus are printed to the PC
// hardware serial interface
byte verbose = 0;
byte monitor = 0;

// Create 24h averages from these parameters
int avg_parameters[20] = {
  8700,                   // Außentemperatur
  8326                    // Brenner-Modulation
};

/* activate logging on SD-card. Requires a FAT32-formatted Micro-SD card inserted into the Ethernet-Shield's card slot */
// #define LOGGER

int log_parameters[20] = {
//  30000,                  // Logging von "rohen" Bus-Datentelegrammen (macht nur als alleiniger Parameter Sinn)
  8700,                   // Außentemperatur
  8743,                   // Vorlauftemperatur
  8314,                   // Rücklauftemperatur
//  20000,                  // Spezialparameter: Brenner-Laufzeit (/B)
//  20001,                  // Spezialparameter: Brenner-Takte (/B)
//  20002,                  // Spezialparameter: TWW-Laufzeit (/B)
//  20003,                  // Spezialparameter: TWW-Takte (/B)
//  20004,                  // Spezialparameter: 24h-Durchschnittswerte (/A)
//  20101,                  // Spezialparameter 20100-20099: DHT22-Sensoren 1-100 (/H)
//  20200                   // Spezialparameter 20200-20299: DS18B20-Sensoren 1-100 (/T)
};

unsigned long log_interval = 3600;    // logging interval in seconds
boolean log_unknown_only = 1;         // should we log only unknown commands when logging bus telegrams?
boolean log_bc_only = 0;              // should we log only broadcast commands (dest = 0x7f) when logging bus telegrams?

// Activate IPWE extension (http://xxx.xxx.xxx.xxx/ipwe.cgi)
#define IPWE

// Parameters to be displayed in IPWE extension
int ipwe_parameters[] = {
  8700,                   // Außentemperatur
  8743,                   // Vorlauftemperatur
  8314,                   // Rücklauftemperatur
  8750,                   // Gebläsedrehzahl
  8830,                   // Warmwassertemperatur
  8740,                   // Raumtemperatur Ist
  8741,                   // Raumtemperatur Soll
  8326,                   // Brenner-Modulation
  8337,                   // Startzähler Brenner
  8703,                   // Aussentemperatur gedämpft
  8704                    // Aussentemperatur gemischt
};

// defines the number of retries for the query command
#define QUERY_RETRIES  3

// defines default flag for parameters (set to FL_RONLY to make all parameters read-only)
#define DEFAULT_FLAG  0

/************************************************************************************/
/************************************************************************************/
/* Settings -   END                                                                 */
/************************************************************************************/
/************************************************************************************/
