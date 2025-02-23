#include <ModbusMaster.h>

// Define RS-485 connection pins
#define MAX485_DE  32
#define MAX485_RE  33

// Create Modbus object
ModbusMaster node;

void preTransmission() {
  digitalWrite(MAX485_RE, 1);
  digitalWrite(MAX485_DE, 1);
}

void postTransmission() {
  digitalWrite(MAX485_RE, 0);
  digitalWrite(MAX485_DE, 0);
}

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600, SERIAL_8N1, 16, 17); // RS-485 on GPIO 16 (RX), 17 (TX)

  pinMode(MAX485_RE, OUTPUT);
  pinMode(MAX485_DE, OUTPUT);
  digitalWrite(MAX485_RE, 0);
  digitalWrite(MAX485_DE, 0);

  node.begin(1, Serial2); // Modbus ID = 1
  node.preTransmission(preTransmission);
  node.postTransmission(postTransmission);
}

void loop() {
  uint8_t result;
  float usage_kWh, lagging_kVarh, leading_kVarh, lagging_pf, leading_pf;

  result = node.readInputRegisters(0x0000, 5);  // Read 5 registers

  if (result == node.ku8MBSuccess) {
    usage_kWh = node.getResponseBuffer(0) / 10.0;
    lagging_kVarh = node.getResponseBuffer(1) / 10.0;
    leading_kVarh = node.getResponseBuffer(2) / 10.0;
    lagging_pf = node.getResponseBuffer(3) / 100.0;
    leading_pf = node.getResponseBuffer(4) / 100.0;

    Serial.print("Usage kWh: "); Serial.println(usage_kWh);
    Serial.print("Lagging kVarh: "); Serial.println(lagging_kVarh);
    Serial.print("Leading kVarh: "); Serial.println(leading_kVarh);
    Serial.print("Lagging PF: "); Serial.println(lagging_pf);
    Serial.print("Leading PF: "); Serial.println(leading_pf);

    delay(15000);  // 15-minute interval
  } else {
    Serial.println("Failed to read data");
  }
}
