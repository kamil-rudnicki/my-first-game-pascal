program komar_racer;
uses crt, graf_fx, dos, procedur;
var
   qwe1:boolean;


{*****************************************************************}

Begin

randomize;
proba:=1;
level:=1;
komar1:=210;

repeat
odtwarzanie_ciagle:=TRUE;
if (g_zresetuj_SB(proba) = FALSE) then proba:=proba+1;
if proba>=30 then break;
until g_zresetuj_SB(proba) = TRUE;

if proba>=30 then begin
 odtwarzanie_ciagle:=FALSE;
 writeln('Problem z karta dzwiekowa.');
 writeln('Przycznya moze byc zajeta karta.');
 writeln('Uruchom ponownie komputer, jesli to nie zadziala, muszisz grac bez dzwieku.');
 writeln('Nacisnij klawisz ENTER, aby kontynuowac gre bez dzwieku.');
repeat
if keypressed then begin
znak:=readkey;
kod_znaku := ord(znak);
end;
until kod_znaku=13;
end;

g_ustaw_tryb_vga($13);
g_pobierz_pamiec_dla_drugiego_buforu(adres_2_buforu);

logo;
menu;

end.