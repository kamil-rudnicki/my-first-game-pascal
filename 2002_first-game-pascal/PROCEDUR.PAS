unit procedur;

interface

USES CRT,DOS, GRAF_FX;
var
   godz,min,sek,sek100,sek1,sek2:word;
   zrodlowy, docelowy:prostokat;
   klatki_kulek:obraz;
   adres_2_buforu:pointer;
   a, b, c, lp, nolo, d, km, obr, e, f :integer;
   k:char;
   znak:char;
   kod_znaku, wibracje, ran, dop1:byte;
   ca,cb,cc,cd,ce:byte;
   dopalacz : array[0..4] of byte;
   x_ludzik : array[0..4] of integer;
   y_ludzik:integer;
   ludzik:integer;
   czekac_na_powrot:boolean;
   czekaj:real;
   komar1, komar2:integer;
   tekstc, teksta, tekstb:string;
   bufor_dzwiekowy:fala_dzwiekowa;
   proba:integer;
   odtwarzanie_ciagle:boolean;
   qwe:longint;
   zda : array[0..4] of integer;
   licznik, dma:integer;
   a1: array[0..4] of integer;
   a2: array[0..4] of integer;
   zycie:integer;
   paleta:paleta_kolorow;
   t:byte;
   delta:integer;
   zycie1: array[0..4] of boolean;
   level, czas:integer;
   nazwa, runda:array[1..30] of string;
   kl:char;
   iloscosob:byte;
   t1:byte;
   plik:text;
   lk, przebieg:integer;
   fps,fps1:byte;


procedure zdarzenia;
procedure menu_gry;
procedure menu;
procedure logo;
procedure exit_gra;
procedure stop;
procedure losuj;
procedure o_grze;
procedure laduj;
PROCEDURE Zapisz;                                       {2}
PROCEDURE Czytaj;                                       {13}
PROCEDURE Wprowadz;
procedure inicjalizacja_gra;
procedure klawisze;
procedure gra;
procedure levels;


implementation

procedure levels;
begin
{******}
if level=1 then begin

 if sek2=43 then begin  {poczatek}
 repeat
 if keypressed then begin
 znak:=readkey;
 kod_znaku := ord(znak);
 end;
 g_wypelnij_bufor(adres_2_buforu, 200);
 g_wyswietl_tekst_13h(adres_2_buforu, 140,40, 'LEVEL 1', 0);
 g_wyswietl_tekst_13h(adres_2_buforu, 5,100, 'Przejedz 15 ludzi w ciagu 40 sekund', 0);
 g_wyswietl_tekst_13h(adres_2_buforu, 10,190, 'Nacisnij SPACJE aby kontynuowac.', 0);
 if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
 g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
 until kod_znaku=32;
 sek2:=42;
 end;

 if sek2<=0 then begin {koniec}
    if zycie>=15 then begin  {wygrana}
    level:=level+1;
    zycie:=0;
    sek2:=42;
    exit;
    end else begin      {przegrana}
    g_wypelnij_bufor(adres_2_buforu, 200);
    g_wyswietl_tekst_13h(adres_2_buforu, 120,90, 'GAME OVER', 0);
    if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
    g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
    delay(1000);
    menu;
    end;
 end;

end;
{******}
if level=2 then begin

 if sek2>=40 then begin  {poczatek}
 repeat
 if keypressed then begin
 znak:=readkey;
 kod_znaku := ord(znak);
 end;
 g_wypelnij_bufor(adres_2_buforu, 200);
 g_wyswietl_tekst_13h(adres_2_buforu, 140,40, 'LEVEL 2', 0);
 g_wyswietl_tekst_13h(adres_2_buforu, 5,100, 'Przejedz 20 ludzi w ciagu 40 sekund', 0);
 g_wyswietl_tekst_13h(adres_2_buforu, 10,190, 'Nacisnij SPACJE aby kontynuowac.', 0);
 if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
 g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
 until kod_znaku=32;
 sek2:=39;
 end;


    if sek2<=0 then begin {koniec}
    if zycie>=20 then begin  {wygrana}
    level:=level+1;
    zycie:=0;
    sek2:=40;
    exit;
    end else begin      {przegrana}
    g_wypelnij_bufor(adres_2_buforu, 200);
    g_wyswietl_tekst_13h(adres_2_buforu, 120,90, 'GAME OVER', 0);
    if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
    g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
    delay(1000);
    menu;
    end;
 end;


