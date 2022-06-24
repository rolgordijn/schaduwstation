#pragma once
#include "Wissel.h"
//#include "boardDefenitions.h"
#include "Track.h"



enum class TrackState  : uint8_t {
  onbekend,
  bezet,
  vrij,
  vertrek,
  waitForButtonRelease,
};





class Track {
  private:
    uint8_t id;
    Wissel * wissel;
    IO * bezetmelder;
    IO * led;
    IO * relay;
    IO * knop;
    TrackState state = TrackState::onbekend;
  public:
    Track();
    Track(Wissel * wissel, IO * bezetmelder, IO * led, IO * relay, IO * knop, uint8_t id);

    bool isBezet(void);
    bool isVrij(void);

    int getID;

    void toString(void);

    bool isVertrekState(void);
    void setState(TrackState state);
    bool vertrek(void);

    void process(bool knipper, bool kop, bool test, bool vertrek) ;
    void process(void) ;

    static void vertrekAutomatisch(void) ;

};
