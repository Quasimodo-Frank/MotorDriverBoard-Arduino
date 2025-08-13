// SENDER CODE
//
// Tech Notes:
// - nRF24L01 on Channel 90
// - Sends a simple char array

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

// Define the CE and CSN pins
#define CE_PIN   9
#define CSN_PIN  10

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Create a pipe address. This is the "street address" for communication.
// The address must be the same on both the sender and receiver.
// It can be any 5-byte sequence.
const byte address[6] = "00001";

// Counter for the message
int counter = 0;

void setup() {
  // Start the Serial Monitor for debugging
  Serial.begin(9600);
  Serial.println("Sender is starting up...");

  // Initialize the nRF24L01 module
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1) {} // Halt
  }
  
  // Set the communication channel.
  // Valid channels are from 0 to 125. 
  // Channel 90 is used as requested.
  // Both sender and receiver MUST be on the same channel.
  radio.setChannel(90);

  // Set the Power Amplifier level.
  // Options are: RF24_PA_MIN, RF24_PA_LOW, RF24_PA_HIGH, RF24_PA_MAX
  radio.setPALevel(RF24_PA_LOW);

  // Set the data rate. 
  // Options: RF24_250KBPS, RF24_1MBPS, RF24_2MBPS
  // Lower data rates have better range and reliability.
  radio.setDataRate(RF24_1MBPS);

  // Open a writing pipe to the specified address.
  radio.openWritingPipe(address);

  // Set the module to be a transmitter
  radio.stopListening();
  
  Serial.println("Setup complete. Starting transmission...");
}

void loop() {
  // Create a message to send
  char text[32] = "";
  sprintf(text, "Hello World #%d", counter);

  // Send the message
  bool report = radio.write(&text, sizeof(text));

  if (!report) {
    Serial.print("Transmission successful. Message: ");
    Serial.println(text);
  } else {
    Serial.println("Transmission failed.");
    Serial.println(text);
  }
  
  counter++;
  delay(1000); // Wait a second before sending the next message
}