typedef struct {
    int wx;
    int wy;
    int wc;  //count
} swort;

//                    Spalte, Zeile, Anzahl
swort w_es              =   {0,0,2};       //es
swort w_ist             =   {3,0,3};       //ist
swort w_zweimin         =   {7,0,4};       //zwei min
swort w_sechsmin        =   {11,0,5};      //sechs min
swort w_achtmin         =   {0,1,4};       //acht min
swort w_achtzehnmin     =   {0,1,8};       //achtzehn min
swort w_siebenmin       =   {10,1,6};      //sieben min
swort w_dreimin         =   {0,2,4};       //acht min
swort w_dreizehnmin     =   {0,2,8};       //achtzehn min
swort w_viermin         =   {8,2,4};       //vier min
swort w_vierzehnmin     =   {8,2,8};       //vierzehn min
swort w_sechzehnmin     =   {0,3,8};       //sechzehn min
swort w_zehnmin         =   {4,3,4};       //sechzehn min
swort w_siebzehnmin     =   {8,3,8};       //siebzehn min
swort w_einemin         =   {0,4,4};       //einmin   
swort w_neunmin         =   {4,4,4};       //neun min 
swort w_neunzehnmin     =   {4,4,8};       //neunzehn min
swort w_kurz            =   {12,4,4};       //kurz
swort w_elfm             =   {0,5,3};       //elf 
swort w_viertelm         =   {3,5,7};       //viertel min
swort w_schlaf          =   {10,5,6};       //schlaf
swort w_fuenfmin           =   {0,6,4};       //fünf
swort w_zwoelfmin          =   {4,6,5};       //zehn    FEHLER-kein Abstand zu Minuten
swort w_minute          =   {9,6,6};       //minuten
swort w_minuten         =   {9,6,7};       //minuten
swort w_vor             =   {0,7,3};       //vor
swort w_nach            =   {4,7,4};       //nach
swort w_heute           =   {7,7,5};       //heute
swort w_halb            =   {12,7,4};       //halb
swort w_dreiviertel     =   {0,8,11};       //dreiviertel
swort w_viertel         =   {4,8,7};       //viertel
swort w_eins            =   {12,8,4};       //eins
swort w_ein             =   {12,8,3};       //ein
swort w_zwei            =   {0,9,4};       //zwei
swort w_drei            =   {4,9,4};       //drei
swort w_vier            =   {8,9,4};       //vier
swort w_acht            =   {12,9,4};       //acht
swort w_fuenf           =   {0,10,4};       //fünf
swort w_sechs           =   {4,10,5};       //sechs
swort w_sieben          =   {9,10,6};       //sieben
swort w_neun            =   {0,11,4};       //neun
swort w_zehn            =   {4,11,4};       //zehn
swort w_elf             =   {8,11,3};       //elf
swort w_zwoelf          =   {11,11,5};       //zwoelf
swort w_uhr             =   {0,12,3};       //uhr
swort w_gut             =   {4,12,3};       //gut
swort w_gute            =   {4,12,4};       //gute
swort w_guten           =   {4,12,5};       //guten
swort w_schoen          =   {9,12,5};       //schoen
swort w_schoene         =   {9,12,6};       //schoenen
swort w_schoenen        =   {9,12,7};       //schoenen
swort w_abend           =   {0,13,5};       //abend
swort w_nacht           =   {5,13,5};       //nacht
swort w_hallo           =   {11,13,5};       //hallo
swort w_gefeiert        =   {0,14,8};       //gefeiert
swort w_feier           =   {2,14,6};       //feier
swort w_morgen          =   {10,14,6};       //morgen
swort w_feiertag        =   {2,14,8};       //feiertag
swort w_tag             =   {7,14,3};       //tag
swort w_liebe           =   {0,15,5};       //liebe
swort w_brigitte        =   {6,15,8};       //brigitte   






void Set_Text(swort txt, int h, int s, int v) {
    for (int x=txt.wx; x<txt.wx+txt.wc; x++)  leds[XY(txt.wy,x)] = CHSV(h,s,v);    //x, y vertauscht zu alten Uhr
}

void Set_Laden (int h, int s, int v) {
    for (int y=2; y<7; y++)  leds[XY(12,y)] = CHSV(h,s,v);
}
