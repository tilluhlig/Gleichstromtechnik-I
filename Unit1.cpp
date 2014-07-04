//---------------------------------------------------------------------------

#include <vcl.h>
#include <stdlib.h>
#include <stdio.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
void Generate2();
void Generate3();
void Schalt (TStringList *list,int a,int b,int c,int d);
int Timer[3];
bool Count[3];

//---------------------------------------------------------------------------
void Generate(){
Timer[0]=60;
TImage *WImage[4] = {Form1->Image15,Form1->Image16,Form1->Image17,Form1->Image18};
TColor WColor[13] = {0,clSilver,0x000085A7,clBlack,0x00000541,clRed,25512736,clYellow,clLime,clBlue,clPurple,clGray,clWhite};
for (int i=0;i<4;i++){
int b;
if (i==0 || i==1){
b=rand() % 10+3;
}
else
if (i==2){
b=rand() % 12+1;
}
else
if (i==3){
int wer[8] = {0,1,2,4,5,8,9,10};
b=wer[rand() % 8];
}

if (b>0){
WImage[i]->Canvas->Brush->Color=WColor[b];
WImage[i]->Canvas->Rectangle(0,0,WImage[i]->Width,WImage[i]->Height);
WImage[i]->Show();
}
else{
WImage[i]->Hide();
WImage[i]->Canvas->Brush->Color=0;
WImage[i]->Canvas->Rectangle(0,0,WImage[i]->Width,WImage[i]->Height);
}
}
Count[0]=true;
}
  #include <math.hpp>
#include <Registry.hpp>
String CheckReg(String Bez,int Wert){
TRegistry *Registry = new TRegistry();
Registry->Access=KEY_ALL_ACCESS;
Registry->RootKey = HKEY_LOCAL_MACHINE;
Registry->OpenKey("SOFTWARE\\GT1",true);
if (Registry->ValueExists(Bez)==false){
Registry->WriteInteger(Bez,Wert);
return IntToStr(Wert);
}
else
{
int a = Registry->ReadInteger(Bez);
if (Wert>a){
Registry->WriteInteger(Bez,Wert);
return IntToStr(Wert);
}
else
return IntToStr(a);
}

}

__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
for (int i=0;i<3;i++){
Timer[i]=0;
Count[i]=true;
}

Form1->Left=0;
Form1->Top=0;
TImage *WImage[13] = {Form1->Image1,Form1->Image2,Form1->Image3,Form1->Image4,Form1->Image5,Form1->Image6,Form1->Image7,Form1->Image8,Form1->Image9,Form1->Image10,Form1->Image11,Form1->Image12,Form1->Image13};
TColor WColor[13] = {NULL,clSilver,0x000085A7,clBlack,0x00000541,clRed,0x000A5AF5,clYellow,clLime,clBlue,clPurple,clGray,clWhite};
for (int i=1;i<13;i++){
WImage[i]->Canvas->Brush->Color=WColor[i];
WImage[i]->Canvas->Rectangle(0,0,WImage[i]->Width,WImage[i]->Height);
}
randomize();
Generate();
Generate2();
Generate3();
Timer1->Enabled=true;

String a = CheckReg("Widerstand",0);
String b = CheckReg("Ohmsches",0);
String c = CheckReg("Schaltung",0);
Form1->TabSheet1->Caption="Widerstände ("+a+")";
Form1->TabSheet3->Caption="Ohmsches Gesetz ("+b+")";
Form1->TabSheet2->Caption="Schaltungen ("+c+")";
}
//---------------------------------------------------------------------------


