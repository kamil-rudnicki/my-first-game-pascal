const plus_niesk  =  1000;
const minus_niesk = -1000;
int GLEBOKOSC_OK=1000;
struct POLE{int val; int gracz;};
struct KANDYDACI{
	int   cpt;
	int   tbl[9];
	};

// ____________________________________________________________________
int KoniecGry(KTO plansza[9])
{
int a,b,c,d,e,f,g,h;

// sukces w linii?

a=((plansza[0]==plansza[1])&&(plansza[1]==plansza[2]) && (plansza[0]!=nic));
b=((plansza[3]==plansza[4])&&(plansza[4]==plansza[5]) && (plansza[3]!=nic));
c=((plansza[6]==plansza[7])&&(plansza[7]==plansza[8]) && (plansza[6]!=nic));

// sukces w kolumnie?

d=((plansza[0]==plansza[3])&&(plansza[3]==plansza[6]) && (plansza[0]!=nic));
e=((plansza[1]==plansza[4])&&(plansza[4]==plansza[7]) && (plansza[1]!=nic));
f=((plansza[2]==plansza[5])&&(plansza[5]==plansza[8]) && (plansza[2]!=nic));

// sukces na przek¹tnej

g=((plansza[0]==plansza[4])&&(plansza[4]==plansza[8]) && (plansza[0]!=nic));
h=((plansza[2]==plansza[4])&&(plansza[4]==plansza[6]) && (plansza[2]!=nic));

//if (!(a||b||c||d||e||f||g||h)) return 0;

if (a) return 1;    // robimy to aby wiedzieæ kto wygra³
if (b) return 3;
if (c) return 6;
if (d) return 3;
if (e) return 4;
if (f) return 5;
if (g) return 4;
if (h) return 4;
return 0;
}


// ____________________________________________________________________
int LiniaPusta(int Line,KTO plansza[9])
{
return ((plansza[(Line-1)*3]==nic) && (plansza[(Line-1)*3+1]==nic) && (plansza[(Line-1)*3+2]==nic));
}
// ____________________________________________________________________
int KolumnaPusta(int Col,KTO plansza[9])
{
return ((plansza[Col-1]==nic) && (plansza[(Col-1)+3]==nic) && (plansza[(Col-1)+6]==nic));
}
// ____________________________________________________________________
int LiniaPelna(int Line,KTO plansza[9])
{
return !((plansza[(Line-1)*3]==nic) || (plansza[(Line-1)*3+1]==nic) || (plansza[(Line-1)*3+2]==nic));
}
// ____________________________________________________________________
int KolumnaPelna(int Col,KTO plansza[9])
{
return !((plansza[Col-1]==nic) || (plansza[(Col-1)+3]==nic) || (plansza[(Col-1)+6]==nic));
}
// ____________________________________________________________________
int Przekatna1_Pusta(KTO plansza[9])
{
return ((plansza[0]==nic) && (plansza[4]==nic) && (plansza[8]==nic));
}
// ____________________________________________________________________
int Diag1_Full (KTO plansza[9])
{
return !((plansza[0]==nic) || (plansza[4]==nic) || (plansza[8]==nic));
}
// ____________________________________________________________________
int Diag2_Empty(KTO plansza[9])
{
return ((plansza[2]==nic) && (plansza[4]==nic) && (plansza[6]==nic));
}
// ____________________________________________________________________
int Diag2_Full (KTO plansza[9])
{
return !((plansza[2]==nic) || (plansza[4]==nic) || (plansza[6]==nic));
}
// ____________________________________________________________________
int Ewaluacja(KTO plansza[9],KTO gracz)
//
{
int val=0;
int result=KoniecGry(plansza);

if(result)
{
        if (plansza[result]==Nastepny_Gracz(gracz)) return minus_niesk;   			// pozycja wygrywaj¹ca dla przeciwnika
	else return  plus_niesk;    			// pozycja wygrywaj¹ca dla nas
}

        for(int Line=1;Line<=3;Line++)
  	 if (!(LiniaPusta(Line,plansza) || LiniaPelna(Line,plansza)))
	 {
	        if ((plansza[(Line-1)*3]==Nastepny_Gracz(gracz)) || (plansza[(Line-1)*3+1]==Nastepny_Gracz(gracz)) || (plansza[(Line-1)*3+2]==Nastepny_Gracz(gracz))) val-=1;
	        if ((plansza[(Line-1)*3]==gracz) || (plansza[(Line-1)*3+1]==gracz) || (plansza[(Line-1)*3+2]==gracz)) val+=1;
	 }

        for(int Col=1;Col<=3;Col++)
  	 if (!(KolumnaPusta(Col,plansza) || KolumnaPelna(Col,plansza)))
	 {
	        if ((plansza[Col-1]==Nastepny_Gracz(gracz)) || (plansza[(Col-1)+3]==Nastepny_Gracz(gracz)) || (plansza[(Col-1)+6]==Nastepny_Gracz(gracz))) val-=1;
	        if ((plansza[Col-1]==gracz) || (plansza[(Col-1)+3]==gracz) || (plansza[(Col-1)+6]==gracz)) val+=1;
	 }

        if (!(Przekatna1_Pusta(plansza)||Diag1_Full(plansza)))
	{
 	        if ((plansza[0]==Nastepny_Gracz(gracz)) || (plansza[4]==Nastepny_Gracz(gracz)) || (plansza[8]==Nastepny_Gracz(gracz))) val=val-1;
 	        if ((plansza[0]==gracz) || (plansza[4]==gracz) || (plansza[8]==gracz)) val+=1;
	};

	if (!(Diag2_Empty(plansza)||Diag2_Full(plansza)))
	{
 	        if ((plansza[2]==Nastepny_Gracz(gracz)) || (plansza[4]==Nastepny_Gracz(gracz)) || (plansza[6]==Nastepny_Gracz(gracz))) val-=1;
                if ((plansza[2]==gracz) || (plansza[4]==gracz) || (plansza[6]==gracz)) val+=1;
        };

return val;
}

KANDYDACI generuj_ruchy(KTO tab[9])
{
KANDYDACI t;
 t.cpt=-1;
 for(int i=0;i<9;i++)
 if (tab[i]==nic)
	  t.tbl[++t.cpt]=i; // zapamiêtanie wolnej pozycji
return t;
}

POLE Minimax(KTO gracz, int glebokosc, KTO plansza[9])
{
KANDYDACI kandydaci=generuj_ruchy(plansza);
POLE best;

if(glebokosc==GLEBOKOSC_OK || kandydaci.cpt==-1){
	best.gracz=-1;
	best.val=Ewaluacja(plansza, gracz);
        return best;
}

best.val=-1000;
int v;

for(int i=0; i<=kandydaci.cpt; i++)
{
	plansza[kandydaci.tbl[i]]=gracz;
	v=-Minimax(Nastepny_Gracz(gracz), glebokosc+1, plansza).val;
	if(v>best.val){
		best.gracz=kandydaci.tbl[i];
		best.val=v;
	}
	plansza[kandydaci.tbl[i]]=nic;
}

return best;
}

