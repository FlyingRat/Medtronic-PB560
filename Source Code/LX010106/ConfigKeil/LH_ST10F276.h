/*--------------------------------------------------------------------------
ST10F276.H

Register Declarations for ST10F276 Processor
Copyright (c) 1992-2004 Keil Elektronik GmbH and Keil Software, Inc.
All rights reserved.

Note: CAN Control Registers are defined in the CAN.H and CAN167.H Include files
---------------------------------------------------------------------------*/
#ifndef __REGST10F276_H__
#define __REGST10F276_H__


/* A/D Converter */
sfr   ADCIC    = 0xFF98;
sfr   ADCON    = 0xFFA0;
sfr   ADDAT    = 0xFEA0;
sfr   ADDAT2   = 0xF0A0;

sfr   ADEIC    = 0xFF9A;
sbit  ADST     = ADCON^7;
sbit  ADBSY    = ADCON^8;
sbit  ADWR     = ADCON^9;
sbit  ADCIN    = ADCON^10;
sbit  ADCRQ    = ADCON^11;
sbit  ADCIE    = ADCIC^6;
sbit  ADCIR    = ADCIC^7;
sbit  ADEIE    = ADEIC^6;
sbit  ADEIR    = ADEIC^7;

/* Timer 0, Timer 1, Timer 7, Timer 8 */
sfr   CC0      = 0xFE80;
sfr   CC0IC    = 0xFF78;
sfr   CC1      = 0xFE82;
sfr   CC1IC    = 0xFF7A;
sfr   CC2      = 0xFE84;
sfr   CC2IC    = 0xFF7C;
sfr   CC3      = 0xFE86;
sfr   CC3IC    = 0xFF7E;
sfr   CC4      = 0xFE88;
sfr   CC4IC    = 0xFF80;
sfr   CC5      = 0xFE8A;
sfr   CC5IC    = 0xFF82;
sfr   CC6      = 0xFE8C;
sfr   CC6IC    = 0xFF84;
sfr   CC7      = 0xFE8E;
sfr   CC7IC    = 0xFF86;
sfr   CC8      = 0xFE90;
sfr   CC8IC    = 0xFF88;
sfr   CC9      = 0xFE92;
sfr   CC9IC    = 0xFF8A;
sfr   CC10     = 0xFE94;
sfr   CC10IC   = 0xFF8C;
sfr   CC11     = 0xFE96;
sfr   CC11IC   = 0xFF8E;
sfr   CC12     = 0xFE98;
sfr   CC12IC   = 0xFF90;
sfr   CC13     = 0xFE9A;
sfr   CC13IC   = 0xFF92;
sfr   CC14     = 0xFE9C;
sfr   CC14IC   = 0xFF94;
sfr   CC15     = 0xFE9E;
sfr   CC15IC   = 0xFF96;
sfr   CC16     = 0xFE60;
sfr   CC16IC   = 0xF160;
sfr   CC17     = 0xFE62;
sfr   CC17IC   = 0xF162;
sfr   CC18     = 0xFE64;
sfr   CC18IC   = 0xF164;
sfr   CC19     = 0xFE66;
sfr   CC19IC   = 0xF166;
sfr   CC20     = 0xFE68;
sfr   CC20IC   = 0xF168;
sfr   CC21     = 0xFE6A;
sfr   CC21IC   = 0xF16A;
sfr   CC22     = 0xFE6C;
sfr   CC22IC   = 0xF16C;
sfr   CC23     = 0xFE6E;
sfr   CC23IC   = 0xF16E;
sfr   CC24     = 0xFE70;
sfr   CC24IC   = 0xF170;
sfr   CC25     = 0xFE72;
sfr   CC25IC   = 0xF172;
sfr   CC26     = 0xFE74;
sfr   CC26IC   = 0xF174;
sfr   CC27     = 0xFE76;
sfr   CC27IC   = 0xF176;
sfr   CC28     = 0xFE78;
sfr   CC28IC   = 0xF178;
sfr   CC29     = 0xFE7A;
sfr   CC29IC   = 0xF184;
sfr   CC30     = 0xFE7C;
sfr   CC30IC   = 0xF18C;
sfr   CC31     = 0xFE7E;
sfr   CC31IC   = 0xF194;
sfr   CCM0     = 0xFF52;
sfr   CCM1     = 0xFF54;
sfr   CCM2     = 0xFF56;
sfr   CCM3     = 0xFF58;
sfr   CCM4     = 0xFF22;
sfr   CCM5     = 0xFF24;
sfr   CCM6     = 0xFF26;
sfr   CCM7     = 0xFF28;
sfr   T0       = 0xFE50;
sfr   T01CON   = 0xFF50;
sfr   T0IC     = 0xFF9C;
sfr   T0REL    = 0xFE54;
sfr   T1       = 0xFE52;
sfr   T1IC     = 0xFF9E;
sfr   T1REL    = 0xFE56;
sfr   T7       = 0xF050;
sfr   T78CON   = 0xFF20;
sfr   T7IC     = 0xF17A;
sfr   T7REL    = 0xF054;
sfr   T8       = 0xF052;
sfr   T8IC     = 0xF17C;
sfr   T8REL    = 0xF056;
sbit  CC0IR    = CC0IC^7;
sbit  CC0IE    = CC0IC^6;
sbit  CC1IR    = CC1IC^7;
sbit  CC1IE    = CC1IC^6;
sbit  CC2IR    = CC2IC^7;
sbit  CC2IE    = CC2IC^6;
sbit  CC3IR    = CC3IC^7;
sbit  CC3IE    = CC3IC^6;
sbit  CC4IR    = CC4IC^7;
sbit  CC4IE    = CC4IC^6;
sbit  CC5IR    = CC5IC^7;
sbit  CC5IE    = CC5IC^6;
sbit  CC6IR    = CC6IC^7;
sbit  CC6IE    = CC6IC^6;
sbit  CC7IR    = CC7IC^7;
sbit  CC7IE    = CC7IC^6;
sbit  CC8IR    = CC8IC^7;
sbit  CC8IE    = CC8IC^6;
sbit  CC9IR    = CC9IC^7;
sbit  CC9IE    = CC9IC^6;
sbit  CC10IR   = CC10IC^7;
sbit  CC10IE   = CC10IC^6;
sbit  CC11IR   = CC11IC^7;
sbit  CC11IE   = CC11IC^6;
sbit  CC12IR   = CC12IC^7;
sbit  CC12IE   = CC12IC^6;
sbit  CC13IR   = CC13IC^7;
sbit  CC13IE   = CC13IC^6;
sbit  CC14IR   = CC14IC^7;
sbit  CC14IE   = CC14IC^6;
sbit  CC15IR   = CC15IC^7;
sbit  CC15IE   = CC15IC^6;
sbit  CC16IR   = CC16IC^7;
sbit  CC16IE   = CC16IC^6;
sbit  CC17IR   = CC17IC^7;
sbit  CC17IE   = CC17IC^6;
sbit  CC18IR   = CC18IC^7;
sbit  CC18IE   = CC18IC^6;
sbit  CC19IR   = CC19IC^7;
sbit  CC19IE   = CC19IC^6;
sbit  CC20IR   = CC20IC^7;
sbit  CC20IE   = CC20IC^6;
sbit  CC21IR   = CC21IC^7;
sbit  CC21IE   = CC21IC^6;
sbit  CC22IR   = CC22IC^7;
sbit  CC22IE   = CC22IC^6;
sbit  CC23IR   = CC23IC^7;
sbit  CC23IE   = CC23IC^6;
sbit  CC24IR   = CC24IC^7;
sbit  CC24IE   = CC24IC^6;
sbit  CC25IR   = CC25IC^7;
sbit  CC25IE   = CC25IC^6;
sbit  CC26IR   = CC26IC^7;
sbit  CC26IE   = CC26IC^6;
sbit  CC27IR   = CC27IC^7;
sbit  CC27IE   = CC27IC^6;
sbit  CC28IR   = CC28IC^7;
sbit  CC28IE   = CC28IC^6;
sbit  CC29IR   = CC29IC^7;
sbit  CC29IE   = CC29IC^6;
sbit  CC30IR   = CC30IC^7;
sbit  CC30IE   = CC30IC^6;
sbit  CC31IR   = CC31IC^7;
sbit  CC31IE   = CC31IC^6;
sbit  ACC0     = CCM0^3;
sbit  ACC1     = CCM0^7;
sbit  ACC2     = CCM0^11;
sbit  ACC3     = CCM0^15;
sbit  ACC4     = CCM1^3;
sbit  ACC5     = CCM1^7;
sbit  ACC6     = CCM1^11;
sbit  ACC7     = CCM1^15;
sbit  ACC8     = CCM2^3;
sbit  ACC9     = CCM2^7;
sbit  ACC10    = CCM2^11;
sbit  ACC11    = CCM2^15;
sbit  ACC12    = CCM3^3;
sbit  ACC13    = CCM3^7;
sbit  ACC14    = CCM3^11;
sbit  ACC15    = CCM3^15;
sbit  ACC16    = CCM4^3;
sbit  ACC17    = CCM4^7;
sbit  ACC18    = CCM4^11;
sbit  ACC19    = CCM4^15;
sbit  ACC20    = CCM5^3;
sbit  ACC21    = CCM5^7;
sbit  ACC22    = CCM5^11;
sbit  ACC23    = CCM5^15;
sbit  ACC24    = CCM6^3;
sbit  ACC25    = CCM6^7;
sbit  ACC26    = CCM6^11;
sbit  ACC27    = CCM6^15;
sbit  ACC28    = CCM7^3;
sbit  ACC29    = CCM7^7;
sbit  ACC30    = CCM7^11;
sbit  ACC31    = CCM7^15;
sbit  T0IE     = T0IC^6;
sbit  T0IR     = T0IC^7;
sbit  T0M      = T01CON^3;
sbit  T0R      = T01CON^6;
sbit  T1IE     = T1IC^6;
sbit  T1IR     = T1IC^7;
sbit  T1M      = T01CON^11;
sbit  T1R      = T01CON^14;
sbit  T7IE     = T7IC^6;
sbit  T7IR     = T7IC^7;
sbit  T7M      = T78CON^3;
sbit  T7R      = T78CON^6;
sbit  T8IE     = T8IC^6;
sbit  T8IR     = T8IC^7;
sbit  T8M      = T78CON^11;
sbit  T8R      = T78CON^14;

