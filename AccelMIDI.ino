#define THRESHOLD_1 13
#define THRESHOLD_2 17
#define THRESHOLD_3 23
#define THRESHOLD_4 27


AccelerationReading previousAccel;

void setup() {
 
  Serial.begin(); 
  previousAccel = Bean.getAcceleration(); 
    
}

// Here we taking the accelerator sensor data and manipulate it in different ways

void loop() {
 
  AccelerationReading acceleration = Bean.getAcceleration();

  int readX =  map (acceleration.xAxis, 0, 1023, 0, 127) + random(7, 23);
  int readX2 = map (acceleration.xAxis, 0, 1023, 0, 127) + random(24, 33);
  
  int readY =  map (acceleration.yAxis, 0, 1023, 0, 127) - random(13,23);
  //  int readY =  ((acceleration.yAxis/11) - random(13,23));

  int readZ =  (acceleration.zAxis/7);

  int sumXY = ((readX + readY)/17);
  int sumXY2 = ((readX + readY)/7);
  //  int sumXY = ((readX + readY)/13);

  int diff2x = abs(readX - readY);
  int diffx3 = abs((readX*3) - readY);
  int diff4 = abs(readX + readY)/4;
 

  AccelerationReading currentAccel = Bean.getAcceleration();    
  int accelDifference = getAccelDifference(previousAccel, currentAccel);   
  previousAccel = currentAccel;  
 
 
// Here we take these numbers generated from the sensor readings and use them to trigger different 
// sets of MIDI note data. This data is sent via Bluetooth to iOS devices running apps such as Animoog


    if(accelDifference > THRESHOLD_4){   

        BeanMidi.noteOn(CHANNEL1, sumXY2, 5);  
        BeanMidi.noteOn(CHANNEL1, readY, sumXY);  
        //BeanMidi.noteOn(CHANNEL1, diffx3, diff2x);  
       
    }   

    else if (accelDifference > THRESHOLD_3){

        BeanMidi.noteOn(CHANNEL1, readX2, 7);  
        //BeanMidi.noteOn(CHANNEL1, diff2x, sumXY);
        BeanMidi.noteOn(CHANNEL1, diff4, diffx3);
                             
           
    }

     else if (accelDifference > THRESHOLD_2){

        BeanMidi.noteOn(CHANNEL1, readX, 9);  
        BeanMidi.noteOn(CHANNEL1, diff2x, sumXY);
        BeanMidi.noteOn(CHANNEL1, diff4, diffx3);
                             
           
    }

     else if (accelDifference > THRESHOLD_1){

        BeanMidi.noteOn(CHANNEL1, readX, 9);  
        BeanMidi.noteOn(CHANNEL1, diff2x, sumXY);
        BeanMidi.noteOn(CHANNEL1, diff4, diffx3);
                             
           
    }

    else {

       for (int j = 0; j < 128; j++) {

        BeanMidi.noteOff(CHANNEL1, j, 3);  
        // BeanMidi.noteOff(CHANNEL1, j, 15);                      
       
      }
    }
    Bean.sleep(3);
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



