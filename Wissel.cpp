#include "Wissel.h"
#include "IO.h"

#include "debug.h"


Wissel::Wissel() {
};



Wissel::Wissel(IO * rechtdoor, IO * afbuigend , int id)  {
  this->rechtdoor = rechtdoor;
  this->afbuigend = afbuigend;
  richting = Richting::onbekend;
  this->id = id;
};





void Wissel::activate(Richting r) {
  if (this->richting == r)   return;
  IO * pin;
  debug("wissel ")
  debug(id);
  if (r == Richting::afbuigend) {
    pin = afbuigend;

    debugln(": afbuigend");
  } else {
    pin = rechtdoor;
    debugln(": rechtdoor");
  }
  pin->setHigh();
  delay(250);
  pin->setLow();
  delay(250);
  this->richting = r;

}

void Wissel::zetafbuigend() {
  this->activate(Richting::afbuigend);
}

void Wissel::zetrechtdoor() {
  this->activate(Richting::rechtdoor);
}

Richting Wissel::getRichting(void) {
  return richting;
}
