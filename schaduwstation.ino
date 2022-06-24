#include <ArduinoTrace.h>

#include "boardDefenitions.h"
#include "IO.h"
#include "Track.h"
#include "Wissel.h"
#include "debug.h"
#include "knipper.h"
#include "debug.h"
#include <assert.h>
#include "StopWatch.h"

#pragma GCC optimize ("-Ofast")
#define ALL_INPUT 0XFF
#define ALL_OUTPUT 0X00


#define KOPSPOOR 0
#define TEST 0



StopWatch stopWatch = StopWatch();
Knipper knipper = Knipper(100, 500);



class StaginYard {





};



Track * zoekBestemming(Track * sporen[], int n) {
  Track * bestemming = NULL;
  for (int i = 0; i < n; i++) {
    if ( sporen[i]->isVrij()) {
      bestemming = sporen[i];
      break;
    }
  }
  return bestemming;
}


void clearBuffer(){
  while(Serial.available()){
    Serial.read();
  }
}



class Inrijspoor {
    IO * melder;
    IO * led;

    IO * relay;

    bool bezet;
  public:

    Inrijspoor() {

    }

    Inrijspoor(IO * melder, IO * led, IO * relay) {
      this->melder = melder;
      this->led = led;
      this->relay = relay;
    }

    bool isBezet() {

      return bezet;
    }


    void process(bool naarKopSpoor, Track * bundel[], int n) {
      static Track * t;
      if (naarKopSpoor) {
        relay->setHigh();
        led->setValue(melder->getValue());
        return;
      }

      if (!bezet && !melder->getValue()) {

      }

      if (!bezet && melder->getValue()) {
        bezet = true;
        led->setHigh();
        t = zoekBestemming(bundel, n);
      }

      if (bezet && !melder->getValue()) {
        relay->setLow();
        if (t->isBezet()) {
          relay->setHigh();
          led->setLow();
          bezet = false;
        }
        if (bezet && melder->getValue()) {
          //do juske niks!
        }




      }
    }


};


Inrijspoor inrijspoor = Inrijspoor(&bezetmelder8, &led8, &relay8);


void mcp23017Reset(MCP23017 * mcp, int dirA, int dirB) {
  debugln("reset mcp23017");
  mcp->init();
  mcp->writeRegister(MCP23017Register::IPOL_A, 0x00); // input not inverted
  mcp->writeRegister(MCP23017Register::IPOL_B, 0x00);
  mcp->writeRegister(MCP23017Register::GPIO_A, 0x00);  //Reset port A
  mcp->writeRegister(MCP23017Register::GPIO_B, 0x00);  //Reset port B
  mcp->portMode(MCP23017Port::A, dirA);          //Port A as output
  mcp->portMode(MCP23017Port::B, dirB);          //Port B as output
}


/*void alleWisselsRechtdoor(void) {
  for (int i = 0; i < 5; i++) wissels[i]->zetrechtdoor();
  }*/

/*void resetAllRelays(void) {
  for (int i = 0; i < 8; i++) relays[i]->setLow();
  }*/

bool readBitInByte(uint8_t in, int n ) {
  return ((1 << n) & in);

}

uint8_t readFeedbackPins(void) {
  return mcp1.readRegister(MCP23017Register::GPIO_B) & 0x1f ;
}

inline uint8_t readButtons(void) {
  return mcp1.readRegister(MCP23017Register::GPIO_A);
}


bool inrijSpoorStop(bool naarKopSpoor, bool bezetmelder) {
  static bool inrij;
  static Track * bestemming;
  //trek duw trein: altijd doorlaten.
  if (naarKopSpoor) {
    return false;
  }


  //gewone trein, zoek zijn bestemming!
  if (bezetmelder && !naarKopSpoor) {
    inrij = true;
    if (zoekBestemming(sporen, 6)) return false;
  }

  //voorbij inrijsectie: volgende trein moet stoppen
  if (inrij && !bezetmelder8.getValue()) return true;

  //bestemming bereikt
  if (inrij && bestemming->isBezet()) inrij = false;

  for (auto s : sporen) {
    if (s->isVertrekState()) {
      if (bestemming > s) return true;
    }


  }
  return false;
}