/* CPU */
sfr   CP       = 0xFE10;
sfr   CSP      = 0xFE08;
sfr   DPP0     = 0xFE00;
sfr   DPP1     = 0xFE02;
sfr   DPP2     = 0xFE04;
sfr   DPP3     = 0xFE06;
sfr   MDC      = 0xFF0E;
sfr   MDH      = 0xFE0C;
sfr   MDL      = 0xFE0E;
sfr   ONES     = 0xFF1E;
sfr   PSW      = 0xFF10;
sfr   SP       = 0xFE12;
sfr   STKOV    = 0xFE14;
sfr   STKUN    = 0xFE16;
sfr   SYSCON   = 0xFF12;
sfr   TFR      = 0xFFAC;
sfr   ZEROS    = 0xFF1C;
sfr   XPERCON  = 0xF024;
sfr   BUSCON0  = 0xFF0C;
sfr   BUSCON1  = 0xFF14;
sfr   BUSCON2  = 0xFF16;
sfr   BUSCON3  = 0xFF18;
sfr   BUSCON4  = 0xFF1A;
sfr   ADDRSEL1 = 0xFE18;
sfr   ADDRSEL2 = 0xFE1A;
sfr   ADDRSEL3 = 0xFE1C;
sfr   ADDRSEL4 = 0xFE1E;