end;

{******}
end;


procedure o_grze;
begin

g_zwolnij_pam(klatki_kulek);
g_laduj_BMP_13h(klatki_kulek, 'credits.bmp');
g_laduj_palete_BMP('credits.bmp');

repeat
if keypressed then begin
znak:=readkey;
kod_znaku := ord(znak);
end;
g_wypelnij_bufor(adres_2_buforu, 15);

g_wypelnij_p(zrodlowy, 0, 0, 320, 200);
g_wypelnij_p(docelowy, 0, 0, 320, 200);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, 0);

g_czekaj_na_powrot_pionowy;
g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
until kod_znaku=27;
g_zwolnij_pam(klatki_kulek);
menu;
end;

procedure logo;
begin
g_laduj_BMP_13h(klatki_kulek, 'logo.bmp');
g_laduj_palete_BMP('logo.bmp');
g_pobierz_palete_VGA(paleta);
g_zamaluj_ekran_13h(0);
a:=-250;
b:=220;
while not(kod_znaku=27) do begin
g_wypelnij_bufor(adres_2_buforu, 0);
if keypressed then begin
znak:=readkey;
kod_znaku := ord(znak);
end;
if a<=70 then a:=a+1;
g_wypelnij_p(zrodlowy, 0, 0, 200, 33);
g_wypelnij_p(docelowy, a, 70, 200, 33);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
if (a=71) and (b>=95) then b:=b-1 else if (c=0) and (a=71) then c:=1;
g_wypelnij_p(zrodlowy, 0, 33, 200, 33);
g_wypelnij_p(docelowy, 70, b, 200, 33);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
if (c=1) and (a=71) then begin
delay(1000);
g_wygas_ekran(10);
g_wypelnij_bufor(adres_2_buforu, 0);
g_zamaluj_ekran_13h(0);
g_rozjasnij_ekran(paleta, 0);
g_wypelnij_p(zrodlowy, 0, 74, 320, 55);
g_wypelnij_p(docelowy, 0, 80, 320, 55);
g_wyswietl_obraz_13h_k_s(ptr($a000,000), zrodlowy, docelowy, klatki_kulek, TRUE, 0);
delay(2000);
g_pobierz_palete_VGA(paleta);
g_rozjasnij_ekran_k(paleta, 20);
delay(1000);
g_zwolnij_pam(klatki_kulek);
exit;
end;
g_czekaj_na_powrot_pionowy;
g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
end;
g_zwolnij_pam(klatki_kulek);
g_zwolnij_pam_w(bufor_dzwiekowy);
exit;
end;


procedure gra;
begin
while 1=1 do
begin


if(odtwarzanie_ciagle = TRUE) then begin
if ((port[$008] and $02) = 2) then
begin
g_przestan_odtwarzac;
g_odegraj_WAV(bufor_dzwiekowy, qwe);
end;
end;



a:=a+1;
if a>=200 then a:=-200;
b:=b+1;
if b>=200 then b:=-200;

if b=150 then przebieg:=przebieg+1;

ludzik:=ludzik+1;
if ludzik>=100 then ludzik:=0;
if ludzik<50 then y_ludzik:=160
else y_ludzik:=180;

d:=d+1;
if d=20 then d:=1;

g_wypelnij_bufor(adres_2_buforu, 200);

ran:=random(15);
if ran=1 then km:=km+1;
if ran=2 then km:=km-1;
if ran=3 then obr:=obr+1;
if ran=4 then obr:=obr-1;

g_wypelnij_p(zrodlowy, 0, 0, 193, 200);
g_wypelnij_p(docelowy, 0, a, 193, 200);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, klatki_kulek.wsk_obrazu^[0]);
g_wypelnij_p(docelowy, 0, b, 193, 200);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, klatki_kulek.wsk_obrazu^[0]);



IF dop1>24 THEN
Begin
g_wypelnij_p(zrodlowy, 245,  60, 75, 33);
g_wypelnij_p(docelowy, 20, nolo-30, 75, 33);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
g_wypelnij_p(docelowy, 95, nolo-30, 75, 33);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;