void setup() {



  delay(100);
  Serial.begin(115200);
  debugln("start init");
  debugln("INIT I2C");
  Wire.begin();

  mcp23017Reset(&mcp0, ALL_OUTPUT, ALL_OUTPUT);
  mcp23017Reset(&mcp1, ALL_INPUT, ALL_INPUT);

  delay(100);

  debugln("Configure MCP1 interrupt registers");
  mcp1.interruptMode(MCP23017InterruptMode::Separated);
  mcp1.interrupt(MCP23017Port::B, CHANGE);
  mcp1.interrupt(MCP23017Port::A, FALLING);
  mcp1.writeRegister(MCP23017Register::IPOL_A, 0xFF);
  mcp1.writeRegister(MCP23017Register::IPOL_B, 0x00);
  mcp1.writeRegister(MCP23017Register::IOCON, mcp1.readRegister(MCP23017Register::IOCON) | 0b10);

  delay(2500);

  int input = readFeedbackPins();
  debug("de huidige bezetmelders die actief zijn zijn: ");
  debugln(input);


  pinMode(5, INPUT);

  for (auto t : sporen) {
    t->process(knipper.getValue(), 0, !digitalRead(5) , knop8.getValue());
  }


  //#if DEBUG ==1

#if TEST == 1
  Serial.println("****************************************");

  Serial.println("start self test");

  assert(inrijSpoorStop(true, false) == false);
  TRACE();

  assert(inrijSpoorStop(true, true) == false);
  TRACE();

  assert(zoekBestemming(sporen, 6) == &track1);
  TRACE();

  assert(track1.isVrij());
  TRACE();



  VirtualIO relay9 = VirtualIO();
  VirtualIO led9 = VirtualIO();
  VirtualIO knop9 = VirtualIO();
  VirtualIO bezetmelder9 = VirtualIO();
  Wissel wissel9 = Wissel(new VirtualIO() , new VirtualIO(), 7);

  VirtualIO relay10 = VirtualIO();
  VirtualIO led10 = VirtualIO();
  VirtualIO knop10 = VirtualIO();
  VirtualIO bezetmelder10 = VirtualIO();
  Wissel wissel10 = Wissel(new VirtualIO() , new VirtualIO(), 7);

  Track track9;
  Track track10;

  Track * bundel[]   {&track9, &track10};


  VirtualIO relay11 = VirtualIO();
  VirtualIO led11 = VirtualIO();
  VirtualIO knop11 = VirtualIO();
  Inrijspoor inrijspoor10 = Inrijspoor(&bezetmelder8, &led8, &relay8);

  /*test wisselstanden*/
  wissel9.zetafbuigend();
  assert(wissel9.getRichting() == Richting::afbuigend);
  TRACE();
  wissel9.zetrechtdoor();
  assert(wissel9.getRichting() == Richting::rechtdoor);
  TRACE();

  //create track object -- bezetmelder is high - check initiële toestand
  bezetmelder10.setHigh();
  track10 = Track(&wissel10, &bezetmelder10, &led10, &relay10, &knop10, 10);
  track10.process();
  assert(track10.isBezet());
  TRACE();
  assert(relay10.getValue() == 0);
  TRACE();
  assert(wissel10.getRichting() == Richting::rechtdoor);


  //create track object -- bezetmelder is low - check initiële toestand
  track9 = Track(&wissel9, &bezetmelder9, &led9, &relay9, &knop9, 9);
  track9.process();
  assert(track9.isVrij());
  TRACE();



  assert( zoekBestemming(bundel, 2) == &track9);
  TRACE();
  assert(!relay9.getValue());
  TRACE();
  assert(wissel9.getRichting() == Richting::afbuigend);
  TRACE();

  //trein komt aangereden op spoor9
  bezetmelder9.setHigh();
  track9.process();
  assert(wissel9.getRichting() == Richting::rechtdoor);
  TRACE();
  assert(track9.isBezet());
  TRACE();


  //twee sporen bezet, geen vrij spoor meer, methode moet Null returnen
  DUMP((int) zoekBestemming(bundel, 2));
  assert(zoekBestemming(bundel, 2) == NULL);
  TRACE();



  //vertrek spoor 10 + check edges
  
  knop10.setHigh();
  track10.process();
  knop10.setLow();
  track10.process();
  assert(track10.isVertrekState());
  TRACE();
  assert(wissel10.getRichting() == Richting::rechtdoor);
  TRACE();
  bezetmelder10.setLow();
  track10.process();
  assert(track10.isVrij());
  TRACE();
  assert(zoekBestemming(bundel, 2) == &track10);
  TRACE();

  //vertrek spoor 0


  //vertrek spoor 10
 
  knop9.setHigh();
  track9.process();
  knop9.setLow();
  track9.process();
  assert(track9.isVertrekState());
  TRACE();
  assert(wissel9.getRichting() == Richting::rechtdoor);
  TRACE();
  bezetmelder9.setLow();
  track9.process();
  assert(track9.isVrij());
  TRACE();
  assert(zoekBestemming(bundel, 2) == &track9);
  TRACE();

  Serial.println("success, all tests passed!");
  Serial.println("****************************************");


#endif 










  //#endif

}


