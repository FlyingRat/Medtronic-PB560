/******************************************************************************/
/*                                                                            */
/* Project N°  :  RB0505                                                      */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/*                                                                            */
/* Filename  : HMI_Message.cpp 	   	      		               	 	  		*/
/*                                                                            */
/*----------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------*/
/******************************************************************************/
/*%C                     Functionnal description :                            */
/*%C                                                                          */
/*%C Objet du menu															 					*/
/*		                                                                   	 	*/
/******************************************************************************/
/******************************************************************************/
/*                           HEADER INCLUDE FILE		                        */
/******************************************************************************/
//---------------------------------------------------------------------------
#include "HMI_Message.hpp"
//---------------------------------------------------------------------------

// generated from PB500 Message Translations.xlsm revision 30837

/*START_MESSAGES*/

// Circuit Check Messages	
const UBYTE *const huge cMSG_CircuitCheck[NB_LANGUAGE]	={"CIRCUIT CHECK","CIRKEL CHECK","PRÜFUNG SCHLAUCHSYSTEM","CIRCUIT CHECK","CIRCUIT CHECK","CONTROL DEL CIRCUITO","TEST DU CIRCUIT","\276\302\276\254\316\305\311 \312\305\313 \301\313\301\302\047\303\273\312\305\311","CONTROLLO CIRCUITO","CIRCUIT CHECK","CIRCUIT CHECK","CIRCUIT CHECK","SIRKEL SJEKK","TEST Obwodu","VERIFIQUE O CIRCUITO","\216\217\215\201\204\217\100\177 \100\215\214\221\222\217\177","LETKUSTON TARKASTUS","Patient cirkel kontroll","Devreyi Kontrol Ediniz "};
const UBYTE *const huge cMSG_LeakTestInstr1[NB_LANGUAGE]	={"Ensure patient is disconnected.","OBS! Patient skal frakobles.","Sicherstellen, dass kein Patient angeschlossen ist.","Ensure patient is disconnected.","Ensure patient is disconnected.","Asegurar desconexion del paciente.","S'assurer que le patient est d\322branch\322.","\311\371\364\377\030\024\366\030\027\366\361\027\366 \035\027\371 \377 \362\026\370\366\375\360\025 \366\361\375\362\371 \362\023\377\026\030\375\365\366\365\366\374\357\375\377\025.","Assicurarsi che il paziente sia disconnesso.","\351\002\212\356\001\202\221\210\177\211\177\200\222\337\006\203\210\201\207\202\177","Ensure patient is disconnected.","Zorg voor ontkoppeling patient.","Sikre at pasienten er frakoblet.","Upewnij si\030, \036e pacjent jest od\033\023czony.","Assegure-se da desconexao do paciente.","\222\244\250\247\253\266\250\264\300, \273\266\306 \262\243\271\253\250\240\266 \306\266\255\256\302\273\250\240","Varmista ett\332 potilas on irroitettu.","F\313rs\332kra dig om att patienten \332r fr\331nkopplad.","Hastay\010 Ventilat\313rden Ay\010rd\010\014\010n\010zdan Emin Olunuz."};
const UBYTE *const huge cMSG_LeakTestInstr2[NB_LANGUAGE]	={"Block circuit at patient connection.","Bloker cirkel ved patienttilkobling.","Schlauchsystem am Patientenanschluss verschlie\335en.","Block circuit at patient connection.","Block circuit at patient connection.","Bloquear conexion del circuito a paciente.","Obstruer circuit en attente de connexion patient.","\303\023\373\377\372\356\024\366\027\366 \027\377 \372\036\372\373\034\374\362 \026\027\367\375 \026\036\375\365\366\026\367 \374\366 \027\377\375 \362\026\370\366\375\360.","Bloccare il circuito alla connessione del paziente.","\351\002\356\001\010\222BLOCK\203\210\201\207\202\177","Block circuit at the patient connection.","Sluit circuit af ter hoogte van pati\317nt.","Blokker slangesirkel ved pasientkobling.","Zablokuj przy\033\023cze pacjenta.","Bloquear a saida do circuito para o paciente.","\206\243\244\256\306\255\253\263\267\254\266\250 \266\263\306\254\240\253\255 \262\243\271\253\250\240\266\243","Irroita potilas letkustosta.","Blockera slangen vid patienten.","Hasta taraf\010ndaki devre ucunu kapat\010n\010z."};
const UBYTE *const huge cMSG_LeakTestInstr3[NB_LANGUAGE]	={"Press \"enter\" key to start test.","Tryk ENTER for at starte test.","Mit ENTER-Taste Test starten.","Press ENTER key to start test.","Press ENTER key to start test.","Pulsar ENTER para iniciar test.","Appuyez sur la touche ENTER pour lancer le test.","\306\371\357\026\027\366 \027\377 \023\373\360\372\027\024\377 ENTER \364\371\362 \375\362 \376\366\372\371\375\360\026\366\371 \367 \366\376\357\027\362\026\367.","Premere il tasto ENTER per iniziare il test.","\244\247\304\254\204\220\212\214ENTER\234\304\222\354\203\210\201\207\202\177","Press ENTER key to start test.","Druk op ENTER om test te starten.","Trykk ENTER for \331 starte test.","Naci\025nij ENTER aby rozpocz\023\034 test.","Pressione ENTER para iniciar teste.","\214\243\251\257\253\266\250 \201\245\306\247 \247\256\303 \240\243\273\243\256\243 \266\250\264\266\243","Paina ENTER aloittaaksesi testauksen.","Tryck ENTER tangent f\313r att starta test.","Teste ba\016lamak i\325in \"ENTER\" tu\016una bas\010n\010z."};
const UBYTE *const huge cMSG_TestStatus[NB_LANGUAGE]	={"test status","Test Status","Test Status","Test Status","Test Status","Resultado del test","Resultat du test","\301\362\027\356\026\027\362\026\367 \276\376\357\027\362\026\367\025","Stato del Test","Test Status","Test Status","Test Status","Test Status","Status testu","Resultado do teste","\220\266\243\266\267\264 \266\250\264\266\243","Testin vaihe","Test status","Test Durumu"};
const UBYTE *const huge cMSG_TestStates[nb_of_test_states][NB_LANGUAGE]	={{"NOT RUN","IKKE KØRT","L\043uft nicht","NOT RUN","NOT RUN","NO INICIADO","EN ATTENTE","\275\276\304 \302\276\250\312\305\313\307\254\276\250","NON in ESECUZIONE","NOT RUN","NOT RUN","NIET LOPEND","KJØRER IKKE","NIE WYKONANY","NAO INICIOU","\214\204 \214\177\226\177\221","EI K\074YNNISS\074","EJ IG\076NG","\075al\010\327m\010yor"},
	{"RUNNING","KØRER","L\043uft","RUNNING","RUNNING","EN MARCHA","EN COURS","\302\276\250\312\305\313\307\254\276\250","IN ESECUZIONE","RUNNING","RUNNING","LOPEND","KJØRER","W TRAKCIE","EM ANDAMENTO","\201 \216\217\215\225\204\220\220\204","K\074YNNISS\074","IG\076NG","\075al\010\327\010yor"},
	{"NOT RUN","IKKE KØRT","L\043uft nicht","NOT RUN","NOT RUN","NO INICIADO","EN ATTENTE","\275\276\304 \302\276\250\312\305\313\307\254\276\250","NON in ESECUZIONE","NOT RUN","NOT RUN","NIET LOPEND","KJØRER IKKE","NIE WYKONANY","NAO INICIOU","\214\204 \214\177\226\177\221","EI K\074YNNISS\074","EJ IG\076NG","\075al\010\327m\010yor"},
	{"PASS","GENNEMFØRT","BESTANDEN","PASS","PASS","APROBADO","RESUSSI ","\306\276\312\313\316\276","TEST SUPERATO","PASS","PASS","GESLAAGD","PASSERER","OK.","PASSOU","\216\217\215\210\073\204\214","L\074P\074ISTY","GODK\074ND","Testi Ge\337ti"},
	{"FAIL","FEJL I TEST","NICHT BESTANDEN","FAIL","FAIL","FALLADO","ECHEC","\273\306\276\312\313\316\276","TEST FALLITO","FAIL","FAIL","MISLUKT","FEILET","B\077\022D","FALHOU","\220\200\215\210","EP\074ONNISTUNUT","EJ GODK\074ND","Testi Ge\337emedi"}};
const UBYTE *const huge cMSG_CircuitLeak[NB_LANGUAGE]	={"leak test","L\327kage Test","Leckagetest","Leak Test","Leak Test","Test de fuga","Test de fuite","\323\373\366\364\022\377\025 \365\371\362\024\024\377\360\025 ","Leak Test","Leak Test","Leak Test","Test op lekken","Lekkasjetest","Test szczelno\025ci","Teste de fugas","\262\263\306\245\250\263\255\243 \267\266\250\273\255\253 \246\243\252\243 \253\252 \255\306\240\266\267\263\243","Vuototesti","L\332ck test","Ka\325ak Testi"};
const UBYTE *const huge cMSG_LanguageCode[NB_LANGUAGE]	={"ZHO","DAN","DEU","ENG","USA","SPA","FRA","GRK","ITA","JPN","KOR","NLD","NOR","POL","POR","RUS","FIN","SWE","TUR"};
	
/*C Messages du Menu Maintenance */	
const UBYTE *const huge cMSG_MenuMaintenance[NB_LANGUAGE]	={"MAINTENANCE","VEDLIGEHOLDELSE","WARTUNG","MAINTENANCE"," MAINTENANCE","MANTENIMIENTO","MAINTENANCE","\311\313\304\312\277\307\277\311\277","MANUTENZIONE","MAINTENANCE","MAINTENANCE","ONDERHOUD","SERVICE","PRZEGL\022D TECHNICZNY","MANUTEN\075AO","\221\204\224 \215\200\220\135\222\205\207\201\177\214\207\204","HUOLTO","SERVICE","BAKIM"};
const UBYTE *const huge cMSG_SoftwareVersion[NB_LANGUAGE]	={"\346\257\301\242","Soft CPU","Soft. Vers.","Version","Ver","Version","Soft CPU","\276\372\365. \302\377\364.","Versione","Version","Version","Soft CPU","Versjon","Opr. CPU","Ver\325ao","\201\250\263\264\253\303","Soft CPU","Soft CPU","Soft CPU"};
const UBYTE *const huge cMSG_SupplySoftwareVersion[NB_LANGUAGE]	={"\306\276","Soft Alim","PW. Vers.","Pw Supply","Alim","Alimentac","Soft Alim","\312\024\377\031.","Alimentaz","Pw Supply","Pw Supply","Soft voeding","Pw supply","Opr. ZASIL","Alimentac","\216\256\243\266\243 \262\253\266\243\240\253\303","Soft POWER","Soft Alim","Soft Alim"};
const UBYTE *const huge cMSG_ShortSerial[NB_LANGUAGE]	={"s/n","S/N","S/Nr.","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","S/N","Sno"};
const UBYTE *const huge cMSG_HistoAnom[NB_LANGUAGE]	={"\230\372\250\244","Fejlbeskeder","Techn. Meldungen Hist.","Faults Check","Faults Check","Verificar Fallos","Historique Anomalies","\323\373\366\364\022\377\025 \311\031\362\373\374\356\027\034\375","Memoria Guasti","\307\003\250\230\251\235","Faults Check","Afwijkingen historiek","Feils\312king","Rejestr b\033\030d\314w","Verificar Falhas","\216\263\306\245\250\263\255\243 \306\274\253\244\306\255","Vika tarkastus","Felkontroll","Hata kontrol\304"};
const UBYTE *const huge cMSG_VoltCtrl[NB_LANGUAGE]	={"\272\360\250\244","Spaendings kontrol","Werte pr\304fen","Measurement Check","Measurement Check","Control de medidas","Controle des Mesures","\323\373\366\364\022\377\025 \303\366\027\024\360\026\366\034\375","Verifiche Tensione","\311\341\316\250\230\251\235","Measurement Check","Spanning controle","M\331lingssjekk","Rejestr pomiar\314w","Controlo de medidas","\216\263\306\245\250\263\255\243 \253\252\257\250\263\250\240\253\254","Mittaustarkastus","M\331ttkontroll","Öl\325\304m Kontrol\304"};
const UBYTE *const huge cMSG_SensorCal[NB_LANGUAGE]	={"\161\213\022\005\245","Sensor kalibrering","Sensorkalibrierung","Sensors Calibration","Sensors Calibration","Calibracion sensores","Calibrage des Capteurs","\274\362\370\374\377\375\035\374\367\026\367 \273\371\026\370\367\027\360\024\034\375","Calibrazione Sensori","\246\303\240Cal","Sensors Calibration","Sensorenkalibratie","Sensor kalibrering","Kalibracja sensor\314w","Calibra\325ao sensores","\100\243\256\253\244\263\306\245\255\243 \247\243\266\273\253\255\306\245","Sensoreiden kalibrointi","Sensorkalibrering","Sens\313r Kalibrasyonu"};
const UBYTE *const huge cMSG_PatientPressure[NB_LANGUAGE]	={"\307\035\210\140","Patient tryk","Patientendruckkal.","Patient Pressure","Patient Pressure","Presion Paciente","Pression Patient","\306\361\366\026\367 \273\026\370\366\375\377\036\025","Calibr Press Paz","CIRCUIT\334","Patient Pressure","Patientdruk","Pasienttrykk","Ci\025nienie pacjenta","Pressao Paciente","\073\243\245\256. \245 \247\277\270 \262\267\266\303\270","Potilaspaine","Patienttryck","Hasta Bas\010nc\010"};
const UBYTE *const huge cMSG_ValvePressure[NB_LANGUAGE]	={"\021\016\243\210\140","Ventil tryk","Ventildruckkal.","Int Valve pressure","Int Valve pressure","Presion Valvula","Pression Valve","\306\361\366\026\367 \274\362\373\363\361\365\362\025","Calibr Press Valv","Int Valve pressure","Int Valve pressure","Interne klepdruk","Ventiltrykk","Ci\025n. wewn\030trzne","Pressao Valvula","\073\243\245\256 \245\240\267\266\263 \255\256\243\262\243\240\243","Venttiilipaine","Int ventil tryck","\017nt Valf Bas\010nc\010"};
const UBYTE *const huge cMSG_FlowIns[NB_LANGUAGE]	={"\016\263\271\360","Insp flow","Inspirationsflowkal.","Inspiration Flow","Inspiration Flow","Flujo INSP","D\322bit Inspir\322","\276\371\026\023\375\366\030\026\027\371\372\360 \307\377\360","Flusso Insp","\331\256Flow","Inspiration Flow","Inspiratieflow","Inspirasjonsflow","Przep\033yw wdechowy","Fluxo INSP","\216\306\266\306\255 \245\247\306\270\243","Sis\332\332nhengitysvirtaus","Insp fl\313de","\017nspirasyon ak\010\016\010"};
const UBYTE *const huge cMSG_FlowExp[NB_LANGUAGE]	={"\021\263\271\360","Eksp flow","Exspirationsflowkal.","Exhalation Flow","Exhalation Flow","Flujo ESP","D\322bit Expir\322","\276\372\023\375\366\030\026\027\371\372\360 \307\377\360","Flusso Esp","\332\256Flow","Exhalation Flow","Expiratieflow","Ekspirasjonsflow","Przep\033yw wydechowy","Fluxo EXP","\216\306\266\306\255 \245\277\247\306\270\243","Uloshengitysvirtaus","Exp fl\313de","Ekspirasyon ak\010\016\010"};
const UBYTE *const huge cMSG_CalibFiO2[NB_LANGUAGE]	={"Fio2","FiO2","FiO2 Kalibrierung","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","Sensor FiO2","FiO2","FiO2","FiO2","FiO2","FiO2"};
const UBYTE *const huge cMSG_O2Pressure[NB_LANGUAGE]	={"\264\263\210\140","O2 tryk","O2 Druckkal.","O2 Pressure","O2 Pressure","Presion O2","Pression O2","\306\361\366\026\367 \305\376\030\364\035\375\377\030","Pressione O2","\011\375\334","O2 Pressure","O2 druk","O2 trykk","Ci\025nienie tlenu O2","Pressao O2","\073\243\245\256\250\240\253\250 \2152","O2 paine","O2 tryck","O2 Bas\010nc\010"};
const UBYTE *const huge cMSG_FlowO2[NB_LANGUAGE]	={"\264\263\271\360","O2 flow","O2 Flowkal.","O2 Flow","O2 Flow","Flujo O2","D\322bit O2","\307\377\360 \3052","Flusso O2","O2 Flow","O2 Flow","O2 flow","O2 flow","Przep\033yw tlenu O2","Fluxo O2","\216\306\266\306\255 \2152","O2 virtaus","O2 fl\313de","O2 Ak\010\016\010"};
const UBYTE *const huge cMSG_PwmBlower[NB_LANGUAGE]	={"turbine speed","Turbinehastighed","Drehzahl Turbine","Turbine Speed","Turbine Speed","Velocidad Turbina","Vitesse Turbine","\311\027\024\377\031\357\025 \312\377\030\024\374\023\361\375\362\025","Velocit\333 Turbina","Turbine Speed","Turbine Speed","Turbinesnelheid","Turbinhastighet","Pr\030dko\025\034 turbiny","Velocidade Turbina","\220\255\306\263\306\264\266\300 \266\267\263\244\253\240\277","Turbiinin nopeus","Turbinhastighet","T\304rbin H\010z\010"};
const UBYTE *const huge cMSG_Back[NB_LANGUAGE]	={"\351\023","Tilbage","Zur\304ck","Back","Back","Volver","Retour","\306\361\026\034","Indietro","\352\220","Back","Terug","Tilbake","Powr\314t","Virar","\214\243\252\243\247","Takaisin","Tillbaka","Geri D\313n"};
	
