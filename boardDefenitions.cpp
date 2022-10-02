#include "boardDefenitions.h"

MCP23017 mcp1 = MCP23017(0x20);
MCP23017 mcp0 = MCP23017(0x27);

Wissel wissel1 = Wissel(new MCP23017IO(&mcp0, 1, OUTPUT) ,  new MCP23017IO(&mcp0, 0, OUTPUT),1);
Wissel wissel2 = Wissel(new MCP23017IO(&mcp0, 3, OUTPUT) ,  new MCP23017IO(&mcp0, 2, OUTPUT),2);
Wissel wissel3 = Wissel(new MCP23017IO(&mcp0, 5, OUTPUT) ,  new MCP23017IO(&mcp0, 4, OUTPUT),3);
Wissel wissel4 = Wissel(new MCP23017IO(&mcp0, 7, OUTPUT) ,  new MCP23017IO(&mcp0, 6, OUTPUT),4);
Wissel wissel5 = Wissel(new MCP23017IO(&mcp0, 9, OUTPUT) ,  new MCP23017IO(&mcp0, 8, OUTPUT),5);
Wissel wissel6 = Wissel(new MCP23017IO(&mcp0, 11, OUTPUT) ,  new MCP23017IO(&mcp0, 10, OUTPUT),6);

MCP23017IO led1 = MCP23017IO(&mcp0, 15, OUTPUT);
MCP23017IO led2 = MCP23017IO(&mcp0, 14, OUTPUT);
MCP23017IO led3 = MCP23017IO(&mcp0, 13, OUTPUT);
MCP23017IO led4 = MCP23017IO(&mcp0, 12, OUTPUT);

MCP23017IO knop1 = MCP23017IO(&mcp1, 0, INPUT);
MCP23017IO knop2 = MCP23017IO(&mcp1, 1, INPUT);
MCP23017IO knop3 = MCP23017IO(&mcp1, 2, INPUT);
MCP23017IO knop4 = MCP23017IO(&mcp1, 3, INPUT);
MCP23017IO knop5 = MCP23017IO(&mcp1, 4, INPUT);
MCP23017IO knop6 = MCP23017IO(&mcp1, 5, INPUT);
MCP23017IO knop7 = MCP23017IO(&mcp1, 6, INPUT);
MCP23017IO knop8 = MCP23017IO(&mcp1, 7, INPUT);

MCP23017IO bezetmelder1 = MCP23017IO(&mcp1, 8, INPUT);
MCP23017IO bezetmelder2 = MCP23017IO(&mcp1, 9, INPUT);
MCP23017IO bezetmelder3 = MCP23017IO(&mcp1, 10, INPUT);
MCP23017IO bezetmelder4 = MCP23017IO(&mcp1, 11, INPUT);
MCP23017IO bezetmelder5 = MCP23017IO(&mcp1, 12, INPUT);
MCP23017IO bezetmelder6 = MCP23017IO(&mcp1, 13, INPUT);
MCP23017IO bezetmelder7 = MCP23017IO(&mcp1, 14, INPUT);
MCP23017IO bezetmelder8 = MCP23017IO(&mcp1, 15, INPUT);


BasicIO led5 = BasicIO(6, OUTPUT);
BasicIO led6 = BasicIO(7, OUTPUT);
BasicIO led7 = BasicIO(8, OUTPUT);
BasicIO led8 = BasicIO(9, OUTPUT);

BasicIO relay1 = BasicIO(10, OUTPUT);
BasicIO relay2 = BasicIO(11, OUTPUT);
BasicIO relay3 = BasicIO(12, OUTPUT);
BasicIO relay4 = BasicIO(13, OUTPUT);
BasicIO relay5 = BasicIO(A3, OUTPUT);
BasicIO relay6 = BasicIO(A2, OUTPUT);
BasicIO relay7 = BasicIO(A1, OUTPUT);
BasicIO relay8 = BasicIO(A0, OUTPUT);

Track track1 = Track(&wissel1, &bezetmelder1, &led1, &relay1, &knop1, 1);
Track track2 = Track(&wissel2, &bezetmelder2, &led2, &relay2, &knop2, 2);
Track track3 = Track(&wissel3, &bezetmelder3, &led3, &relay3, &knop3, 3);
Track track4 = Track(&wissel4, &bezetmelder4, &led4, &relay4, &knop4, 4);
Track track5 = Track(&wissel5, &bezetmelder5, &led5, &relay5, &knop5, 5);
Track track6 = Track(&wissel6, &bezetmelder6, &led6, &relay6, &knop6, 6);

BasicIO intBezetmelders = BasicIO(2, INPUT);
BasicIO intDrukknop = BasicIO(3, INPUT);

Wissel * wissels[6] = {&wissel1, &wissel2, &wissel3, &wissel4, &wissel5, &wissel6};
IO * relays[8] = {&relay1, &relay2, &relay3, &relay4, &relay5, &relay6, &relay7, &relay8};
Track * sporen[6]  {&track1, &track2, &track3, &track4 , &track5, &track6};
IO * bezetmelders[8]= {&bezetmelder1,&bezetmelder2,&bezetmelder3,&bezetmelder4,&bezetmelder5,&bezetmelder6, &bezetmelder7,&bezetmelder8};
