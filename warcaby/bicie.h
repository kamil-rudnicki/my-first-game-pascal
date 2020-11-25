extern nr_pionka_bialego1, nr_pionka_czarnego1;
extern zbitych[];

void TWarcaby::bicie_bialy()
{
zbitych[0]++;
Label15->Caption=IntToStr(zbitych[0]);
if(nr_pionka_bialego1==0) Image2->Visible=FALSE;
else if(nr_pionka_bialego1==1) Image3->Visible=FALSE;
else if(nr_pionka_bialego1==2) Image4->Visible=FALSE;
else if(nr_pionka_bialego1==3) Image5->Visible=FALSE;
else if(nr_pionka_bialego1==4) Image6->Visible=FALSE;
else if(nr_pionka_bialego1==5) Image7->Visible=FALSE;
else if(nr_pionka_bialego1==6) Image8->Visible=FALSE;
else if(nr_pionka_bialego1==7) Image9->Visible=FALSE;
else if(nr_pionka_bialego1==8) Image10->Visible=FALSE;
else if(nr_pionka_bialego1==9) Image11->Visible=FALSE;
else if(nr_pionka_bialego1==10) Image12->Visible=FALSE;
else if(nr_pionka_bialego1==11) Image13->Visible=FALSE;
   if(Image2->Visible==FALSE && Image6->Visible==FALSE && Image10->Visible==FALSE &&
      Image3->Visible==FALSE && Image7->Visible==FALSE && Image11->Visible==FALSE &&
      Image4->Visible==FALSE && Image8->Visible==FALSE && Image12->Visible==FALSE &&
      Image5->Visible==FALSE && Image9->Visible==FALSE && Image13->Visible==FALSE){
      ShowMessage("Gratulacje, wygra³ gracz zielony!");
      plansza_inicjuj();
      }
}

void TWarcaby::bicie_czarny()
{
zbitych[1]++;
Label16->Caption=IntToStr(zbitych[1]);
if(nr_pionka_czarnego1==0) Image14->Visible=FALSE;
else if(nr_pionka_czarnego1==1) Image15->Visible=FALSE;
else if(nr_pionka_czarnego1==2) Image16->Visible=FALSE;
else if(nr_pionka_czarnego1==3) Image17->Visible=FALSE;
else if(nr_pionka_czarnego1==4) Image18->Visible=FALSE;
else if(nr_pionka_czarnego1==5) Image19->Visible=FALSE;
else if(nr_pionka_czarnego1==6) Image20->Visible=FALSE;
else if(nr_pionka_czarnego1==7) Image21->Visible=FALSE;
else if(nr_pionka_czarnego1==8) Image22->Visible=FALSE;
else if(nr_pionka_czarnego1==9) Image23->Visible=FALSE;
else if(nr_pionka_czarnego1==10) Image24->Visible=FALSE;
else if(nr_pionka_czarnego1==11) Image25->Visible=FALSE;

   if(Image14->Visible==FALSE && Image18->Visible==FALSE && Image22->Visible==FALSE &&
      Image15->Visible==FALSE && Image19->Visible==FALSE && Image23->Visible==FALSE &&
      Image16->Visible==FALSE && Image20->Visible==FALSE && Image24->Visible==FALSE &&
      Image17->Visible==FALSE && Image21->Visible==FALSE && Image25->Visible==FALSE){
      ShowMessage("Gratulacje, wygra³ gracz zó³ty!");
      plansza_inicjuj();
      }

}