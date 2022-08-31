#include <ChibiOS_ARM.h>

static THD_WORKING_AREA(waTH1,100);
static THD_WORKING_AREA(waTH2,100);

struct threadData{
  int _blinkingTime;
  int _lightPin;
  int _fadingTime;
};

static THD_FUNCTION (blinkerThread, arg){
  threadData *thisData = (threadData*)arg;
  int lightPin = thisData->_lightPin;
  int blinkingTime = thisData->_blinkingTime;

  pinMode(lightPin, OUTPUT);

  while(1){
    digitalWrite(lightPin, HIGH);
    chThdSleep(blinkingTime);
    digitalWrite(lightPin, LOW);
    chThdSleep(blinkingTime);
  }
}

static THD_FUNCTION (fadeThread, arg){
  threadData *thisData = (threadData*)arg;
  int lightPin = thisData->_lightPin;
  int fadingTime = thisData->_fadingTime;

  pinMode(lightPin, OUTPUT);
  while(1){

    for(int i = 0; i < 255; i+=5){
      analogWrite(lightPin, i);
      chThdSleep(fadingTime);
    }
    for(int i = 255; i > 0; i-=5){
      analogWrite(lightPin, i);
      chThdSleep(fadingTime);
    }
  }
}

void setup() {
  // initialize and start ChibiOS
  chBegin(chSetup);
  
  // should not return
  while(1);
}


//------------------------------------------------------------------------------
void chSetup() {
  threadData set1;
  set1._lightPin = 13;
  set1._blinkingTime = 300;

  threadData set2;
  set2._lightPin = 20;
  set2._fadingTime = 10;


  //schedule thread 2 
  chThdCreateStatic(waTh1, sizeof(waTh1), NORMALPRIO, blinkerThread, (void*)&set1);

  //schedule thread 3 (fading)
  chThdCreateStatic(waTh2, sizeof(waTh2), NORMALPRIO, fadeThread, (void*)&set2);



  while(1){
    chThdSleep(10000);
  }
}
//------------------------------------------------------------------------------
void loop() {/* not used */}

void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
