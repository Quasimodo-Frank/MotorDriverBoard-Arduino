// RECEIVER CODE
//
// Tech Notes:
// - nRF24L01 on Channel 90
// - Listens for incoming messages

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>


// Define the CE and CSN pins
//currently using the motor board pin settings
#define CE_PIN   10//9
#define CSN_PIN  8

//default pin settings
//#define CE_PIN   19
//#define CSN_PIN  10

// Create an RF24 object
RF24 radio(CE_PIN, CSN_PIN);

// Create a pipe address. This must match the sender's address.
const byte address[6] = "00001";

void setup() {
  // Start the Serial Monitor
  Serial.begin(9600);
  Serial.println("Receiver is starting up...");

  // Initialize the nRF24L01 module
  if (!radio.begin()) {
    Serial.println("Radio hardware is not responding!");
    while (1) {} // Halt
  }

  // Set the communication channel.
  // MUST match the sender's channel (90).
  radio.setChannel(90);

  // Set the data rate. MUST match the sender's data rate.
  radio.setDataRate(RF24_1MBPS);

  // Open a reading pipe on the specified address.
  radio.openReadingPipe(0, address); // Using pipe 0

  // Set the module to be a receiver
  radio.startListening();
  
  Serial.println("Setup complete. Listening for messages...");
}

void loop() {
  // Check if there is any data available to be read
  if (radio.available()) {
    char text[32] = ""; // Create a buffer to hold the received data
    radio.read(&text, sizeof(text)); // Read the data into the buffer
    
    Serial.print("Message received: ");
    Serial.println(text);
  }
}