IF CA=1 THEN
Begin
g_wypelnij_p(zrodlowy, a1[0],  a2[0], 20, 20);
g_wypelnij_p(docelowy, 25, nolo+dopalacz[0], 20, 20);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;
IF CB=1 THEN
Begin
g_wypelnij_p(zrodlowy, a1[1],  a2[1], 20, 20);
g_wypelnij_p(docelowy, 55, nolo+dopalacz[1], 20, 20);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;
IF CC=1 THEN
Begin
g_wypelnij_p(zrodlowy, a1[2],  a2[2], 20, 20);
g_wypelnij_p(docelowy, 85, nolo+dopalacz[2], 20, 20);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;
IF CD=1 THEN
Begin
g_wypelnij_p(zrodlowy, a1[3],  a2[3], 20, 20);
g_wypelnij_p(docelowy, 115, nolo+dopalacz[3], 20, 20);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;
IF CE=1 THEN
Begin
g_wypelnij_p(zrodlowy, a1[4],  a2[4], 20, 20);
g_wypelnij_p(docelowy, 145, nolo+dopalacz[4], 20, 20);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;

NOLO:=NOLO+1;
If nolo>=280 then losuj;

if (ca=1) and (lp>=20) and (lp<=32) and (nolo+dopalacz[0]>=135) and (nolo+dopalacz[0]<=200) then zda[0]:=1;
if (cb=1) and (lp>=43) and (lp<=61) and (nolo+dopalacz[1]>=135) and (nolo+dopalacz[1]<=200) then zda[1]:=1;
if (cc=1) and (lp>=74) and (lp<=92) and (nolo+dopalacz[2]>=135) and (nolo+dopalacz[2]<=200) then zda[2]:=1;
if (cd=1) and (lp>=106) and (lp<=120) and (nolo+dopalacz[3]>=135) and (nolo+dopalacz[3]<=200) then zda[3]:=1;
if (ce=1) and (lp>=132) and (lp<=170) and (nolo+dopalacz[4]>=135) and (nolo+dopalacz[4]<=200) then zda[4]:=1;


zdarzenia;

g_wypelnij_p(zrodlowy, komar1, 10, 27, 51);
g_wypelnij_p(docelowy, lp, 140, 27, 51);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);


str(km,teksta);
g_wyswietl_tekst_13h(adres_2_buforu, 200,10, 'KM/h', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 285,10, teksta, 0);

str(obr,tekstb);
g_wyswietl_tekst_13h(adres_2_buforu, 200,20, 'Obr/min.', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 285,20, tekstb, 0);

str(zycie,tekstc);
g_wyswietl_tekst_13h(adres_2_buforu, 200,30, 'Punkty', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 285,30, tekstc, 0);

fps:=fps+1;
sek1:=sek;
GetTime(godz,min,sek,sek100);
if (sek1<>sek) then begin
sek2:=sek2-1;

fps:=0;
end;

str(sek2,tekstc);
g_wyswietl_tekst_13h(adres_2_buforu, 200,40, 'Czas', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 285,40, tekstc, 0);

str(przebieg,tekstc);
g_wyswietl_tekst_13h(adres_2_buforu, 200,50, 'Przebieg', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 285,50, tekstc, 0);

str(fps,tekstc);
g_wyswietl_tekst_13h(adres_2_buforu, 200,60, 'FPS', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 285,60, tekstc, 0);

if keypressed then klawisze;
if d=19 then komar1:=210;


IF dop1<4 THEN
Begin
g_wypelnij_p(zrodlowy, 193,  171, 20, 29);
g_wypelnij_p(docelowy, 1, nolo, 20, 29);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;

IF (dop1>16) and (dop1<20) THEN
Begin
g_wypelnij_p(zrodlowy, 193,  0, 20, 55);
g_wypelnij_p(docelowy, 1, nolo, 20, 55);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;

IF (dop1>22) and (dop1<25) THEN
Begin
g_wypelnij_p(zrodlowy, 193,  171, 20, 29);
g_wypelnij_p(docelowy, 171, nolo-40, 20, 29);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;

IF dop1=8 THEN
Begin
g_wypelnij_p(zrodlowy, 193,  0, 20, 55);
g_wypelnij_p(docelowy, 171, nolo-20, 20, 55);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 222);
end;





levels;

delay(round(czekaj));

if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
end;
end;

{*****************************************************************}

procedure menu;
begin

