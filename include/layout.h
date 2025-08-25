typedef struct {
    int wx;
    int wy;
    int wc;  //count
} swort;

swort wort[]= {
   {0,0,2},       //es
   {3,0,3},       //ist
   {7,0,6},       //gleich
   {0,1,2},       //ca
   {3,1,4},       //fünf
   {7,1,4},       //zehn
   {7,1,8},       //fünfzehn
   {0,2,11},       //dreiviertel
   {4,2,7},       //viertel
   {0,3,7},       //zwanzig
   {8,3,3},       //vor
   {0,4,4},       //nach
   {5,4,4},       //halb
   {0,5,3},       //elf
   {2,5,4},       //fünf
   {6,5,5},       //sechs
   {0,6,4},       //eins
   {4,6,4},       //zwei
   {0,7,4},       //vier
   {4,7,4},       //zehn
   {7,7,4},       //neun
   {0,8,4},       //acht
   {4,8,6},       //sieben
   {0,9,4},       //drei
   {4,9,5},       //zwoelf
   {0,10,3},       //uhr
   {4,11,5},       //solar

   {11,8,1},       //renate
   {12,8,1},       //michael
   {10,9,1},       //sommer
   {11,9,1},       //winter
   {12,9,1},       //weihnachten
   {10,10,1},       //warnung a
   {11,10,1},       //warnung b
   {12,10,1},       //warnung c
   {10,11,1},       //warnung e
   {11,11,1},       //warnung f
   {12,11,1},       //warnung g

   {0,6,3}       //ein

};

#define w_es 0
#define w_ist 1
#define w_gleich 2
#define w_ca 3
#define w_fuenf_vn 4
#define w_zehn_vn 5
#define w_fuenfzehn_vn 6
#define w_dreiviertel 7
#define w_viertel 8
#define w_zwanzig 9
#define w_vor 10
#define w_nach 11
#define w_halb 12
#define w_elf 13
#define w_fuenf 14
#define w_sechs 15
#define w_eins 16
#define w_zwei 17
#define w_vier 18
#define w_zehn 19
#define w_neun 20
#define w_acht 21
#define w_sieben 22
#define w_drei 23
#define w_zwoelf 24
#define w_uhr 25
#define w_solar 26
#define w_renate 27
#define w_michael 28
#define w_sommer 29
#define w_winter 30
#define w_weihnachten 31
#define w_warnung_a 32
#define w_warnung_b 33
#define w_warnung_c 34
#define w_warnung_e 35
#define w_warnung_f 36
#define w_warnung_g 37
#define w_ein 38

#define w_laden 90


void Set_Text(int txt, int h, int s, int v) {
    if (txt<90) for (int x=wort[txt].wx; x<wort[txt].wx+wort[txt].wc; x++)  leds[XY(x,wort[txt].wy)] = CHSV(h,s,v);
    else if (txt==90) for (int y=2; y<7; y++)  leds[XY(12,y)] = CHSV(h,s,v);
}