/*C Messages Menu Controle des tensions */	
const UBYTE *const huge cMSG_MenuVoltControl[NB_LANGUAGE]	={"MEASUREMENTS CHECK","SPAENDINGS KONTROL","WERTE PRÜFEN","MEASUREMENTS CHECK","MEASUREMENTS CHECK","CONTROL DE MEDIDAS","CONTROLE DES MESURES","\276\302\276\254\316\305\311 \303\276\312\307\277\311\276\047\304","VERIFICHE TENSIONE","MEASUREMENTS CHECK","MEASUREMENTS CHECK","SPANNING CONTROLE","SPENNINGSKONTROLL","POMIARY KONTROLNE","CONTROLO DE MEDIDAS","\216\217\215\201\204\217\100\177 \207\206\213\204\217\204\214\207\210","MITTAUSTEN TARKASTUS","SP\074NNINGSKONTROLL","ÖL\075ÜM KONTROLÜ"};
const UBYTE *const huge cMSG_SupplyTest[NB_LANGUAGE]	={"24V\306\210\250\244","24V Tjek","24V Check","24V Check","24V Check","Verif Alim 24V","Alim 24V","\323\373\366\364\022\377\025 \312\356\026\367\025 24V","24V Check","24V \250\230\251\235","24V Check","24V Controle","24V sjekk","Sprawdzenie 24V","Verif. Alim 24V","\221\250\264\266 24V","24V tarkastus","24V kontroll","24V Kontrol\304"};
const UBYTE *const huge cMSG_WatchdogTest[NB_LANGUAGE]	={"\310\022","Vagthund","Watchdog","Watchdog","Watchdog","Watchdog","Watchdog","Watchdog","Watchdog","Watchdog","Watchdog","Waakhond","Vakthund","System nadzoru","Watchdog","\100\306\240\266\263\306\256\256\250\263","H\332lytysrajan arvo","Vakthund","Watchdog"};
const UBYTE *const huge cMSG_AbsPress[NB_LANGUAGE]	={"\014\263\210","Barometer","Barometrischer Druck","Barometric","Barometric","Presion Atm","Pression barom\322trique","\274\362\024\377\374\366\027\024\371\372\035","Pressione Barometrica","\256\334","Barometric","Barometrisch","Barometer","Ci\025nienie atmosferyczne","Pressao Atm.","\200\243\263\306\257\250\266\263\253\273\250\264\255\253\254","Barometrinen","Barometer","Barometrik "};
const UBYTE *const huge cMSG_Temperature[NB_LANGUAGE]	={"\133\357\275\177","Intern temperatur","Interne Temperatur","Internal Temperature","Internal Temperature","Temp Interna","Temp Interne","\276\026\034\027\366\024\371\372\360 \335\366\024\374\377\372\024\362\026\361\362","Temp Interna","VENT\136\135","Internal Temperature","Interne temperatuur","Intern temperatur","Temperatura wewn\030trzna","Temp Interna","\201\240\267\266\263\250\240\240\303\303 \266\250\257\262\250\263\243\266\267\263\243","Sis\332inen l\332mp\313","Intern temperatur","\017\325 S\010cakl\010k"};
const UBYTE *const huge cMSG_BlowerTemperature[NB_LANGUAGE]	={"\375\243\275\177","Bl\327ser temperatur","Blower Temperatur","Blower Temperature","Blower Temperature","Temp Turbina","Temp Turbine","\335\366\024\374\377\372\024\362\026\361\362 \312\377\030\024\374\023\361\375\362\025","Temperatura Blower","Blower\136\135","Blower Temperature","Turbine Temperatuur","Blower Temperature","Temperatura turbiny","Temperatura Turbina","\221\250\257\262\250\263\243\266\267\263\243 \266\267\263\244\253\240\277","Puhaltimen l\332mp\313tila","Turbin temperatur","T\304rbin Is\010s\010"};
const UBYTE *const huge cMSG_Buzzer[NB_LANGUAGE]	={"\333\377\022","Alarm","Alarm","Buzzer","Buzzer","Zumbador","Buzzer","\274\377\374\363\367\027\360\025","Buzzer","Backup\264\241\304","Buzzer","Zoemer","Buzzer","Brz\030czyk","Zumbidor","\214\243\262\263\303\251\250\240\253\250 \244\243\266 \266\263\250\245\306\246\253","H\332lytys 1","Larm 1","Alarm "};
const UBYTE *const huge cMSG_BuzzerSec[NB_LANGUAGE]	={"\013\305\333\377\022","Back up Alarm ","Back-up Alarm","Back-up Buzzer ","Back-up Buzzer ","Zumbador Sec","Buzzer Sec","\276\031\366\365\024\371\372\035\025 \274\377\374\363\367\027\360\025","Buzzer di back-up","\036\251\235\224\251\265\264\241\304","Back-up Buzzer ","Back-up zoemer","Back-up buzzer","Brz\030czyk zapasowy","Zumbador Sec","\216\263\306\245\250\263\255\243 \252\245\267\255\243 \266\263\250\245\306\246\253","H\332lytys 2","Larm 2","Back UP alarm"};
const UBYTE *const huge cMSG_BatteryMenu[NB_LANGUAGE]	={"\133\330\306\265","Intern Batteri Menu","Men\304 interne Batterie","Internal Battery Menu","Internal Battery Menu","Menu Bateria Interna","Menu Batterie","\303\366\375\377\036 \276\026\034\027. \303\023\362\027\362\024\361\362\025","Men\311 Batteria Interna","Internal Battery Menu","Internal Battery Menu","Menu interne batterij","Intern batterimeny","Wewn\030trzna Bateria","Menu Bateria Interna","\213\250\240\302 \245\240\267\266\263\250\240\240\250\254 \244\243\266\243\263\250\253","Akkuvalikko","Internbatteri meny","Dahili Batarya Men\304"};
const UBYTE *const huge cMSG_BaroCorrect[NB_LANGUAGE]	={"altitude comp","H\312jde kompensation","H\313henkompensation","Altitude Comp","Altitude Comp.","Compensacion Altitud","Compensation d'altitude","\313\033\377\374\366\027\024\371\372\360 \275\371\035\024\370\034\026\367","Compensaz Altitudine","Altitude Comp","Altitude Comp","Hoogte compensatie","H\312ydekompensasjon","Komp Wysoko\025ci n.p.m","Compensa\325ao Altitude","\100\306\257\262\250\240\264\243\271\253\303 \243\266\257. \247\243\245\256","Ilmanpaineen korjaus","H\313jdkompensation","Y\304kseklik Komp"};
	
/*C Messages Menu batterie */	
const UBYTE *const huge cMSG_InternalBatteryMenu[NB_LANGUAGE]	={"INTERNAL BATTERY","INTERNT BATTERI","INTERNE BATTERIE","INTERNAL BATTERY","INTERNAL BATTERY","BATERIA INTERNA","BATTERIE INTERNE","\276\311\047\312\276\307\250\301\277 \303\306\273\312\273\307\250\273","BATTERIA INTERNA","INTERNAL BATTERY","INTERNAL BATTERY","INTERNE BATTERIJ","INTERNT BATTERI","WEWN\027TRZNA BATERIA","BATERIA INTERNA","\201\214\222\221\217\204\214\214\242\242 \200\177\221\177\217\204\242","AKKU","INTERNT BATTERI","DAH\017L\017 BATARYA"};
const UBYTE *const huge cMSG_BatSupplier[NB_LANGUAGE]	={"\306\276","Batteriforsyning","Batterietyp","Supplier","Supplier","Proovedor","Fournisseur","\306\024\377\374\367\370\366\030\027\360\025","Tipo Batteria","Supplier","Supplier","Leverancier","Leverand\312r","Dostawca","Provedor","\216\306\264\266\243\245\275\253\255","L\332hde","Supplier","Supplier"};
const UBYTE *const huge cMSG_BatTheoreticalCapacity[NB_LANGUAGE]	={"\237\014\006\360","Teoretisk kapacitet","Theoretische Kapazit\332t","Theoretical capacity","Theoretical capacity","Capacidad teorica","Capacit\322 th\322orique","\305\375\377\374\362\026\027\371\372\360 \353\034\024\367\027\371\372\035\027\367\027\362","Capacit\333 Teorica","Theoretical capacity","Theoretical capacity","Theor. Capaciteit","Teoretisk kapasitet","Pojemno\025\034 katalog","Capacidade te\314rica","\204\257\255\306\264\266\300 \244\243\266\243\263\250\253","Teoreettinen suorituskyky","Teoretisk kapacitet","Teorik kapasite"};
const UBYTE *const huge cMSG_FirstUseDate[NB_LANGUAGE]	={"\252\132\305","Ibrugtagningsdato","Erste Verwendung","First Use Date","First Use Date","Fecha primer uso","Premi\324re utilisation","\353\024\360\026\367 \362\023\035","Data 1° Utilizzo","\315\325\137\133\363","First Use Date","Datum 1e gebruik","Oppstartsdato","Data instalacji","Data primeiro uso","\073\243\266\243 1-\246\306 \245\255\256\302\273\250\240\253\303","Ensik\332ytt\313 pvm","Anv\332ndningsstart","Ba\016lang\010\325 Tarihi"};
const UBYTE *const huge cMSG_BatAgeing[NB_LANGUAGE]	={"\006\360","Kapacitet","Kapazit\332t","Capacity","Capacity","Capacidad","Capacit\322","\353\034\024\367\027\371\372\035\027\367\027\362","Capacit\333","Capacity","Capacity","Capaciteit","Kapasitet ","Pojemno\025\034 pomiar","Capacidade","\223\243\255\266\253\273. \250\257\255\306\264\266\300","Suorituskyky","Kapacitet","Kapasite"};
const UBYTE *const huge cMSG_CyclesDone[NB_LANGUAGE]	={"\227\306\004","Rest Kapacitet ","Entladezyklen","Cycles done","Cycles done","Ciclos realizados","Cycles effectu\322s","\301\036\372\373\377\371","Capacit\333 Res Batt","\360\020\240\226\235\300","Cycles done","aantal ontladingen","Antall ladinger","Wykonane \033adowania","Capacidade restante","\100-\245\306 \271\253\255\256\306\245 \252\243\263\303\247\255\253","Akkua j\332ljell\332","Kapacitet kvar","Dolum Say\010s\010"};
const UBYTE *const huge cMSG_BatteryVoltage[NB_LANGUAGE]	={"\306\265\306\210","Batteri sp\327nding","Batteriespannung","Battery Voltage","Battery Voltage","Tension Bateria","Tension Batterie","\312\356\026\367 \303\023\362\027\362\024\361\362\025","Tensione Batteria","Battery Voltage","Battery Voltage","Batterij voltage","Batteri volt","Napi\030cie Baterii","Tensao Bateria","\201\306\256\300\266\243\251 \244\243\266\243\263\250\253","Akun j\332nnite","Batteri volt","Batarya Voltaj\010"};
const UBYTE *const huge cMSG_BatteryTemperature[NB_LANGUAGE]	={"\306\265\275\177","Batteri Temperatur","Batterietemperatur","Battery Temperature","Battery Temperature","Temp Bateria","Temp Batterie","\335\366\024\374\377\372\024\362\026\361\362 \303\023\362\027\362\024\361\362\025","Temp Batteria","Battery Temperature","Battery Temperature","Batterij temperatuur","Batteritemperatur","Temperatura Baterii","Temp Bateria","\221\250\257\262\250\263. \244\243\266\243\263\250\253","Akun l\332mp\313","Batteritemperatur","Batarya Is\010s\010"};
const UBYTE *const huge cMSG_BatSupplierUnknown[NB_LANGUAGE]	={"UNKNOWN","UKENDT BATTERI","UNBEKANNTE BATT","UNKNOWN","UNKNOWN","BAT DESCONOCIDA","INCONNU","\273\254\304\047\311\312\277 \303\306\273\312\273\307\250\273","BATT SCONOSC","UNKNOWN","UNKNOWN","ONGEKENDE BAT.","UKJENT BATTERI","NIEZNANY","BAT DESCONHECID","\214\204\207\206\201 \200\177\221\177\217\204\242","TUNTEMATON","OK\074NT BATTERI","TANIMSIZ PIL"};
const UBYTE *const huge cMSG_BatSupplier3[NB_LANGUAGE]	={"APPROVED","GODKENDT","GOEDGEKEURD","APPROVED","APPROVED","APROBADO","APPROUVÉ","APPROVED","APPROVATO","APPROVED","APPROVED","GODKJENT","ZATWIERDZONY","APROVADO","APPROVED","APPROVED","APPROVED","APPROVED","ONAYLANDI"};
const UBYTE *const huge cMSG_NoBat[NB_LANGUAGE]	={"\306\265","Intet batteri fundet","Keine Batterie","No Battery detected","No Battery detected","Bateria no detectada","Batterie absente","\273\023\377\030\026\361\362 \303\023\362\027\362\024\361\362\025","Batteria Non Rilevata","No Battery detected","No Battery detected","Geen Batterij Aanwezig","Mangler batteri","Brak Baterii","Bateria nao detectada","\214\250\266 \244\243\266\243\263\250\253","Ei akkua tunnistettu","inget batteri p\331tr\332ffat","BATARYA YOK"};
	
