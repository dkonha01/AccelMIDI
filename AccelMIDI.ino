#define THRESHOLD_1 13
#define THRESHOLD_2 23

AccelerationReading previousAccel;

void setup() {
 
  Serial.begin(); 
  previousAccel = Bean.getAcceleration(); 
    
}

void loop() {
 
  AccelerationReading acceleration = Bean.getAcceleration();

  int readX =  map (acceleration.xAxis, 0, 1023, 0, 127) + random(7, 23);
  //  int readX =  (acceleration.xAxis/9) ;
  
  int readY =  map (acceleration.yAxis, 0, 1023, 0, 127) - random(13,23);
  //  int readY =  ((acceleration.yAxis/11) - random(13,23));

  int readZ =  (acceleration.zAxis/7);

  int sumXY = ((readX + readY)/17);
  //  int sumXY = ((readX + readY)/13);

  int diff2x = abs(readX - readY);
  //  int diff2x = abs(readX - readY);

  AccelerationReading currentAccel = Bean.getAcceleration();    
  int accelDifference = getAccelDifference(previousAccel, currentAccel);   
  previousAccel = currentAccel;  


    if(accelDifference > THRESHOLD_2){   

        BeanMidi.noteOn(CHANNEL1, sumXY, 11);  
        BeanMidi.noteOn(CHANNEL1, readY, sumXY);  
       
    }   

    else if (accelDifference > THRESHOLD_1){

        BeanMidi.noteOn(CHANNEL1, readX, 9);  
        BeanMidi.noteOn(CHANNEL1, diff2x, sumXY);                     
           
    }

    else {

       for (int j = 0; j < 128; j++) {

        BeanMidi.noteOff(CHANNEL1, j, 7);  
        // BeanMidi.noteOff(CHANNEL1, j, 15);                      
       
      }
    }
    Bean.sleep(7);
    // Bean.sleep(49);

    
   Bean.setLed((uint8_t)readX,(uint8_t)readY,(uint8_t)readZ);   
}


int getAccelDifference(AccelerationReading readingOne, AccelerationReading readingTwo){
  int deltaX = abs(readingTwo.xAxis - readingOne.xAxis);
  int deltaY = abs(readingTwo.yAxis - readingOne.yAxis);
  int deltaZ = abs(readingTwo.zAxis - readingOne.zAxis);

  return deltaX + deltaY + deltaZ;   
}


int getAccelDifferenceX(AccelerationReading readingOne, AccelerationReading readingTwo){
  int deltaX = abs(readingTwo.xAxis - readingOne.xAxis);
  return deltaX;   
}

int getAccelDifferenceY(AccelerationReading readingOne, AccelerationReading readingTwo){

  int deltaY = abs(readingTwo.yAxis - readingOne.yAxis);
  return deltaY;   
}



