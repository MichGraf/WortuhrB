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


if ((millis()-variantenticker) > 30000) {
    tmp=millis() % 6;
    if (tmp < 3) variante=0; else variante=1;
    if ((tmp >=2) && (tmp<=4)) enable_es_ist=0; else enable_es_ist=1;
    variantenticker=millis();
   }


if (enable_es_ist==1) {Set_Text(w_es,h,s,v); Set_Text(w_ist,h,s,v);}

if (min_mod==1 || min_mod==2) Set_Text(w_ca,h,s,v);
if (min_mod==3 || min_mod==4) Set_Text(w_gleich,h,s,v);

//letzte Stelle 3..7	erste Stelle 0,2,3,5		fünf
if (min_first==0 || min_first==2 || min_first==3 || min_first==5)
   if (min_last>=3 && min_last<=7) Set_Text(w_fuenf_vn,h,s,v);

//zehn
if (variante==0) 
   { if ((tm.tm_min>=8 && tm.tm_min<=12) || (tm.tm_min>=48 && tm.tm_min<=52)) Set_Text(w_zehn_vn,h,s,v); }
else
   { if ((tm.tm_min>=8 && tm.tm_min<=12) || (tm.tm_min>=18 && tm.tm_min<=22) || (tm.tm_min>=38 && tm.tm_min<=42) || (tm.tm_min>=48 && tm.tm_min<=52)) Set_Text(w_zehn_vn,h,s,v); }

//letzte Stelle 3..7	erste Stelle 1, 4		viertel
if (min_first==1 || min_first==4)
   if (min_last>=3 && min_last<=7) Set_Text(w_viertel,h,s,v);

//zwanzig
if (variante==0)
    if ((tm.tm_min>=18 && tm.tm_min<=22) || (tm.tm_min>=38 && tm.tm_min<=42)) Set_Text(w_zwanzig,h,s,v);

//23..37			dreiviertel
if (variante!=0) 
    if (tm.tm_min>=43 && tm.tm_min<=47) Set_Text(w_dreiviertel,h,s,v);


//23..37			halb
if (variante==0) 
   { if (tm.tm_min>=23 && tm.tm_min<=37) Set_Text(w_halb,h,s,v); }
else
   { if (tm.tm_min>=18 && tm.tm_min<=42) Set_Text(w_halb,h,s,v); }

//3..22, 33.37			nach
if (variante==0) 
   { if ((tm.tm_min>=3 && tm.tm_min<=22) || (tm.tm_min>=33 && tm.tm_min<=37)) Set_Text(w_nach,h,s,v); }
else
   { if ((tm.tm_min>=3 && tm.tm_min<=17) || (tm.tm_min>=33 && tm.tm_min<=42)) Set_Text(w_nach,h,s,v); }

//23..27, 38..57			vor
if (variante==0) 
   { if ((tm.tm_min>=23 && tm.tm_min<=27) || (tm.tm_min>=38 && tm.tm_min<=57)) Set_Text(w_vor,h,s,v); }
else
   { if ((tm.tm_min>=18 && tm.tm_min<=27) || (tm.tm_min>=48 && tm.tm_min<=57)) Set_Text(w_vor,h,s,v); }

//uhr
if ((tm.tm_min>=0 && tm.tm_min<=2) || (tm.tm_min>=58 && tm.tm_min<=59)) Set_Text(w_uhr,h,s,v);


if ((tm.tm_min>=23 && tm.tm_min<=59)) stunde++;
if ((tm.tm_min>=18 && tm.tm_min<=22) && (variante!=0)) stunde++;

if (stunde>12) stunde=stunde-12;

switch(stunde) {

case 0: Set_Text(w_zwoelf,h,s,v); break;
case 1: if (tm.tm_min==58 || tm.tm_min==59 || (tm.tm_min>=0 && tm.tm_min<=2)) Set_Text(w_ein,h,s,v); else Set_Text(w_eins,h,s,v); break;
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

}



