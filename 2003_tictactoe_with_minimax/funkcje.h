int ilosc_krzyzykow=0;
int ilosc_kolek=0;

enum KTO{nic,komputer,czlowiek};
KTO v[9];
KTO aktualny_gracz=komputer;
int element;
POINT pozycja;
POINT pozycja_kursora;

// ____________________________________________________________________
KTO Nastepny_Gracz(KTO gracz)
{
if (gracz==komputer)
	return czlowiek;
else
	return komputer;
}
// _________________________________________________________________
POINT wspolrzedne_na_wspolrzedne(POINT wspolrzedna)
{
wspolrzedna.x=(wspolrzedna.x*100)+4;
wspolrzedna.y=(wspolrzedna.y*100)+6;
return wspolrzedna;
}

// ____________________________________________________________________
POINT element_na_wspolrzedne(int element)
{
POINT wspolrzedna;

        if(element==0){wspolrzedna.x=0; wspolrzedna.y=0;}
   else if(element==1){wspolrzedna.x=1; wspolrzedna.y=0;}
   else if(element==2){wspolrzedna.x=2; wspolrzedna.y=0;}
   else if(element==3){wspolrzedna.x=0; wspolrzedna.y=1;}
   else if(element==4){wspolrzedna.x=1; wspolrzedna.y=1;}
   else if(element==5){wspolrzedna.x=2; wspolrzedna.y=1;}
   else if(element==6){wspolrzedna.x=0; wspolrzedna.y=2;}
   else if(element==7){wspolrzedna.x=1; wspolrzedna.y=2;}
   else if(element==8){wspolrzedna.x=2; wspolrzedna.y=2;}
   //else exit(1);

return wspolrzedna;
}

// ____________________________________________________________________
int wspolrzedne_na_element(POINT wspolrzedna)
{
int pole;

        if(wspolrzedna.x==0 && wspolrzedna.y==0) pole=0;
   else if(wspolrzedna.x==1 && wspolrzedna.y==0) pole=1;
   else if(wspolrzedna.x==2 && wspolrzedna.y==0) pole=2;
   else if(wspolrzedna.x==0 && wspolrzedna.y==1) pole=3;
   else if(wspolrzedna.x==1 && wspolrzedna.y==1) pole=4;
   else if(wspolrzedna.x==2 && wspolrzedna.y==1) pole=5;
   else if(wspolrzedna.x==0 && wspolrzedna.y==2) pole=6;
   else if(wspolrzedna.x==1 && wspolrzedna.y==2) pole=7;
   else if(wspolrzedna.x==2 && wspolrzedna.y==2) pole=8;
   //else exit(1);

return pole;
}

void TKolko::postaw_kolko(int element)
{
POINT poz;
poz=element_na_wspolrzedne(element);
poz=wspolrzedne_na_wspolrzedne(poz);

        if(ilosc_kolek==0){
                Image2->Left=poz.x;
                Image2->Top=poz.y;
                Image2->Visible=true;}
        else if(ilosc_kolek==1){
                Image3->Left=poz.x;
                Image3->Top=poz.y;
                Image3->Visible=true;}
        else if(ilosc_kolek==2){
                Image4->Left=poz.x;
                Image4->Top=poz.y;
                Image4->Visible=true;}
        else if(ilosc_kolek==3){
                Image5->Left=poz.x;
                Image5->Top=poz.y;
                Image5->Visible=true;}
        else if(ilosc_kolek==4){
                Image6->Left=poz.x;
                Image6->Top=poz.y;
                Image6->Visible=true;}
ilosc_kolek++;
}

// ____________________________________________________________________
void TKolko::postaw_krzyzyk(int element)
{
POINT poz;
poz=element_na_wspolrzedne(element);
poz=wspolrzedne_na_wspolrzedne(poz);

        if(ilosc_krzyzykow==0){
                Image7->Left=poz.x;
                Image7->Top=poz.y;
                Image7->Visible=true;}
   else if(ilosc_krzyzykow==1){
                Image8->Left=poz.x;
                Image8->Top=poz.y;
                Image8->Visible=true;}
   else if(ilosc_krzyzykow==2){
                Image9->Left=poz.x;
                Image9->Top=poz.y;
                Image9->Visible=true;}
   else if(ilosc_krzyzykow==3){
                Image10->Left=poz.x;
                Image10->Top=poz.y;
                Image10->Visible=true;}
   else if(ilosc_krzyzykow==4){
                Image11->Left=poz.x;
                Image11->Top=poz.y;
                Image11->Visible=true;}

ilosc_krzyzykow++;
}