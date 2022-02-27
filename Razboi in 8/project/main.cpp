#include <iostream>
#include <fstream>
#include <graphics.h>
#include <windows.h>
#include "mmsystem.h"
using namespace std;
FILE* pFile=fopen("Matr.txt","r+");
FILE* NumeJucator1=fopen("NumeJucator1.txt","r+");
FILE* NumeJucator2=fopen("NumeJucator2.txt","r+");
bool joc_pe_negru,joc_pe_alb=1;
int culoare[4]= {15,0,4,1},culoare_jucator_1=culoare[0],culoare_jucator_2=culoare[1];
bool inceput;
bool muta_primul_jucator=1;
int mutari_de_inceput=8;
int stanga,sus,width,height,latura, numar;
int nr_piese_jucator_1, nr_piese_jucator_2;
int TablaDeJoc[9][9];
char scor_1[2], scor_2[2];
void Menu();
void Game();
void SettingsMenu();
void HelpMenu();
void deseneazaPiesa(int linia, int coloana, int culoare);
void mutarePiesa(int jucator);
void eliminare_piese();
void resetare_matrice();
void salvare_matrice();
void salvare_nume_jucatori();
void dreptunghi_jucator_1_negru();
void dreptunghi_jucator_1_alb();
void dreptunghi_jucator_1_rosu();
void dreptunghi_jucator_1_albastru();
void dreptunghi_jucator_2_negru();
void dreptunghi_jucator_2_alb();
void dreptunghi_jucator_2_rosu();
void dreptunghi_jucator_2_albastru();
void dreptunghi_culoare_joc_alb();
void dreptunghi_culoare_joc_negru();
void dreptunghi_volum_0();
void dreptunghi_volum_1();
void dreptunghi_volum_2();
void dreptunghi_volum_3();
void dreptunghi_volum_4();
void scrie_setari();
void citesteSir(char s[40],int x, int y);
void Setari_nume_1();
void Setari_nume_2();
char SirSpatii[]="                     ";
char*NumeleJucatorilor="Numele Jucatorilor:";
char*SchimbaNumeleJucatorului1="Schimba numele Jucatorului 1";
char*SchimbaNumeleJucatorului2="Schimba numele Jucatorului 2";
char*ReseteazaScorul="Reseteaza scorul";
char*Back="Back";
char*Reset="Reset";
char*RandulJucatorului1="Este randul jucatorului 1";
char*RandulJucatorului2="Este randul jucatorului 2";
char*JocTerminat="Jocul s-a terminat";
char*Remiza="Remiza";
char*Castigat1="Castigator: Jucatorul 1";
char*Castigat2="Castigator: Jucatorul 2";
char*RazboiIn8="Razboi in 8";
char*Play="Play";
char*Reguli="Reguli";
char*Exit="Exit";
char*SetariMeniu="Setari";
char*MutareImposibila="Mutare imposibila!";
char*Setari="-Setari-";
char*SelectatiCuloareaJucatorului1="Selectati culoarea jucatorului 1:";
char*SelectatiCuloareaJucatorului2="Selectati culoarea jucatorului 2:";
char*AlbNegruRosuAlbastru="ALB     NEGRU       ROSU       ALBASTRU";
char*Alb="ALB";
char*AlbSpatiu="ALB     ";
char*AlbNegru="ALB     NEGRU";
char*AlbNegruSpatiu="ALB     NEGRU       ";
char*AlbNegruRosu="ALB     NEGRU       ROSU";
char*AlbNegruRosuSpatiu="ALB     NEGRU       ROSU       ";
char*CuloareaJocului="Selectati culoarea pe care se va desfasura jocul:";
char*Volum0="0";
char*Volum01234="0   1   2   3   4";
char*Volum0Spatiu="0   ";
char*Volum01="0   1";
char*Volum01Spatiu="0   1   ";
char*Volum012="0   1   2";
char*Volum012Spatiu="0   1   2   ";
char*Volum0123="0   1   2   3";
char*Volum0123Spatiu="0   1   2   3   ";
char*Volum="Volum:";
char Nume1[100]=" ";
char Nume2[100]=" ";
int volum=1;
int scor1=1;
int scor2=1;
char Scor1[3];
char Scor2[3];
char*Scor="Scor";
char*Cratima="-";
int main()
{
    initwindow(1000,700,RazboiIn8);
    for(int i=0; i<=9; i++)
    {
        TablaDeJoc[0][i]=TablaDeJoc[i][0]=TablaDeJoc[9][i]=TablaDeJoc[i][9]=3;
    }
    volum=0;
    inceput=1;
    fseek(pFile,0, SEEK_SET);
    fseek(NumeJucator1,0, SEEK_SET);
    fseek(NumeJucator2,0, SEEK_SET);
    for(int linie=1; linie<=8; linie++)
        for(int coloana=1; coloana<=8; coloana++)
            fscanf(pFile,"%d",&TablaDeJoc[linie][coloana]);
    fscanf(pFile,"%d",&culoare_jucator_1);
    fscanf(pFile,"%d",&culoare_jucator_2);
    fscanf(pFile,"%d",&joc_pe_alb);
    fscanf(pFile,"%d",&joc_pe_negru);
    fscanf(pFile,"%d",&nr_piese_jucator_1);
    fscanf(pFile,"%d",&nr_piese_jucator_2);
    fscanf(pFile,"%d",&scor1);
    fscanf(pFile,"%d",&scor2);
    fscanf(pFile,"%d",&mutari_de_inceput);
    fscanf(pFile,"%d",&muta_primul_jucator);
    fscanf(pFile,"%d",&inceput);
    fscanf(NumeJucator1,"%s",&Nume1);
    fscanf(NumeJucator2,"%s",&Nume2);
    Menu();
}
void Menu()
{
    cleardevice();
    setcolor(15);
    int y=75;
    int font=1;
    int mijlX=getmaxx()/2;
    settextstyle(font,HORIZ_DIR,7);
    outtextxy(mijlX-textwidth(RazboiIn8)/2,y,RazboiIn8);
    settextstyle(font,HORIZ_DIR,5);
    outtextxy(mijlX-textwidth(Play)/2,y+150,Play);
    outtextxy(mijlX-textwidth(SetariMeniu)/2,y+250,SetariMeniu);
    outtextxy(mijlX-textwidth(Reguli)/2,y+350,Reguli);
    outtextxy(mijlX-textwidth(Exit)/2,y+450,Exit);
    rectangle(mijlX-textwidth(Reguli)/2-2,y+150,mijlX+textwidth(Reguli)/2+2,y+textheight(Reguli)+150);
    rectangle(mijlX-textwidth(Reguli)/2-2,y+250,mijlX+textwidth(Reguli)/2+2,y+textheight(Reguli)+250);
    rectangle(mijlX-textwidth(Reguli)/2-2,y+350,mijlX+textwidth(Reguli)/2+2,y+textheight(Reguli)+350);
    rectangle(mijlX-textwidth(Reguli)/2-2,y+450,mijlX+textwidth(Reguli)/2+2,y+textheight(Reguli)+450);
    int coordonate[16];
    coordonate[1]=mijlX-textwidth(Reguli)/2-2;
    coordonate[2]=y+150;
    coordonate[3]=mijlX+textwidth(Reguli)/2+2;
    coordonate[4]=y+textheight(Reguli)+150;
    coordonate[5]=mijlX-textwidth(Reguli)/2-2;
    coordonate[6]=y+250;
    coordonate[7]=mijlX+textwidth(Reguli)/2+2;
    coordonate[8]=y+textheight(Reguli)+250;
    coordonate[9]=mijlX-textwidth(Reguli)/2-2;
    coordonate[10]=y+350;
    coordonate[11]=mijlX+textwidth(Reguli)/2+2;
    coordonate[12]=y+textheight(Reguli)+350;
    coordonate[13]=mijlX-textwidth(Reguli)/2-2;
    coordonate[14]=y+450;
    coordonate[15]=mijlX+textwidth(Reguli)/2+2;
    coordonate[16]=y+textheight(Reguli)+450;
    int x;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(), y=mousey();
        }
        if(x>=coordonate[1]&&y>=coordonate[2]&&x<=coordonate[3]&&y<=coordonate[4])
        {
            cleardevice();
            Game();
        }
        else if(x>=coordonate[5]&&y>=coordonate[6]&&x<=coordonate[7]&&y<=coordonate[8])
        {
            cleardevice();
            SettingsMenu();
        }
        else if(x>=coordonate[9]&&y>=coordonate[10]&&x<=coordonate[11]&&y<=coordonate[12])
        {
            cleardevice();
            HelpMenu();
        }
        else if(x>=coordonate[13]&&y>=coordonate[14]&&x<=coordonate[15]&&y<=coordonate[16])
        {
            exit(0);
        }
    }
}
void Game()
{
    int x,y;
    setcolor(15);
    readimagefile("tabla_joc.jpg",0,0,700,getmaxy());
    settextstyle(1,HORIZ_DIR,4);
    outtextxy(getmaxx()-textwidth(Back),getmaxy()-textheight(Back),Back);
    outtextxy(703,getmaxy()-textheight(Reset),Reset);
    numar=8;
    width=600;
    height=600;
    latura=width/numar;
    sus=50;
    stanga=50;
    int linia,coloana;
    if(inceput==1)
    {
        muta_primul_jucator=1;
        resetare_matrice();
        inceput=0;
    }
    else
    {
        for(linia=1; linia<=numar; linia++)
            for(coloana=1; coloana<=numar; coloana++)
            {
                if(TablaDeJoc[linia][coloana]==1)
                    deseneazaPiesa(linia,coloana,culoare_jucator_1);
                else if(TablaDeJoc[linia][coloana]==2)
                    deseneazaPiesa(linia,coloana,culoare_jucator_2);
            }
    }
    do
    {
        if(muta_primul_jucator)
        {
            mutarePiesa(1);
            muta_primul_jucator=0;
            salvare_matrice();
            salvare_nume_jucatori();
            muta_primul_jucator=1;
        }
        else
            muta_primul_jucator=1;
        if(nr_piese_jucator_2==0||((nr_piese_jucator_1==nr_piese_jucator_2)&&(nr_piese_jucator_1==1)))
            break;
        if(inceput==0)
        {
            mutarePiesa(2);
            salvare_matrice();
            salvare_nume_jucatori();
        }
    }
    while ((nr_piese_jucator_1 >0&& nr_piese_jucator_2 >0)&&(nr_piese_jucator_1!=1||nr_piese_jucator_2!=1));
    inceput=1;
    setcolor(0);
    outtextxy(705,getmaxy()/8,RandulJucatorului1);
    outtextxy(705,getmaxy()-getmaxy()/8,RandulJucatorului2);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(850-textwidth(Nume1)/2,getmaxy()/8+textheight(RandulJucatorului1)+2,Nume1);
    outtextxy(850-textwidth(Nume2)/2,getmaxy()-getmaxy()/8+textheight(RandulJucatorului2),Nume2);
    setcolor(15);
    settextstyle(1,HORIZ_DIR,3);
    outtextxy(705,getmaxy()/4,JocTerminat);
    settextstyle(1,HORIZ_DIR,1);
    outtextxy(850-textwidth(ReseteazaScorul)/2,getmaxy()/5,ReseteazaScorul);
    if(nr_piese_jucator_2==nr_piese_jucator_1)
        outtextxy(803,getmaxy()/2,Remiza);
    else if(nr_piese_jucator_2==0)
    {
        outtextxy(710,getmaxy()/2,Castigat1);
        outtextxy(850-textwidth(Nume1)/2,getmaxy()/2+textheight(Castigat1)+2,Nume1);
        scor1++;
    }
    else
    {
        outtextxy(710,getmaxy()/2,Castigat2);
        outtextxy(850-textwidth(Nume2)/2,getmaxy()/2+textheight(Castigat2)+2,Nume2);
        scor2++;
    }
    salvare_matrice();
    settextstyle(1,HORIZ_DIR,3);
    itoa(scor1-1,Scor1,10);
    itoa(scor2-1,Scor2,10);
    outtextxy(850-textwidth(Scor)/2,getmaxy()/8,Scor);
    outtextxy(850-textwidth(Scor)/2,getmaxy()/8+textheight(Alb),Scor1);
    outtextxy(850-textwidth(Cratima)/2,getmaxy()/8+textheight(Alb),Cratima);
    outtextxy(850+textwidth(Scor)/2-textwidth(Scor2),getmaxy()/8+textheight(Alb),Scor2);
    settextstyle(1,HORIZ_DIR,3);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {

            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            settextstyle(1,HORIZ_DIR,1);
            if(x>=850-textwidth(ReseteazaScorul)/2&&y>=getmaxy()/5&&x<=850+textwidth(ReseteazaScorul)/2&&y<=getmaxy()/5+textheight(ReseteazaScorul))
            {
                settextstyle(1,HORIZ_DIR,3);
                scor1=1;
                scor2=1;
                salvare_matrice();
                itoa(scor1-1,Scor1,10);
                itoa(scor2-1,Scor2,10);
                outtextxy(850-textwidth(Scor)/2,getmaxy()/8+textheight(Alb),Scor1);
                outtextxy(850+textwidth(Scor)/2-textwidth(Scor2),getmaxy()/8+textheight(Alb),Scor2);
            }
            settextstyle(1,HORIZ_DIR,4);
            if(x>=getmaxx()-textwidth(Back)&&x<=getmaxx()&&y>=getmaxy()-textheight(Back)&&y<=getmaxy())
            {
                resetare_matrice();
                cleardevice();
                Menu();
            }
            if(x>=700&&y>=getmaxy()-textheight(Reset)&&x<=700+textwidth(Reset)&&y<=getmaxy())
            {
                resetare_matrice();
                salvare_matrice();
                cleardevice();
                Game();
            }
        }
    }
}
void SettingsMenu()
{
    int x,y;
    int font=1;
    y=50;
    int mijlX=getmaxx()/2;
    scrie_setari();
    settextstyle(font,HORIZ_DIR,1);
    y=0;
    int coordonate[70];
    coordonate[0]=mijlX-textwidth(AlbNegruRosuAlbastru)/2;
    coordonate[1]=y+200-3;
    coordonate[2]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(Alb)+2;
    coordonate[3]=y+200+textheight(Alb)+3;
    coordonate[4]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3+textwidth(AlbSpatiu);
    coordonate[5]=y+200-3;
    coordonate[6]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(AlbNegru)+3;
    coordonate[7]=y+200+textheight(Alb)+3;
    coordonate[8]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3+textwidth(AlbNegruSpatiu);
    coordonate[9]=y+200-3;
    coordonate[10]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(AlbNegruRosu)+3;
    coordonate[11]=y+200+textheight(Alb)+3;
    coordonate[12]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3+textwidth(AlbNegruRosuSpatiu);
    coordonate[13]=y+200-3;
    coordonate[14]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(AlbNegruRosuAlbastru)+3;
    coordonate[15]=y+200+textheight(Alb)+3;
    coordonate[16]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    coordonate[17]=y+300-3;
    coordonate[18]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(Alb)+3;
    coordonate[19]=y+300+textheight(Alb)+3;
    coordonate[20]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3+textwidth(AlbSpatiu);
    coordonate[21]=y+300-3;
    coordonate[22]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(AlbNegru)+3;
    coordonate[23]=y+300+textheight(Alb)+3;
    coordonate[24]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3+textwidth(AlbNegruSpatiu);
    coordonate[25]=y+300-3;
    coordonate[26]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(AlbNegruRosu)+3;
    coordonate[27]=y+300+textheight(Alb)+3;
    coordonate[28]=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3+textwidth(AlbNegruRosuSpatiu);
    coordonate[29]=y+300-3;
    coordonate[30]=mijlX-textwidth(AlbNegruRosuAlbastru)/2+textwidth(AlbNegruRosuAlbastru)+3;
    coordonate[31]=y+300+textheight(Alb)+3;
    coordonate[33]=mijlX-textwidth(AlbNegru)/2-3;
    coordonate[34]=y+400-3;
    coordonate[35]=mijlX-textwidth(AlbNegru)/2+textwidth(Alb)+3;
    coordonate[36]=y+textheight(Alb)+400+3;
    coordonate[37]=mijlX-textwidth(AlbNegru)/2-3+textwidth(AlbSpatiu);
    coordonate[38]=y+400-3;
    coordonate[39]=mijlX-textwidth(AlbNegru)/2+textwidth(AlbNegru)+3;
    coordonate[40]=y+textheight(Alb)+400+3;
    coordonate[41]=mijlX-textwidth(Volum01234)/2-2;
    coordonate[42]=y+500-2;
    coordonate[43]=mijlX-textwidth(Volum01234)/2+textwidth(Volum0)+2;
    coordonate[44]=y+500+textwidth(Volum0)+2;
    coordonate[45]=mijlX-textwidth(Volum01234)/2+textwidth(Volum0Spatiu)-2;
    coordonate[46]=y+500-2;
    coordonate[47]=mijlX-textwidth(Volum01234)/2+textwidth(Volum01)+2;
    coordonate[48]=y+500+textwidth(Volum0)+2;
    coordonate[49]=mijlX-textwidth(Volum01234)/2+textwidth(Volum01Spatiu)-2;
    coordonate[50]=y+500-2;
    coordonate[51]=mijlX-textwidth(Volum01234)/2+textwidth(Volum012)+2;
    coordonate[52]=y+500+textwidth(Volum0)+2;
    coordonate[53]=mijlX-textwidth(Volum01234)/2+textwidth(Volum012Spatiu)-2;
    coordonate[54]=y+500-2;
    coordonate[55]=mijlX-textwidth(Volum01234)/2+textwidth(Volum0123)+2;
    coordonate[56]=y+500+textwidth(Volum0)+2;
    coordonate[57]=mijlX-textwidth(Volum01234)/2+textwidth(Volum0123Spatiu)-2;
    coordonate[58]=y+500-2;
    coordonate[59]=mijlX-textwidth(Volum01234)/2+textwidth(Volum01234)+2;
    coordonate[60]=y+500+textwidth(Volum0)+2;
    coordonate[61]=mijlX-textwidth(SchimbaNumeleJucatorului1)/2;
    coordonate[62]=y+600;
    coordonate[63]=mijlX-textwidth(SchimbaNumeleJucatorului1)/2+textwidth(SchimbaNumeleJucatorului1);
    coordonate[64]=y+600+textheight(Alb);
    coordonate[65]=mijlX-textwidth(SchimbaNumeleJucatorului2)/2;
    coordonate[66]=y+625;
    coordonate[67]=mijlX-textwidth(SchimbaNumeleJucatorului2)/2+textwidth(SchimbaNumeleJucatorului2);
    coordonate[68]=y+625+textheight(Alb);
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(), y=mousey();
            if(x>=coordonate[0]&&y>=coordonate[1]&&x<=coordonate[2]&&y<=coordonate[3]&&culoare_jucator_2!=culoare[0])
            {
                culoare_jucator_1=culoare[0];
                dreptunghi_jucator_1_alb();
                salvare_matrice();
            }
            else if(x>=coordonate[4]&&y>=coordonate[5]&&x<=coordonate[6]&&y<=coordonate[7]&&culoare_jucator_2!=culoare[1])
            {
                culoare_jucator_1=culoare[1];
                dreptunghi_jucator_1_negru();
                salvare_matrice();
            }
            else if(x>=coordonate[8]&&y>=coordonate[9]&&x<=coordonate[10]&&y<=coordonate[11]&&culoare_jucator_2!=culoare[2])
            {
                culoare_jucator_1=culoare[2];
                dreptunghi_jucator_1_rosu();
                salvare_matrice();
            }
            else if(x>=coordonate[12]&&y>=coordonate[13]&&x<=coordonate[14]&&y<=coordonate[15]&&culoare_jucator_2!=culoare[3])
            {
                culoare_jucator_1=culoare[3];
                dreptunghi_jucator_1_albastru();
                salvare_matrice();
            }
            if(x>=coordonate[16]&&y>=coordonate[17]&&x<=coordonate[18]&&y<=coordonate[19]&&culoare_jucator_1!=culoare[0])
            {
                culoare_jucator_2=culoare[0];
                dreptunghi_jucator_2_alb();
                salvare_matrice();
            }
            else if(x>=coordonate[20]&&y>=coordonate[21]&&x<=coordonate[22]&&y<=coordonate[23]&&culoare_jucator_1!=culoare[1])
            {
                culoare_jucator_2=culoare[1];
                dreptunghi_jucator_2_negru();
                salvare_matrice();
            }
            else if(x>=coordonate[24]&&y>=coordonate[25]&&x<=coordonate[26]&&y<=coordonate[27]&&culoare_jucator_1!=culoare[2])
            {
                culoare_jucator_2=culoare[2];
                dreptunghi_jucator_2_rosu();
                salvare_matrice();
            }
            else if(x>=coordonate[28]&&y>=coordonate[29]&&x<=coordonate[30]&&y<=coordonate[31]&&culoare_jucator_1!=culoare[3])
            {
                culoare_jucator_2=culoare[3];
                dreptunghi_jucator_2_albastru();
                setcolor(0);
                salvare_matrice();
            }

            else if(x>=coordonate[33]&&y>=coordonate[34]&&x<=coordonate[35]&&y<=coordonate[36])
            {
                if(joc_pe_negru)
                {
                    inceput=1;
                    muta_primul_jucator=1;
                }
                joc_pe_alb=1;
                joc_pe_negru=0;
                dreptunghi_culoare_joc_alb();
                salvare_matrice();
            }
            else if(x>=coordonate[37]&&y>=coordonate[38]&&x<=coordonate[39]&&y<=coordonate[40])
            {
                if(joc_pe_alb)
                {
                    inceput=1;
                    muta_primul_jucator=1;
                }
                joc_pe_negru=1;
                joc_pe_alb=0;
                dreptunghi_culoare_joc_negru();
                salvare_matrice();
            }
            else if(x>=coordonate[41]&&y>=coordonate[42]&&x<=coordonate[43]&&y<=coordonate[44])
            {
                dreptunghi_volum_0();
                volum=0;
                PlaySound(NULL,NULL,0);
            }
            else if(x>=coordonate[45]&&y>=coordonate[46]&&x<=coordonate[47]&&y<=coordonate[48])
            {
                dreptunghi_volum_1();
                volum=1;
                PlaySound("volum1.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(x>=coordonate[49]&&y>=coordonate[50]&&x<=coordonate[51]&&y<=coordonate[52])
            {
                dreptunghi_volum_2();
                volum=2;
                PlaySound("volum2.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(x>=coordonate[53]&&y>=coordonate[54]&&x<=coordonate[55]&&y<=coordonate[56])
            {
                dreptunghi_volum_3();
                volum=3;
                PlaySound("volum3.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(x>=coordonate[57]&&y>=coordonate[58]&&x<=coordonate[59]&&y<=coordonate[60])
            {
                dreptunghi_volum_4();
                volum=4;
                PlaySound("volum4.wav",NULL,SND_LOOP|SND_ASYNC);
            }
            else if(x>=coordonate[61]&&y>=coordonate[62]&&x<=coordonate[63]&&y<=coordonate[64])
            {
                cleardevice();
                Setari_nume_1();
            }
            else if(x>=coordonate[65]&&y>=coordonate[66]&&x<=coordonate[67]&&y<=coordonate[68])
            {
                cleardevice();
                Setari_nume_2();
            }
            else
            {
                settextstyle(1,HORIZ_DIR,4);
                if(x>=getmaxx()-textwidth(Back)&&x<=getmaxx()&&y>=getmaxy()-textheight(Back)&&y<=getmaxy())
                {
                    cleardevice();
                    Menu();
                }
                settextstyle(1,HORIZ_DIR,1);
            }
        }
    }
}
void HelpMenu()
{
    int font=1;
    setcolor(15);
    settextstyle(font,HORIZ_DIR,4);
    int y=75;
    readimagefile("Reguli.jpg",0,0,1000,700);
    outtextxy(getmaxx()-textwidth(Back),getmaxy()-textheight(Back),Back);
    int x;
    while(1)
    {
        if(ismouseclick(WM_LBUTTONDOWN))
        {
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex(), y=mousey();
        }
        if(x>=getmaxx()-textwidth(Back)&&x<=getmaxx()&&y>=getmaxy()-textheight(Back)&&y<=getmaxy())
        {
            cleardevice();
            Menu();
        }
    }
}
void deseneazaPiesa(int linia, int coloana, int culoare)
{
    int x1, y1, x2, y2;
    int xmijloc, ymijloc;
    x1=stanga+latura*(coloana-1);
    y1=sus+latura*(linia-1);
    x2=x1+latura;
    y2=y1+latura;
    xmijloc=(x1+x2)/2;
    ymijloc=(y1+y2)/2;
    setcolor(culoare);
    setfillstyle(SOLID_FILL,culoare);
    fillellipse(xmijloc,ymijloc,30,30);
}
void mutarePiesa(int jucator)
{
    for(int i=0; i<=9; i++)
    {
        TablaDeJoc[0][i]=TablaDeJoc[i][0]=TablaDeJoc[9][i]=TablaDeJoc[i][9]=3;
    }
    if(jucator==1)
    {
        setcolor(15);
        settextstyle(1,HORIZ_DIR,1);
        outtextxy(705,getmaxy()/8,RandulJucatorului1);
        outtextxy(850-textwidth(Nume1)/2,getmaxy()/8+textheight(RandulJucatorului1)+2,Nume1);
        setcolor(0);
        outtextxy(705,getmaxy()-getmaxy()/8,RandulJucatorului2);
        outtextxy(850-textwidth(Nume2)/2,getmaxy()-getmaxy()/8+textheight(RandulJucatorului2),Nume2);
    }
    else
    {
        setcolor(0);
        settextstyle(1,HORIZ_DIR,1);
        outtextxy(705,getmaxy()/8,RandulJucatorului1);
        outtextxy(850-textwidth(Nume1)/2,getmaxy()/8+textheight(RandulJucatorului1)+2,Nume1);
        setcolor(15);
        outtextxy(705,getmaxy()-getmaxy()/8,RandulJucatorului2);
        outtextxy(850-textwidth(Nume2)/2,getmaxy()-getmaxy()/8+textheight(RandulJucatorului2),Nume2);
    }
    int ok=1;
    int linia1,coloana1,linia2,coloana2,x,y;
    int click=false;
    do
        if(ismouseclick(WM_LBUTTONDOWN)&& !click)
        {
            click=true;
            clearmouseclick(WM_LBUTTONDOWN);
            x=mousex();
            y=mousey();
            linia1=(y-sus)/latura+1;
            coloana1=(x-stanga)/latura+1;
            if(TablaDeJoc[linia1][coloana1]==0||TablaDeJoc[linia1][coloana1]!=jucator)
                click=false;
            setcolor(BLACK);
            settextstyle(1,HORIZ_DIR,1);
            outtextxy(getmaxx()-(getmaxx()-700)/2-textwidth(MutareImposibila)/2,getmaxy()/2,MutareImposibila);
            settextstyle(1,HORIZ_DIR,4);
            if(x>=getmaxx()-textwidth(Back)&&x<=getmaxx()&&y>=getmaxy()-textheight(Back)&&y<=getmaxy())
            {
                if(jucator==2)
                    muta_primul_jucator=0;
                cleardevice();
                Menu();
            }
            if(x>=703&&y>=getmaxy()-textheight(Reset)&&x<=703+textwidth(Reset)&&y<=getmaxy())
            {
                resetare_matrice();
                inceput=1;
                ok=0;
                break;
            }
        }
    while (!click);
    if(ok)
    {
        inceput=0;
        click=false;
        do
            if(ismouseclick(WM_LBUTTONDOWN) && !click)
            {
                click=true;
                clearmouseclick(WM_LBUTTONDOWN);
                x=mousex();
                y=mousey();
                linia2=(y-sus)/latura+1;
                coloana2=(x-stanga)/latura+1;
                settextstyle(1,HORIZ_DIR,4);
                if(x>=getmaxx()-textwidth(Back)&&x<=getmaxx()&&y>=getmaxy()-textheight(Back)&&y<=getmaxy())
                {
                    if(jucator==2)
                        muta_primul_jucator=0;
                    cleardevice();
                    Menu();
                }
                else if(x>=703&&y>=getmaxy()-textheight(Reset)&&x<=703+textwidth(Reset)&&y<=getmaxy())
                {
                    resetare_matrice();
                    inceput=1;
                    ok=0;
                    break;
                }
                else if(x>703)
                    click=false;
                else if((((TablaDeJoc[linia2][coloana2]!=0))||linia2>linia1+1||linia2<linia1-1||coloana2>coloana1+1||coloana2<coloana1-1)||((linia2==linia1+1&&coloana2==coloana1)||(linia2==linia1-1&&coloana2==coloana1)||(linia2==linia1&&coloana2==coloana1-1)||(linia2==linia1&&coloana2==coloana1+1)))
                {
                    if(x<=703)
                    {
                        setcolor(15);
                        settextstyle(1,HORIZ_DIR,1);
                        outtextxy(getmaxx()-(getmaxx()-700)/2-textwidth(MutareImposibila)/2,getmaxy()/2,MutareImposibila);
                        setcolor(0);
                        mutarePiesa(jucator);
                    }
                    ok=0;
                }
            }
        while(!click);
    }
    if(ok)
    {
        inceput=0;
        setcolor(0);
        outtextxy(705,getmaxy()/2,MutareImposibila);
        TablaDeJoc[linia1][coloana1]=0;
        TablaDeJoc[linia2][coloana2]=jucator;
        if(joc_pe_negru)
            deseneazaPiesa(linia1,coloana1,RGB(152,92,56));
        else
            deseneazaPiesa(linia1,coloana1,RGB(215,182,129));
        if(jucator==1)
            deseneazaPiesa(linia2,coloana2,culoare_jucator_1);
        else
            deseneazaPiesa(linia2,coloana2,culoare_jucator_2);
        if(mutari_de_inceput==1)
        {
            eliminare_piese();
        }
        else if(mutari_de_inceput>=0)
            mutari_de_inceput--;
    }
    for(int k=0; k<=9; k++)
    {
        for(int k1=0; k1<=9; k1++)
        {
            cout<<TablaDeJoc[k][k1]<<' ';
        }
        cout<<endl;
    }
    cout<<endl<<endl;
}
void resetare_matrice()
{
    readimagefile("tabla_joc.jpg",0,0,700,getmaxy());
    int linie, coloana;
    for(linie=1; linie<=numar; linie++)
        for(coloana=1; coloana<=numar; coloana++)
        {
            if(TablaDeJoc[linie][coloana])
            {
                TablaDeJoc[linie][coloana]=0;
            }
        }
    if(joc_pe_alb)
    {
        for (int i=1; i<=numar; i++)
            if(i%2)
            {
                TablaDeJoc[1][i]=1;
                TablaDeJoc[numar-1][i]=2;
                deseneazaPiesa(1,i,culoare_jucator_1);
                deseneazaPiesa(numar-1,i,culoare_jucator_2);
            }
            else
            {
                TablaDeJoc[2][i]=1;
                TablaDeJoc[numar][i]=2;
                deseneazaPiesa(2,i,culoare_jucator_1);
                deseneazaPiesa(numar,i,culoare_jucator_2);
            }
    }
    else if(joc_pe_negru)
    {
        for (int i=1; i<=numar; i++)
            if(i%2)
            {
                TablaDeJoc[2][i]=1;
                TablaDeJoc[numar][i]=2;
                deseneazaPiesa(2,i,culoare_jucator_1);
                deseneazaPiesa(numar,i,culoare_jucator_2);
            }
            else
            {
                TablaDeJoc[1][i]=1;
                TablaDeJoc[numar-1][i]=2;
                deseneazaPiesa(1,i,culoare_jucator_1);
                deseneazaPiesa(numar-1,i,culoare_jucator_2);
            }
    }
    nr_piese_jucator_1=8;
    nr_piese_jucator_2=8;
    mutari_de_inceput=8;
}
void eliminare_piese()
{
    for(int linie=1; linie<=numar; linie++)
        for(int coloana=1; coloana<=numar; coloana++)
        {
            if(TablaDeJoc[linie][coloana]!=0)
                if(TablaDeJoc[linie-1][coloana-1]!=0)
                    if(TablaDeJoc[linie-1][coloana+1]!=0)
                        if(TablaDeJoc[linie+1][coloana-1]!=0)
                            if(TablaDeJoc[linie+1][coloana+1]!=0)
                            {
                                if(TablaDeJoc[linie][coloana]==1)
                                {
                                    nr_piese_jucator_1--;
                                }
                                else
                                {
                                    nr_piese_jucator_2--;
                                }
                                TablaDeJoc[linie][coloana]=0;
                                if(joc_pe_alb)
                                    deseneazaPiesa(linie,coloana,RGB(215,182,129));
                                else
                                    deseneazaPiesa(linie,coloana,RGB(152,92,56));
                            }
        }
}
void salvare_matrice()
{
    fseek(pFile,0, SEEK_SET);
    int linie, coloana;
    for(linie=1; linie<=8; linie++)
        for(coloana=1; coloana<=8; coloana++)
            fprintf(pFile,"%d\n",TablaDeJoc[linie][coloana]);
    fprintf(pFile,"%d\n",culoare_jucator_1);
    fprintf(pFile,"%d\n",culoare_jucator_2);
    fprintf(pFile,"%d\n",joc_pe_alb);
    fprintf(pFile,"%d\n",joc_pe_negru);
    fprintf(pFile,"%d\n",nr_piese_jucator_1);
    fprintf(pFile,"%d\n",nr_piese_jucator_2);
    fprintf(pFile,"%d\n",scor1);
    fprintf(pFile,"%d\n",scor2);
    fprintf(pFile,"%d\n",mutari_de_inceput);
    fprintf(pFile,"%d\n",muta_primul_jucator);
    fprintf(pFile,"%d\n",inceput);
}
void salvare_nume_jucatori()
{
    fseek(NumeJucator1,0, SEEK_SET);
    fseek(NumeJucator2,0, SEEK_SET);
    fprintf(NumeJucator1,"%s",SirSpatii);
    fprintf(NumeJucator2,"%s",SirSpatii);
    fseek(NumeJucator1,0, SEEK_SET);
    fseek(NumeJucator2,0, SEEK_SET);
    fprintf(NumeJucator1,"%s",Nume1);
    fprintf(NumeJucator2,"%s",Nume2);

}
void scrie_setari()
{
    int y;
    int font=1;
    y=50;
    int mijlX=getmaxx()/2;
    setcolor(15);
    settextstyle(font,HORIZ_DIR,7);
    outtextxy(mijlX-textwidth(Setari)/2,y,Setari);
    settextstyle(font,HORIZ_DIR,2);
    y=0;
    outtextxy(mijlX-textwidth(SelectatiCuloareaJucatorului1)/2,y+150,SelectatiCuloareaJucatorului1);
    outtextxy(mijlX-textwidth(SelectatiCuloareaJucatorului2)/2,y+250,SelectatiCuloareaJucatorului2);
    outtextxy(mijlX-textwidth(CuloareaJocului)/2,y+350,CuloareaJocului);
    outtextxy(mijlX-textwidth(Volum)/2,y+450,Volum);
    outtextxy(mijlX-textwidth(NumeleJucatorilor)/2,y+550,NumeleJucatorilor);
    settextstyle(font,HORIZ_DIR,1);
    outtextxy(mijlX-textwidth(AlbNegruRosuAlbastru)/2,y+200,AlbNegruRosuAlbastru);
    outtextxy(mijlX-textwidth(AlbNegruRosuAlbastru)/2,y+300,AlbNegruRosuAlbastru);
    outtextxy(mijlX-textwidth(AlbNegru)/2,y+400,AlbNegru);
    outtextxy(mijlX-textwidth(Volum01234)/2,y+500,Volum01234);
    outtextxy(mijlX-textwidth(SchimbaNumeleJucatorului1)/2,y+600,SchimbaNumeleJucatorului1);
    outtextxy(mijlX-textwidth(SchimbaNumeleJucatorului2)/2,y+625,SchimbaNumeleJucatorului2);
    settextstyle(font,HORIZ_DIR,2);
    settextstyle(1,HORIZ_DIR,4);
    outtextxy(getmaxx()-textwidth(Back),getmaxy()-textheight(Back),Back);
    if(culoare_jucator_1==culoare[0])
        dreptunghi_jucator_1_alb();
    else if(culoare_jucator_1==culoare[1])
        dreptunghi_jucator_1_negru();
    else if(culoare_jucator_1==culoare[2])
        dreptunghi_jucator_1_rosu();
    else if(culoare_jucator_1==culoare[3])
        dreptunghi_jucator_1_albastru();
    if(culoare_jucator_2==culoare[0])
        dreptunghi_jucator_2_alb();
    else if(culoare_jucator_2==culoare[1])
        dreptunghi_jucator_2_negru();
    else if(culoare_jucator_2==culoare[2])
        dreptunghi_jucator_2_rosu();
    else if(culoare_jucator_2==culoare[3])
        dreptunghi_jucator_2_albastru();
    if(joc_pe_alb)
        dreptunghi_culoare_joc_alb();
    else
        dreptunghi_culoare_joc_negru();
    if(volum==0)
        dreptunghi_volum_0();
    else if(volum==1)
        dreptunghi_volum_1();
    else if(volum==2)
        dreptunghi_volum_2();
    else if(volum==3)
        dreptunghi_volum_3();
    else if(volum==4)
        dreptunghi_volum_4();
}
void dreptunghi_jucator_1_alb()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=200-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(15);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
    setcolor(15);
}
void dreptunghi_jucator_1_negru()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=200-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
    setcolor(15);
}
void dreptunghi_jucator_1_rosu()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=200-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
    setcolor(15);
}
void dreptunghi_jucator_1_albastru()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=200-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
  //  setcolor(0);
    setcolor(15);
}
void dreptunghi_jucator_2_alb()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=300-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(15);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
    setcolor(15);
}
void dreptunghi_jucator_2_negru()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=300-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
    setcolor(15);
}
void dreptunghi_jucator_2_rosu()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=300-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
    setcolor(15);
}
void dreptunghi_jucator_2_albastru()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=300-3;
    int y2=y1+textheight(Volum0)+3+3;
    int x1=mijlX-textwidth(AlbNegruRosuAlbastru)/2-3;
    int x2=mijlX-textwidth(AlbNegruRosuAlbastru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    rectangle(x1+textwidth(AlbNegruSpatiu),y1,x2+textwidth(AlbNegruRosu),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbNegruRosuSpatiu),y1,x2+textwidth(AlbNegruRosuAlbastru),y2);
   // setcolor(0);
    setcolor(15);
}
void dreptunghi_culoare_joc_alb()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=400-3;
    int y2=y1+textheight(Alb)+3+3;
    int x1=mijlX-textwidth(AlbNegru)/2-3;
    int x2=mijlX-textwidth(AlbNegru)/2+3;
    setcolor(15);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    setcolor(0);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
    setcolor(15);
}
void dreptunghi_culoare_joc_negru()
{
    settextstyle(1,HORIZ_DIR,1);
    int mijlX=getmaxx()/2;
    int y1=400-3;
    int y2=y1+textheight(Alb)+3+3;
    int x1=mijlX-textwidth(AlbNegru)/2-3;
    int x2=mijlX-textwidth(AlbNegru)/2+3;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Alb),y2);
    setcolor(15);
    rectangle(x1+textwidth(AlbSpatiu),y1,x2+textwidth(AlbNegru),y2);
}
void dreptunghi_volum_0()
{
    int mijlX=getmaxx()/2;
    int x1=mijlX-textwidth(Volum01234)/2-2;
    int x2=mijlX-textwidth(Volum01234)/2+2;
    int y1=500-2;
    int y2=500+textwidth(Volum0)+2;
    setcolor(15);
    rectangle(x1,y1,x2+textwidth(Volum0)+2,y2);
    setcolor(0);
    rectangle(x1+textwidth(Volum0Spatiu)-2,y1,x2+textwidth(Volum01),y2);
    rectangle(x1+textwidth(Volum01Spatiu)-2,y1,x2+textwidth(Volum012),y2);
    rectangle(x1+textwidth(Volum012Spatiu)-2,y1,x2+textwidth(Volum0123),y2);
    rectangle(x1+textwidth(Volum0123Spatiu)-2,y1,x2+textwidth(Volum01234),y2);
    setcolor(15);
}
void dreptunghi_volum_1()
{
    int mijlX=getmaxx()/2;
    int x1=mijlX-textwidth(Volum01234)/2-2;
    int x2=mijlX-textwidth(Volum01234)/2+2;
    int y1=500-2;
    int y2=500+textwidth(Volum0)+2;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Volum0)+2,y2);
    setcolor(15);
    rectangle(x1+textwidth(Volum0Spatiu)-2,y1,x2+textwidth(Volum01),y2);
    setcolor(0);
    rectangle(x1+textwidth(Volum01Spatiu)-2,y1,x2+textwidth(Volum012),y2);
    rectangle(x1+textwidth(Volum012Spatiu)-2,y1,x2+textwidth(Volum0123),y2);
    rectangle(x1+textwidth(Volum0123Spatiu)-2,y1,x2+textwidth(Volum01234),y2);
    setcolor(15);
}
void dreptunghi_volum_2()
{
    int mijlX=getmaxx()/2;
    int x1=mijlX-textwidth(Volum01234)/2-2;
    int x2=mijlX-textwidth(Volum01234)/2+2;
    int y1=500-2;
    int y2=500+textwidth(Volum0)+2;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Volum0)+2,y2);
    rectangle(x1+textwidth(Volum0Spatiu)-2,y1,x2+textwidth(Volum01),y2);
    setcolor(15);
    rectangle(x1+textwidth(Volum01Spatiu)-2,y1,x2+textwidth(Volum012),y2);
    setcolor(0);
    rectangle(x1+textwidth(Volum012Spatiu)-2,y1,x2+textwidth(Volum0123),y2);
    rectangle(x1+textwidth(Volum0123Spatiu)-2,y1,x2+textwidth(Volum01234),y2);
    setcolor(15);
}
void dreptunghi_volum_3()
{
    int mijlX=getmaxx()/2;
    int x1=mijlX-textwidth(Volum01234)/2-2;
    int x2=mijlX-textwidth(Volum01234)/2+2;
    int y1=500-2;
    int y2=500+textwidth(Volum0)+2;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Volum0)+2,y2);
    rectangle(x1+textwidth(Volum0Spatiu)-2,y1,x2+textwidth(Volum01),y2);
    rectangle(x1+textwidth(Volum01Spatiu)-2,y1,x2+textwidth(Volum012),y2);
    setcolor(15);
    rectangle(x1+textwidth(Volum012Spatiu)-2,y1,x2+textwidth(Volum0123),y2);
    setcolor(0);
    rectangle(x1+textwidth(Volum0123Spatiu)-2,y1,x2+textwidth(Volum01234),y2);
    setcolor(15);
}
void dreptunghi_volum_4()
{
    int mijlX=getmaxx()/2;
    int x1=mijlX-textwidth(Volum01234)/2-2;
    int x2=mijlX-textwidth(Volum01234)/2+2;
    int y1=500-2;
    int y2=500+textwidth(Volum0)+2;
    setcolor(0);
    rectangle(x1,y1,x2+textwidth(Volum0)+2,y2);
    rectangle(x1+textwidth(Volum0Spatiu)-2,y1,x2+textwidth(Volum01),y2);
    rectangle(x1+textwidth(Volum01Spatiu)-2,y1,x2+textwidth(Volum012),y2);
    rectangle(x1+textwidth(Volum012Spatiu)-2,y1,x2+textwidth(Volum0123),y2);
    setcolor(15);
    rectangle(x1+textwidth(Volum0123Spatiu)-2,y1,x2+textwidth(Volum01234),y2);
}
void citesteSir(char s[20],int x, int y)
{
    strcpy(s,"");
    char s1[20];
    char t[2];
    char tasta;
    t[0]=tasta;
    t[1]='\0';
    strcat(s,t);
    s[0]='\0';
    strcpy(s1,s);
    strcat(s1,"_");
    setcolor(WHITE);
    outtextxy(x,y,s1);
    do
    {
        tasta=getch();
        if (tasta==8)
        {
            if (strlen(s)>0)
            {
                setcolor(BLACK);
                strcpy(s1,s);
                strcat(s1,"_");
                outtextxy(x,y,s1);
                s[strlen(s)-1]='\0';
                strcpy(s1,s);
                strcat(s1,"_");
                outtextxy(x,y,s1);
                setcolor(WHITE);
                outtextxy(x,y,s1);
            }
        }
        else if (tasta!=13&&tasta!=32&&strlen(s)<=15)
        {
            t[0]=tasta;
            t[1]='\0';
            strcat(s,t);
            strcpy(s1,s);
            strcat(s1,"_");
            setcolor(WHITE);
            outtextxy(x,y,s1);
        }
    }
    while (tasta!=13);
    strcat(s1,"_");
    setcolor(BLACK);
    outtextxy(x,y,s1);
    setcolor(WHITE);
}
void Setari_nume_1()
{
    readimagefile("SetariNume1.jpg",0,0,getmaxx(),getmaxy());
    settextstyle(1,HORIZ_DIR,4);
    citesteSir(Nume1,270,320);
    char paranteza1[20]="(";
    char paranteza2[20]=")";
    if(strlen(Nume1)>=1)
    {
        strcat(paranteza1,Nume1);
        strcpy(Nume1,paranteza1);
        strcat(Nume1,paranteza2);
        salvare_nume_jucatori();
    }
    cleardevice();
    SettingsMenu();

}
void Setari_nume_2()
{
    readimagefile("SetariNume2.jpg",0,0,getmaxx(),getmaxy());
    settextstyle(1,HORIZ_DIR,4);
    citesteSir(Nume2,270,320);
    char paranteza1[2]="(";
    char paranteza2[2]=")";
    if(strlen(Nume2)>=1)
    {
        strcat(paranteza1,Nume2);
        strcpy(Nume2,paranteza1);
        strcat(Nume2,paranteza2);
        salvare_nume_jucatori();
    }
    cleardevice();
    SettingsMenu();
}