sbit  XPERSHARE = SYSCON^0;
sbit  VISIBLE   = SYSCON^1;
sbit  XPEN      = SYSCON^2;
sbit  BDRSTEN   = SYSCON^3;
sbit  OWDDIS    = SYSCON^4;
sbit  CSCFG     = SYSCON^6;
sbit  WRCFG     = SYSCON^7;
sbit  CLKEN     = SYSCON^8;
sbit  BYTDIS    = SYSCON^9;
sbit  ROMEN     = SYSCON^10;
sbit  SGTEN     = SYSCON^11;
sbit  ROMS1     = SYSCON^12;
sbit  N        = PSW^0;
sbit  C        = PSW^1;
sbit  V        = PSW^2;
sbit  Z        = PSW^3;
sbit  E        = PSW^4;
sbit  MULIP    = PSW^5;
sbit  USR0     = PSW^6;
sbit  HLDEN    = PSW^10;
sbit  IEN      = PSW^11;
sbit  MDRIU    = MDC^4;
sbit  RWDC0    = BUSCON0^4;
sbit  MTTC0    = BUSCON0^5;
sbit  ALECTL0  = BUSCON0^9;
sbit  BUSACT0  = BUSCON0^10;
sbit  RDYEN0   = BUSCON0^12;
sbit  RWDC1    = BUSCON1^4;
sbit  MTTC1    = BUSCON1^5;
sbit  ALECTL1  = BUSCON1^9;
sbit  BUSACT1  = BUSCON1^10;
sbit  RDYEN1   = BUSCON1^12;
sbit  CSREN1   = BUSCON1^14;
sbit  CSWEN1   = BUSCON1^15;
sbit  RWDC2    = BUSCON2^4;
sbit  MTTC2    = BUSCON2^5;
sbit  ALECTL2  = BUSCON2^9;
sbit  BUSACT2  = BUSCON2^10;
sbit  RDYEN2   = BUSCON2^12;
sbit  CSREN2   = BUSCON2^14;
sbit  CSWEN2   = BUSCON2^15;
sbit  RWDC3    = BUSCON3^4;
sbit  MTTC3    = BUSCON3^5;
sbit  ALECTL3  = BUSCON3^9;
sbit  BUSACT3  = BUSCON3^10;
sbit  RDYEN3   = BUSCON3^12;
sbit  CSREN3   = BUSCON3^14;
sbit  CSWEN3   = BUSCON3^15;
sbit  RWDC4    = BUSCON4^4;
sbit  MTTC4    = BUSCON4^5;
sbit  ALECTL4  = BUSCON4^9;
sbit  BUSACT4  = BUSCON4^10;
sbit  RDYEN4   = BUSCON4^12;
sbit  CSREN4   = BUSCON4^14;
sbit  CSWEN4   = BUSCON4^15;
sbit  ILLBUS   = TFR^0;
sbit  ILLINA   = TFR^1;
sbit  ILLOPA   = TFR^2;
sbit  PRTFLT   = TFR^3;
sbit  UNDOPC   = TFR^7;
sbit  STKUF    = TFR^13;
sbit  STKOF    = TFR^14;
sbit  NMI      = TFR^15;

