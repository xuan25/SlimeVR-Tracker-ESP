/*
	SlimeVR Code is placed under the MIT license
	Copyright (c) 2024 Gorbit99 & SlimeVR Contributors

	Permission is hereby granted, free of charge, to any person obtaining a copy
	of this software and associated documentation files (the "Software"), to deal
	in the Software without restriction, including without limitation the rights
	to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
	copies of the Software, and to permit persons to whom the Software is
	furnished to do so, subject to the following conditions:

	The above copyright notice and this permission notice shall be included in
	all copies or substantial portions of the Software.

	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
	IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
	FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
	AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
	LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
	OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
	THE SOFTWARE.
*/

#pragma once

#include "../logging/Logger.h"

#include <quat.h>
#include <vector3.h>
#include <algorithm>
#include <cstdint>
#ifdef ESP8266
#include <ESP8266WiFi.h>
#include <espnow.h>
#elif defined(ESP32)
#include <WiFi.h>
#include <esp_now.h>
#endif
#include <cmath>

namespace SlimeVR::Network {

class ESPNowConnection {
public:
	void setup();
	void broadcastPairingRequest();
	void sendPacket(uint8_t sensorId, float batteryPercentage, float batteryVoltage, Quat fusedQuat, Vector3 accel);

private:
	bool registerPeer(uint8_t macAddress[6]);
	void sendConnectionRequest();

	void handleMessage(uint8_t *senderMacAddress, const uint8_t *data, uint8_t dataLen);

	template<unsigned int Q>
	static constexpr inline int16_t toFixed(float number) {
		auto unsaturated = static_cast<int32_t>(number * (1 << Q));
		auto saturated = std::clamp(
				unsaturated,
				static_cast<int32_t>(-32768),
				static_cast<int32_t>(32767)
		);
		return static_cast<int16_t>(saturated);
	}

	bool paired = false;
	bool connected = false;
	uint8_t dongleMacAddress[6];
	uint8_t trackerId;

	Logging::Logger m_Logger = Logging::Logger("ESPNowConnection");

	#if defined(ESP8266)
	static uint8_t broadcastMacAddress[6];
	#elif defined(ESP32)
	static constexpr uint8_t broadcastMacAddress[6] = {
		0xff, 0xff, 0xff, 0xff, 0xff, 0xff
	};
	#endif

	static constexpr uint8_t espnowWifiChannel = 6;

	#if defined(ESP8266)
	friend void onReceive(uint8_t *, uint8_t *, uint8_t);
	#elif defined(ESP32)
	friend void onReceive(const esp_now_recv_info_t *, const uint8_t *, int);
	#endif
};

}  // namespace SlimeVR::Network