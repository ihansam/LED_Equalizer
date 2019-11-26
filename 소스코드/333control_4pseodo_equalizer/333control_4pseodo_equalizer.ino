int layer[3] = {A0,A1,A2};
int room[9] = {10,9,8,7,6,5,4,3,2};
int m_layer = 3;    // 층 수
int m_room = 9;     // 칸 수
int m_delay = 100;   // 패턴 유지 시간

unsigned int numberPattern[10] = {  // 숫자 패턴 (각 index가 그 층에서 킬 LED의 개수)
  0B0000000000000000,
  0B0000000000000001,
  0B0000000000000011,
  0B0000000000000111,
  0B0000000000001111,
  0B0000000000011111,
  0B0000000000111111,
  0B0000000001111111,
  0B0000000011111111,
  0B0000000111111111,
  };

void LEDSetting(int layer, unsigned int state){
  digitalWrite(layer, HIGH); //층 개방
  for(int i=0;i<9;i++){    
    digitalWrite(room[i],not(bitRead(state, i))); // 패턴 코드에 따라 칸 개방     
    }
  delay(1);
  for(int i=0;i<9;i++){     
    digitalWrite(room[i], HIGH);   // 모든 칸 닫힘      
    }
  digitalWrite(layer, LOW); //층 닫힘    
}

void setup()
{  
  for(int i=0;i<m_layer;i++){
    pinMode(layer[i], OUTPUT);      // 층 선언
    digitalWrite(layer[i], LOW);    // 각 층 비활성화
  }  
  for(int i=0;i<m_room;i++){
    pinMode(room[i], OUTPUT);       // 칸 선언
  }
}

void loop()
{
  int randNum1 = random(3)+1;       // 1,2,3개 중 랜덤
  int randNum2 = random(3)+1;
  int randNum3 = random(3)+1;
  for(int j=0;j<m_delay;j++){  //m_delay 시간만큼 해당 패턴을 유지한다.
    LEDSetting(layer[0], numberPattern[randNum1]);  // 0층: randNum1개의 LED ON        
    LEDSetting(layer[1], numberPattern[randNum2]);  // 1층: randNum1개의 LED ON        
    LEDSetting(layer[2], numberPattern[randNum3]);  // 2층: randNum1개의 LED ON        
  }
}