/*C Messages Menu Historique anomalies */	
const UBYTE *const huge cMSG_MenuHistoAno[NB_LANGUAGE]	={"\354\377","FEJLBESKEDER","FEHLERSPEICHER","FAULTS","FAULTS","FALLOS","HISTORIQUE ANOMALIES","\311\314\273\302\303\273\312\273","GUASTI","FAULTS","FAULTS","FOUTEN","FEILMELDINGER","REJESTR B\077\027DÓW","FALHAS","\215\227\207\200\100\207","VIRHEILMOITUKSET","FELMEDDELANDEN","HATALAR"};
const UBYTE *const huge cMSG_Cpt[NB_LANGUAGE]	={"\337\234\022","Timer","Stundenz\332hler","Hour Meter","Hour Meter","Conta Hr","Compteur","\355\024\377\374\366\027\024.","Conta Ore","\373\371\346\370","Hour Meter","Urenmeter","Timer","Godz pracy"," Conta Hr","\220\273\250\266\273\253\255 \273\243\264\306\245","Tuntilaskuri","Timmar","Saat Saya\325"};
	
/*C Messages du Menu Welcome */	
const UBYTE *const huge cMSG_Welcome[NB_LANGUAGE]	={"HELLO","VELKOMMEN","GUTEN TAG","HELLO","HELLO","HOLA","BONJOUR","HELLO","BUONGIORNO","     HELLO","HELLO","HALLO","VELKOMMEN","WITAM","OLA","\206\073\217\177\201\220\221\201\222\210\221\204","TERVETULOA","V\074LKOMMEN","MERHABA"};
const UBYTE *const huge cMSG_Machine[NB_LANGUAGE]	={"\243\022","Maskine","Masch.","Machine","Machine","Maquina","Machine","\311\030\026\372\366\030\360","Macchina","\373\371","Machine","Machine","Maskin","Aparat","Maquina","\177\262\262\243\263\243\266","Laite","Maskin","Makine"};
const UBYTE *const huge cMSG_PatWelcome[NB_LANGUAGE]	={"\307\035","Patient","Therap.","Patient","Patient","Paciente","Patient","\273\026\370\366\375\360\025","Paziente","\351\002","Patient","Pati\317nt","Pasient","Pacjent","Paciente","\216\243\271\253\250\240\266","Potilas","Patient","Hasta"};
const UBYTE *const huge cMSG_VSoft[NB_LANGUAGE]	={"\346\257\301\242","Software Version","Software Version","Software version","Software version","Version Software","Versions logiciel","\323\372\365\377\026\367 \302\377\364\371\026\374\371\372\377\036","Versione SW","Software version","Software versions","Software versie","Programversjon","Wersja programowa","Versao Software","\201\250\263\264\253\303 \262\263\306\246\263 \306\244\250\264\262","Ohjelmistoversio","Mjukvaru version","Software Versiyonu"};
const UBYTE *const huge cMSG_CopyrightWelcome[NB_LANGUAGE]	={"Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019","Copyright 2019"};
const UBYTE *const huge cMSG_CompanyWelcome[NB_LANGUAGE]	={"COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN","COVIDIEN"};
	
/*C Messages des Modes de Ventilation */	
const UBYTE *const huge cMSG_Mode[nb_of_mode][NB_LANGUAGE]	={{"ACV","VACV","A/C VCV","V A/C","V A/C","VAC","VAC","V A/C","V A/C","V A/C","V A/C","AVC","VACV","ACV","ACV","V A/C","VACV","VACV","ACV"},
	{"PACV","PACV","A/C PCV","P A/C","P A/C","VPAC","VPAC","P A/C","P A/C","P A/C","P A/C","PACV","PACV","PACV","PACV","P A/C","PACV","PACV","PACV"},
	{"PSV ST","PSV ST","PSV S/T","PSV ST","PSV ST","PSV ST","AI FR","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST","PSV ST"},
	{"SIMV","SIMV","V-SIMV","V SIMV","V SIMV","V SIMV","VACI","V SIMV","SIMV","V SIMV","V SIMV","V SIMV","SIMV","SIMV"," V SIMV","V SIMV","SIMV","SIMV","SIMV"},
	{"P SIMV","P SIMV","P-SIMV","P SIMV","P SIMV","P SIMV","PACI","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV"},
	{"CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP"}};
const UBYTE *const huge cMSG_Mode2[nb_of_mode][NB_LANGUAGE]	={{"CV","VCV","VCV","VC","VC","VC","VC","VC","VCV","VCV","VC","VC","VCV","CV","CV","VC","VCV","VCV","CV"},
	{"PCV","PCV","PCV","PC","PC","VPC","VPC","PC","PCV","PCV","PC","PCV","PCV","PCV","PCV","PC","PCV","PCV","PCV"},
	{"PSV S","PSV S","PSV S ","PSV ","PSV ","PSV S","AI","PSV","PSV","PSV","PSV ","PSV ST","PSV S","PSV S","PSV S","PSV ","PSV S","PSV S","PSV S"},
	{"SIMV","SIMV","V-SIMV","V SIMV","V SIMV","V SIMV","VACI","V SIMV","SIMV","V SIMV","V SIMV","V SIMV","SIMV","SIMV"," V SIMV","V SIMV","SIMV","SIMV","SIMV"},
	{"P SIMV","P SIMV","P-SIMV","P SIMV","P SIMV","P SIMV","PACI","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV"},
	{"CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP"}};
const UBYTE *const huge cMSG_Mode3[nb_of_mode][NB_LANGUAGE]	={{"CV (ACV)","VCV (VACV)","(A/C) VCV","CV(V A/C)","CV(V A/C)","VC (VAC)","VC (VAC)","CV(V A/C)","VCV(ACV)","CV(V A/C)","CV(V A/C)","VC (AVC)","VCV (VACV)","CV (ACV)","CV (ACV)","CV(V A/C)","VCV (VACV)","VCV (VACV)","CV (ACV)"},
	{"PCV (PACV)","PCV (PACV)","(A/C) PCV","PC(P A/C)","PC(P A/C)","VPC(VPAC)","VPC (VPAC)","PC(P A/C)","PCV(PACV)","PC(P A/C)","PC(P A/C)","PCV (PACV)","PCV (PACV)","PCV (PACV)","PCV (PACV)","PC(P A/C)","PCV (PACV)","PCV (PACV)","PCV (PACV)"},
	{"PSV S(T)","PSV S(T)","PSV S(T)","PSV (ST)","PSV (ST)","PSV (ST)","AI (FR)","PSV (ST)","PSV(PSV ST)","PSV S(T)","PSV (ST)","PSV S(T)","PSV S(T)","PSV S(T)","PSV (ST)","PSV (ST)","PSV S(T)","PSV S(T)","PSV S(T)"},
	{"SIMV","SIMV","V-SIMV","V SIMV","V SIMV","V SIMV","VACI","V SIMV","SIMV","V SIMV","V SIMV","V SIMV","SIMV","SIMV"," V SIMV","V SIMV","SIMV","SIMV","SIMV"},
	{"P SIMV","P SIMV","P-SIMV","P SIMV","P SIMV","P SIMV","PACI","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV","P SIMV"},
	{"CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP","CPAP"}};
const UBYTE *const huge cMSG_InspTrigger[nb_of_trigger_levels][NB_LANGUAGE]	={{"OFF","OFF","AUS","OFF","OFF","OFF","OFF","OFF","OFF","OFF","OFF","OFF","AV","WY\077","OFF","OT\100\135","OFF","OFF","OFF"},
	{"0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P","0P"},
	{"1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P","1P"},
	{"2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2","2"},
	{"3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3","3"},
	{"4","4","4","4","4","4","4","4","4","4","4","4","4","4","4","4","4","4","4"},
	{"5","5","5","5","5","5","5","5","5","5","5","5","5","5","5","5","5","5","5"}};
const UBYTE *const huge cMSG_EnableMode[NB_LANGUAGE]	={"\175\037\100","AKTIV","AKTIV","ACTIVE","ACTIVE","ACTIVO","ACTIF","\276\304\276\307\254\305","ATTIVO","\314\326\310","ACTIVE","ACTIEF","AKTIV","AKTYWNE","ACTIVO","\177\100\221\207\201","K\074YTÖSS\074","AKTIV","AKT\017F"};
const UBYTE *const huge cMSG_DisableMode[NB_LANGUAGE]	={"\241\037\100","IKKE AKTIV","NICHT AKTIV","INACTIVE","INACTIVE","NO ACTIVO","NON ACTIF","\303\277 \276\304\276\307\254\305","NON ATTIVO","\367\314\326","INACTIVE","NIET ACTIEF","IKKE AKTIV","PROPOZYCJA","INACTIVO","\214\204\177\100\221\207\201","EI K\074YTÖSS\074","EJ AKTIV","\017NAKT\017F"};
const UBYTE *const huge cMSG_AutoMode[NB_LANGUAGE]	={"\371\342","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","\177\201\221\215","AUTO","AUTO","OTO"};
const UBYTE *const huge cMSG_PressureSlope[NB_LANGUAGE]	={"\210\140\052\041\234\365","Stigningstid","Anstiegzeit","Rise Time","Rise Time","Acele Flujo","Pente","Rise Time","Rise Time","Rise Time","Rise Time","Stijgingstijd","Stigetid","Narastanie","Subida Ti","\222\264\255 \216\306\266\306\255\243","Nousuaika","Stigtid","Rise Ti"};
const UBYTE *const huge cMSG_Rampe[NB_LANGUAGE]	={"\271\360\267\205","Flowkurve","Flow","Ramp","Flow","Rampa","Rampe","Ramp","Flusso","\331\256\257\350","Ramp","Ramp","Ramp","Krzywa","Rampa","\223\306\263\257\243 \255\263.","Flow k\332yr\332","Ramp","Rampa"};
const UBYTE *const huge cMSG_ExhalationPressure[NB_LANGUAGE]	={"EPAP","EPAP","EPAP","PEEP","PEEP","EPAP","Pe","PEEP","EPAP","PEEP","PEEP","EPAP","EPAP","EPAP","EPAP","PEEP","EPAP","EPAP","EPAP"};
const UBYTE *const huge cMSG_CpapPressure[NB_LANGUAGE]	={"CPAP","Cpap","CPAP","CPAP","CPAP","CPAP","Cpap","CPAP","CPAP","CPAP","CPAP","CPAP","Cpap","CPAP","Cpap","CPAP","Cpap","Cpap","Cpap"};
const UBYTE *const huge cMSG_InsuflationPressureControl[NB_LANGUAGE]	={"Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi"};
const UBYTE *const huge cMSG_InsuflationPressureControl2[NB_LANGUAGE]	={"Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi"};
const UBYTE *const huge cMSG_InsuflationPressureSupport[NB_LANGUAGE]	={"P Support","P Support","IPAP supp","P Support","P Support","P Soporte","Support P","P Support","IPAP","P Support","P Support","P Support","P Support","P Support","P Suporte","P Support","P Support","P Support","P Support"};
const UBYTE *const huge cMSG_CurrantVolume[NB_LANGUAGE]	={"Vt","VT","Vt","Vt","Vt","VT","Vt","Vt","Vt","Vt","Vt","VT","VT","VT","VT","Vt","VT","VT","VT"};
const UBYTE *const huge cMSG_InspirationTrigger[NB_LANGUAGE]	={"\016\263\335\044","Insp trigg","Trigg I","I Sens","Insp Sens","Trigg I","Trigg I","I Sens","Trigg Insp","\331\256Sens","Trigg I","Trigg Insp.","Insp trigg","Wyzw I","Trigg I","\221\263\253\246 \201\247\306\270\243","Insp Trigg","Insp trigg","Tetik I"};
const UBYTE *const huge cMSG_ExhalationTrigger[NB_LANGUAGE]	={"\021\263\335\044","Eksp trigg","Trigg E","E Sens","Exh Sens","Trigg E","Trigg E","E Sens","Trigg Esp","\332\256Sens","Trigg E","Trigg Exp.","Eksp trigg","Wyzw E","Trigg E","\221\263\253\246 \201\277\247.","Eksp trigg","Exp trigg","Tetik E"};
const UBYTE *const huge cMSG_ControlRate[NB_LANGUAGE]	={"\021\016\374\303","Frekvens","Af","Rate","R-Rate","Fr","Fr mini","Rate","Frequenza","\333\361","Rate","Frequentie","Frekvens","RR","Fr","\226\073","Taajuus","Frekvens","Frekans"};
const UBYTE *const huge cMSG_BackupRate[NB_LANGUAGE]	={"\036\013\021\016\374\303","Sikret Fr","Backup Af","Backup R","Backup R","Fr Reserva","Fr sec","Backup R","F Back Up","Backup\361","Backup R","Backup F","Backup R","RRa Apnea","Fr Reserva","\226\073 \243\262\240\306\301","Min Frekv","Back up R","Back Up R"};
const UBYTE *const huge cMSG_Apnee[NB_LANGUAGE]	={"\321\211\354\263","Apn\312 tid","Apnoezeit","Apnea time","Apnea time","Apnea","Apn\322e","Apnea Time","Apnea","\322\332\331\364\014","Apnea time","Apneu Tijd","Apnea","Ta Apnea","Apneia","T \243\262\240\306\301","Apnea","Apne","Apne"};
const UBYTE *const huge cMSG_TiControl[NB_LANGUAGE]	={"\016\263\234\365","Insp Time","Insp. Zeit","Insp Time","Insp Time","T. Insp","Ti Control\322","Insp Time","Tempo Insp","\331\256\364\014","Insp Time","Insp Tijd","Insp Time","Czas wdech","Tempo Insp ","T \245\247\306\270\243","Insp Time","Insp Time","Insp Time"};
const UBYTE *const huge cMSG_IERation[NB_LANGUAGE]	={"I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E"};
const UBYTE *const huge cMSG_ITRation[NB_LANGUAGE]	={"I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T"};
const UBYTE *const huge cMSG_TiMon[NB_LANGUAGE]	={"Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","Ti","T \245\247\306\270\243","Ti","Ti","Ti"};
const UBYTE *const huge cMSG_TeMon[NB_LANGUAGE]	={"Te","Te","Te","Te","Te","Te","Te","Te","Te","Te","Te","Te","Te","Te","Te","T \245\277\247\306\270\243","Te","Te","Te"};
const UBYTE *const huge cMSG_Pulse[NB_LANGUAGE]	={"#CHAR!#CHAR!","Pulse","Puls","Pulse","Pulse","Pulso","Pulsation","Pulse","Freq Polso","Pulse","Pulse","Pulse","Puls","Puls","Pulso","\216\267\256\300\264","Pulssi","Puls","Pulse"};
const UBYTE *const huge cMSG_Soupir[NB_LANGUAGE]	={"\034\211","Suk","Seufzer","Sigh","Sigh","Suspiro","Soupir","Sigh","Sigh","\302\332\331","Sigh","Zucht","Sukk","Westchn.","Suspiro","\201\252\247\306\270","Huokaisu","Suck","Sigh"};
const UBYTE *const huge cMSG_VtSoupir[NB_LANGUAGE]	={"\034\211\300\263\360","Suk Vt","Vt Seufz","Sigh Vt","Sigh Vt","Vt Susp","Vt Soupir","Sigh Vt","Vt Sigh","\302\332\331Vt","Sigh Vt","Zucht Vt","Sukk Vt","Westchn. VT","Vt Susp","Vt \245\252\247\306\270\243","Huokaisu Vt","Suck Vt","Sigh Vt"};
const UBYTE *const huge cMSG_CptSoupir[NB_LANGUAGE]	={"\034\211\021\016\374\303","Suk Frekv","Af Seufz","Sigh Rate","Sigh Rate","Fr Susp","Cpt Soupir","Sigh Rate","Freq Sigh","\302\332\331\333\361","Sigh Rate","Zucht Freq","Sukk frekv","Westchn. RR","Fr Susp","\226\073 \245\252\247\306\270\306\245","Huokaisutaajuus","Suck Frekv","Sigh fre"};
const UBYTE *const huge cMSG_FiO2[NB_LANGUAGE]	={"FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2 "};
const UBYTE *const huge cMSG_VTCible[NB_LANGUAGE]	={"\312\245\300\263\360","Vt garanti","Ziel Vt","Vt Target","Vt Target","Vt Target","Vt Cible","Vt Target","Vt Target","\327\372Vt","Vt Target","Vt Target","Vt garanti","VTdocelowa","Vt Target","Vt \271\250\256\250\245\306\254","Tav.Tilavuus","Vt garanti","Hedef Vt"};
const UBYTE *const huge cMSG_PiMax[NB_LANGUAGE]	={"\237\014\016\263\210","Max tryk","P Max","Max P","Max P","P Maxi","Pi Maxi","Max P","P Maxi","\366\022\334","Maxi P","P Max","Max trykk","P max","P Maxi","P max","Max paine","Max tryck","Maks P"};
const UBYTE *const huge cMSG_VaciRate[NB_LANGUAGE]	={"SIMV\374\303","SIMV Frek","Af SIMV","SIMV Rate","SIMV Rate","Fr SIMV","Fr VACI","SIMV Rate","SIMV Rate","SIMV\361","SIMV Rate","SIMV Freq","SIMV Frekv","SIMV RR","Fr SIMV","\226\073 SIMV","SIMV- taajuus","SIMV Frekv","SIMV frekans"};
const UBYTE *const huge cMSG_InsuflationPressurePeakMon[NB_LANGUAGE]	={"PIP","IPAP","PIP","PIP","PIP","PIP","Pi","PIP","PIP","PIP","PIP","IPAP","IPAP","PIP","PIP","P \262\253\255","IPAP","IPAP","PIP "};
const UBYTE *const huge cMSG_Vti[NB_LANGUAGE]	={"Vti","VTI","Vti","VtI","VtI","VTI","Vti","VtI","Vt I","VTI","VtI","VTI","VTI","VTI","VTI","Vt \245\247","VTI","VTI","VTI"};
const UBYTE *const huge cMSG_Vte[NB_LANGUAGE]	={"Vte","VTE","Vte","VtE","VtE","VTE","Vte","VtE","Vt E","VTE","VtE","VTE","VTE","VTE","VTE","Vt \245\277\247","VTE","VTE","VTE"};
const UBYTE *const huge cMSG_Vm[NB_LANGUAGE]	={"M.Vol","M.Vol","M.Vol","M.Vol","M.Vol","Vol M","Vm","M.Vol","V Min","M.Vol","M.Vol","AMV","M.Vol","MVE","Vol M","M.Vol","M.Vol","M.Vol","D Hac"};
const UBYTE *const huge cMSG_RateMon[NB_LANGUAGE]	={"rate","Fr","Af","Rate","Rate","Fr","Fr","Rate","Freq","Rate","Rate","Freq","Fr","RR","Fr","\226\073","Fr ","Fr","Rate"};
const UBYTE *const huge cMSG_IERationMon[NB_LANGUAGE]	={"I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E","I:E "};
const UBYTE *const huge cMSG_ITRationMon[NB_LANGUAGE]	={"I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I/T","I:T","I/T","I/T","I/T"};
const UBYTE *const huge cMSG_FuiteMon[NB_LANGUAGE]	={"leak","Leaks","Leck","Leak","Leak","Fuga","Fuite","Leaks","Leak","\277\304\235","Leak","Lek","Lekk","Leak","Fuga","\222\266\250\273\255\253","Vuoto","L\332ck","Ka\325ak"};
const UBYTE *const huge cMSG_FiO2Mon[NB_LANGUAGE]	={"FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2","FiO2"};
const UBYTE *const huge cMSG_SpO2[NB_LANGUAGE]	={"SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2"};
const UBYTE *const huge cMSG_StartVentil[NB_LANGUAGE]	={"\221\210|\200\003\354\263","TRYK|FOR START","ZUM START|DRÜCKEN","PRESS|TO START VENTILATION","PRESS|TO START VENTILATION","PULSAR|PARA VENTILAR","APPUYER SUR POUR VENTILER","\306\250\276\311\312\276 \254\250\273|\276\304\273\307\343\277 \273\276\307\250\311\303\305\313","PREMERE|PER|VENTILARE","\357\256\137\133\212\214|\222\354\203\210\201\207\202\177","PRESS|TO START VENTILATION","DRUK|OM VENTILATIE|TE STARTEN","TRYKK|FOR START","NACI\024NIJ ABY|ROZPOCZ\022\026|WENTYLACJ\027","APERTAR|PARA VENTILAR","\214\243\251\243\266\300|\247\256\303 \240\243\273\243\256\243|\245\250\240\266\253\256\303\271\253\253","PAINA|K\074YNNIST\074","TRYCK|FÖR START","VENT\017LASYONA|BA\011LAMAK \017Ç\017N|BASIN"};
const UBYTE *const huge cMSG_StopVentil[NB_LANGUAGE]	={"\221\210|\217\3263\317|\256\254\354\263","HOLD|3 SEK|FOR STOP","FÜR STOP|3 SEK DRÜCKEN|UND HALTEN","KEEP|PRESSED FOR|3 SEC TO STOP","KEEP|PRESSED FOR|3 SEC TO STOP","MANTENER|3 SEGUNDOS|PARA PARAR","MAINTENIR|3 SECONDES|POUR STOPPER","\306\250\276\311\312\276 3 \275\276\313\312.|\254\250\273 \306\273\313\311\277|\273\276\307\250\311\303\305\313","PREMERE PER|3 SECONDI|PER FERMARE","3\344|\354\203\210|\317\374\203\210\201\207\202\177","KEEP|PRESSED FOR|3 SEC TO STOP","DRUK 3 SEC|OM VENTILATIE|TE STOPPEN","HOLD|3 SEK|FOR STOPP","PRZYCI\024NIJ NA|3 SEK|ABY ZATRZYMA\026","MANTER|3 SEGUNDOS|PARA PARAR","\073\256\303 \306\264\266\243\240\306\245\255\253|\240\243\251\243\266\300 \253 \247\250\263\251\243\266\300|3 \264\250\255\267\240\247\277","PYS\074YT\074|PID\074 ALHAALLA|3 SEK ","TRYCK|3 SEK|FÖR STOPP","KAPATMAK \017Ç\017N|3 SN|BASILI TUTUN"};
	