g_laduj_BMP_13h(klatki_kulek, 'menu.bmp');
g_laduj_palete_BMP('menu.bmp');
g_pobierz_palete_VGA(paleta);
g_ustaw_wzorzec_koloru(200,0, 63, 60);
g_ustaw_wzorzec_koloru(201, 0, 55, 0);

t:=1;
c:=1;
a:=1;
b:=174;
km:=0;
delta:=1;

while (1=1) do begin
g_wypelnij_bufor(adres_2_buforu, 201);

if (((km + delta) < 0) or ((km + delta) > 40)) then delta:= -delta;
km:=km + delta;

if keypressed then begin
znak:=readkey;
kod_znaku := ord(znak);
case kod_znaku of
72 : begin
sound(800);
delay(50);
nosound;
 t:=t-1; {gora}
 if t=0 then t:=4;
 end;
80 : begin
sound(800);
delay(50);
nosound;
t:=t+1; {dol}
if t=5 then t:=1;
end;
13 : begin
if t=1 then begin
inicjalizacja_gra;
gra;
end;
if t=2 then laduj;
if t=3 then o_grze;
if t=4 then exit_gra;

end; {enter}
end;
end;

c:=c+1;
if c=63 then c:=10;
if c<40 then a:=1 else a:=2;
if a=1 then b:=174 else b:=149;

g_wypelnij_p(zrodlowy, 317, 150, 2, 50);
g_wypelnij_p(docelowy, 0, 0, 320, 50);
g_wyswietl_obraz_13h_k_s(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 317, 150, 2, 50);
g_wypelnij_p(docelowy, 0, 50, 320, 50);
g_wyswietl_obraz_13h_k_s(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 317, 150, 2, 50);
g_wypelnij_p(docelowy, 0, 100, 320, 50);
g_wyswietl_obraz_13h_k_s(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 317, 150, 2, 50);
g_wypelnij_p(docelowy, 0, 150, 320, 50);
g_wyswietl_obraz_13h_k_s(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);

g_wypelnij_p(zrodlowy, 100, 2, 210, 80);
g_wypelnij_p(docelowy, km, 0, 210, 80);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);

g_wyswietl_tekst_13h(adres_2_buforu, 235,50, ' gedon', 0);
g_wyswietl_tekst_13h(adres_2_buforu,235,60, 'ver. 1.0', 0);

g_wypelnij_p(zrodlowy, 0, 0, 99, 22);
g_wypelnij_p(docelowy, 110, 96, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 0, 22, 99, 22);
g_wypelnij_p(docelowy, 110, 122, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 0, 44, 99, 22);
g_wypelnij_p(docelowy, 110, 148, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 0, 66, 99, 22);
g_wypelnij_p(docelowy, 110, 174, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);

