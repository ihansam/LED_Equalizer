
// MSGEQ7 bands = 63Hz, 160Hz, 400Hz, 1,000Hz, 2,500Hz, 6,250Hz, 16,000Hz

int ctrlReset    = 23;                   // Digital pin 23 = signal to reset MSGEQ7s
int ctrlStrobe   = 22;                   // Digital pin 22 = signal to strobe (read data from) MSGEQ7s
int channelLeft  =  0;                   // Analog pin 0 = spectrum data from left channel
int channelRight =  1;                   // Analog pin 1 = spectrum data from right channel

int spectrumLeft[7];                     // Array to store 7 bands of spectrum data from left channel 
int spectrumRight[7];                    // Array to store 7 bands of spectrum data from right channel


void setup()
{
  Serial.begin(9600);
  pinMode(ctrlReset,OUTPUT);             // Define reset as output
  pinMode(ctrlStrobe,OUTPUT);            // Define strobe as output
  digitalWrite(ctrlReset,LOW);           // Pull the reset signal low
  digitalWrite(ctrlStrobe,HIGH);         // Drive the strobe signal high
}


void loop()
{
  readMSGEQ7();

  // Display values from the left channel on the serial monitor
  for (int i = 0; i < 7; i++)
  {
    if (spectrumLeft[i] < 100) Serial.print(" ");
    if (spectrumLeft[i] <  10) Serial.print(" ");
    Serial.print(spectrumLeft[i]);
    Serial.print(" ");
  }
  Serial.print("  ");

  // Display values from the right channel on the serial monitor
  for (int i = 0; i < 7; i++)
  {
    if (spectrumRight[i] < 100) Serial.print(" ");
    if (spectrumRight[i] <  10) Serial.print(" ");
    Serial.print(spectrumRight[i]);
    Serial.print(" ");
  }
  Serial.println();
}


void readMSGEQ7()
// Read the seven spectrum bands from the MSGEQ7 chips
{
  digitalWrite(ctrlReset, HIGH);                     // Pulse the reset signal, which causes
  digitalWrite(ctrlReset, LOW);                      // the MSGEQ7s to latch the spectrum values
  delayMicroseconds(75);                             // Delay to meet minimum reset-to-strobe time

  for(int i=0; i <7; i++)                            // Cycle through the 7 spectrum bands
  {
    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(40);                           // Wait for outputs to settle

    spectrumLeft[i] = analogRead(channelLeft) / 4;   // Store current values from left & right channels 
    spectrumRight[i] = analogRead(channelRight) / 4; // Divide 0-1023 by 4 to give 0-255

    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(40);                           // Delay to meet minimum strobe-to-strobe time
  }
}
