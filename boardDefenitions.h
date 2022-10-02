
#pragma once
#include <MCP23017.h>
#include "Track.h"
#include "Wissel.h"
#include "IO.h"

extern MCP23017 mcp1;
extern MCP23017 mcp0; 


extern Wissel  wissel1;
extern Wissel  wissel2;
extern Wissel  wissel3 ;
extern Wissel  wissel4 ;
extern Wissel  wissel5 ;
extern Wissel  wissel6 ;


extern MCP23017IO led1;
extern MCP23017IO led2;
extern MCP23017IO led3;
extern MCP23017IO led4;

extern MCP23017IO knop1;
extern MCP23017IO knop2;
extern MCP23017IO knop3;
extern MCP23017IO knop4;
extern MCP23017IO knop5;
extern MCP23017IO knop6;
extern MCP23017IO knop7;
extern MCP23017IO knop8;


extern MCP23017IO bezetmelder1;
extern MCP23017IO bezetmelder2;
extern MCP23017IO bezetmelder3;
extern MCP23017IO bezetmelder4;
extern MCP23017IO bezetmelder5;
extern MCP23017IO bezetmelder6;
extern MCP23017IO bezetmelder7;
extern MCP23017IO bezetmelder8;


extern IO * bezetmelders[8];


extern BasicIO led5;
extern BasicIO led6;
extern BasicIO led7;
extern BasicIO led8;

extern BasicIO relay1;
extern BasicIO relay2;
extern BasicIO relay3;
extern BasicIO relay4;
extern BasicIO relay5;
extern BasicIO relay6;
extern BasicIO relay7;
extern BasicIO relay8;

extern Track track1;
extern Track track2;
extern Track track3;
extern Track track4;
extern Track track5;
extern Track track6;

extern BasicIO intBezetmelders;
extern BasicIO intDrukknop;

extern Wissel * wissels[6]; 
extern IO * relays[8] ;

extern Track * sporen[6] ; 