/*
0	0		Es ist					stunde-ein	Uhr																	
1	1		Es ist	ca				stunde-ein	Uhr																	
2	2		Es ist	ca				stunde-ein	Uhr																	
3	3		Es ist	gleich	fünf	nach		stunde																		
4	4		Es ist	gleich	fünf	nach		stunde																		
5	0		Es ist		fünf	nach 		stunde																		
6	1		Es ist	ca	fünf	nach		stunde																		
7	2		Es ist	ca	fünf	nach		stunde																		
8	3		Es ist	gleich	zehn	nach		stunde																		
9	4		Es ist	gleich	zehn	nach		stunde																		
10	0		Es ist		zehn	nach		stunde																		
11	1		Es ist	ca	zehn	nach		stunde																		
12	2		Es ist	ca	zehn	nach		stunde																		
13	3		Es ist	gleich	viertel	nach		stunde																		
14	4		Es ist	gleich	viertel	nach		stunde																		
15	0		Es ist		viertel	nach		stunde																		
16	1		Es ist	ca	viertel	nach		stunde																		
17	2		Es ist	ca	viertel	nach		stunde																		
18	3		Es ist	gleich	zwanzig	nach		stunde			Es ist	gleich	zehn	vor	halb	stundeplus										
19	4		Es ist	gleich	zwanzig	nach		stunde			Es ist	gleich	zehn	vor	halb	stundeplus										
20	0		Es ist		zwanzig	nach		stunde			Es ist		zehn	vor	halb	stundeplus										
21	1		Es ist	ca	zwanzig	nach		stunde			Es ist	ca	zehn	vor	halb	stundeplus										
22	2		Es ist	ca	zwanzig	nach		stunde			Es ist	ca	zehn	vor	halb	stundeplus										
23	3		Es ist	gleich	fünf	vor	halb	stundeplus																		
24	4		Es ist	gleich	fünf	vor	halb	stundeplus																		
25	0		Es ist		fünf	vor	halb	stundeplus																		
26	1		Es ist	ca	fünf	vor	halb	stundeplus																		
27	2		Es ist	ca	fünf	vor	halb	stundeplus																		
28	3		Es ist	gleich			halb	stundeplus																		
29	4		Es ist	gleich			halb	stundeplus																		
30	0		Es ist				halb	stundeplus																		
31	1		Es ist	ca			halb	stundeplus																		
32	2		Es ist	ca			halb	stundeplus																		
33	3		Es ist	gleich	fünf	nach	halb	stundeplus																		
34	4		Es ist	gleich	fünf	nach	halb	stundeplus																		
35	0		Es ist		fünf	nach	halb	stundeplus																		
36	1		Es ist	ca	fünf	nach	halb	stundeplus																		
37	2		Es ist	ca	fünf	nach	halb	stundeplus																		
38	3		Es ist	gleich	zwanzig	vor		stundeplus			Es ist	gleich	zehn	nach	halb	stundeplus										
39	4		Es ist	gleich	zwanzig	vor		stundeplus			Es ist	gleich	zehn	nach	halb	stundeplus										
40	0		Es ist		zwanzig	vor		stundeplus			Es ist		zehn	nach	halb	stundeplus										
41	1		Es ist	ca	zwanzig	vor		stundeplus			Es ist	ca	zehn	nach	halb	stundeplus										
42	2		Es ist	ca	zwanzig	vor		stundeplus			Es ist	ca	zehn	nach	halb	stundeplus										
43	3		Es ist	gleich	viertel	vor		stundeplus			Es ist	gleich	dreiviertel			stundeplus										
44	4		Es ist	gleich	viertel	vor		stundeplus			Es ist	gleich	dreiviertel			stundeplus										
45	0		Es ist		viertel	vor		stundeplus			Es ist		dreiviertel			stundeplus										
46	1		Es ist	ca	viertel	vor		stundeplus			Es ist	ca	dreiviertel			stundeplus										
47	2		Es ist	ca	viertel	vor		stundeplus			Es ist	ca	dreiviertel			stundeplus										
48	3		Es ist	gleich	zehn	vor		stundeplus																		
49	4		Es ist	gleich	zehn	vor		stundeplus																		
50	0		Es ist		zehn	vor		stundeplus																		
51	1		Es ist	ca	zehn	vor		stundeplus																		
52	2		Es ist	ca	zehn	vor		stundeplus																		
53	3		Es ist	gleich	fünf	vor		stundeplus																		
54	4		Es ist	gleich	fünf	vor		stundeplus																		
55	0		Es ist		fünf	vor		stundeplus																		
56	1		Es ist	ca	fünf	vor		stundeplus																		
57	2		Es ist	ca	fünf	vor		stundeplus																		
58	3		Es ist	gleich				stundeplus-eins	Uhr																	
59	4		Es ist	gleich				stundeplus-eins	Uhr																	
																										
																										*/