long loopCounter = 0;
float loopTime = 0;
long totalLoopTime;

enum class kopSpoorState {
  vrij,
  naarKopSpoor,
  bezet,
  vertrek,
  onbekend,

};

/*int kopspoorhandler(Knipper knipper) {
  static kopSpoorState state = kopSpoorState::onbekend;
  int ret = 0;
  switch (state) {
    case kopSpoorState::vrij:
      led7.setLow();
      relay7.setLow();
      if (knop7.getValue()) state = kopSpoorState::naarKopSpoor;
      break;
    case kopSpoorState::naarKopSpoor:
      while (knop7.getValue()) delay(10);
      ret = 1;
      relay7.setHigh();
      led7.setValue(knipper.getValue());
      if (bezetmelder7.getValue()) state = kopSpoorState::bezet;
      if (knop7.getValue()) state = kopSpoorState::vrij;
      break;
    case kopSpoorState::bezet:
      relay7.setLow();
      led7.setHigh();
      if (knop7.getValue()) state = kopSpoorState::vertrek;
      break;
    case kopSpoorState::vertrek:
      while (knop7.getValue()) delay(10);
      led7.setValue(knipper.getValue());
      relay7.setHigh();
      if (knop7.getValue()) state = kopSpoorState::bezet;
      if (!bezetmelder7.getValue()) state = kopSpoorState::vrij;
      break;
    default:
      if (bezetmelder7.getValue()) state = kopSpoorState::bezet;
      else state = kopSpoorState::vrij;
  }


  return ret;


  }*/




void loop() {

  if (intBezetmelders.getValue() || intDrukknop.getValue()) {
    stopWatch.startTimer();

    //int state = kopspoorhandler(knipper);
    for (auto t : sporen) {
      t->process(knipper.getValue(), 0, !digitalRead(5) , knop8.getValue());
    }

    //relay8.setValue(1);

    if (inrijSpoorStop(0, 0))  led8.setHigh();
    if (inrijSpoorStop(0, 1))  led8.setValue(knipper.getValue());
    if (inrijSpoorStop(1, 0))  led8.setLow();
    if (inrijSpoorStop(1, 1))  led8.setLow();
  }




  if (Serial.available() > 0) {
    long myInt = Serial.parseInt(SKIP_ALL, '\n');
    debug("I received: ");  debugln(myInt);
    if (myInt < 7 && myInt > 0) {
      myInt-=1;
      if (wissels[myInt]->getRichting() == Richting::afbuigend){
        wissels[myInt]->zetrechtdoor();
       
      }
      else {
        wissels[myInt]->zetafbuigend();
      }

      
    }else{
      debugln("ongeldig getal ingevoerd");
    }

    clearBuffer();
  }

  stopWatch.stopTimer();



#if DEBUG == 0
  if (stopWatch.getCounter() == 2) {
    //Serial.print("average loop time for 500 iterations ");
    debugln(stopWatch.averageElapsedTimeMillis(), 3);
    //Serial.println(" mS");
    stopWatch.reset();
  }

#endif

}