const UBYTE *const huge cMSG_StopConfirmVentil[NB_LANGUAGE]	={"\221\210|\256\254\354\375","TRYK|IGEN FOR AT|GODKENDE STOP","STOP BEST\074T.|TASTE ERNEUT|DRÜCKEN","PRESS|AGAIN TO|CONFIRM STOP","PRESS|AGAIN TO|CONFIRM STOP","PULSAR|DE NUEVO PARA|CONFIRMAR ","APPUYER|POUR|CONFIRMER","\306\250\276\311\312\276 \275\250\311|\254\250\273 \306\273\313\311\277","PREMERE|ANCORA|PER FERMARE","\314\326\317\374\212\214|\222\354\203\215\204|(\337\006\325)","PRESS|AGAIN TO|CONFIRM STOP","DRUK|NOG EENS OM|TE BEVESTIGEN","TRYKK IGJEN|FOR Å|BEKREFTE STOPP","NACI\024NIJ|PONOWNIE|ABY ZATRZYMA\026","PRIMIR|DE NOVO PARA|CONFIRMAR","\214\243\251\243\266\300|\262\306\245\266\306\263\240\306|\247\256\303 \306\264\266\243\240\306\245\255\253","PAINA|UUDELLEEN|VAHVISTAAKSESI","TRYCK|FÖR ATT|BEKR\074FTA STOPP","KAPATMAYI|ONAYLAMAK \017Ç\017N|TEKRAR BASIN"};
const UBYTE *const huge cMSG_VPreferences[NB_LANGUAGE]	={"\043\232","Praeferencer","Grundeinstellungen","Preferences","Preferences","Preferencias","Pr\322f\322rences","\306\024\377\027\371\374\360\026\366\371\025","Preferiti","\005\341","Preferences","Voorkeursinstellingen","Preferanser","Preferencje","Preferencias","\073\306\262\306\256\240\253\266\250\256\300\240\306","Suositukset","Preferenser","Tercihler"};
const UBYTE *const huge cMSG_IsensHelperTxt[NB_LANGUAGE]={"The lower the number, the more sensitive the trigger.", "Jo lavere nummer, jo mere f\312lsom er udl\312seren.", "Je niedriger der Wert, desto empfindlicher der Trigger.", "The lower the number, the more sensitive the trigger", "The lower the number, the more sensitive the trigger", "A menor numero, mas sensible sera el trigger.", "Plus nbre est petit, plus d\322clench resp est sensible.", "\325\026\377 \023\371\377 \374\371\372\024\035\025 \362\024\371\370\374\035\025 \027\035\026\377 \023\371\377 \366\030\362\361\026\370\367\027\367 \023\030\024\377\365\035\027\367\026\367.", "Pi\311 piccolo \324 il numero, pi\311 sensibile \324 il trigger. ", "\361\316\214\313\177\211\217, sensitivity\214\022\201\211\220.", "The lower the number, the more sensitive the trigger.", "Hoe lager het getal, hoe gevoeliger de trigger.", "Jo lavere tall, desto mer sensitiv er triggeren.", "Im ni\036sza cyfra, tym bardziej czu\033a jest czu\033o\025\034 wyzwalania.", "Quanto mais baixo o numero, mais sensivel o disparo.", "\226\250\257 \257\250\240\300\274\250 \273\253\264\256\306, \266\250\257 \273\267\245\264\266\245\253\266\250\256\300\240\250\250 \266\263\253\246\246\250\263.", "Mit\332 pienempi numero, sit\332 herkempi laukaisu. ", "Ju l\332gre siffra, desto k\332nsligare trigger.", "Say\010 ne kadar k\304\325\304k olursa, tetik o kadar hassas olur."};

