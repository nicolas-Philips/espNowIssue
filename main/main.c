#include "station_example_main.h"
#include "espnow_example.h"
#include "conntest.h"

void app_main(void)
{
	/* 
	 * connect to wifi (STA)
	 * Complete copy from: https://github.com/espressif/esp-idf/tree/d6d8324ad9b957f85ecb323ec0db12c4d03a93c4/examples/wifi/getting_started/station
	 * TO CONNECT:
	 * 	- Set SSID in sdkconfig
	 *	- Set password in sdkconfig
	 */ 
	wifi_example_init();

	/*
	 * Run ESP now example
	 * espNOW part copied from: https://github.com/espressif/esp-idf/tree/d6d8324ad9b957f85ecb323ec0db12c4d03a93c4/examples/wifi/espnow
	 * set CHANNEL to 0
	 * no further changes made
	 */
	example_espnow_init();

	/*
	 * Create tls connection to azure server, disconnect and try again 
	 * The minimum code example (code comes from azure Iot)
	 */
	startConnTest();
}