sfr   EXICON   = 0xF1C0;
sfr   EXISEL   = 0xF1DA;


/* PEC */
sfr   PECC0    = 0xFEC0;
sfr   PECC1    = 0xFEC2;
sfr   PECC2    = 0xFEC4;
sfr   PECC3    = 0xFEC6;
sfr   PECC4    = 0xFEC8;
sfr   PECC5    = 0xFECA;
sfr   PECC6    = 0xFECC;
sfr   PECC7    = 0xFECE;

#define  SRCP0 (*((unsigned int volatile sdata *) 0xFCE0))
#define  DSTP0 (*((unsigned int volatile sdata *) 0xFCE2))
#define  SRCP1 (*((unsigned int volatile sdata *) 0xFCE4))
#define  DSTP1 (*((unsigned int volatile sdata *) 0xFCE6))
#define  SRCP2 (*((unsigned int volatile sdata *) 0xFCE8))
#define  DSTP2 (*((unsigned int volatile sdata *) 0xFCEA))
#define  SRCP3 (*((unsigned int volatile sdata *) 0xFCEC))
#define  DSTP3 (*((unsigned int volatile sdata *) 0xFCEE))
#define  SRCP4 (*((unsigned int volatile sdata *) 0xFCF0))
#define  DSTP4 (*((unsigned int volatile sdata *) 0xFCF2))
#define  SRCP5 (*((unsigned int volatile sdata *) 0xFCF4))
#define  DSTP5 (*((unsigned int volatile sdata *) 0xFCF6))
#define  SRCP6 (*((unsigned int volatile sdata *) 0xFCF8))
#define  DSTP6 (*((unsigned int volatile sdata *) 0xFCFA))
#define  SRCP7 (*((unsigned int volatile sdata *) 0xFCFC))
#define  DSTP7 (*((unsigned int volatile sdata *) 0xFCFE))

/* I/O Ports */
sfr   DP0L     = 0xF100;
sfr   DP0H     = 0xF102;
sfr   DP1L     = 0xF104;
sfr   DP1H     = 0xF106;
sfr   DP2      = 0xFFC2;
sfr   DP3      = 0xFFC6;
sfr   DP4      = 0xFFCA;
sfr   DP6      = 0xFFCE;
sfr   DP7      = 0xFFD2;
sfr   DP8      = 0xFFD6;

sfr   P0L      = 0xFF00;
sfr   P0H      = 0xFF02;
sfr   P1L      = 0xFF04;
sfr   P1H      = 0xFF06;
sfr   P2       = 0xFFC0;
sfr   P3       = 0xFFC4;
sfr   P4       = 0xFFC8;
sfr   P5       = 0xFFA2;
sfr   P6       = 0xFFCC;
sfr   P7       = 0xFFD0;
sfr   P8       = 0xFFD4;
sfr   P5DIDIS  = 0xFFA4;
sfr   ODP2     = 0xF1C2;
sfr   ODP3     = 0xF1C6;
sfr   ODP4     = 0xF1CA;
sfr   ODP6     = 0xF1CE;
sfr   ODP7     = 0xF1D2;
sfr   ODP8     = 0xF1D6;
sfr   RP0H     = 0xF108;
sfr   PICON    = 0xF1C4;