/*C Messages Menu d'Alarme */	
const UBYTE *const huge cMSG_MiniTab[NB_LANGUAGE]	={"\237\010","Min ","Min","Min","Low","Mini","Mini","\276\373\362\022.","Min","\306\034","Min","Min","Min","Min","Min","\213\253\240","Min","Mini","Min"};
const UBYTE *const huge cMSG_PatientTab[NB_LANGUAGE]	={"\203\137","Patient","Patient","Current","Current","Actual","Patient","\312\024\357\022\034\375","Pazient"," \311\341\316","Current","Huidig","Pasient","Pomiar","Atual","\216\243\263\243\257","Potilas","Patient","Aktif "};
const UBYTE *const huge cMSG_MaxiTab[NB_LANGUAGE]	={"\237\014","Max  ","Max","Max","High","Maxi"," Maxi","\303\366\364.","Max","\305\034","Max","Max","Max","Max","Max","\213\243\255\264","Max","Maxi","Max"};
const UBYTE *const huge cMSG_PiMbar[NB_LANGUAGE]	={"PIP","IPAP","PIP","PIP","PIP","PIP","Pi","PIP","PIP","PIP","PIP","IPAP","IPAP","PIP","PIP","P \262\253\255","IPAP","IPAP","PIP"};
const UBYTE *const huge cMSG_VteMl[NB_LANGUAGE]	={"Vte ml","VTE mL","Vte ml","VtE mL","VTE mL","VTE ml","Vte mL","VtE mL","Vt E mL","VTE mL","VTE mL","VTE mL","VTE mL","VTE mL","VTE mL","V \245\277\247 \257\256","VTE (ml)","VTE mL","VTE mL"};
const UBYTE *const huge cMSG_VmLpm[NB_LANGUAGE]	={"M.Vol l","M.Vol L","M.Vol L","M.Vol L","Min.Vol L","Vol M L","Vm L","M.Vol L","Vol Min L","M.Vol L","M.Vol L","AMV L","M.Vol L","MVI L","Vol M L","M.Vol \256","Min Vol (l)","M.Vol L","D Hac L"};
const UBYTE *const huge cMSG_FrCMin[NB_LANGUAGE]	={"Rtot bpm","Fr /min","F AZ/min","Rtot bpm","R tot bpm","Fr c/min","Fr c/min","Rtot bpm","Fr bpm","\333\361","Rtot bpm","Freq bpm","Fr /min","RRtot bpm","Fr c/min","\226\073 /\257\253\240","Fr /min","Fr /min","Rtot n/dak"};
const UBYTE *const huge cMSG_TiS[NB_LANGUAGE]	={"\016\263\234\365","I Time s","Ti s","I Time s","I Time s","Ti s","Ti s","I Time s","T Insp","I Time s","I Time s","Ti sec","I Tid s","Czas Ti s","Ti s","T \245\247 \264\250\255","I aika s","I tid s","I Zaman s"};
const UBYTE *const huge cMSG_VtiMl[NB_LANGUAGE]	={"Vti ml","VTI mL","Vti ml","VTI mL","VTI mL","VTI ml","Vti mL","VtI mL","VtI mL","VTI mL","VTI mL","VTI mL","VTI mL","VTI mL","VTI mL","V \245\247 \257\256","VTI (ml)","VTI mL","VTI mL"};
const UBYTE *const huge cMSG_FiO2Pc[NB_LANGUAGE]	={"FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %","FiO2 %"};
const UBYTE *const huge cMSG_ExhalationPressureMon[NB_LANGUAGE]	={"PEEP","PEEP","EPAP","PEEP","PEEP","PEEP","Pe","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP","PEEP"};
const UBYTE *const huge cMSG_SpO2Pc[NB_LANGUAGE]	={"spO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %","SpO2 %"};
const UBYTE *const huge cMSG_FuiteParam[NB_LANGUAGE]	={"\277\263\360","Leak l/min","Leck l/min","Leak l/min","Leak l/min","Fuga l/min","Fuite l/min","Leak l/min","Leak l/min","\277\304\235/min","Leak l/min","Lek. lpm","Lekk l/min","Leak l/min","Fuga l/min","\222\266\250\273 \256/\257","Vuoto l/s","L\332ck I/min","Ka\325ak l/d"};
const UBYTE *const huge cMSG_MeanAirwayPressureMon[NB_LANGUAGE]	={"MAP","MAP","MAP","MAP","MAP","Pres media","MAP","MAP","MAP","MAP","MAP","MAP","MAP","MAP","Press media","P \264\263\250\247","MAP","MAP","MAP"};
const UBYTE *const huge cMSG_HistoAlarm[NB_LANGUAGE]	={"\216\336\340\204","Gemte alarmer","Alarmprotokoll","Alarms Logs","Alarm Log","Historico Alarmas","Historique Alarmes","\277\374\366\024. \311\030\375\362\364\366\024\374\037\375","Memoria Allarmi","\224\276\304\270\343\376","Alarms Logs","Alarmhistoriek","Alarm-minne","Rejestr Alarm\314w","Historico Alarmes","\205\267\263\240\243\256 \266\263\250\245\306\246","H\332lytykset","Larm logg","Alarm Kay\010tlar\010"};
const UBYTE *const huge cMSG_switchMode[NB_LANGUAGE]	={"\315\005\251\201","Skift Modus","Modus \332ndern","Accept Mode","Accept Mode","Cambiar modo","Changer Mode","\273\023\377\365\377\022\360","Camb Modalit\333","\272\304\255\335\365","Accept Mode","Accepteer modus","Aksepter modus","Zaakceptuj Tryb","Mudar modo","\201\245\306\247","Hyv\332ksy","\074ndra Mode","Onay"};
const UBYTE *const huge cMSG_CalibQExpTab[NB_LANGUAGE]	={"\246\255\021\263\271\360","Kalibrering Eksp Flow ?","Kalibration Exsp. Flow?","Calibration Exp. Flow ?","Calibration Exp. Flow ?","Calibracion Flujo Esp?","Calibration d\322bit Exp ?","\274\362\370\374\377\375\035\374\367\026\367 \276\372\023\375. \307\377\360\025;","Calibrazione Flusso Esp ?","\332\256Flow Cal\222\342\362 ?","Calibration Exp. Flow ?","Kalibratie exp Flow?","Kalibrere eksp flow?","Kalibracja wydech sensora przep\033ywu?","Calibra\325ao| Fluxo Exp.?","\100\243\256\253\244\263\306\245\243\266\300 \262\306\266\306\255 \245\277\247\306\270\243?","Kalibroi uloshengitys ?","Kalibrering Exp fl\313de?","Ekp Ak\010\016 Kalibrasyonu"};
const UBYTE *const huge cMSG_CalibQExpProcessing[NB_LANGUAGE]	={"\021\263\246\255\352\334\131","Eksp kalib|i proces...","Exsp. Kalib.|l\332uft...","Exp. calib.|Processing","Exp. calib.|Processing","Calibr.| Flujo Esp en curso","Calib d\322bit Exp|en cours...","\274\362\370\374\377\375\035\374\367\026\367 \276\372\023\375. \307\377\360\025|\026\366 \366\376\357\373\371\376\367...","Calibrazione Flusso|Esp in corso...","\332\256Flow Cal|\342\362\310","Exp. calib.|Processing","Exp Kalibratie|in werking...","Eksp kal|p\331g\331r...","Kalibracja wydech sensora w trakcie...","Calibr.| Fluxo Exp. em curso","\207\247\250\266 \255\243\256\253\244\263\306\245\255\243|\262\306\266\306\255\243 \245\277\247\306\270\243","Uloshengitys kalibroituu...","Exp kalib|p\331g\331r...","Ekp Kalib / \017\016lemde"};
const UBYTE *const huge cMSG_CalibFiO2Tab[NB_LANGUAGE]	={"\246\255\016\107\264\273\177","FiO2 Kalibrering ?","Kalibration FiO2 ?","FiO2 Calibration ?","FiO2 Calibration ?","Calibracion FiO2 ?","Calibration FiO2 ?","\274\362\370\374\377\375\035\374\367\026\367|\273\371\026\370\367\027\360\024\362 FIO2;","Calibrazione FiO2 ?","FiO2 Cal \222\342\362?","FiO2 Calibration ?","Kalibratie FiO2?","FiO2 kalibrering?","Kalibracja sensora tlenu FIO2?","Calibra\325ao FiO2 ?","\215\266\255\243\256\253\244\263\306\245\243\266\300 FiO2 ?","Kalibroi FiO2 ?","FiO2 Kalibrering ?","FiO2 Kalibrasyonu?"};
const UBYTE *const huge cMSG_CalibFiO2Processing[NB_LANGUAGE]	={"\016\107\264\273\177\246\255\352\334\131","FiO2 kalib|i proces...","FiO2 Kalib.|l\332uft...","FiO2 calib|Processing...","FiO2 calib.|Processing...","Calibr.| FiO2 en curso","Calib FiO2|en cours...","\274\362\370\374\377\375\035\374\367\026\367 \273\371\026\370\367\027\360\024\362|FIO2 \026\366 \366\376\357\373\371\376\367...","Calibrazione FiO2 in corso...","FiO2 cal\342\362\310","FiO2 calib|Processing...","FiO2 kalibratie|in werking...","FiO2 kalibrering|p\331g\331r...","Kalibracja sensora FIO2 w trakcie...","Calibr.| FiO2 em curso","\207\247\250\266 \255\243\256\253\244\263\306\245\255\243|FiO2","FiO2 kalibroituu...","FiO2 Kalibrering|p\331g\331r...","FiO2 Kalib / \017\016lemde"};
	
	
const UBYTE *const huge cMSG_SettingBlock[NB_LANGUAGE]	={"\341\005\370\136","Indstilling blokeret","Einstell. begrenzt","Setting limited by","Setting limited by","Ajuste limitado por","R\322glage bloqu\322 par","\306\366\024\371\377\024\371\026\374\035\025 \362\023\035","Impost Limit da","Setting limited by","Setting limited by","Instel. begrensd door","Inst begrenses av","Ograniczono przez","Ajuste limitado por","\214\243\264\266\263\306\254\255\243 \306\246\263\243\240\253\273\250\240\243","Asetus rajoitettu","Inst begr\332nsas av","Limitli Ayarlar"};
const UBYTE *const huge cMSG_BlockedSetting[End_Limit_Setting - Start_Limit_Setting - 1][NB_LANGUAGE]	={{"\016\263\011\210\054\370","IPAP Min","IPAP Min","PIP Min","Low PIP","PIP Min","Pi Mini","PIP Min","P Min","P Min","PIP Min","IPAP min","IPAP Min","PIP Min","PIP Min","P\262\253\255 \257\253\240","IPAP Minimi","IPAP Min","PIP Min"},
	{"\016\263\011\210\052\370","IPAP Max","IPAP Max","PIP Max","High PIP","PIP Max","Pi Maxi","PIP Max","P Max","P Max","PIP Max","IPAP max","IPAP Max","PIP Max","PIP Max","P\262\253\255 \257\243\255\264","IPAP Maksimi","IPAP Max","PIP Max"},
	{"EPAP","EPAP","EPAP","PEEP","PEEP","PEEP","Pe","PEEP","PEEP","PEEP","PEEP","EPAP","EPAP","Ci\025nienie EPAP","PEEP","PEEP","EPAP","EPAP","EPAP"},
	{"VT","VT","Vt","Vt","Vt","VT","Vt","Vt","VT","VT","Vt","VT","VT","Obj\030to\025\034 VT","VT","Vt","VT","VT","VT"},
	{"\016\263\234\365","Insp Tid","Insp.-zeit","Insp Time","Insp Time","T. Insp","Ti Control","Insp Time","Tempo Insp","\331\256\364\014","Insp Time","Insp Tijd","Insp Time","Insp Time","Tempo Insp","T \245\247\306\270\243","Sis\332\332nhengitysaika","Insp Time","Insp Time"},
	{"\021\016\374\303","Fr","Af","Rate","Rate","Fr","Fr","Rate","Frequenza","\333\361","Rate","Freq","Rate","Cz\030sto\025\034 RR","Fr","\226\073","Taajuus","Fr","Frekans"},
	{"Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi","Pi"},
	{"\016\263\300\263\360\054\370","VTI Min","Vti Min","VtI Min","Low VTI","VTI Min","Vti Mini","VtI Min","Vt I Min","VTI Min","VtI Min","VTI min","VTI Min","Obj\030to\025\034 VTI Min","VTI Min","V \245\247\306\270\243 \257\253\240","VTI Minimi","VTI Min","VTI Min"},
	{"\016\263\300\263\360\052\370","VTI Max","Vti Max","VtI Max","High VTI","VTI Max","Vti Maxi","VtI Max","Vt I Max","VTI Max","VtI Max","VTI max","VTI Max","Obj\030to\025\034 VTI Max","VTI Max","V \245\247\306\270\243 \257\243\255\264","VTI Mksimi","VTI Max","Vt\010 Max"},
	{"\021\263\300\263\360\054\370","VTE Min","Vte Min","VtE Min","Low VTE","VTE Min","Vte Mini","VtE Min","Vt E Min","VTE Min","VtE Min","VTE min","VTE Min","Obj\030to\025\034 VTE Min","VTE Min","V \245\277\247 \257\253\240","VTE Minimi","VTE Min","VTE Min"},
	{"\021\263\300\263\360\052\370","VTE Max","Vte Max","VtE Max","High VTE","VTE Max","Vte Maxi","VtE Max","Vt E Max","VTE Max","VtE Max","VTE max","VTE Max","Obj\030to\025\034 VTE Max","VTE Max","V \245\277\247 \257\243\255\264","VTE Maksimi","VTE Max","VTE Max"},
	{"P Support","P Support","IPAP support","P Support","P Support","P Soporte","Support P","P Support","P Supporto","\240\267\304\254\334","P Support","P Support","P Support","P Support","P Suporte","P Support","Painetuki","P Support","P Support"},
	{"\016\263\234\365\054\370","ITime Min","Ti Min","ITime Min","Low Itime","Ti Min","Ti Mini","ITime Min","Tempo Insp Min","ITime Min","ITime Min","Insp. tijd min","I Tid Min","Czas Ti Min","Ti Min","T \245\247 \257\253\240","Minimi sis\332\332nhengitysaika","I tid min","I Zaman\010 Min"},
	{"\016\263\234\365\052\370","ITime Max","Ti Max","ITime Max","Max Itime","Ti Max","Ti Maxi","ITime Max","Tempo Insp Max","ITime Max","ITime Max","Insp. tijd max","I Tid Max","Czas Ti Max","Ti Max","T \245\247 \257\243\255\264","Maksimi sis\332\332nhengitysaika","I tid max","I Zaman\010 Max"},
	{"SpO2\054\370","SpO2 mini","SpO2 min","SpO2 min","Low SpO2","SpO2 mini","SpO2 mini","SpO2 min","SpO2 mini","SpO2 Min","SpO2 min","SpO2 min","SpO2 min","SpO2 Min","SpO2 mini","SpO2 min","SpO2 minimi","SpO2 mini","SpO2 mini"},
	{"SpO2\052\370","SpO2 maxi","SpO2 max","SpO2 max","High SpO2","SpO2 maxi","SpO2 maxi","SpO2 max","SpO2 maxi","SpO2 Max","SpO2 max","SpO2 max","SpO2 max","SpO2 Max","SpO2 maxi","SpO2 max","SpO2 maksimi","SpO2 maxi","SpO2 maxi"},
	{"\016\263\335\044","Insp trigg","Trigg I","I Sens","Insp Sens","Trigg I","Trigg I","I Sens","Trigg Insp","\331\256Sens","I Sens","Trigg Insp.","Insp Trigg","Wyzwalanie I","Trigg I","\221\263\253\246 \245\247\306\270\243","Sis\332\332nhengityksen triggeri","Insp trigg","Tetik I"},
	{"\034\211","Suk","Seufzer","Sigh","Sigh","Suspiro","Soupir","Sigh","Sigh","\302\332\331","Sigh","Zucht","Sukk","Westchnienia","Suspiro","\201\252\247\306\270","Huokaisu","Suck","Sigh"},
	{"\312\245\300\263\360","Vt garanti","Ziel Vt","Vt Target","Vt Target","Vt Target","Vt Cible","Vt Target","Vt Target","\327\372Vt","Vt Target","Vt Target","Vt garanti","Docelow\023 VT ","Vt Target","Vt \271\250\256\250\245\306\254","Tav.Tilavuus","Vt garanti","Hedef Vt"},
	{"\321\211\354\263","Apnea","Apnoe","Apnea","Apnea","Apnea","Apn\322e","Apnea","Apnea","\322\332\331","Apnea","Apneu","Apne","Czas Apnea Ta","Apneia","\177\262\240\306\301","Apnea","Apne","Apne"},
	{"high FiO2","High FiO2","High FiO2","High FiO2","High FiO2","FiO2 Max","High FiO2","High FiO2","High FiO2","High FiO2","High FiO2","High FiO2","H\312y FiO2","High FiO2","FiO2 Alto","\201\277\264\306\255\253\254 FiO2","High FiO2","High FiO2","High FiO2"},
	{"low FiO2","Low FiO2","Low FiO2","Low FiO2","Low FiO2","FiO2 Min","Low FiO2","Low FiO2","Low FiO2","Low FiO2","Low FiO2","Low FiO2","Lav FiO2","Low FiO2","FiO2 baixo","\214\253\252\255\253\254 FiO2","Low FiO2","Low FiO2","Low FiO2"},
	{"SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2"},
	{"\351\023\354\263\302\207","Sikret Fr","Backup Af","Back up R","Bk up R","Fr Reserva","Fr sec","Back up R","F Back Up","Backup\361","Back up R","Backup F","Backup Fr","Cz\030sto\025\034 Apnea RRa","Fr Reserva","\226\073 \243\262\240\306\301","Turvataajuus","Back up R","Back Up R"},
	{"Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","Pmax","P \257\243\255\264","Pmax","Pmax","Pmax"}};
	
/*C Messages Menu Courbes */	
const UBYTE *const huge cMSG_Vmi[NB_LANGUAGE]	={"M.Vol","M.Vol","M.Vol","M.Vol","M.Vol","Vol M","Vm","M.Vol","V Min","M.Vol","M.Vol","M.Vol","M.Vol","MVI","M.Vol","M.Vol","M.Vol","M.Vol","M.Vol"};
const UBYTE *const huge cMSG_OutOfLimit[NB_LANGUAGE]	={"\344\073\024","Uden for omr\331de","Au\335erhalb der Anzeige","Out Of Range","Out Of Range","Fuera Limites","Hors Limites","Out Of Range","Fuori Limite","Out Of Range","Out Of Range","Buiten bereik","Utenfor m\331leskala","Poza zakresem","Fora Limites","\201\240\250 \247\306\262\267\264\266 \262\263\250\247\250\256\306\245","Rajojen ulkopuolella","Utanf\313r m\332tskala","Limit D\010\016\010"};
	
/*C Units */	
const UBYTE *const huge cMSG_PressureUnit[3][NB_LANGUAGE]	={{"mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","mbar","\257\200\243\263","mbar","mbar","mbar"},
	{"cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","cmH2O","\264\257H2O","cmH2O","cmH2O","cmH2O"},
	{"hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","hPa","\246\216\243","hPa","hPa","hPa"}};
