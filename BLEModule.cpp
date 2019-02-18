//TODO: create event handler for server
//TODO: create event handler for characteristics 
//TODO: maybe add battery service?
//TODO: define for ECG
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#include "BLEModule.h"
#define THERMOMETER_SERVICE_UUID "1809"
#define THERMOMETER_TEMPERATURE_MEASUREMENT_UUID "2A1C"
#define HEARTRATE_SERVICE_UUID "180D"
#define HEARTRATE_HEARTRATE_MEASUREMENT_UUID "2A37"
#define LINKLOSS_SERVICE_UUID "1803"
#define LINKLOSS_ALERT_LEVEL_UUID "2A06"

class linkloss_Callbacks: public BLECharacteristicCallbacks {
    void onWrite(BLECharacteristic *pCharacteristic) {
    link_loss_alert_level= *pCharacteristic->getData();
    }
};

class FYP_Callbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Phone Connected");
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Phone Disconnected");
    }
};

void BLESetUp(){
  Serial.println("Starting BLESetUp"); 
  BLEDevice::init("FYP_ESP32"); //set module name
  //initializing BLE Server
  Serial.println("initializing BLE Server"); 
  BLEServer *FYP_server = BLEDevice::createServer(); 
  FYP_server->setCallbacks(new FYP_Callbacks());
  //create services
  Serial.println("initializing BLE Services"); 
  thermometer_service = FYP_server->createService(THERMOMETER_SERVICE_UUID);
  heartrate_service = FYP_server->createService(HEARTRATE_SERVICE_UUID);
  linkloss_service = FYP_server->createService(LINKLOSS_SERVICE_UUID);
  //initialize thermometer service
  Serial.println("initializing thermometer Service"); 
  thermometer_temperature_measurement = thermometer_service->createCharacteristic(THERMOMETER_TEMPERATURE_MEASUREMENT_UUID,
  BLECharacteristic::PROPERTY_INDICATE
  );
  thermometer_temperature_measurement->addDescriptor(new BLE2902());
  thermometer_service->start();
  //initialize heartrate_service
  Serial.println("initializing heartrate Service"); 
  heartrate_heartrate_measurement = heartrate_service->createCharacteristic(HEARTRATE_HEARTRATE_MEASUREMENT_UUID,
  BLECharacteristic::PROPERTY_NOTIFY
  );
  heartrate_heartrate_measurement->addDescriptor(new BLE2902());
  heartrate_service->start();
  //initialize linkloss_service
  Serial.println("initializing linkloss Service"); 
  BLECharacteristic * linkloss_alert_level = linkloss_service->createCharacteristic(LINKLOSS_ALERT_LEVEL_UUID,
  BLECharacteristic::PROPERTY_READ |
  BLECharacteristic::PROPERTY_WRITE
  );
  linkloss_alert_level->setCallbacks(new linkloss_Callbacks);
  linkloss_alert_level->setValue(&NO_ALERT,1);
  linkloss_service->start();
  //initializing BLE Advertising
  Serial.println("initializing BLE Advertising"); 
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  //initialize BLEDevice security and bonding
  Serial.println("initializing BLE Device security and bonding"); 
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
  BLESecurity *server_security= new BLESecurity();
  server_security->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  server_security->setCapability(ESP_IO_CAP_NONE);
  server_security->setInitEncryptionKey(ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK);
  //Print success message on serial
  Serial.println("BLE Initialized succesfully!");
  }