void __fastcall TForm1::Button1Click(TObject *Sender)
{
Count[0]=false;
Button1->Hide();
Panel1->Show();
bool right=false;
bool right2=false;
TImage *WImage[4] = {Form1->Image15,Form1->Image16,Form1->Image17,Form1->Image18};
TColor WColor[13] = {clAqua,clSilver,0x000085A7,clBlack,0x00000541,clRed,0x000A5AF5,clYellow,clLime,clBlue,clPurple,clGray,clWhite};
float WFaktor[13] = {0,0.01,0.1,1,10,100,1000,10000,100000,1000000,10000000,100000000,1000000000};
String Toleranz[13] = {"20","10","5","-","1","2","-","-","0,5","0,25","0,1","-","-"};
String Wert="";
// Ziffern
for (int i=1;i<13;i++){
if (WImage[0]->Canvas->Pixels[1][1]==WColor[i]){
Wert+=IntToStr(i-3);
break;
}
}
for (int i=1;i<13;i++){
if (WImage[1]->Canvas->Pixels[1][1]==WColor[i]){
Wert+=IntToStr(i-3);
break;
}
}

String Verg[4];

for (int i=0;i<13;i++){
if (WImage[2]->Canvas->Pixels[1][1]==WColor[i]){
float a =(float) StrToFloat(Wert)*WFaktor[i];
//ShowMessage(Wert+"\n"+FloatToStr(a)+"\n"+FloatToStr(WFaktor[i])+"\n"+IntToStr(i));

if (a>=1000*1000*1000){
Wert=FloatToStr(RoundTo(a/1000/1000/1000,-4))+"G";
}
else
if (a>=1000*1000){
Wert=FloatToStr(RoundTo(a/1000/1000,-4))+"M";
}
else
if (a>=1000){
Wert=FloatToStr(RoundTo(a/1000,-4))+"k";
}
else
Wert=FloatToStr(RoundTo(a,-4));



Verg[0] = FloatToStr(RoundTo(a,-4));
Verg[1] = FloatToStr(RoundTo(a/1000,-4))+"k";
Verg[2] = FloatToStr(RoundTo(a/1000/1000,-4))+"M";
Verg[3] = FloatToStr(RoundTo(a/1000/1000/1000,-4))+"G";

break;
}
}

for (int i=1;i<13;i++){
if (Image18->Visible==false){
Label6->Caption=Toleranz[0]+"%";
break;
}
else
if (WImage[3]->Canvas->Pixels[1][1]==WColor[i]){
Label6->Caption=Toleranz[i]+"%";
break;
}
}

Label5->Caption=Wert;
if (Edit1->Text=="")Edit1->Text="0";
if (Edit2->Text=="")Edit2->Text="0";
for (int i=0;i<4;i++){
if (Edit1->Text.UpperCase()==Verg[i].UpperCase()){
right=true;
break;
}
}

if (Label6->Caption.UpperCase()==(Edit2->Text+"%").UpperCase())
right2=true;

if (right==true){
Label4->Caption="Richtig";
Label4->Font->Color=clLime;
Label5->Hide();
}
else{
Label4->Caption="Falsch";
Label4->Font->Color=clRed;
Label5->Show();
}

if (right2==true){
Label52->Caption="Richtig";
Label52->Font->Color=clLime;
Label6->Hide();
}
else{
Label52->Caption="Falsch";
Label52->Font->Color=clRed;
Label6->Show();
}

int Punkte=0;
if (right)
Punkte+=Timer[0]*3;

if (right2)
Punkte+=Timer[0];

if (Punkte<0)Punkte=0;
Label87->Caption=IntToStr(Punkte);

String a = CheckReg("Widerstand",Punkte);
Form1->TabSheet1->Caption="Widerstände ("+a+")";
}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{
Button1->Show();
Panel1->Hide();
Edit1->Clear();
Edit2->Clear();
Generate();
}
//---------------------------------------------------------------------------
AnsiString __fastcall IntToBinStr(const int AValue)
{
 AnsiString Result;
 for (int i = (sizeof(int) * 8) - 1; i >= 0; i--)
  Result += (AValue >> i) & 1;
 return Result;
}

#include <IdGlobal.hpp>
int typ[4];
int Maximal=0;
void Generate2(){
Timer[1]=600;
Form1->Label76->Caption="";
TImage *Not[12] = {Form1->Image33,Form1->Image34,Form1->Image35,Form1->Image36,Form1->Image37,Form1->Image38,Form1->Image39,Form1->Image40,Form1->Image41,Form1->Image42,Form1->Image43,Form1->Image44};
TImage *Ze[4] = {Form1->Image30,Form1->Image31,Form1->Image29,Form1->Image32};
TImage *Pic[3] = {Form1->Image47,Form1->Image48,Form1->Image49};
for (int i=0;i<12;i++){
int a = rand() % 2;
Not[i]->Visible=a;
}

for (int i=0;i<4;i++){
int a = rand() % 3;
// =
Ze[i]->Picture=Pic[a]->Picture;
typ[i]=a;
}
TStringGrid *G = Form1->StringGrid1;
String fill[6] = {"A","B","C","D","Q1","Q2"};
for (int i=0;i<6;i++)
G->Cells[i][0]=fill[i];


for (int i=0;i<16;i++){
G->Cells[4][i+1]="";
G->Cells[5][i+1]="";
}

for (int i=0;i<16;i++){
String a=IntToBinStr(i).SubString(29,4);
//ShowMessage(a);
G->Cells[0][i+1]=a.SubString(1,1);
G->Cells[1][i+1]=a.SubString(2,1);
G->Cells[2][i+1]=a.SubString(3,1);
G->Cells[3][i+1]=a.SubString(4,1);
}


TStringList *list = new TStringList();
Maximal=0;
for (int i=0;i<16;i++){
int a = StrToInt(G->Cells[0][1+i]);
int b = StrToInt(G->Cells[1][1+i]);
int c = StrToInt(G->Cells[2][1+i]);
int d = StrToInt(G->Cells[3][1+i]);
Schalt(list,a,b,c,d);
if (list->Strings[0]=="1")
Maximal++;
if (list->Strings[1]=="1")
Maximal++;
 list->Clear();
}
Form1->Label76->Caption=IntToStr(Maximal);
if (Maximal==0)
Generate2();

Count[1]=true;
}