const UBYTE *const huge cMSG_VolumeUnit[NB_LANGUAGE]	={"ml","mL","mL","mL","mL","mL","mL","mL","mL","mL","mL","mL","mL","mL","mL","\257\256","mL","mL","mL"};
const UBYTE *const huge cMSG_VolumeLiterUnit[NB_LANGUAGE]	={"l","L","L","L","L","L","L","L","L","L","L","L","L","L","L","\256","L","L","L"};
const UBYTE *const huge cMSG_PerCentUnit[NB_LANGUAGE]	={"%","%","%","%","%","%","%","%","%","%","%","%","%","%","%","%","%","%","%"};
const UBYTE *const huge cMSG_FlowUnit[NB_LANGUAGE]	={"lpm","L/min","L/min","Lpm","Lpm","Lpm","Lpm","Lpm","Lpm","Lpm","Lpm","Lpm","L/min","Lpm","Lpm","\256/\257\253\240","l/min","L/min","L/dak"};
const UBYTE *const huge cMSG_StandardFlowUnit[NB_LANGUAGE]	={"slpm","L/min","L/min","sLpm","sLpm","sLpm","sLpm","sLpm","sLpm","sLpm","sLpm","sLpm","L/min","sLpm","sLpm","\264.\256/\257\253\240","l/min","L/min","L/dak"};
const UBYTE *const huge cMSG_FrequencyUnit[NB_LANGUAGE]	={"bpm","bpm","AZ/min","bpm","bpm","c/min","c/min","bpm","bpm","bpm","bpm","spm","bpm","bpm","c/min","\247/\257\253\240","bpm","bpm ","n/dak"};
const UBYTE *const huge cMSG_SpeedUnit[NB_LANGUAGE]	={"rpm","rpm","u/min","rpm","rpm","rpm","tr/min","rpm","rpm","rpm","rpm","rpm","rpm","rpm","rpm","\306\244/\257\253\240","rpm","rpm","rpm"};
const UBYTE *const huge cMSG_TensionUnit[NB_LANGUAGE]	={"V","V","V","V","V","V","V","V","V","V","V","V","V","V","V","V","V","V","V"};
const UBYTE *const huge cMSG_PowerUnit[NB_LANGUAGE]	={"mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh","mAh"};
const UBYTE *const huge cMSG_TempUnit[NB_LANGUAGE]	={"°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","°C","C"};
const UBYTE *const huge cMSG_AbsPressUnit[NB_LANGUAGE]	={"mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","mmHg","\257\257.\263\266.\264\266.","mmHg","mmHg","mmHg"};
const UBYTE *const huge cMSG_PressBarUnit[NB_LANGUAGE]	={"bar","bar","bar","bar","bar","bar","bar","bar","bar","bar","bar","bar","bar","bar","bar","\244\243\263","bar","bar","bar"};
const UBYTE *const huge cMSG_HourUnit[NB_LANGUAGE]	={"h","t","Std.","h","h","h","h","h","h","h","h","uur","t","h","h","\273","t","t","sa"};
const UBYTE *const huge cMSG_MinuteUnit[NB_LANGUAGE]	={"min","min","Min.","min","min","min","min","min","min","min","min","min","min","min","min","\257\253\240","min","min","dak"};
const UBYTE *const huge cMSG_SecondUnit[NB_LANGUAGE]	={"s","s","sek","s","s","s","s","s","s","s","s","s","s","s","s","ce\255","s","s","s"};
const UBYTE *const huge cMSG_eventUnit[NB_LANGUAGE]	={"\252\047\257/\010\234","Ev/t","Ev/Std","Ev/h","Ev/h","Ev/h","Ev/h","Ev/h","Ev/h","Ev/h","Ev/h","Ev/uur","Ev/t","Ev/h","Ev/h","\264\306\244/\273","tap/t","Ev/h","Ev/ s"};
const UBYTE *const huge cMSG_DayUnit[NB_LANGUAGE]	={"\001","dage","Tag","days","days","dias","Jours","days","gg","days","days","dagen","dager","dni","dias","\247\240\250\254","pv","dagar","g\304n"};
const UBYTE *const huge cMSG_MonthUnit[NB_LANGUAGE]	={"months","months","Monat","months","months","meses","mois","months","months","months","months","months","m\331neder","months","meses","\257\250\264\303\271\250\245","months","m\331nader","months"};
const UBYTE *const huge cMSG_HoursByDayUnit[NB_LANGUAGE]	={"\010\234/\001","t/dage","Std/T","h/days","h/days","h/dias","h/jour","h/days","hh/gg","h/days","h/days","uur/dg","t/dag","h/dob\030","h/dias","\273/\247\250\240\300","h/pv","t/dag","s/ g\304n"};
	
/*C Miscellaneous Messages */	
const UBYTE *const huge cMSG_Stop[NB_LANGUAGE]	={"\256\254","Stop","Stop","Stop","Stop","Stop","Stop","\306\362\036\026\367","Stop","Stop","Stop","Stop","Stopp","Stop","Stop","\220\266\306\262","Stop","Stop","Stop"};
const UBYTE *const huge cMSG_Wait[NB_LANGUAGE]	={"|wait...","|WAIT . . .","|Bitte warten..","|WAIT . . .","|WAIT . . .","|Espere  . . .","|PATIENTEZ . . .","|\273\304\273\303\305\304\277 . . .","|Attendere  . . .","|WAIT . . .","|WAIT . . .","|WACHT . . .","|VENT . . .","|CZEKAJ . . .","|Espere  . . .","|\215\251\253\247\243\240\253\250 . . .","|ODOTA. . .","|V\074NTA . . .","|WAIT . . ."};
const UBYTE *const huge cMSG_ShortWait[NB_LANGUAGE]	={"wait...","WAIT . . .","Bitte warten..","WAIT . . .","WAIT . . .","Espere  . . .","PATIENTEZ . . .","\273\304\273\303\305\304\277 . . .","Attendere  . . .","WAIT . . .","WAIT . . .","WACHT . . .","VENT . . .","CZEKAJ . . .","Espere  . . .","\215\251\253\247\243\240\253\250 . . .","ODOTA . . .","V\074NTA. . .","WAIT . . ."};
const UBYTE *const huge cMSG_No[NB_LANGUAGE]	={"OFF","NEJ","NEIN","OFF","OFF","NO","NON","NO","NO","OFF","OFF","UIT","AV","WY\077","NAO","\214\204\221","EI","AV","OFF"};
const UBYTE *const huge cMSG_Off[NB_LANGUAGE]	={"OFF","AF","AUS","OFF","OFF","OFF","NON","OFF","OFF","OFF","OFF","UIT","AV","WY\077","OFF","\201\230\100\135","POIS","AV","OFF"};
const UBYTE *const huge cMSG_Yes[NB_LANGUAGE]	={"YES","JA","JA","YES","YES","SI","OUI","YES","SI","YES","YES","JA","JA","TAK","SIM","\073A","KYLL","JA","EVET"};
const UBYTE *const huge cMSG_On[NB_LANGUAGE]	={"ON","TIL","EIN","ON","ON","ON","ON","ON","ON","ON","ON","AAN","P\076","ZA\077","ON","B\100\135","P\074\074L","P\076","A\075IK"};
const UBYTE *const huge cMSG_NoneUnit[NB_LANGUAGE]	={"","","","","","","","",""," ","","","","","","","","",""};
const UBYTE *const huge cMSG_Slash[NB_LANGUAGE]	={"/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/","/"};
const UBYTE *const huge cMSG_Colon[NB_LANGUAGE]	={":",":",":",":",":",":",":",":",":",":",":",":",":",":",":",":",":",":",":"};
const UBYTE *const huge cMSG_Sup[NB_LANGUAGE]	={">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>",">>"};
const UBYTE *const huge cMSG_MoreOrLess[NB_LANGUAGE]	={"±","±","±","±","±","±","±","±","±","±","±","±","±","±","±","±","±","±","±"};
const UBYTE *const huge cMSG_Auto[NB_LANGUAGE]	={"AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","AUTO","ABTO","AUTO","AUTO","OTO"};
const UBYTE *const huge cMSG_IEHeader[NB_LANGUAGE]	={"1/","1/","1/","1/","1/","1/","1/","1/","1/","1/","1/"," ","1/","1/","1/","1/","1/","1/","1/"};
const UBYTE *const huge cMSG_Pediatric[NB_LANGUAGE]	={"1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1 (P)","1(P)","1 (P)","1 (\216)","1 (P)","1 (P)","1(P)"};
const UBYTE *const huge cMSG_Am[NB_LANGUAGE]	={"am","am","am","am","am","am","am","\023\374","am","am","am","am","am","am","am","am","am","am","am"};
const UBYTE *const huge cMSG_Pm[NB_LANGUAGE]	={"pm","pm","pm","pm","pm","pm","pm","\374\374","pm","pm","pm","pm","pm","pm","pm","pm","pm","pm","pm"};
const UBYTE *const huge cMSG_Original[NB_LANGUAGE]	={"Original(louder)" ,  "ORIGINAL(HØJERE)", "Original (lauter)"  ,"Original(louder)" ,"Original(louder)" ,"Original (+ alto)"  ,"Original/fort"  , "\306\307\211\312\305\311(\313\245.)",   "Originale(alto)"  ,"Original(louder)",   "Original(louder)" , "Oorspr. (hard)"  , "Orig (kraft.)" , "Orygin. (g\136.)" ,"Original (mais alto)" ,"\215\217\207\202.(\202\217\215\213\100\207\210)" , "Alk.p. (kova)" , "Original (h\175gre)","ORJ. (Y\334KSEK)"};
const UBYTE *const huge cMSG_Compliant[NB_LANGUAGE]	={"Compliant(softer)",  "TILPAS(LAVERE)"  , "Angepasst (leiser)" ,"Compliant(softer)","Compliant(softer)","Conf. (+ bajo)"  ,"Adaptative/faible" , "\273\306\302\133\311(\316\273\303.)",   "Tono Confort(low)"  ,"Compliant(softer)",  "Compliant(softer)", "Norm (zacht)"  , "Komp. (svak.)"  ,"Zgodny (mi\173kszy)"  ,"Cmpt. (+ suave)","\220\221\177\214\073.(\221\207\227\204)", "Std. (vaimea)" ,  "Komp. (mjuk.)" ,    "UYUMLU (YUM.)"};
	
/*C Messages Menu config graph */	
const UBYTE *const huge cMSG_MenuGraphConfig[NB_LANGUAGE]	={"\356\367\374\370","KURVE INDSTILLING","KURVENKONFIGURATION","WAVEFORM SETUP","WAVEFORM SETUP","CONFIGURACION CURVA","CONFIGURATION COURBE","\307\313\300\303\250\311\276\250\311 \301\313\303\273\312\305\303\305\307\314\277\311","TIPOLOGIA CURVE","WAVEFORM SETUP","CURVE SETUP","CURVES INSTELLEN","KURVEOPPSETT","USTAWIENIA WYKRESÓW","CONFIGURA\075AO CURVA","\214\177\220\221\217\215\210\100\177 \100\217\207\201\215\210","K\074YR\074 S\074\074DÖT","SETUP KURVOR","DALGA FORMU AYARLARI"};
const UBYTE *const huge cMSG_Visualisation[NB_LANGUAGE]	={"\235\316","Skaerm","Anzeige","Display","Display","Visualizacion","Visualisation","\273\023\366\371\372\035\375\371\026\367","Visualizzazione","\253\225\244\265\301\304","Display","Display","Display","Typ wykresu","Visualiza\325ao","\073\253\264\262\256\250\254","N\332ytt\313","Display","Ekran"};
const UBYTE *const huge cMSG_PressionMax[NB_LANGUAGE]	={"\210\140\237\014\121","Max tryk","Bargraph Druck","Max pressure","Max pressure","Presion max","Pression max","\303\366\364. \306\361\366\026\367","Pressione Max","Max pressure","Max pressure","Max druk","Max trykk","Skala Ci\025nienia","Pressao max","\213\243\255\264 \247\243\245\256\250\240\253\250","Maksimipaine","Max tryck","Max Bas\010n\325"};
const UBYTE *const huge cMSG_DebitMax[NB_LANGUAGE]	={"\271\360\237\014\121","Max flow","Bargraph Flow","Max flow","Max flow","Flujo max","D\322bit max","\303\366\364. \307\377\360","Flusso Max","Max flow","Max flow","Max flow","Max flow","Skala Przep\033ywu","Fluxo max","\213\243\255\264 \262\306\266\306\255","Maksimivirtaus","Max fl\313de","Max Ak\010\016"};
const UBYTE *const huge cMSG_VtMax[NB_LANGUAGE]	={"\300\263\360\237\014\121","Vt max","Bargraph Volumen","Vt max","Vt max","Vt max","Vt max","\303\366\364. Vt","Vt Max","Vt max","Vt max","Vt max","Vt Max","Skala Obj\030to\025ci","Vt max","\213\243\255\264 Vt","Vt maksimi","Vt Max","Vt Max"};
const UBYTE *const huge cMSG_TempsMax[NB_LANGUAGE]	={"\234\365\237\014\121","Max tid","Bargraph Zeit","Max time","Max time","Tiempo max","Temps max","\303\366\364. \353\024\035\375\377\025","Tempo Massimo","Max time","Max time","Max tijd","Max tid","Skala Czasu","Tempo max","\213\243\255\264 \245\263\250\257\303","Maksimiaika","Max tid","Max zaman"};
const UBYTE *const huge cMSG_Representation[NB_LANGUAGE]	={"\236\325\324\027","Kurve type","Kurventyp","Waveform type","Waveform type","Representacion","Repr\322sentation","\312\036\023\377\025 \372\030\374\362\027\377\374\377\024\031\360\025","Tipo Curva","\257\350\247\226\265","Waveform type","Type curve","Kurvetype","Rodzaj wykresu","Representa\325ao","\221\253\262 \255\263\253\245\306\254","K\332yr\332n muoto","Kurv typ","Dalga \016ekli "};
const UBYTE *const huge cMSG_CurveVisualisation1[NB_LANGUAGE]	={"\343\341+\365\376","TRYK+FLOW","DRUCK UND FLOW","PRESSURE+FLOW","PRESSURE+FLOW","PRESION+FLUJO","PRESSION+DEBIT","\306\250\276\311\277+\307\305\277","PRESS / FLUSSO","PRESSURE+FLOW","PRESSURE+FLOW","DRUK+ FLOW","TRYKK+FLOW","CI\024N+PRZEP\077YW","PRESSAO+FLUXO","\073\177\201\135\204\214\207\204+\216\215\221\215\100","PAINE+VIRTAUS","TRYCK+FLÖDE","BASIN\075+AKI\011"};
const UBYTE *const huge cMSG_CurveVisualisation2[NB_LANGUAGE]	={"\366","KURVE","LOOPS","LOOP","LOOP","BUCLE","BOUCLE","\274\307\305\316\305\311","LOOP","\037\236\033","LOOP","LOOP","KURVE","P\027TLA","BUCLE","\216\204\221\135\242","LOOP","KURVA","HALKA"};
const UBYTE *const huge cMSG_CurveRepresentation1[NB_LANGUAGE]	={"\367","LINIE","LINIE","LINE","LINE","TRAZO","TRAIT","\254\307\273\303\303\277","LINEA","\036\004\235","LINE","LIJN","LINJE","LINIA","LINHA","\100\217\207\201\177\242","LINJA","LINJE","\075\017ZG\017"};
const UBYTE *const huge cMSG_CurveRepresentation2[NB_LANGUAGE]	={"\347","HISTOGRAM","HISTOGRAMM","HISTOGRAM","HISTOGRAM","HISTOGRAMA","HISTOGRAMME","\250\311\312\305\254\307\273\303\303\273","ISTOGRAMMA","\025\007\023\006\036\035","HISTOGRAM","HISTOGRAM","HISTOGRAM","HISTOGRAM","HISTOGRAMA","\202\207\220\221\215\202\217\177\213\213\177","HISTOGRAMMI","HISTOGRAM","H\017STOGRAM"};
	
