#include <Arduino.h>

void BoardGetUniqueId(uint8_t *id)
{
#ifdef ESP8266
	uint32_t uniqueId = ESP.getChipId();
	// Using ESP8266 chip ID (32 bytes only, so we use it twice
	id[7] = (uint8_t)(uniqueId >> 24);
	id[6] = (uint8_t)(uniqueId >> 16);
	id[5] = (uint8_t)(uniqueId >> 8);
	id[4] = (uint8_t)(uniqueId);
	id[3] = (uint8_t)(uniqueId >> 24);
	id[2] = (uint8_t)(uniqueId >> 16);
	id[1] = (uint8_t)(uniqueId >> 8);
	id[0] = (uint8_t)(uniqueId);
#else
	uint64_t uniqueId = ESP.getEfuseMac();
	// Using ESP32 MAC (48 bytes only, so upper 2 bytes will be 0)
	id[7] = (uint8_t)(uniqueId >> 56);
	id[6] = (uint8_t)(uniqueId >> 48);
	id[5] = (uint8_t)(uniqueId >> 40);
	id[4] = (uint8_t)(uniqueId >> 32);
	id[3] = (uint8_t)(uniqueId >> 24);
	id[2] = (uint8_t)(uniqueId >> 16);
	id[1] = (uint8_t)(uniqueId >> 8);
	id[0] = (uint8_t)(uniqueId);
#endif
}

void setup() {
  	Serial.begin(921600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t deviceId[8] = {0};
  BoardGetUniqueId(deviceId);

  	Serial.printf("BoardId: %02X-%02X-%02X-%02X-%02X-%02X-%02X-%02X\n",
				  deviceId[0],
				  deviceId[1],
				  deviceId[2],
				  deviceId[3],
				  deviceId[4],
				  deviceId[5],
				  deviceId[6],
				  deviceId[7]);

          vTaskDelay(1000);
}