void Generate3(){
Timer[2]=600;
TLabel *list[10] = {Form1->Label53,Form1->Label54,Form1->Label65,Form1->Label66,Form1->Label69,Form1->Label70,Form1->Label71,Form1->Label72,Form1->Label73,Form1->Label74};
for (int i=0;i<10;i++){
list[i]->Caption="";
}

TStringGrid *G = Form1->StringGrid2;
for (int i=0;i<11;i++){
for (int b=0;b<4;b++){
G->Cells[b][i]="";
}
}


G->Cells[0][0]="R (Ohm)";G->Cells[1][0]="U (V)";G->Cells[2][0]="I (mA)";G->Cells[3][0]="Ergebnis";
for (int i=0;i<10;i++){
int a = rand()%3;
G->Cells[a][i+1]="?";
}
for (int i=0;i<10;i++){
if (G->Cells[0][i+1]!="?"){
int a = rand()%1000+1;
G->Cells[0][i+1]=IntToStr(a);
}

if (G->Cells[1][i+1]!="?"){
int a = rand()%230+1;
G->Cells[1][i+1]=IntToStr(a);
}

if (G->Cells[2][i+1]!="?"){
int a = rand()%900+1;
G->Cells[2][i+1]=IntToStr(a);
}


}
Count[2]=true;
}


void __fastcall TForm1::Button6Click(TObject *Sender)
{
Panel3->Hide();
Button5->Show();
Generate2();
StringGrid1->Enabled=true;
}
//---------------------------------------------------------------------------
int NOT(int a){
if (a==0){
a=1;
}
else
a=0;
return a;
}

void Schalt (TStringList *list,int a,int b,int c,int d){
TImage *Verg[3] = {Form1->Image47,Form1->Image48,Form1->Image49};
int Kanal[4];
Kanal[0]=a;Kanal[1]=b;Kanal[2]=c;Kanal[3]=d;
int Ausg[2] = {0,0};
if (Form1->Image39->Visible)Kanal[0]=NOT(a);
if (Form1->Image40->Visible)Kanal[1]=NOT(b);
if (Form1->Image41->Visible)Kanal[2]=NOT(c);
if (Form1->Image42->Visible)Kanal[3]=NOT(d);
TImage *Pic[2] = {Form1->Image30,Form1->Image31};
int Use[2][2] = {{0,1},{2,3}};
// ShowMessage("a="+IntToStr(Kanal[0])+"\nb="+IntToStr(Kanal[1])+"\nc="+IntToStr(Kanal[2])+"\nd="+IntToStr(Kanal[3])+"\n");

// Erster Bereich
for (int i=0;i<2;i++){
int b = typ[i];
// ShowMessage(b);
if (b==0){
// EQU
if (Kanal[Use[i][0]]==Kanal[Use[i][1]]){
Ausg[i]=1;
}
else
Ausg[i]=0;
}
else
if (b==1){
// ODER
if (Kanal[Use[i][0]] || Kanal[Use[i][1]]){
Ausg[i]=1;
}
else
Ausg[i]=0;
}
else
if (b==2){
// UND
if (Kanal[Use[i][0]] && Kanal[Use[i][1]]){
Ausg[i]=1;
}
else
Ausg[i]=0;
}}

if (Form1->Image43->Visible)Ausg[0]=NOT(Ausg[0]);
if (Form1->Image44->Visible)Ausg[1]=NOT(Ausg[1]);
if (Form1->Image35->Visible)Ausg[1]=NOT(Ausg[1]);
if (Form1->Image36->Visible)Ausg[0]=NOT(Ausg[0]);

// Zweiter Bereich
Kanal[0]=a;
Kanal[1]=d;
if (Form1->Image33->Visible)Kanal[0]=NOT(Kanal[0]);
if (Form1->Image34->Visible)Kanal[1]=NOT(Kanal[1]);
Kanal[2]=Ausg[1];
Kanal[3]=Ausg[0];


Pic[0] = Form1->Image29;
Pic[1] = Form1->Image32;
int Use2[2][2] = {{0,2},{1,3}};
for (int i=0;i<2;i++){
int b = typ[i+2];
//ShowMessage(b);

if (b==0){
// EQU
if (Kanal[Use2[i][0]]==Kanal[Use2[i][1]]){
Ausg[i]=1;
}
else
Ausg[i]=0;
}
else
if (b==1){
// ODER
if (Kanal[Use2[i][0]] || Kanal[Use2[i][1]]){
Ausg[i]=1;
}
else
Ausg[i]=0;
}
else
if (b==2){
// UND
if (Kanal[Use2[i][0]] && Kanal[Use2[i][1]]){
Ausg[i]=1;
}
else
Ausg[i]=0;
}}



if (Form1->Image38->Visible)Ausg[0]=NOT(Ausg[0]);
if (Form1->Image37->Visible)Ausg[1]=NOT(Ausg[1]);
list->Add(Ausg[0]);
list->Add(Ausg[1]);

}