/* Serial Interface */
sfr   S0BG     = 0xFEB4;
sfr   S0CON    = 0xFFB0;
sfr   S0EIC    = 0xFF70;
sfr   S0RBUF   = 0xFEB2;
sfr   S0RIC    = 0xFF6E;
sfr   S0TBUF   = 0xFEB0;
sfr   S0TIC    = 0xFF6C;
sfr   S0TBIC   = 0xF19C;
sbit  S0STP    = S0CON^3;
sbit  S0REN    = S0CON^4;
sbit  S0PEN    = S0CON^5;
sbit  S0FEN    = S0CON^6;
sbit  S0OEN    = S0CON^7;
sbit  S0PE     = S0CON^8;
sbit  S0FE     = S0CON^9;
sbit  S0OE     = S0CON^10;
sbit  S0ODD    = S0CON^12;
sbit  S0BRS    = S0CON^13;
sbit  S0LB     = S0CON^14;
sbit  S0R      = S0CON^15;
sbit  S0TIE    = S0TIC^6;
sbit  S0TIR    = S0TIC^7;
sbit  S0TBIE   = S0TBIC^6;
sbit  S0TBIR   = S0TBIC^7;
sbit  S0RIE    = S0RIC^6;
sbit  S0RIR    = S0RIC^7;
sbit  S0EIE    = S0EIC^6;
sbit  S0EIR    = S0EIC^7;

sfr   SSCTIC   = 0xFF72;
sfr   SSCRIC   = 0xFF74;
sfr   SSCEIC   = 0xFF76;
sfr   SSCTB    = 0xF0B0;
sfr   SSCRB    = 0xF0B2;
sfr   SSCBR    = 0xF0B4;
sfr   SSCCON   = 0xFFB2;
sbit  SSCHB    = SSCCON^4;
sbit  SSCPH    = SSCCON^5;
sbit  SSCPO    = SSCCON^6;
sbit  SSCTE    = SSCCON^8;
sbit  SSCTEN   = SSCCON^8;
sbit  SSCRE    = SSCCON^9;
sbit  SSCREN   = SSCCON^9;
sbit  SSCPE    = SSCCON^10;
sbit  SSCPEN   = SSCCON^10;
sbit  SSCBE    = SSCCON^11;
sbit  SSCBEN   = SSCCON^11;
sbit  SSCBSY   = SSCCON^12;
sbit  SSCMS    = SSCCON^14;
sbit  SSCEN    = SSCCON^15;
sbit  SSCTIR   = SSCTIC^7;
sbit  SSCTIE   = SSCTIC^6;
sbit  SSCRIR   = SSCRIC^7;
sbit  SSCRIE   = SSCRIC^6;
sbit  SSCEIR   = SSCEIC^7;
sbit  SSCEIE   = SSCEIC^6;

/* GPT1, GPT2 */
sfr   CAPREL   = 0xFE4A;
sfr   CRIC     = 0xFF6A;
sfr   T2       = 0xFE40;
sfr   T2CON    = 0xFF40;
sfr   T2IC     = 0xFF60;
sfr   T3       = 0xFE42;
sfr   T3CON    = 0xFF42;
sfr   T3IC     = 0xFF62;
sfr   T4       = 0xFE44;
sfr   T4CON    = 0xFF44;
sfr   T4IC     = 0xFF64;
sfr   T5       = 0xFE46;
sfr   T5CON    = 0xFF46;
sfr   T5IC     = 0xFF66;
sfr   T6       = 0xFE48;
sfr   T6CON    = 0xFF48;
sfr   T6IC     = 0xFF68;
sfr   WDT      = 0xFEAE;
sfr   WDTCON   = 0xFFAE;
sbit  CRIE     = CRIC^6;
sbit  CRIR     = CRIC^7;
sbit  T2R      = T2CON^6;
sbit  T2UD     = T2CON^7;
sbit  T2UDE    = T2CON^8;
sbit  T2IE     = T2IC^6;
sbit  T2IR     = T2IC^7;
sbit  T3R      = T3CON^6;
sbit  T3UD     = T3CON^7;
sbit  T3UDE    = T3CON^8;
sbit  T3OE     = T3CON^9;
sbit  T3OTL    = T3CON^10;
sbit  T3IE     = T3IC^6;
sbit  T3IR     = T3IC^7;
sbit  T4R      = T4CON^6;
sbit  T4UD     = T4CON^7;
sbit  T4UDE    = T4CON^8;
sbit  T4IE     = T4IC^6;
sbit  T4IR     = T4IC^7;
sbit  T5R      = T5CON^6;
sbit  T5UD     = T5CON^7;
sbit  T5UDE    = T5CON^8;
sbit  T5CLR    = T5CON^14;
sbit  T5SC     = T5CON^15;
sbit  T5IE     = T5IC^6;
sbit  T5IR     = T5IC^7;
sbit  T6R      = T6CON^6;
sbit  T6UD     = T6CON^7;
sbit  T6UDE    = T6CON^8;
sbit  T6OE     = T6CON^9;
sbit  T6OTL    = T6CON^10;
sbit  T6SR     = T6CON^15;
sbit  T6IE     = T6IC^6;
sbit  T6IR     = T6IC^7;
sbit  T0IN     = P3^0;
sbit  T2IN     = P3^7;
sbit  T3IN     = P3^6;
sbit  T4IN     = P3^5;
sbit  T5IN     = P5^13;
sbit  T6IN     = P5^12;
sbit  T2EUD    = P5^15;
sbit  T3EUD    = P3^4;
sbit  T4EUD    = P5^14;
sbit  T5EUD    = P5^11;
sbit  T6EUD    = P5^10;
sbit  T3OUT    = P3^3;
sbit  CAPIN    = P3^2;
sbit  T6OUT    = P3^1;
sbit	WDTIN    = WDTCON^0;
sbit	WDTR     = WDTCON^1;
sbit	SWR      = WDTCON^2;
sbit	SHWR     = WDTCON^3;
sbit	LHWR     = WDTCON^4;
sbit	PONR     = WDTCON^5;
sbit	WDTPRE   = WDTCON^7;

