bool bedwahr, bedaktion=false;

void Uhrlogik() {

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


if (enable_es_ist==1) {Set_Text(w_es); Set_Text(w_ist);}



if (variante==0) {
switch(tm.tm_min) {

case 0: Set_Text(w_uhr); break;
case 1: Set_Text(w_einemin); Set_Text(w_minute); Set_Text(w_nach); break;
case 2: Set_Text(w_zweimin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 3: Set_Text(w_dreimin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 4: Set_Text(w_viermin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 5: Set_Text(w_fuenfmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 6: Set_Text(w_sechsmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 7: Set_Text(w_siebenmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 8: Set_Text(w_achtmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 9: Set_Text(w_neunmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 10: Set_Text(w_zehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 11: Set_Text(w_elfm); Set_Text(w_minuten); Set_Text(w_nach); break;
case 12: Set_Text(w_zwoelfmin); Set_Text(w_nach); break;
case 13: Set_Text(w_dreizehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 14: Set_Text(w_vierzehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 15: Set_Text(w_viertelm); Set_Text(w_nach); break;
case 16: Set_Text(w_sechzehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 17: Set_Text(w_siebzehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 18: Set_Text(w_achtzehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 19: Set_Text(w_neunzehnmin); Set_Text(w_minuten); Set_Text(w_nach); break;
case 20: Set_Text(w_zehnmin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 21: Set_Text(w_neunmin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 22: Set_Text(w_achtmin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 23: Set_Text(w_siebenmin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 24: Set_Text(w_sechsmin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 25: Set_Text(w_fuenfmin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 26: Set_Text(w_viermin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 27: Set_Text(w_dreimin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 28: Set_Text(w_zweimin); Set_Text(w_minuten); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 29: Set_Text(w_einemin); Set_Text(w_minute); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 30: Set_Text(w_halb); stunde++; break;
case 31: Set_Text(w_einemin); Set_Text(w_minute); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 32: Set_Text(w_zweimin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 33: Set_Text(w_dreimin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 34: Set_Text(w_viermin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 35: Set_Text(w_fuenfmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 36: Set_Text(w_sechsmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 37: Set_Text(w_siebenmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 38: Set_Text(w_achtmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 39: Set_Text(w_neunmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 40: Set_Text(w_zehnmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 41: Set_Text(w_elfm); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 42: Set_Text(w_zwoelfmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 43: Set_Text(w_dreizehnmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 44: Set_Text(w_vierzehnmin); Set_Text(w_minuten); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 45: if (variante==0) {Set_Text(w_viertelm); Set_Text(w_vor); stunde++;}
         else {Set_Text(w_dreiviertel); stunde++;} break;
case 46: Set_Text(w_vierzehnmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 47: Set_Text(w_dreizehnmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 48: Set_Text(w_zwoelfmin); Set_Text(w_vor); stunde++; break;
case 49: Set_Text(w_elfm); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 50: Set_Text(w_zehnmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 51: Set_Text(w_neunmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 52: Set_Text(w_achtmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 53: Set_Text(w_siebenmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 54: Set_Text(w_sechsmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 55: Set_Text(w_fuenfmin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 56: Set_Text(w_viermin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 57: Set_Text(w_dreimin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 58: Set_Text(w_zweimin); Set_Text(w_minuten); Set_Text(w_vor); stunde++; break;
case 59: Set_Text(w_einemin); Set_Text(w_minute); Set_Text(w_vor); stunde++; break;

}
} else {

switch(tm.tm_min) {

case 0: Set_Text(w_uhr); break;
case 1: 
case 2:
case 3:
case 4: Set_Text(w_kurz); Set_Text(w_nach); break;
case 5: Set_Text(w_fuenfmin);  Set_Text(w_nach); break;
case 6: Set_Text(w_sechsmin); Set_Text(w_nach); break;
case 7: Set_Text(w_siebenmin); Set_Text(w_nach); break;
case 8: Set_Text(w_achtmin); Set_Text(w_nach); break;
case 9: Set_Text(w_neunmin); Set_Text(w_nach); break;
case 10: Set_Text(w_zehnmin); Set_Text(w_nach); break;
case 11: Set_Text(w_elfm); Set_Text(w_nach); break;
case 12: Set_Text(w_zwoelfmin); Set_Text(w_nach); break;
case 13: Set_Text(w_dreizehnmin); Set_Text(w_vor); break;
case 14: Set_Text(w_vierzehnmin); Set_Text(w_nach); break;
case 15: Set_Text(w_viertelm); Set_Text(w_nach); break;
case 16: Set_Text(w_sechzehnmin); Set_Text(w_nach); break;
case 17: Set_Text(w_siebzehnmin); Set_Text(w_nach); break;
case 18: Set_Text(w_achtzehnmin); Set_Text(w_nach); break;
case 19: Set_Text(w_neunzehnmin); Set_Text(w_nach); break;
case 20: Set_Text(w_zehnmin); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 21: Set_Text(w_neunmin); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 22: Set_Text(w_achtmin); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 23: Set_Text(w_siebenmin); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 24: Set_Text(w_sechsmin); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 25: Set_Text(w_fuenfmin); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 26: 
case 27: 
case 28: 
case 29: Set_Text(w_kurz); Set_Text(w_vor); Set_Text(w_halb); stunde++; break;
case 30: Set_Text(w_halb); stunde++; break;
case 31: 
case 32: 
case 33: 
case 34: Set_Text(w_kurz); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 35: Set_Text(w_fuenfmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 36: Set_Text(w_sechsmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 37: Set_Text(w_siebenmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 38: Set_Text(w_achtmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 39: Set_Text(w_neunmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 40: Set_Text(w_zehnmin); Set_Text(w_nach); Set_Text(w_halb); stunde++; break;
case 41: 
case 42: 
case 43: 
case 44: Set_Text(w_kurz); Set_Text(w_vor); Set_Text(w_dreiviertel); stunde++; break;
case 45: if (variante==0) {Set_Text(w_viertelm); Set_Text(w_vor); stunde++;}
         else {Set_Text(w_dreiviertel); stunde++;} break;
case 46: 
case 47:
case 48:
case 49: Set_Text(w_kurz); Set_Text(w_nach); Set_Text(w_dreiviertel); stunde++; break;
case 50: Set_Text(w_zehnmin); Set_Text(w_vor); stunde++; break;
case 51: Set_Text(w_neunmin); Set_Text(w_vor); stunde++; break;
case 52: Set_Text(w_achtmin); Set_Text(w_vor); stunde++; break;
case 53: Set_Text(w_siebenmin); Set_Text(w_vor); stunde++; break;
case 54: Set_Text(w_sechsmin); Set_Text(w_vor); stunde++; break;
case 55: Set_Text(w_fuenfmin); Set_Text(w_vor); stunde++; break;
case 56: 
case 57:
case 58:
case 59: Set_Text(w_kurz); Set_Text(w_vor); stunde++; break;

}
}

/*
switch(stunde) {
case 0: Set_CText(w_gute,30,150,helli/2); Set_CText(w_nacht,30,150,helli/2); break;
case 1: 

case 3: 
case 2: 
case 4: break;
case 5: Set_CText(w_guten,30,150,helli/2); Set_CText(w_morgen,30,150,helli/2); break;
case 6: Set_CText(w_guten,30,150,helli/2); Set_CText(w_morgen,30,150,helli/2); break;
case 7: Set_CText(w_guten,30,150,helli/2); Set_CText(w_morgen,30,150,helli/2); break;
case 8: 
case 9: 
case 10: break;
case 11: Set_CText(w_schoenen,30,150,helli/2); Set_CText(w_tag,30,150,helli/2);break;
case 12: Set_CText(w_schoenen,30,150,helli/2); Set_CText(w_tag,30,150,helli/2); break;
case 13: Set_CText(w_schoenen,30,150,helli/2); Set_CText(w_tag,30,150,helli/2);  break;
case 14:
case 15:
case 16: break;
case 17: Set_CText(w_guten,30,150,helli/2); Set_CText(w_abend,30,150,helli/2); break;
case 18: Set_CText(w_guten,30,150,helli/2); Set_CText(w_abend,30,150,helli/2); break;
case 19: Set_CText(w_guten,30,150,helli/2); Set_CText(w_abend,30,150,helli/2); break;
case 20: Set_CText(w_schoenen,30,150,helli/2); Set_CText(w_abend,30,150,helli/2); break;
case 21: Set_CText(w_schoenen,30,150,helli/2); Set_CText(w_abend,30,150,helli/2); break;
case 22: Set_CText(w_gute,30,150,helli/2); Set_CText(w_nacht,30,150,helli/2); break;
case 23: Set_CText(w_gute,30,150,helli/2); Set_CText(w_nacht,30,150,helli/2); break;

}

*/

if (stunde>12) stunde=stunde-12;

switch(stunde) {
case 0: Set_Text(w_zwoelf); break;
case 1: if (tm.tm_min==0) Set_Text(w_ein); else Set_Text(w_eins); break;
case 2: Set_Text(w_zwei); break;
case 3: Set_Text(w_drei); break;
case 4: Set_Text(w_vier); break;
case 5: Set_Text(w_fuenf); break;
case 6: Set_Text(w_sechs); break;
case 7: Set_Text(w_sieben); break;
case 8: Set_Text(w_acht); break;
case 9: Set_Text(w_neun); break;
case 10: Set_Text(w_zehn); break;
case 11: Set_Text(w_elf); break;
case 12: Set_Text(w_zwoelf); break;
}



if (enablehallo==1 && digitalRead(praesenz)!=0) {Set_CText(w_hallo,30,150,helli/2); Set_CText(w_brigitte,30,150,helli/2); if (variante==0) Set_CText(w_liebe,30,150,helli/2);}

FastLED.show();
last_millis=millis();
}