void __fastcall TForm1::Button5Click(TObject *Sender)
{
Count[1]=false;
Label76->Caption="0";
TStringGrid *G = Form1->StringGrid1;
Panel3->Show();
Button5->Hide();
//G->ColCount=8;
//G->FixedCols=7;
TStringList *erg[2];
erg[0] = new TStringList();
erg[1] = new TStringList();
TStringList *list = new TStringList();
for (int i=0;i<16;i++){
int a = StrToInt(G->Cells[0][1+i]);
int b = StrToInt(G->Cells[1][1+i]);
int c = StrToInt(G->Cells[2][1+i]);
int d = StrToInt(G->Cells[3][1+i]);
Schalt(list,a,b,c,d);
if (G->Cells[4][1+i]!=list->Strings[0]){
G->Cells[4][1+i]=list->Strings[0];
erg[0]->Add("0");
}
else
erg[0]->Add("1");

if (G->Cells[5][1+i]!=list->Strings[1]){
G->Cells[5][1+i]=list->Strings[1];
erg[1]->Add("0");
}
else
erg[1]->Add("1");


//Form1->StringGrid3->Canvas->Rectangle(0,0,10,10);
//Form1->StringGrid3->Canvas->Rectangle(0*21+15,(1+i)*20,1*21,(2+i)*20-15);


list->Clear();
}

G->Refresh();
int right=0;
int wrong=0;

for (int b=0;b<2;b++){
for (int i=0;i<16;i++){

if (erg[b]->Strings[i]=="1"){
Form1->StringGrid1->Canvas->Pen->Color=clGreen;
Form1->StringGrid1->Canvas->Brush->Color=clGreen;
right++;
}
else{
Form1->StringGrid1->Canvas->Pen->Color=clRed;
Form1->StringGrid1->Canvas->Brush->Color=clRed;
wrong++;
}
Form1->StringGrid1->Canvas->Rectangle((4+b)*21+15,(1+i)*20,(5+b)*21,(2+i)*20-15);
}
}
 StringGrid1->Enabled=false;
 int Punkte = Timer[1]*(right-wrong*4);

 if (Punkte<0)Punkte=0;
 Label29->Caption=IntToStr(Punkte);

 String a = CheckReg("Schaltung",Punkte);
Form1->TabSheet2->Caption="Schaltungen ("+a+")";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button3Click(TObject *Sender)
{
Count[2]=false;
TLabel *list[10] = {Form1->Label53,Form1->Label54,Form1->Label65,Form1->Label66,Form1->Label69,Form1->Label70,Form1->Label71,Form1->Label72,Form1->Label73,Form1->Label74};
Panel2->Show();
Button3->Hide();
int right=0;
int wrong=0;
TStringGrid *G = Form1->StringGrid2;
for (int i=0;i<10;i++){
if (G->Cells[0][1+i]=="?"){
// R berechnen
// R = U/I
double Erg = (double) StrToFloat(G->Cells[1][1+i]) / ((double) StrToFloat(G->Cells[2][1+i])/1000);
String verg=FloatToStr(RoundTo(Erg,-3));
if (G->Cells[3][1+i]==verg){
list[i]->Caption="V";
list[i]->Font->Color=clLime;
right++;
}
else
{
G->Cells[3][1+i]=verg;
list[i]->Caption="X";
list[i]->Font->Color=clRed;
wrong++;
}
}
else
if (G->Cells[1][1+i]=="?"){
// U berechnen
// U = R*I
double Erg = (double)StrToFloat(G->Cells[0][1+i]) * ((double) StrToFloat(G->Cells[2][1+i])/1000);
String verg=FloatToStr(RoundTo(Erg,-3));
if (G->Cells[3][1+i]==verg){
list[i]->Caption="V";
list[i]->Font->Color=clLime;
right++;
}
else
{
G->Cells[3][1+i]=verg;
list[i]->Caption="X";
list[i]->Font->Color=clRed;
wrong++;
}
}
else
if (G->Cells[2][1+i]=="?"){
// I berechnen
// I = U/R
double Erg = (double)StrToFloat(G->Cells[1][1+i]) /  StrToFloat(G->Cells[0][1+i])*1000;
String verg=FloatToStr(RoundTo(Erg,-3));
if (G->Cells[3][1+i]==verg){
list[i]->Caption="V";
list[i]->Font->Color=clLime;
right++;
}
else
{
G->Cells[3][1+i]=verg;
list[i]->Caption="X";
list[i]->Font->Color=clRed;
wrong++;
}
}
}

int Punkte=Timer[2]*(right-wrong);
if (Punkte<0)Punkte=0;
Label85->Caption=IntToStr(Punkte);
String a = CheckReg("Ohmsches",Punkte);
Form1->TabSheet3->Caption="Ohmsches Gesetz ("+a+")";
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button4Click(TObject *Sender)
{
Generate3();
Panel2->Hide();
Button3->Show();
}
//---------------------------------------------------------------------------


void Hilfe_akt(){
Form1->PageControl1->Hide();
Form1->Memo4->Show();
Form1->Label24->Show();
Form1->Label24->BringToFront();
Form1->Memo4->Clear();
Form1->Memo4->Left=10;
Form1->Memo4->Top=25;
Form1->Memo4->Height=Form1->PageControl1->Height-50;
Form1->Memo4->Width=Form1->PageControl1->Width-20;
Form1->SpeedButton2->Show();
Form1->SpeedButton2->BringToFront();
Form1->SpeedButton2->Top=Form1->PageControl1->Height-25;
Form1->SpeedButton2->Left=Form1->PageControl1->Width/2-Form1->SpeedButton2->Width/2;
Form1->Label24->Top=1;
}

void __fastcall TForm1::SpeedButton1Click(TObject *Sender)
{
Hilfe_akt();
Label24->Caption="Widerstände";
Label24->AutoSize=true;
Label24->Left=PageControl1->Width/2-Label24->Width/2;
Memo4->Lines->AddStrings(Memo5->Lines);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton2Click(TObject *Sender)
{
PageControl1->Show();
Memo4->Hide();
SpeedButton2->Hide();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton3Click(TObject *Sender)
{
Hilfe_akt();
Label24->Caption="Ohmsches Gesetz";
Label24->AutoSize=true;
Label24->Left=PageControl1->Width/2-Label24->Width/2;
Memo4->Lines->AddStrings(Memo6->Lines);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::SpeedButton4Click(TObject *Sender)
{
Hilfe_akt();
Label24->Caption="Schaltungen";
Label24->AutoSize=true;
Label24->Left=PageControl1->Width/2-Label24->Width/2;
Memo4->Lines->AddStrings(Memo7->Lines);
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
TLabel *list[3] = {Label83,Label79,Label81};
for (int i=0;i<3;i++){
if (Count[i]==true){
if (Timer[i]>0){
Timer[i]--;
if (list[i]!=NULL){
String add="";
if (Timer[i]<100)
add+="0";
if (Timer[i]<10)
add+="0";

list[i]->Caption=add+IntToStr(Timer[i])+" Sekunden";
}
}
}
}
}
//---------------------------------------------------------------------------

void __fastcall TForm1::StringGrid1Click(TObject *Sender)
{
TStringGrid *G = StringGrid1;

if (G->Cells[G->Selection.Left][G->Selection.Top]=="0"){
G->Cells[G->Selection.Left][G->Selection.Top]="1";
Label76->Caption=IntToStr(StrToInt(Label76->Caption)-1);
}
else{
if (G->Cells[G->Selection.Left][G->Selection.Top]=="1")
Label76->Caption=IntToStr(StrToInt(Label76->Caption)+1);
G->Cells[G->Selection.Left][G->Selection.Top]="0";
}
}
//---------------------------------------------------------------------------