/* PWM Module */
sfr   PWMCON0  = 0xFF30;
sfr   PWMCON1  = 0xFF32;
sfr   PW0      = 0xFE30;
sfr   PW1      = 0xFE32;
sfr   PW2      = 0xFE34;
sfr   PW3      = 0xFE36;
sfr   PWMIC    = 0xF17E;
sfr   PT0      = 0xF030;
sfr   PT1      = 0xF032;
sfr   PT2      = 0xF034;
sfr   PT3      = 0xF036;
sfr   PP0      = 0xF038;
sfr   PP1      = 0xF03A;
sfr   PP2      = 0xF03C;
sfr   PP3      = 0xF03E;
sbit  PTR0     = PWMCON0^0;
sbit  PTR1     = PWMCON0^1;
sbit  PTR2     = PWMCON0^2;
sbit  PTR3     = PWMCON0^3;
sbit  PTI0     = PWMCON0^4;
sbit  PTI1     = PWMCON0^5;
sbit  PTI2     = PWMCON0^6;
sbit  PTI3     = PWMCON0^7;
sbit  PIE0     = PWMCON0^8;
sbit  PIE1     = PWMCON0^9;
sbit  PIE2     = PWMCON0^10;
sbit  PIE3     = PWMCON0^11;
sbit  PIR0     = PWMCON0^12;
sbit  PIR1     = PWMCON0^13;
sbit  PIR2     = PWMCON0^14;
sbit  PIR3     = PWMCON0^15;
sbit  PEN0     = PWMCON1^0;
sbit  PEN1     = PWMCON1^1;
sbit  PEN2     = PWMCON1^2;
sbit  PEN3     = PWMCON1^3;
sbit  PM0      = PWMCON1^4;
sbit  PM1      = PWMCON1^5;
sbit  PM2      = PWMCON1^6;
sbit  PM3      = PWMCON1^7;
sbit  PB01     = PWMCON1^12;
sbit  PS2      = PWMCON1^14;
sbit  PS3      = PWMCON1^15;
sbit  PWMIR    = PWMIC^7;
sbit  PWMIE    = PWMIC^6;

/* Identification */
sfr   IDCHIP   = 0xF07C;
sfr   IDMANUF  = 0xF07E;
sfr   IDMEM    = 0xF07A;
sfr   IDPROG   = 0xF078;

/*  MAC Unit  */
sfr   IDX0	   = 0xFF08;
sfr   IDX1     = 0xFF0A;
sfr   MAH      = 0xFE5E;
sfr   MAL	     = 0xFE5C;
sfr   MCW      = 0xFFDC;
sfr   MRW      = 0xFFDA;
sfr   MSW      = 0xFFDE;
sfr   QR0      = 0xF004;
sfr   QR1      = 0xF006;
sfr   QX0      = 0xF000;
sfr   QX1      = 0xF002;

sbit  MS   = MCW^9;
sbit  MP   = MCW^10;
sbit  CW   = MCW^11;
sbit  VM   = MCW^12;
sbit  EM   = MCW^13;
sbit  LM   = MCW^14;
sbit  MIE  = MCW^15;
     
