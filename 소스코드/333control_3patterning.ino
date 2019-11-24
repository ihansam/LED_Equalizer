int layer[3] = {A0,A1,A2};
int room[9] = {10,9,8,7,6,5,4,3,2};
int m_layer = 3;    // 층 수
int m_room = 9;     // 칸 수
int m_pattern = 9;  // 패턴 수
int m_delay[9] ={20,20,20,20,20,20,20,20,20}; //패턴유지시간

unsigned int layerPattern1[9] ={ //0층 패턴
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
  0B0000000000000001, 
};
unsigned int layerPattern2[9] ={ //1층 패턴
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
  0B0000000000010000,
};
unsigned int layerPattern3[9] ={ //2층 패턴
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
  0B0000000100000000, 
};

void LEDSetting(int layer, unsigned int state){   // 확인해보고 고치자
  digitalWrite(layer, HIGH); //층 개방
  for(int i=0;i<9;i++){    
    digitalWrite(room[i],not(bitRead(state, i))); // 패턴 코드에 따라 칸 개방     
    }
  delay(1);
  for(int i=0;i<9;i++){     
    digitalWrite(room[i], LOW);   // 모든 칸 닫힘      
    }
  digitalWrite(layer, LOW); //층 닫힘    
}
/*
void LEDSetting(int layer, unsigned int state){   // 좀 더 짧은 이 코드는 동작할까?
  digitalWrite(layer, HIGH); //층 개방
  for(int i=0;i<9;i++){    
    digitalWrite(room[i],not(bitRead(state, i))); // 패턴 코드에 따라 칸 개방     
    delay(1);
    }
  digitalWrite(layer, LOW); //층 닫힘    
}
*/
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
  for(int i=0;i<m_pattern;i++){  //순차적으로 패턴수만큼 동작
    for(int j=0;j<m_delay[i];j++){  //m_delay 시간만큼 해당 패턴을 유지한다.
      LEDSetting(layer[0], layerPattern1[i]);  //1층 i번째 패턴        
      LEDSetting(layer[1], layerPattern2[i]);  //2층 i번째 패턴        
      LEDSetting(layer[2], layerPattern3[i]);  //3층 i번째 패턴        
    }  
  }
}