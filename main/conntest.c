#include "conntest.h"
#include "rootca.h"

static const char *TAG = "connTest";

static esp_transport_list_handle_t transportList;

static void conntest_task(void *pvparameters)
{
	while(1)
	{
		ESP_LOGI(TAG, "Start connTest example");

		esp_transport_handle_t xTransport = esp_transport_list_get_transport(transportList, "_conntest");

		esp_transport_ssl_set_cert_data_der( xTransport, ( const char * ) DEF_ROOT_CA, sizeof(DEF_ROOT_CA));
		if(esp_transport_connect( xTransport, "jaga-dev-iothubdeviceprovisioning.azure-devices-provisioning.net", 8883, 5000 ) < 0 )
		{
			ESP_LOGE( TAG, "Failed establishing TLS connection (esp_transport_connect failed)" );
		}
		else
			ESP_LOGI( TAG, "Connected to server");

		esp_transport_close( xTransport );

		ESP_LOGI(TAG, "Finished connTest example");

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void startConnTest()
{

	transportList = esp_transport_list_init();

	/* create new transport to the transport list */
	esp_transport_handle_t ssl = esp_transport_ssl_init();
	if(ssl == NULL)
	{
		esp_restart();
	}
	esp_transport_list_add(transportList, ssl, "_conntest");

	xTaskCreate(&conntest_task, "test_task", 8192, NULL, 5, NULL);
}