if t=1 then begin
g_wypelnij_p(zrodlowy, 0, 88, 99, 22);
g_wypelnij_p(docelowy, 110, 96, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 45, 94, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 225, 94, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
end;

if t=2 then begin
g_wypelnij_p(zrodlowy, 0, 110, 99, 22);
g_wypelnij_p(docelowy, 110, 122, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 45, 120, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 225, 120, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
end;
if t=3 then begin
g_wypelnij_p(zrodlowy, 0, 132, 99, 22);
g_wypelnij_p(docelowy, 110, 148, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 45, 146, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 225, 146, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
end;
if t=4 then begin
g_wypelnij_p(zrodlowy, 0, 154, 99, 22);
g_wypelnij_p(docelowy, 110, 174, 99, 22);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, FALSE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 45, 172, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
g_wypelnij_p(zrodlowy, 266, b, 49, 24);
g_wypelnij_p(docelowy, 225, 172, 49, 24);
g_wyswietl_obraz_13h_k(adres_2_buforu, zrodlowy, docelowy, klatki_kulek, TRUE, 0);
end;

if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
delay(1);
end;

g_wygas_ekran(5);
g_zwolnij_pam(klatki_kulek);
exit;

end;

procedure exit_gra;
begin
if odtwarzanie_ciagle = TRUE then
begin
g_przestan_odtwarzac;
g_odegraj_WAV(bufor_dzwiekowy, 11025);
delay(1000);
g_zwolnij_pam_w(bufor_dzwiekowy);
g_wylacz_glosniki;
end;
g_wygas_ekran(10);
g_zwolnij_pam(klatki_kulek);
g_zwolnij_pam_buforu(adres_2_buforu);
g_wylacz_tryb_VGA;
halt;
end;

{*****************************************************************}

procedure losuj;
Begin
nolo:=-180;
randomize;

dop1:=random(30);

for licznik:=0 to 4 do
begin
zda[licznik]:=2;
x_ludzik[licznik]:=(random(5) * 20)+220;
dopalacz[licznik]:=random(150);
end;

repeat
ca:=random(2);
cb:=random(2);
cc:=random(2);
cd:=random(2);
ce:=random(2);
until ca+cb+cc+ce+cd=4;
end;

{*****************************************************************}

procedure stop;
begin
repeat until keypressed;
end;

{*****************************************************************}

procedure klawisze;
begin
begin
znak:=readkey;
kod_znaku := ord(znak);
case kod_znaku of
80 : begin   {hamulec}
czekaj:=czekaj+1;
if czekaj>=20 then czekaj:=20;
qwe:=qwe-200;
if qwe<=10000 then qwe:=10000;
km:=km-2;
if km<10 then km:=10;
obr:=obr-200;
if obr<=2000 then obr:=2000;
 end;
72 : Begin    {gaz}
czekaj:=czekaj-0.5;
if czekaj<=1 then czekaj:=1;
qwe:=qwe+100;
if qwe>=14000 then qwe:=14000;
km:=km+1;
if km>=50 then km:=50;
obr:=obr+100;
if obr>=6000 then obr:=6000;
  end;
75 : Begin {lewo}
komar1:=236;
lp:=lp-3;

if lp<=20 then lp:=20;
 end;
77 : begin  {prawo}
komar1:=262;
lp:=lp+3;

if lp>=144 then lp:=144;
 end;
27 : menu_gry;
32 : stop;
112 : begin
g_wygas_ekran_k(30, 5);
readkey;
g_rozjasnij_ekran(paleta, 5);

end;
end;
end;
end;

{*****************************************************************}

procedure zdarzenia;
begin

for licznik:=0 to 4 do
begin
if zda[licznik]=1 then
begin
a1[licznik]:=297;
a2[licznik]:=20;

if zycie1[licznik]=TRUE then begin
zycie:=zycie+1;
if odtwarzanie_ciagle=TRUE then begin
g_przestan_odtwarzac;
g_odegraj_WAV(bufor_dzwiekowy, 11050);
end;
zycie1[licznik]:=FALSE;
end;

end else begin
a1[licznik]:=x_ludzik[licznik];
a2[licznik]:=y_ludzik;
zycie1[licznik]:=TRUE;
end;
end;
end;

{*****************************************************************}

procedure inicjalizacja_gra;
begin
km:=10;
d:=1;
proba:=0;
qwe:=10000;
obr:=2000;
lp:=82;
nolo:=270;
czekaj:=20;
c:=1;
b:=-200;
a:=0;
sek2:=44;
zycie:=0;
przebieg:=0;
level:=1;



g_laduj_BMP_13h(klatki_kulek, 'gra.bmp');
g_laduj_palete_BMP('gra.bmp');

if odtwarzanie_ciagle = TRUE then
begin
g_laduj_WAV(bufor_dzwiekowy, 'gra.wav');
g_wlacz_glosniki;
g_przestan_odtwarzac;
g_odegraj_WAV(bufor_dzwiekowy, qwe);
end;

g_ustaw_wzorzec_koloru(200,63, 63, 60);
g_pobierz_palete_VGA(paleta);

end;

PROCEDURE Zapisz;                                       {2}
Begin
  Assign(plik,'Load.DAN');                              {3}
  ReWrite(plik);                                        {4}
  WriteLn(plik,iloscosob);                              {5}
  t1:=0;                                                {6}
  Repeat
    t1:=t1+1;                                           {7}
    WriteLn(plik,nazwa[t1] );                            {8}
    WriteLn(plik,runda[t1] );                        {9}                         {10}
  Until t1=iloscosob;                                   {11}
  Close(plik);                                          {12}
End;

PROCEDURE Czytaj;                                       {13}
Begin
  Assign(plik,'Load.DAN');                              {14}
  Reset(plik);                                          {15}
  ReadLn(plik,iloscosob);                               {16}
  t1:=0;                                                {17}
  Repeat
    t1:=t1+1;                                           {18}
    ReadLn(plik,nazwa[t1]);                             {19}
    ReadLn(plik,runda[t1]);                         {20}                        {21}
  Until t1=iloscosob;                                   {22}
  Close(plik);                                          {23}
End;
                                             {1}

procedure laduj;
begin
czytaj;
lk:=0;
g_wypelnij_bufor(adres_2_buforu, 29);
repeat
lk:=lk+1;
g_wyswietl_tekst_13h(adres_2_buforu, 20,lk*10, nazwa[lk], 0);
g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
until lk=iloscosob;
val(runda[b],level,level);
repeat until keypressed;
exit;
end;

PROCEDURE Wprowadz;
Begin
  ClrScr;
  Iloscosob:=iloscosob+1;                                       {4}
  Write('Nazwa : ');
  ReadLn( nazwa[iloscosob] );                                    {5}
  Write('Runda : ');
  ReadLn( runda[iloscosob] );
  zapisz;                                {6}                               {7}
End;


procedure menu_gry;
begin
t:=1;
while (1=1) do begin
if keypressed then begin
znak:=readkey;
kod_znaku := ord(znak);
case kod_znaku of
72 : begin
sound(800);
delay(20);
sound(700);
delay(20);
sound(600);
delay(20);
nosound;
 t:=t-1; {gora}
 if t=0 then t:=4;
 end;
80 : begin
sound(600);
delay(20);
sound(700);
delay(20);
sound(800);
delay(20);
nosound;
t:=t+1; {dol}
if t=5 then t:=1;
end;
13 : begin
if t=1 then begin
c:=1;
b:=-200;
a:=0;
g_zwolnij_pam(klatki_kulek);
g_laduj_BMP_13h(klatki_kulek, 'gra.bmp');
g_laduj_palete_BMP('gra.bmp');
g_ustaw_wzorzec_koloru(200,63, 63, 60);
g_pobierz_palete_VGA(paleta);
exit;
end;
if t=2 then begin
t:=30;
g_wyswietl_tekst_13h(ptr($a000,0000), 30, 20, 'Zapisz jako:', 46);
g_wyswietl_tekst_13h(ptr($a000,0000), 30, 30, '(max 10 znak.):', 97);
repeat until keypressed;
repeat
if keypressed then begin
znak:=readkey;
kod_znaku:=ord(znak);
t:=t+7;
g_wyswietl_tekst_13h(ptr($a000,0000), t, 40, znak, 0);
end;

Iloscosob:=iloscosob+1;                                       {4}



  zapisz;

if t>=96 then break;
g_wyswietl_tekst_13h(ptr($a000,0000), t, 42, '_', random(256));
until kod_znaku=13;
delay(1000);
c:=1;
b:=-200;
a:=0;
g_zwolnij_pam(klatki_kulek);
g_laduj_BMP_13h(klatki_kulek, 'gra.bmp');
g_laduj_palete_BMP('gra.bmp');
g_ustaw_wzorzec_koloru(200,63, 63, 60);
g_pobierz_palete_VGA(paleta);
exit;
gra;
end;
if t=3 then begin
 g_zwolnij_pam(klatki_kulek);
 menu;
end;
if t=4 then EXIT_GRA;

end; {enter}
end;
end;

c:=c+1;
if c=63 then c:=10;
if c<40 then a:=1 else a:=2;
if a=1 then b:=174 else b:=149;

g_wyswietl_tekst_13h(adres_2_buforu, 50,50, 'RETURN TO GAME', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 50,60, '     SAVE', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 50,70, 'RETURN TO MENU', 0);
g_wyswietl_tekst_13h(adres_2_buforu, 50,80, 'EXIT TO SYSTEM', 0);

if t=1 then begin
g_wyswietl_tekst_13h(adres_2_buforu, 50,50, 'RETURN TO GAME', 48);
end;
if t=2 then begin
g_wyswietl_tekst_13h(adres_2_buforu, 50,60, '     SAVE', 94);
end;
if t=3 then begin
g_wyswietl_tekst_13h(adres_2_buforu, 50,70, 'RETURN TO MENU', 148);
end;
if t=4 then begin
g_wyswietl_tekst_13h(adres_2_buforu, 50,80, 'EXIT TO SYSTEM', 222);
end;

if (czekac_na_powrot = TRUE) then g_czekaj_na_powrot_pionowy;
g_kopiuj_bufor(ptr($A000,0000), adres_2_buforu);
end;
end;




end.




