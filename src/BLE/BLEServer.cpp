//TODO: create event handler for server
//TODO: create event handler for characteristics 
//TODO: maybe add battery service?
//TODO: define for ECG
// See the following for generating UUIDs:
// https://www.uuidgenerator.net/
#include "BLEServer.h"
void BLESetUpBonding(){
//initialize BLEDevice security and bonding
  Serial.println("initializing BLE Device security and bonding"); 
  BLEDevice::setEncryptionLevel(ESP_BLE_SEC_ENCRYPT);
  BLESecurity *server_security= new BLESecurity();
  server_security->setAuthenticationMode(ESP_LE_AUTH_REQ_SC_BOND);
  server_security->setCapability(ESP_IO_CAP_NONE);
  server_security->setInitEncryptionKey(ESP_BLE_ENC_KEY_MASK | ESP_BLE_ID_KEY_MASK);
}
void BLESetUpAdvertising(){
  //initializing BLE Advertising
  Serial.println("initializing BLE Advertising"); 
  BLEAdvertising *pAdvertising = BLEDevice::getAdvertising();
  pAdvertising->setScanResponse(true);
  pAdvertising->setMinPreferred(0x06);  
  pAdvertising->setMinPreferred(0x12);
  BLEDevice::startAdvertising();
  rgbLED->setBlink(true);
  rgbLED->setColor(HIGH,HIGH,LOW);
  rgbLED->setRGBState(HIGH);
}
void BLESetUp(){
  class FYP_Callbacks: public BLEServerCallbacks {
    void onConnect(BLEServer* pServer) {
      deviceConnected = true;
      Serial.println("Phone Connected");
      rgbLED->setBlink(false);
      rgbLED->setColor(HIGH,HIGH,LOW);
      rgbLED->setRGBState(HIGH);
    };

    void onDisconnect(BLEServer* pServer) {
      deviceConnected = false;
      Serial.println("Phone Disconnected");
      rgbLED->setBlink(true);
      rgbLED->setColor(LOW,HIGH,HIGH);
      rgbLED->setRGBState(HIGH);
    }
};
  Serial.println("Starting BLEServerSetUp"); 
  BLEDevice::init("FYP_ESP32"); //set module name
  //initializing BLE Server
  Serial.println("initializing BLE Server"); 
  FYP_server = BLEDevice::createServer(); 
  FYP_server->setCallbacks(new FYP_Callbacks());
  BLESetUpAdvertising();
  BLESetUpBonding();
  Serial.println("BLE Initialized succesfully!");
  }