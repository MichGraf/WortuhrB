typedef struct {
    int wx;
    int wy;
    int wc;  //count
} swort;


swort w_es              =   {0,0,2};       //es
swort w_ist             =   {3,0,3};       //ist
swort w_gleich          =   {7,0,6};       //gleich
swort w_ca              =   {0,1,2};       //ca
swort w_fuenf_vn        =   {3,1,4};       //fünf
swort w_zehn_vn         =   {7,1,4};       //zehn
swort w_fuenfzehn_vn    =   {7,1,8};       //fünfzehn
swort w_dreiviertel     =   {0,2,11};       //dreiviertel
swort w_viertel         =   {4,2,7};       //viertel
swort w_zwanzig         =   {0,3,7};       //zwanzig
swort w_vor             =   {8,3,3};       //vor
swort w_nach            =   {0,4,4};       //nach
swort w_halb            =   {5,4,4};       //halb
swort w_elf             =   {0,5,3};       //elf
swort w_fuenf           =   {2,5,4};       //fünf
swort w_sechs           =   {6,5,5};       //sechs
swort w_eins            =   {0,6,4};       //eins
swort w_ein             =   {0,6,3};       //ein
swort w_zwei            =   {4,6,4};       //zwei
swort w_vier            =   {0,7,4};       //vier
swort w_zehn            =   {4,7,4};       //zehn
swort w_neun            =   {7,7,4};       //neun
swort w_acht            =   {0,8,4};       //acht
swort w_sieben          =   {4,8,6};       //sieben
swort w_drei            =   {0,9,4};       //drei
swort w_zwoelf          =   {4,9,5};       //zwoelf
swort w_uhr             =   {0,10,3};       //uhr
swort w_solar           =   {4,11,5};       //solar

swort w_renate          =   {11,8,1};       //renate
swort w_michael         =   {12,8,1};       //michael
swort w_sommer          =   {10,9,1};       //sommer
swort w_winter          =   {11,9,1};       //winter
swort w_weihnachten     =   {12,9,1};       //weihnachten
swort w_warnung_a       =   {10,10,1};       //warnung a
swort w_warnung_b       =   {11,10,1};       //warnung b
swort w_warnung_c       =   {12,10,1};       //warnung c
swort w_warnung_e       =   {10,11,1};       //warnung e
swort w_warnung_f       =   {11,11,1};       //warnung f
swort w_warnung_g       =   {12,11,1};       //warnung g




void Set_Text(swort txt, int h, int s, int v) {
    for (int x=txt.wx; x<txt.wx+txt.wc; x++)  leds[XY(x,txt.wy)] = CHSV(h,s,v);
}

void Set_Laden (int h, int s, int v) {
    for (int y=2; y<7; y++)  leds[XY(12,y)] = CHSV(h,s,v);
}
