bool bedwahr, bedaktion=false;

void Uhrlogik(int h,int s, int v) {

/*   Info über verfügbare Zeitinfos
  int	tm_sec;
  int	tm_min;
  int	tm_hour;
  int	tm_mday;
  int	tm_mon;
  int	tm_year;
  int	tm_wday;
  int	tm_yday;
  int	tm_isdst;
#ifdef __TM_GMTOFF
  long	__TM_GMTOFF;
#endif
#ifdef __TM_ZONE
  const char *__TM_ZONE;
*/

int min_mod=tm.tm_min % 5;
int min_first=tm.tm_min/10;
int min_last=tm.tm_min-min_first*10;
int stunde=tm.tm_hour;
int tmp;

 for(int i = 0; i < kMatrixWidth; i++) {
    for(int j = 0; j < kMatrixHeight; j++) {

            leds[XY(i,j)] = CHSV(30,0,0);
    }
  }


if ((millis()-variantenticker) > 30000) {
    tmp=millis() % 6;
    if (tmp < 3) variante=0; else variante=1;
    if ((tmp >=2) && (tmp<=4)) enable_es_ist=0; else enable_es_ist=1;
    if ((tmp ==1) || (tmp ==3) || (tmp ==5)) enable_gimmik=0; else enable_gimmik=1;
    variantenticker=millis();
   }


if (enable_es_ist==1) {Set_Text(w_es,h,s,v); Set_Text(w_ist,h,s,v);}



if (variante==0) {
switch(tm.tm_min) {

case 0: Set_Text(w_uhr,h,s,v); break;
case 1: Set_Text(w_einemin,h,s,v); Set_Text(w_minute,h,s,v); Set_Text(w_nach,h,s,v); break;
case 2: Set_Text(w_zweimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 3: Set_Text(w_dreimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 4: Set_Text(w_viermin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 5: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 6: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 7: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 8: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 9: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 10: Set_Text(w_zehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 11: Set_Text(w_elfm,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 12: Set_Text(w_zwoelfmin,h,s,v); Set_Text(w_nach,h,s,v); break;
case 13: Set_Text(w_dreizehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); break;
case 14: Set_Text(w_vierzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 15: Set_Text(w_viertelm,h,s,v); Set_Text(w_nach,h,s,v); break;
case 16: Set_Text(w_sechzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 17: Set_Text(w_siebzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 18: Set_Text(w_achtzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 19: Set_Text(w_neunzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 20: Set_Text(w_zehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 21: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 22: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 23: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 24: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 25: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 26: Set_Text(w_viermin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 27: Set_Text(w_dreimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 28: Set_Text(w_zweimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 29: Set_Text(w_einemin,h,s,v); Set_Text(w_minute,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 30: Set_Text(w_halb,h,s,v); stunde++; break;
case 31: Set_Text(w_einemin,h,s,v); Set_Text(w_minute,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 32: Set_Text(w_zweimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 33: Set_Text(w_dreimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 34: Set_Text(w_viermin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 35: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 36: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 37: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 38: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 39: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 40: Set_Text(w_zehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 41: Set_Text(w_elfm,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 42: Set_Text(w_zwoelfmin,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 43: Set_Text(w_dreizehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 44: Set_Text(w_vierzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 45: if (variante==0) {Set_Text(w_viertelm,h,s,v); Set_Text(w_vor,h,s,v); stunde++;}
         else {Set_Text(w_dreiviertel,h,s,v); stunde++;} break;
case 46: Set_Text(w_vierzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 47: Set_Text(w_dreizehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 48: Set_Text(w_zwoelfmin,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 49: Set_Text(w_elfm,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 50: Set_Text(w_zehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 51: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 52: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 53: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 54: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 55: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 56: Set_Text(w_viermin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 57: Set_Text(w_dreimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 58: Set_Text(w_zweimin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 59: Set_Text(w_einemin,h,s,v); Set_Text(w_minute,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;

}
} else {

switch(tm.tm_min) {

case 0: Set_Text(w_uhr,h,s,v); break;
case 1: 
case 2:
case 3:
case 4: Set_Text(w_kurz,h,s,v); Set_Text(w_nach,h,s,v); break;
case 5: Set_Text(w_fuenfmin,h,s,v);  Set_Text(w_nach,h,s,v); break;
case 6: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 7: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 8: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 9: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 10: Set_Text(w_zehnmin,h,s,v); Set_Text(w_nach,h,s,v); break;
case 11: Set_Text(w_elfm,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 12: Set_Text(w_zwoelfmin,h,s,v); Set_Text(w_nach,h,s,v); break;
case 13: Set_Text(w_dreizehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); break;
case 14: Set_Text(w_vierzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 15: Set_Text(w_viertelm,h,s,v); Set_Text(w_nach,h,s,v); break;
case 16: Set_Text(w_sechzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 17: Set_Text(w_siebzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 18: Set_Text(w_achtzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 19: Set_Text(w_neunzehnmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); break;
case 20: Set_Text(w_zehnmin,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 21: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 22: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 23: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 24: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 25: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 26: 
case 27: 
case 28: 
case 29: Set_Text(w_kurz,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 30: Set_Text(w_halb,h,s,v); stunde++; break;
case 31: 
case 32: 
case 33: 
case 34: Set_Text(w_kurz,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 35: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 36: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 37: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 38: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 39: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 40: Set_Text(w_zehnmin,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_halb,h,s,v); stunde++; break;
case 41: 
case 42: 
case 43: 
case 44: Set_Text(w_kurz,h,s,v); Set_Text(w_vor,h,s,v); Set_Text(w_dreiviertel,h,s,v); stunde++; break;
case 45: if (variante==0) {Set_Text(w_viertelm,h,s,v); Set_Text(w_vor,h,s,v); stunde++;}
         else {Set_Text(w_dreiviertel,h,s,v); stunde++;} break;
case 46: 
case 47:
case 48:
case 49: Set_Text(w_kurz,h,s,v); Set_Text(w_nach,h,s,v); Set_Text(w_dreiviertel,h,s,v); stunde++; break;
case 50: Set_Text(w_zehnmin,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 51: Set_Text(w_neunmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 52: Set_Text(w_achtmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 53: Set_Text(w_siebenmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 54: Set_Text(w_sechsmin,h,s,v); Set_Text(w_minuten,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 55: Set_Text(w_fuenfmin,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;
case 56: 
case 57:
case 58:
case 59: Set_Text(w_kurz,h,s,v); Set_Text(w_vor,h,s,v); stunde++; break;

}
}

if (stunde>12) stunde=stunde-12;

switch(stunde) {

case 0: Set_Text(w_zwoelf,h,s,v); break;
case 1: if (tm.tm_min==0) Set_Text(w_ein,h,s,v); else Set_Text(w_eins,h,s,v); break;
case 2: Set_Text(w_zwei,h,s,v); break;
case 3: Set_Text(w_drei,h,s,v); break;
case 4: Set_Text(w_vier,h,s,v); break;
case 5: Set_Text(w_fuenf,h,s,v); break;
case 6: Set_Text(w_sechs,h,s,v); break;
case 7: Set_Text(w_sieben,h,s,v); break;
case 8: Set_Text(w_acht,h,s,v); break;
case 9: Set_Text(w_neun,h,s,v); break;
case 10: Set_Text(w_zehn,h,s,v); break;
case 11: Set_Text(w_elf,h,s,v); break;
case 12: Set_Text(w_zwoelf,h,s,v); break;

}
    FastLED.show();
    last_millis=millis();
}


void Anzeigelogik(int h,int s, int v) {

  if (enablehallo==1 && digitalRead(praesenz)!=0) {
       if (bedwahr==false) {bedwahr=true; bedaktion=true;}
      } 
  else bedwahr=false;


   if (bedaktion) {Set_Text(w_hallo,30,150,v/2); Set_Text(w_brigitte,30,150,v/2); if (variante==0) Set_Text(w_liebe,30,150,v/2);
       bedaktion=false;
       FastLED.show();
      }
  
}