/*C Messages Menu Rapport de ventilation */	
const UBYTE *const huge cMSG_ReportTitle[NB_LANGUAGE]	={"\361\362\375\363\352\346","VENTILATION RAPPORT","BEATMUNGSREPORT","VENTILATION REPORT","VENTILATION REPORT","INFORME DE VENTILACION","RAPPORT VENTILATION","\273\304\273\314\305\307\273 \273\276\307\250\311\303\305\313","REPORT VENTILAZIONE","VENTILATION REPORT","VENTILATION REPORT","VENTILATIERAPPORT","VENTILASJONSRAPPORT","RAPORT WENTYLACJI","INFORME DE VENTILA\075AO","\215\221\226\204\221 \215 \201\204\214\221\207\135\242\225\207\207","VENTILAATIO RAPORTTI","VENTILATION RAPPORT","VENTILASYON RAPORU"};
const UBYTE *const huge cMSG_VentTimeReport[NB_LANGUAGE]	={"\176\026\354\263\234\365","Vent gennemsnit","Beatmungszeit","Vent Time","Vent Time","Promedio Vent","Dur\322e de ventilation","\303.\305. \353\024\360\026\367\025","Media Vent/gg","Vent Time","Vent Time","Vent. tijd ","Vent. Tid","Wentylacja \025rednio","Prom\322dio Vent","\201\263\250\257\303 \207\201\135","Vent.Keskiarvo.","Genomsn vent","Averaj vent"};
const UBYTE *const huge cMSG_ReportDay[NB_LANGUAGE]	={"on","on","am","on","on","el","le","on","il","on","on","aan","p\331","od","el"," ","P\332\332ll\332","on","on"};
const UBYTE *const huge cMSG_ReportTableTitle[NB_LANGUAGE]	={"\237\350\075\001\310\272\133\006","Sidste monitoreringsdag","Monitoring letzter Tag","Last day monitoring","Last day monitoring","Monitorizacion ultimo dia","Monitorages sur la derni\324re journ\322e","\312\366\373\366\030\027\362\361\362 \367\374\357\024\362 \023\362\024\362\372\377\373\377\036\370\367\026\367\025","Ultimo gg Monitorato","Last day monitoring","Last day monitoring","Laatste monitoring dag","Sist overv\331ket","Dane z ostatniego dnia","Monitoriza\325ao ultimo dia","\213\306\240\253\266\306\263\253\240\246 \252\243 \264\267\266\255\253","Viimeinen monitorointip\332iv\332","Senast \313vervakad ","Son monit\313rizasyon bilgileri"};
const UBYTE *const huge cMSG_VtiReport[NB_LANGUAGE]	={"Vti","VTI","Vti","VtI","VtI","VTI","Vti","VtI","Vt I","VTI","VTI","VTI","VTI","VTI","VTI","Vt \245\247\306\270\243","VTI","VTI","VTI"};
const UBYTE *const huge cMSG_VteReport[NB_LANGUAGE]	={"Vte","VTE","Vte","VtE","VtE","VTE","Vte","VtE","Vt E","VTE","VTE","VTE","VTE","VTE","VTE","Vt \245\277\247\306\270\243","VTE","VTE","VTE"};
const UBYTE *const huge cMSG_VmReport[NB_LANGUAGE]	={"Vm","M.Vol","M.Vol","M.Vol","M.Vol","Vol M","Vm","M.Vol","Vol Min","M.Vol","M.Vol","AMV","M.Vol","MVI","Vol M","M.Vol","M.Vol","M.Vol","D Hac"};
const UBYTE *const huge cMSG_Spo2Report[NB_LANGUAGE]	={"SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2","SpO2"};
const UBYTE *const huge cMSG_IAReport[NB_LANGUAGE]	={"\321\211\220\232","Al","Apnoe Index","AI","AI","I Apnea","IA","AI","AI","\322\332\331\355\361","AI","AI","Al","AI","I Apneia","\207\240\247 \243\262\240\306\301","AI","AI","Apne"};
const UBYTE *const huge cMSG_SpontReport[NB_LANGUAGE]	={"Spont","Spontan","Spontan","Spont cyc","Spont cyc","Espont","Spont","Spont cyc","Spont","Spont","Spont cyc","Spont. Cycli","Spontan","SPONT","Espon.","% \220\262\306\240\266","Spontaanit syklit %","Spontan","Spont"};
const UBYTE *const huge cMSG_FrReport[NB_LANGUAGE]	={"\021\016\374\303","Fr","Af","Rate","Rate","Fr","Fr ","Rate","Freq","\333\361","Rate","Frequentie","Fr","RR","Fr","\226\073","Taajuus","Fr","F"};
const UBYTE *const huge cMSG_LeakReport[NB_LANGUAGE]	={"\277\263","Laekager","Leckagen","Leak","Leak","Fuga","Fuite","Leak","Leak","\277\304\235","Leak","Lekkage","Lekkasje","Przeciek","Fuga","\222\266\250\273\255\253","Vuoto","L\332ck","Ka\325ak"};
const UBYTE *const huge cMSG_PipReport[NB_LANGUAGE]	={"\263\355\011\210","IPAP","PIP","Paw","Paw","Pi media","Pi ","Paw","Press","Paw","Paw","IPAP","IPAP","PIP","Pi media","P \245\247\306\270\243 \264\263","IPAP","IPAP","PIP"};
const UBYTE *const huge cMSG_TapneaReport[NB_LANGUAGE]	={"\321\211\234\365","Apnea tid","Apnoezeit","Apnea Ti","Apnea Ti","T Apnea","Tapn\322e ","Apnea Ti","T Apnea","\346\370\322\332\331\364\014","Apnea Ti","Apneutijd","Apnea tid","Ta Apnea","T. Apneia","T \243\262\240\306\301","Apnea-aika","Apnea tid","Apnea T"};
const UBYTE *const huge cMSG_ContrReport[NB_LANGUAGE]	={"\225\136\354\263","Kontrol","% Kontrollierte Beatmung","Contr cyc","Contr cyc","Controlad","Contr","Contr cyc","% Atti Contr","Control","Contr cyc","Gecontrolleerde. Cycli","Kontroll ","KONTR","Controlad","% \216\263\253\240\267\247","Kontrolloidut syklit %","Kontroll ","Kontr"};
	
/*C Messages Menu Clé USB */	
const UBYTE *const huge cMSG_TitleUSB[NB_LANGUAGE]	={"USB MEMORY DEVICE","USB MEMORY DEVICE","USB MEMORY STICK","USB MEMORY DEVICE","USB MEMORY DEVICE","DISPOSITIVO USB","USB MEMORY DEVICE","USB MEMORY DEVICE","USB MEMORY DEVICE","USB MEMORY DEVICE","USB MEMORY DEVICE","USB MEMORY DEVICE","USB MINNEBRIKKE","ZARZ\022DZANIE PAMI\027CI\022 USB","DISPOSITIVO USB","USB \100\177\217\221\177 \216\177\213\242\221\207","USB MEMORY DEVICE","USB MEMORY DEVICE","USB  BÖLÜMÜ"};
const UBYTE *const huge cMSG_EraseKey[NB_LANGUAGE]	={"erase key","Slette noegle","USB l\313schen","Erase Key","Erase Key","Borrar Disp","Effacer cl\322 USB","\311\363\030\026\371\374\035 \301\373\366\371\365\371\377\036","Cancellazione Chiave","\262\330\234\304","Erase Key","USB stick wissen","Slettetast","Skasuj Pami\030\034 USB","Apagar Disp.","\100\240\306\262\255\243 \267\247\243\256\250\240\253\303","TYHJENN\074 MUISTITIKKU","Radera nyckel","Silme Tu\016u"};
const UBYTE *const huge cMSG_TransferOnUSB[NB_LANGUAGE]	={"transfer settings on","Optage indstilling til","Einstellungen Transfer ein","Transfer settings on","Transfer settings on","Transferencia ajustes","Transf\322rer R\322glages sur","\303\366\027\362\031\377\024\356 \307\030\370\374\361\026\366\034\375","Impostazioni Trasferimento","Transfer settings on","Transfer settings on","Overdracht instelling aan","Overf\312rt innstilling p\331","Transfer ustawie\037 do","Transferencia ajustes","\216\250\263\250\240\250\264\266\253 \247\243\240\240\277\250 \240\243","Siirtoasetukset p\332\332lle","Överf\313r inst\332llning p\331","Transfer Ayarlar\010 A\325\010k"};
const UBYTE *const huge cMSG_TransferToVentil[NB_LANGUAGE]	={"VENT","VENT","RESP","VENT","VENT","VENT","VENT","\273\276\307.","VENT","VENT","VENT","VENT","VENT","RESP","VENT","\207\201\135","VENT","VENT","VENT"};
const UBYTE *const huge cMSG_TransferToKey[NB_LANGUAGE]	={"KEY","USB","USB","KEY","KEY","DISP","CLE","\301\302\276\250","KEY","KEY","KEY","USB","USB","USB","DISP","\100\135\233\226","KEY","USB","USB "};
const UBYTE *const huge cMSG_ContRecordUSB[NB_LANGUAGE]	={"transfer continuously","Optage uafbrudt","Kontin. Transfer","Transfer Continuously","Transfer Continuously","Transfer Tiempo Real","Enregistrer en continu","\311\030\375. \303\366\027\362\031\377\024\356","Trasferimento Continuo","Transfer Continuously","Transfer Continuously","Continu overdracht","Overf\312r kontinuerlig","Ci\023g\033y transfer danych","Transfer. Tempo Real","\216\306\264\266\306\303\240\240\277\254 \262\250\263\250\240\306\264","Jatkuva siirto","Överf\313r kontinuerligt","S\304rekli Transfer"};
const UBYTE *const huge cMSG_TransferMonitUSB[NB_LANGUAGE]	={"transfer monitorings","Optage monitoreringer","Monitoring Transfer","Transfer Monitorings","Transfer Monitorings","Transfer Monitoriz","Transf\322rer Monitorages","\303\366\027. \306\362\024\362\372\377\373\377\036\370\367\026\367\025","Trasferimento Monit","Transfer Monitorings","Transfer Monitorings","Overdracht monitoring","Overf\312r overv\331kning","Transfer Monitoringu","Transf. Monitoriz.","\216\250\263\250\240\306\264 \247\243\240\240\277\270 \257\306\240\253\266\306\263\253\240\246\243","Siirretyt tallennukset","Överf\313r \313vervakning","Monit\313r Transferi"};
const UBYTE *const huge cMSG_TransferTrendUSB[NB_LANGUAGE]	={"transfer trends","Optage trends","Trends Transfer","Transfer Trends","Transfer Trends","Transfer Tendencias","Transf\322rer Tendances","\303\366\027. \254\024\362\364. \306\362\024\362\026.","Trasferimento Trend","Transfer Trends","Transfer Trends","Overdracht trends","Overf\312r trender","Transfer Trend\314w","Transfer Tendencias","\216\250\263\250\240\306\264 \266\263\250\240\247\306\245","Siirretyt trendit","Överf\313r trender","Trend Transferi"};
const UBYTE *const huge cMSG_TransferEventsUSB[NB_LANGUAGE]	={"transfer events ","Optage haendelser","Ereigniss Transfer","Transfer Events ","Transfer Events ","Transfer Eventos","Transf\322rer Ev\322nements","\303\366\027. \311\030\374\363\356\375\027\034\375","Eventi Trasferimento","Transfer Events ","Transfer Events ","Overdracht events","Overf\312r hendelser","Transfer Zdarze\037","Transfer Eventos","\216\250\263\250\240\306\264 \264\306\244\277\266\253\254","Siirretyt tapahtumat","Överf\313r h\332ndelser","Olay Transferi"};
	
