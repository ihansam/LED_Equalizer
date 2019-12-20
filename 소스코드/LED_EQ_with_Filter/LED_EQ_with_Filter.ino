// Modified by Kidan Jin, EEE, SKKU. 30th 11, 2019.
// code based on https://www.eetimes.com/author.asp?doc_id=1323030&page_number=3
// MSGEQ7 bands = 63Hz, 160Hz, 400Hz, 1,000Hz, 2,500Hz, 6,250Hz, 16,000Hz

int ctrlReset    = 23;                   // Digital pin 23 = signal to reset MSGEQ7s
int ctrlStrobe   = 22;                   // Digital pin 22 = signal to strobe (read data from) MSGEQ7s
int readchannel  = A0;                   // Analog pin 0 = spectrum data from channel
int spectrum[7];                         // amplitudes of spectrum

int frequency[7] = {A1,A2,A3,A4,A5,A6,A7};
int amplitude[8] = {2,3,4,5,6,7,8,9};
int freqnum = 7;                    // 가로 진동수 개수
int ampnum = 8;                     // 세로 세기 개수
int delaytime = 25;                 // 패턴 유지 시간
unsigned int numberPattern[9] = {   // 해당 freq에서 킬 led 개수(index) 패턴
  0B0000000000000000,
  0B0000000000000001,
  0B0000000000000011,
  0B0000000000000111,
  0B0000000000001111,
  0B0000000000011111,
  0B0000000000111111,
  0B0000000001111111,
  0B0000000011111111,
};

void setup()
{
  Serial.begin(9600);
  pinMode(ctrlReset,OUTPUT);             // Define reset as output
  pinMode(ctrlStrobe,OUTPUT);            // Define strobe as output
  digitalWrite(ctrlReset,LOW);           // Pull the reset signal low
  digitalWrite(ctrlStrobe,HIGH);         // Drive the strobe signal high
  
  for(int i=0;i<freqnum;i++){
    pinMode(frequency[i], OUTPUT);       // freq level 선언
    digitalWrite(frequency[i], HIGH);    // 각 level 비활성화
  }  
  for(int i=0;i<ampnum;i++){
    pinMode(amplitude[i], OUTPUT);       // 칸 선언
  }
}

void loop()
{
  // read spectrum
  readMSGEQ7();

  // for test
  for (int i = 0; i < 7; i++)
  {
    if (spectrum[i]<100) Serial.print(" ");
    if (spectrum[i]<10) Serial.print(" ");
    Serial.print(spectrum[i]);
    Serial.print(" ");
  }
  Serial.println();

  // main
  for(int j=0;j<delaytime;j++){     // delaytime 시간만큼 해당 패턴을 유지
    for(int f=0; f<freqnum; f++){   // 각 level마다 ledOnNum개의 led를 on하도록 setting
      int levelAmp = spectrum[f]/10 - 2;
      int ledOnNum;
      if (levelAmp<0) ledOnNum = 0;
      else if (levelAmp>ampnum) ledOnNum = ampnum;
      else ledOnNum = levelAmp;
      if (j==0){  // for test
        Serial.print("  ");            
        Serial.print(ledOnNum); 
        Serial.print(" ");            
      }
      LEDSetting(frequency[f], numberPattern[ledOnNum]);       
    }
  }
  Serial.println();


}

void readMSGEQ7()
// Read the seven spectrum bands from the MSGEQ7 chips
{
  digitalWrite(ctrlReset, HIGH);                     // Pulse the reset signal, which causes
  delayMicroseconds(1);                              // Delay for reset pulse width
  digitalWrite(ctrlReset, LOW);                      // the MSGEQ7s to latch the spectrum values
  delayMicroseconds(75);                             // Delay to meet minimum reset-to-strobe time

  for(int i=0; i <7; i++)                            // Cycle through the 7 spectrum bands
  {
    digitalWrite(ctrlStrobe,LOW);                    // Read current band (then increment to next band)
    delayMicroseconds(40);                           // Wait for outputs to settle

    spectrum[i] = analogRead(readchannel) / 4;   // Store current values from left & right channels 
    
    digitalWrite(ctrlStrobe,HIGH);
    delayMicroseconds(40);                           // Delay to meet minimum strobe-to-strobe time
  }
}

void LEDSetting(int level, unsigned int state){       // 한 freq level에 특정 개수 led on
  digitalWrite(level, LOW); //해당 열 open
  for(int i=0;i<ampnum;i++){    
    digitalWrite(amplitude[i],(bitRead(state, i)));   // led on     
    }
  delay(1);
  for(int i=0;i<ampnum;i++){     
    digitalWrite(amplitude[i], LOW);                  // led off
    }
  digitalWrite(level, HIGH); //해당 열 close   
}