sbit  MIR  = MSW^15;
sbit  MSL  = MSW^13;
sbit  ME   = MSW^12;
sbit  MSV  = MSW^11;
sbit  MC   = MSW^10;
sbit  MZ   = MSW^9;
sbit  MN   = MSW^8;



/* X-Peripherals */
sfr   XP0IC    = 0xF186;
sfr   XP1IC    = 0xF18E;
sfr   XP2IC    = 0xF196;
sfr   XP3IC    = 0xF19E;
sbit  XP0IR    = XP0IC^7;
sbit  XP0IE    = XP0IC^6;
sbit  XP1IR    = XP1IC^7;
sbit  XP1IE    = XP1IC^6;
sbit  XP2IR    = XP2IC^7;
sbit  XP2IE    = XP2IC^6;
sbit  XP3IR    = XP3IC^7;
sbit  XP3IE    = XP3IC^6;


/* Emulator Control Register */
sfr     EMUCON   = 0xFE0A;


/* XBUS Peripherals */

/* I2C Bus */

#define CR   (*((unsigned int volatile sdata *) 0xEA00))  // I2C Control Register
#define SR1  (*((unsigned int volatile sdata *) 0xEA02))  // I2C Status Register 1
#define SR2  (*((unsigned int volatile sdata *) 0xEA04))  // I2C Status Register 2
#define CCR1 (*((unsigned int volatile sdata *) 0xEA06))  // I2C Clock Control Register 1
#define OAR1 (*((unsigned int volatile sdata *) 0xEA08))  // IC2 Own Address Register 1
#define OAR2 (*((unsigned int volatile sdata *) 0xEA0A))  // I2C Own Address Register 2
#define DR   (*((unsigned int volatile sdata *) 0xEA0C))  // I2C Data Register
#define CCR2 (*((unsigned int volatile sdata *) 0xEA0E))  // I2C Clock Control Register 2


/* RTC */
#define RTCCON (*((unsigned int volatile sdata *) 0xED00))  // RTC Control Register
#define RTCPL  (*((unsigned int volatile sdata *) 0xED06))  // RTC Prescaler Register Low Byte
#define RTCPH  (*((unsigned int volatile sdata *) 0xED08))  // RTC Prescaler Register High Byte
#define RTCDH  (*((unsigned int volatile sdata *) 0xED0C))  // RTC Divider Counter High Byte
#define RTCDL  (*((unsigned int volatile sdata *) 0xED0A))  // RTC Divider Counter Low Byte
#define RTCL   (*((unsigned int volatile sdata *) 0xED0E))  // RTC Programmable Counter Low Byte
#define RTCH   (*((unsigned int volatile sdata *) 0xED10))  // RTC Programmable Counter High Byte
#define RTCAL  (*((unsigned int volatile sdata *) 0xED12))  // RTC Alarm Register Low Byte
#define RTCAH  (*((unsigned int volatile sdata *) 0xED14))  // RTC Alarm Register High Byte


/* CLK Output */
#define XCLKOUTDIV (*((unsigned int volatile sdata *) 0xEB02))  // CLKOUT Divider Control Register

/* X-Interrupt */
#define XIR0SEL (*((unsigned int volatile sdata *) 0xEB10))  // X-Interrupt 0 Selection Register (read only)
#define XIR0SET (*((unsigned int volatile sdata *) 0xEB12))  // X-Interrupt 0 Set Register (write only)
#define XIF0CLR (*((unsigned int volatile sdata *) 0xEB14))  // X-Interrupt 0 Clear Register (write only)
#define XIR1SEL (*((unsigned int volatile sdata *) 0xEB20))  // X-Interrupt 1 Selection Register (read only)
#define XIR1SET (*((unsigned int volatile sdata *) 0xEB22))  // X-Interrupt 1 Set Register (write only)
#define XIR1CLR (*((unsigned int volatile sdata *) 0xEB24))  // X-Interrupt 1 Clear Register (write only)
#define XIR2SEL (*((unsigned int volatile sdata *) 0xEB30))  // X-Interrupt 2 Selection Register (read only)
#define XIR2SET (*((unsigned int volatile sdata *) 0xEB32))  // X-Interrupt 2 Set Register (write only)
#define XIR2CLR (*((unsigned int volatile sdata *) 0xEB34))  // X-Interrupt 2 Clear Register (write only)
#define XIR3SEL (*((unsigned int volatile sdata *) 0xEB40))  // X-Interrupt 3 Selection Register (read only)
#define XIR3SET (*((unsigned int volatile sdata *) 0xEB42))  // X-Interrupt 3 Set Register (write only)
#define XIR3CLR (*((unsigned int volatile sdata *) 0xEB44))  // X-Interrupt 3 Clear Register (write only)

