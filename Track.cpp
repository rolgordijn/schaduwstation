#include "Track.h"
#include "boarddefenitions.h"


Track::Track() {

};

Track::Track(Wissel * wissel, IO * bezetmelder, IO * led, IO * relay, IO * knop, uint8_t id) {
  this->wissel = wissel;
  this->bezetmelder = bezetmelder;
  this->led = led;
  this->relay = relay;
  this->knop = knop;
  this->id = id;
}

bool Track::isBezet(void) {
  return state == TrackState::bezet;
}


bool Track::isVertrekState(void) {
  return state == TrackState::vertrek;
}

bool Track::isVrij(void) {
  return state == TrackState::vrij;
}


bool Track::vertrek(void) {
  if (!this->isBezet()) return false;
  this->state = TrackState::vertrek;
  return true;
}


void Track::setState(TrackState state) {
  this->state = state;
  this->toString();
}

void Track::process(void) {
  for(int i=0;i<5;i++) this->process(0, 0, 0, 0);
}

void Track::process(bool knipper, bool kop, bool test, bool vertrek) {
  //if (test) {
  //  if (knop->getValue()) wissel->zetrechtdoor();
  //  else wissel->zetafbuigend();
  //  return;
  // }

  // if (kop) {
  //   wissel->zetrechtdoor();
  // }

  switch (this->state) {
    case TrackState::bezet:
      wissel->activate(Richting::rechtdoor);
      led->setHigh();
      relay->setLow();
      if (knop->getValue()) {
        this->setState(TrackState::waitForButtonRelease);
      }
      break;

    case TrackState::waitForButtonRelease:
      if (!knop->getValue()) this->setState(TrackState::vertrek);
      break;

    case TrackState::vertrek:
      led->setValue(knipper);
      relay->setHigh();
      if (!bezetmelder->getValue() && !knop->getValue()) {
        this->setState(TrackState::vrij);
      }
      break;
    case TrackState::vrij:
      //if (!kop) wissel->activate(Richting::afbuigend);
      if (!kop) wissel->activate(Richting::afbuigend);
      led->setLow();
      relay->setLow();
      if (bezetmelder->getValue() && !knop->getValue()) {
        this->setState(TrackState::bezet);

        //if (vertrek) vertrekAutomatisch();
      }
      break;

    default:
      this->toString();
      if (bezetmelder->getValue()) this->state = TrackState::bezet;
      else this->state = TrackState::vrij;
      break;
  }

}



void Track::toString(void) {
  debug("Spoor ")
  debug(id)
  debug(": status= " )
  switch (this->state) {
    case TrackState::bezet:
      debugln("bezet");
      break;
    case TrackState::vertrek:
      debugln("vertrek");
      break;
    case TrackState::vrij:
      debugln("vrij");
      break;
    default:
      debugln("initialisatie");
      break;
  }



}


void Track::vertrekAutomatisch(void) {
  Track * t;
  do {
    t = sporen[random(6)];
  } while (!t->vertrek());

}