/*C Messages d'alarme USB */	
const UBYTE *const huge cMSG_UsbErrDisconnect[NB_LANGUAGE]	={"transfer error|key disconnection","OPTAGE FEJL|NOEGLE FRAKOBLET","TRANSFER FEHLER|USB FEHLT","TRANSFER ERROR|USB DISCONNECTION","TRANSFER ERROR|KEY DISCONNECTION","ERROR DE TRANSF|DESCONEXION DISP","ERREUR DE TRANSFERT|DECONNEXION CLE","\311\314\273\302\303\273 \303\276\312\273\314\305\307\273\311|\273\306\305\311\313\304\275\276\311\277 \301\302\276\250\275\250\305\313","Errore Trasferimento|USB Disconnessa","Trancfer\231\276\304|USB DISCONNECTION","TRANSFER ERROR|KEY DISCONNECTION","OVERDRACHT FOUT|STICK DISCONNECTIE","OVERFØRINGSFEIL|USB-STICK FRAKOBLET","B\021\022D TRANSFERU|OD\021\022CZENIE PAMI\027CI USB","ERRO DE TRANSF.|DESCONEXAO DISP","\215\274\253\244\255\243 \262\250\263\250\240\306\264\243|\215\266\264\306\250\247 USB","SIIRROSSA VIRHE|USB IRTI","Överf\313rings fel|USB Nyckel urkopplad","TRANSFER HATASIUSB  BA\013LANTISIZLI\013I"};
const UBYTE *const huge cMSG_UsbErrFullKey[NB_LANGUAGE]	={"transfer error|key full","OPTAGE FEJL|NOEGLE FULD","TRANSFER FEHLER|USB VOLL","TRANSFER ERROR|USB FULL","TRANSFER ERROR|KEY FULL","ERROR DE TRANSF|DISPOS LLENO","ERREUR DE TRANSFERT|CLE PLEINE","\311\314\273\302\303\273 \303\276\312\273\314\305\307\273\311|\301\302\276\250\275\250 \306\302\277\307\276\311","Errore Trasferimento|Chiave Piena","Trancfer\231\276\304|USB FULL","TRANSFER ERROR|KEY FULL","OVERDRACHTFOUT|STICK VOL","OVERFØRINGSFEIL|USB-STICK FULL","B\021\022D TRANSFERU|PE\021NA PAMI\027\026 USB","ERRO DE TRANSF.|DISPOS. CHEIO","\215\274\253\244\255\243 \262\250\263\250\240\306\264\243|USB \262\250\263\250\262\306\256\240\250\240","SIIRROSSA VIRHE|USB T\074YSI","Överf\313rings fel|USB Nyckel full","TRANSFER HATASI|USB DOLU"};
const UBYTE *const huge cMSG_UsbErrTooManyKeys[NB_LANGUAGE]	={"transfer not allowed|remove a key","OPTAGNING IKKE TILLADT|FJERN NOEGLE","TRANSFER NICHT ERLAUBT|USB ENTFERNEN","TRANSFER NOT ALLOWED|REMOVE A KEY","TRANSFER NOT ALLOWED|REMOVE A KEY","TRANSF NO PERMITIDA|SACAR UN DISPOS","TRANSFERT IMPOSSIBLE|ENLEVER UNE CLE","\303\277 \276\343\305\313\311\250\305\275\305\312\277\303\276\304\277 \303\276\312\273\314\305\307\273|\273\306\305\303\273\301\307\313\304\311\277 \301\302\276\250\275\250\305\313","Trasferimento Non consentito|Problemi Tecnici","TRANSFER NOT ALLOWED|REMOVE A KEY","TRANSFER NOT ALLOWED|REMOVE A KEY","OVERDRACHT NIET MOGELIJK|VERWIJDER STICK","OVERFØRING IKKE|TILLATT FJERN USB-STICK","TRANSFER NIEDOZWOLONY|OD\021\022CZ PAMI\027\026 USB","TRANSF.NO PERMITIDA|TIRAR UM DISPOS.","\216\250\263\250\240\306\264 \240\250\245\306\252\257\306\251\250\240|\207\252\245\256\250\273\300 USB","SIIRTO EI MAHD|IRROITA USB","Överf\313ring ej till\331ten|ta bort USB nyckel","TRANSFERE \017Z\017N YOK|USB ÇIKARIN "};
const UBYTE *const huge cMSG_UsbErrTransfer[NB_LANGUAGE]	={"transfer error|technical problem","OPTAGE FEJL|TEKNISK PROBLEM","TRANSFERFEHLER|TECHNISCHES PROBLEM","TRANSFER ERROR|TECHNICAL PROBLEM","TRANSFER ERROR|TECHNICAL PROBLEM","ERROR DE TRANSF|FALLO TECNICO","ERREUR DE TRANSFERT|PROBLEME TECHNIQUE","\311\314\273\302\303\273 \303\276\312\273\314\305\307\273\311|\312\276\353\304\250\301\305 \306\307\305\274\302\277\303\273","Errore Trasferimento|Problema Tecnico","Trancfer\231\276\304|TECHNICAL PROBLEM","TRANSFER ERROR|TECHNICAL PROBLEM","OVERDRACHT FOUT|TECHNISCH PROBLEEM","OVERFØRINGSFEIL|TEKNISK PROBLEM","B\021\022D TRANSFERU|PROBLEM TECHNICZNY","ERRO DE TRANSF.|FALHA TECNICA","\215\274\253\244\255\243 \262\250\263\250\240\306\264\243|\221\250\270\240\253\273. \262\263\306\244\256\250\257\243","SIIRROSSA VIRHE|TEKNINEN ONGELMA","Överf\313rings fel|tekniska problem","TRANSFER HATASI|TEKN\017K PROBLEM"};
const UBYTE *const huge cMSG_UsbErrErase[NB_LANGUAGE]	={"erase error|technical problem","SLET FEJL|TEKNISK PROBLEM","LÖSCHFEHLER|TECHNISCHES PROBLEM","ERASE ERROR|TECHNICAL PROBLEM","ERASE ERROR|TECHNICAL PROBLEM","ERROR DE BORRADO|FALLO TECNICO","ERREUR D'EFFACEMENT|PROBLEME TECHNIQUE","\311\314\273\302\303\273 \275\250\273\254\307\273\314\277\311|\312\276\353\304\250\301\305 \306\307\305\274\302\277\303\273","Errore Cancellazione|Problema Tecnico","ERASE ERROR|TECHNICAL PROBLEM","ERASE ERROR|TECHNICAL PROBLEM","WIS FOUT|TECHNISCH PROBLEEM","PROBLEM Å|SLETTE TEKNISK FEIL","B\021\022D KASOWANIA|PROBLEM TECHNICZNY","ERRO DE APAGAR|FALHA TECNICA","\215\274\253\244\255\243 \267\247\243\256\250\240\253\303|\221\250\270\240\253\273. \262\263\306\244\256\250\257\243","POISTA VIRHE|TEKNINEN ONGELMA","Problem att radera|tekniska problem","S\017LME HATASI|TEKN\017K PROBLEM"};
const UBYTE *const huge cMSG_UsbErrFile[NB_LANGUAGE]	={"transfer not allowed|file not found or wrong","OPTAGNING IKKE TILLADT|FIL IKKE FUNDET EL. FORKERT","TRANSFER NICHT ERLAUBT|DATEI FEHLT ODER FALSCH","TRANSFER NOT ALLOWED|FILE NOT FOUND OR WRONG","TRANSFER NOT ALLOWED|FILE NOT FOUND OR WRONG","TRANSF NO PERMITIDA|ARCHIVO DAÑADO O AUSENTE","TRANSFERT IMPOSSIBLE|FICHIER INTROUVABLE OU ERRONE","\303\277 \276\343\305\313\311\250\305\275\305\312\277\303\276\304\277 \303\276\312\273\314\305\307\273|\273\306\305\313\311\250\273 \324 \311\314\273\302\303\273 \273\307\353\276\250\305\313","Trasferimento Non Consentito|File Non Trovato o Errato","TRANSFER NOT ALLOWED|FILE NOT FOUND OR WRONG","TRANSFER NOT ALLOWED|FILE NOT FOUND OR WRONG","OVERDRACHT NIET MOGELIJK|BESTAND NIET GEVONDEN OF FOUT","OVERFØRING IKKE|TILLATT  FINNER IKKE FILER","TRANSFER NIEDOZWOLONY|PLIK NIEODNALEZIONY LUB USZKODZONY","TRANSF.NAO PERMITIDA|ARQUIVO ESTRAGADO O AUSENTE","\216\250\263\250\240\306\264 \240\250\245\306\252\257\306\251\250\240|\223\243\254\256 \240\250 \240\243\254\247\250\240 \253\256\253 \240\250\245\250\263\250\240","SIIRTO EI MAHDOLLINEN|TIEDOSTOA EI LÖYDY TAI V\074\074R\074","Överf\313ring ej till\331ten|filerna hittas ej","TRANSFERE \017Z\017N YOK|DOSYA BULUNAMADI YANLI\011 DOSYA"};
const UBYTE *const huge cMSG_UsbErrPortability[NB_LANGUAGE]	={"transfer not allowed|incompatible settings ","OPTAGNING IKKE TILLADT|UKOMPATIBLE INDSTILLINGER","TRANSFER NICHT ERLAUBT|INKOMPATIBLE EINSTELLUNGEN","TRANSFER NOT ALLOWED|INCOMPATIBLE SETTINGS ","TRANSFER NOT ALLOWED|INCOMPATIBLE SETTINGS ","TRANSF NO PERMITIDA|AJUSTES INCOMPATIBLES","TRANSFERT IMPOSSIBLE|REGLAGES ET VENT INCOMPATIBLES","\303\277 \276\343\305\313\311\250\305\275\305\312\277\303\276\304\277 \303\276\312\273\314\305\307\273|\273\311\313\303\274\273\312\276\311 \307\313\335\303\250\311\276\250\311","Trasferimento Non Consentito|Impostazioni Non Compatibili","TRANSFER NOT ALLOWED|INCOMPATIBLE SETTINGS ","TRANSFER NOT ALLOWED|INCOMPATIBLE SETTINGS ","OVERDRACHT NIET MOGELIJK|ONVERENIGBARE INSTELLINGEN","OVERFØRING IKKE TILLATT|IKKE KOMPATIBLE INNSTILLINGER ","TRANSFER NIEDOZWOLONY|NIEKOMPATYBILNE USTAWIENIA","TRANSF.NAO PERMITIDA|AJUSTES INCOMPATIVEIS","\216\250\263\250\240\306\264 \240\250\245\306\252\257\306\251\250\240|\214\250\264\306\245\257\250\264\266\253\257\277\250 \240\243\264\266\263\306\254\255\253","SIIRTO EI MAHDOLLINEN|V\074\074R\074T ASETUKSET","Överf\313ring ej till\331ten|icke kompatibla inst\332llningar","TRANSFERE \017Z\017N YOK|UYUMSUZ AYARLAMA"};
const UBYTE *const huge cMSG_SettingsOverWrite[NB_LANGUAGE]	={"caution this function erases|the precedent settings","ADVARSEL FUNKTION SLETTER|FORUDGAAENDE INDSTILLINGS FILE","ACHTUNG DIESE FUNKTION LÖSCHT|VORHERIGE EINSTELLDATEI","CAUTION THIS FUNCTION ERASES|THE PREVIOUS SETTINGS","CAUTION THIS FUNCTION ERASES|THE PRECEDENT SETTINGS","PRECAUCION BORRADO|DE AJUSTES ANTERIORES","ATTENTION CETTE FONCTION|ECRASE LES REGLAGES PRECEDENTS ","\306\307\305\311\305\353\277  \275\250\273\254\307.|\273\307\353\276\250\305\313 \306\307\305\301\273\335. \307\313\335\303.","Questa Funzione Elimina|i File di Impostazione","CAUTION THIS FUNCTION ERASES|THE PREVIOUS SETTINGS","CAUTION THIS FUNCTION ERASES|THE PRECEDENT SETTINGS","PAS OP DEZE FUNCTIE WIST|VOORGAAND INSTELLINGENBESTAND","ADVARSEL DENNE FUNKSJONEN SLETTER|TIDLIGERE INNSTILLINGER","UWAGA TA FUNKCJA|KASUJE PLIK Z NASTAWAMI","PRECAUÇAO. APAGADO|DE AJUSTES ANTERIORES","\201\240\253\257\243\240\253\250 \301\266\243 \223\267\240\255\271\253\303 \264\266\253\263\243\250\266|\262\263\250\247\277\247\267\275\253\250 \240\243\264\266\263\306\254\255\253","VAROITUS T\074M\074 TOIMINTO POISTAA|ENNAKKOASETUSKANSION","Varning denna funktion raderar|tidigare inst\332llningar","UYARI BU FONKS\017YON|MEVCUT DOSYAYI S\017LER"};
const UBYTE *const huge cMSG_VentilCompatible[NB_LANGUAGE]	={"ventilators compatibles|of the settings are:","VENTILATOR KOMPATIBLE|AF INDSTILLINGER ER:","KOMPATIBLE RESPIRATOREN|DER EINSTELLUNGEN SIND:","VENTILATORS COMPATIBLE|OF THE SETTINGS ARE:","VENTILATORS COMPATIBLE|OF THE SETTINGS ARE:","VENTILADORES COMPATIBLES|CON LOS AJUSTES SON: ","VENTILATEURS COMPATIBLES|DES REGLAGES:","\311\313\303\274\273\312\305\312\277\312\273 \273\304\273\306\304\276\313\311\312\277\307\273|\273\306\305 \312\250\311 \307\313\335\303. \276\250\304\273\250:","Ventilatori Compatibili|le Impostazioni Sono:","VENTILATORS COMPATIBLE|OF THE SETTINGS ARE:","VENTILATORS COMPATIBLES|OF THE SETTINGS ARE:","VENTILATOREN VERENIGBAAR|MET INSTELLINGEN:","VENTILATOR KOMPATIBEL|MED INSTILLINGER ER:","RESPIRATORY KOMPATYBILNE|Z PLIKIEM NASTAW:","VENTILADORES COMPATIVEIS|COM OS AJUSTES SOM:","\220\306\245\257\250\264\266\253\257\306\264\266\300|\240\243\264\266\263\306\250\255 \243\262\262\243\263\243\266\243 \207\201\135:","ASETUKSIIN SOPIVAT VENTILAATTORIT:","Ventilatorer kompatibla|med inst\332lln \332r:","VENT\017L\017ATÖR UYUMLU|AYARLAMALAR :"};
const UBYTE *const huge cMSG_NotEnoughKeySpace[NB_LANGUAGE]	={"transfer not allowed| key capacity insufficient","OPTAGNING IKKE TILLADT| NOEGLE KAPACITET UDUELIG","TRANSFER NICHT ERLAUBT|USB UNZUREICHEND","TRANSFER NOT ALLOWED|USB CAPACITY INSUFFICIENT","TRANSFER NOT ALLOWED|USB CAPACITY INSUFFICIENT","TRANSF NO PERMITIDA|CAPACIDAD DISPOS INSUFICIENTE","TRANSFERT IMPOSSIBLE|CAPACITE CLE INSUFFISANTE","\303\277 \276\343\305\313\311\250\305\275\305\312\277\303\276\304\277 \303\276\312\273\314\305\307\273|\273\304\276\306\273\307\301\277\311 \353\355\307\277\312\250\301\305\312\277\312\273 \301\302\276\250\275\250\305\313","Trasferimento Non Consentito|Capacit\333 Memoria Insufficiente","TRANSFER NOT ALLOWED|USB CAPACITY INSUFFICIENT","TRANSFER NOT ALLOWED| KEY CAPACITY INSUFFICIENT","OVERDRACHT NIET MOGELIJK|STICK CAPACITEIT NIET VOLDOENDE","OVERFØRING IKKE TILLATT| UTILSTREKKELIG USB-MINNE","TRANSFER NIEDOZWOLONY|POJEMNO\024\026 PAMI\027CI ZA MA\021A","TRANSF.NAO PERMITIDA|CAPACIDADE DISPOS. INSUFICIENTE","\216\250\263\250\240\306\264 \240\250\245\306\252\257\306\251\250\240|\214\250\247\306\264\266\243\266\306\273\240\243\303 \250\257\255\306\264\266\300 USB","SIIRTO EI MAHDOLLINEN|USB KAPASITEETTI EI RIIT\074","Överf\313ring ej till\331ten|Otillr\332cklig USB kapacitiet","TRANSFERE \017Z\017N YOK|USB KAPAS\017TES\017 YETERS\017Z"};
const UBYTE *const huge cMSG_UsbErrTransfProcessing[NB_LANGUAGE]	={"transfer in progress...|remaining time :","OPTAGNING I PROCES...|Remaining Time :","TRANSFER L\074UFT...|Restzeit :","TRANSFER IN PROGRESS...|Remaining Time :","TRANSFER IN PROGRESS...|Remaining Time :","TRANSFERANCIA EN PROGRESO|Tiempo restante :","TRANSFERT EN COURS...|Temps restant :","\303\276\312\273\314\305\307\273 \311\276 \276\343\276\302\250\343\277...|\313\023\377\373\366\371\023\035\374\366\375\377\025 \353\024\035\375\377\025 :","Trasferimento in Corso...|Tempo Rimanente :","TRANSFER IN PROGRESS...|Remaining Time :","TRANSFER IN PROGRESS...|Remaining Time :","OVERDRACHT IN WERKING...|Resterende Tijd :","OVERFØRING PÅGÅR...|Gjenst\331ende tid :","TRANSFER DANYCH W TOKU...|POZOSTA\021Y CZAS:","TRANSFERANCIA EM PROGRESO|TEMPO QUE FALTA","\207\247\250\266 \262\250\263\250\240\306\264...|\215\264\266\243\256\306\264\300:","SIIRTO K\074YNNISS\074...|aikaa j\332ljell\332 :","Överf\313ring p\331g\331r...|Återst\331ende tid :","TRANSFER YAPILIYOR...|Remaining Time :"};
const UBYTE *const huge cMSG_UsbErrEraseProcessing[NB_LANGUAGE]	={"erase in progress...|remaining time :","SLET I PROCES...|Remaining Time :","LÖSCHEN L\074UFT...|Restzeit :","ERASE IN PROGRESS...|Remaining Time :","ERASE IN PROGRESS...|Remaining Time :","BORRADO EN PROGRESO|Tiempo restante :","EFFACEMENT EN COURS...|Temps restant :","\275\250\273\254\307\273\314\277 \311\276 \276\343\276\302\250\343\277...|\313\023\377\373\366\371\023\035\374\366\375\377\025 \353\024\035\375\377\025 :","Cancellazione in Corso...|Tempo Rimanente :","ERASE IN PROGRESS...|Remaining Time :","ERASE IN PROGRESS...|Remaining Time :","WISSEN IN WERKING...|Resterende Tijd :","SLETTING PÅGÅR...|Gjenst\331ende tid:","KASOWANIE DANYCH W TOKU...|POZOSTA\021Y CZAS:","APAGAR EM PROGRESSO|TEMPO QUE FALTA","\207\247\250\266 \306\273\253\264\266\255\243...|\215\264\266\243\256\306\264\300:","POISTO K\074YNNISS\074...|aikaa j\332ljell\332:","Radering p\331g\331r...|Återst\331ende tid :","S\017LME  YAPILIYOR...|Remaining Time :"};
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	

	
/*END_MESSAGES*/