/* XBUS */
#define XP1DIDIS    (*((unsigned int volatile sdata *) 0xEB36))  // Port 1 Digital Disable Register
#define XMISC       (*((unsigned int volatile sdata *) 0xEB46))  // XBUS Miscellaneous Features Register

/* XPWM */
#define XPWMCON0    (*((unsigned int volatile sdata *) 0xEC00))  // XPWM Module Control Register 0
#define XPWMCON1    (*((unsigned int volatile sdata *) 0xEC02))  // XPWM Module Control Register 1
#define XPOLAR      (*((unsigned int volatile sdata *) 0xEC04))  // XPWM Module Channel Polarity Register
#define XPMWCON0SET (*((unsigned int volatile sdata *) 0xEC06))  // XPWM Module Set Control Register 0 (write only)
#define XPMWCON0CLR (*((unsigned int volatile sdata *) 0xEC08))  // XPWM Module Clear Control Register 0 (write only)
#define XPMWCON1SET (*((unsigned int volatile sdata *) 0xEC0A))  // XPWM Module Set Control Register 1 (write only)
#define XPMWCON1CLR (*((unsigned int volatile sdata *) 0xEC0C))  // XPWM Module Clear Control Register 1 (write only)
#define XPT0        (*((unsigned int volatile sdata *) 0xEC10))  // XPWM Module Up/Down Register 0
#define XPT1        (*((unsigned int volatile sdata *) 0xEC12))  // XPWM Module Up/Down Register 1
#define XPT2        (*((unsigned int volatile sdata *) 0xEC14))  // XPWM Module Up/Down Register 2
#define XPT3        (*((unsigned int volatile sdata *) 0xEC16))  // XPWM Module Up/Down Register 3
#define XPP0        (*((unsigned int volatile sdata *) 0xEC20))  // XPWM Module Period Register 0
#define XPP1        (*((unsigned int volatile sdata *) 0xEC22))  // XPWM Module Period Register 1
#define XPP2        (*((unsigned int volatile sdata *) 0xEC24))  // XPWM Module Period Register 2
#define XPP3        (*((unsigned int volatile sdata *) 0xEC26))  // XPWM Module Period Register 3
#define XPW0        (*((unsigned int volatile sdata *) 0xEC30))  // XPWM Module Pulse Width Register 0
#define XPW1        (*((unsigned int volatile sdata *) 0xEC32))  // XPWM Module Pulse Width Register 1
#define XPW2        (*((unsigned int volatile sdata *) 0xEC34))  // XPWM Module Pulse Width Register 2
#define XPW3        (*((unsigned int volatile sdata *) 0xEC36))  // XPWM Module Pulse Width Register 3
#define XPWMPORT    (*((unsigned int volatile sdata *) 0xEC80))  // XPWM Module Port Control Register


/* XAS */
#define XSSCCON    (*((unsigned int volatile sdata *) 0xE800))  // XSSC Control Register
#define XSSCCONSET  (*((unsigned int volatile sdata *) 0xE802))  // XSSC Control Register
#define XSSCCONCLR (*((unsigned int volatile sdata *) 0xE804))  // XSSC Control Register

#define XSSCBR     (*((unsigned int volatile sdata *) 0xE80A))  // XSSC Baud Rate Register
#define XSSCRB     (*((unsigned int volatile sdata *) 0xE808))  // XSSC Receive Buffer Register
#define XSSCTB     (*((unsigned int volatile sdata *) 0xE806))  // XSSC Receive Buffer Register
#define XSSCPORT     (*((unsigned int volatile sdata *) 0xE880)) // XSSC port control Register

#define XS1CON    (*((unsigned int volatile sdata *) 0xE900))  // XASC Control Register
#define XS1CONSET (*((unsigned int volatile sdata *) 0xE902))  // XASC Set Control Register (write only)
#define XS1CONCLR (*((unsigned int volatile sdata *) 0xE904))  // XASC Clear Control Register (wirte only)
#define XS1BG     (*((unsigned int volatile sdata *) 0xE906))  // XASC Baud Rate Generator Reload Register
#define XS1TBUF   (*((unsigned int volatile sdata *) 0xE908))  // XASC Transmit Buffer Register (write only)
#define XS1RBUF   (*((unsigned int volatile sdata *) 0xE90A))  // XASC Receive Buffer Registe
#define XS1PORT   (*((unsigned int volatile sdata *) 0xE980))  // XASC Port Control Register
#define XPEREMU 	(*((unsigned int volatile sdata *) 0xEB7E))	// Registre copie XPERCON

#endif
