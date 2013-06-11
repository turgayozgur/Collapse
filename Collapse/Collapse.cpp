// Collapse.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <windows.h>
using namespace std;

HANDLE hcon = GetStdHandle(STD_OUTPUT_HANDLE);
void gotoxy(int,int);
void menu(void);
char secim,devam;
char maxPuan[8];
int bip,sayac=1;
FILE *dosya;

class Collapse{
private:
	char maxPuan[8];
protected:
	int str,stn;
public:
	Collapse(){
		str=0;
		stn=0;
	}
	struct bListe{
	char c;
	unsigned int isaret;
	bListe *sag, *sol, *alt, *ust;
	};
	bListe *ilk[16], *son[16], *gecici, *gecici2, *on, *arka;

	void getCOLLAPSE(void);
	void getBaslik(void);
	void setMaxPuan(int);
	int getMaxPuan(void);
	void yardim(void);
	~Collapse(){}
};
void Collapse::getCOLLAPSE(void){
	gotoxy(30,12); Sleep(100);
	SetConsoleTextAttribute(hcon,49); Beep(550,120); cout << "C  "; Sleep(110);
	SetConsoleTextAttribute(hcon,52); Beep(550,120); cout << "O  "; Sleep(110);
	SetConsoleTextAttribute(hcon,62); Beep(550,120); cout << "L  "; Sleep(110);
	SetConsoleTextAttribute(hcon,58); Beep(550,120); cout << "L  "; Sleep(110);
	SetConsoleTextAttribute(hcon,49); Beep(550,120); cout << "A  "; Sleep(110);
	SetConsoleTextAttribute(hcon,62); Beep(550,120); cout << "P  "; Sleep(110);
	SetConsoleTextAttribute(hcon,52); Beep(550,120); cout << "S  "; Sleep(110);
	SetConsoleTextAttribute(hcon,58); Beep(550,120); cout << "E  "; Sleep(110);
	SetConsoleTextAttribute(hcon,63); Sleep(1000);
} 
void Collapse::getBaslik(void){
	cout << "\n****************************|   ";
	SetConsoleTextAttribute(hcon,49); cout << "C ";
	SetConsoleTextAttribute(hcon,52); cout << "O ";
	SetConsoleTextAttribute(hcon,62); cout << "L ";
	SetConsoleTextAttribute(hcon,58); cout << "L ";
	SetConsoleTextAttribute(hcon,49); cout << "A ";
	SetConsoleTextAttribute(hcon,62); cout << "P ";
	SetConsoleTextAttribute(hcon,52); cout << "S ";
	SetConsoleTextAttribute(hcon,58); cout << "E ";
	SetConsoleTextAttribute(hcon,63);
	cout << "   |****************************\n"; 
}
void Collapse::setMaxPuan(int max){
	_itoa_s(max,maxPuan,10);// max icindeki int degeri maxPuan'a char olarak 10luk tabanda yazar.
	fopen_s(&dosya,"puan.txt","w");
    fprintf(dosya,"%s",maxPuan);
	fclose(dosya);
}
int Collapse::getMaxPuan(void){
	if((fopen_s(&dosya,"puan.txt","r"))==NULL){//fopen_s dosyayý acarsa NULL dondurur.
		fscanf(dosya,"%s",maxPuan);
		fclose(dosya);
		return atoi(maxPuan);
	}
	else return -1;
}
void Collapse::yardim(void){
	getBaslik();
	cout << "\n\n\t" << (char)260 << " Collapse bir strateji oyunudur.\n\n\t"<< (char)260 <<" Amac ekranda yanyana yada ust uste gelen ayni rekten kutulardan\n  herhangi birini secerek yok etmektir.\n\n";
	cout << "\t" << (char)260 << " Bu oyunda secme, secilecek elemanin satir ve sutun sayilarinin\n  girilmesiyle saglanir.\n\n";
	cout << "\t" << (char)260 << " Dogru ya da yanlis her 3 hamlenizden sonra ekranin alt kisimdan\n  yeni bir satir eklenir.\n\n";
	cout << "\t" << (char)260 << " Renkli kutucuklardan herhangi biri ust kisma degerse oyun biter.\n\n";
	SetConsoleTextAttribute(hcon,52); cout << "\t\t\t\tIyi Oyunlar!\n"; SetConsoleTextAttribute(hcon,63);
}

class Bilesen: public Collapse{
private:
	int randomSayi;
public:
	Bilesen();
	char randomHarf(void);
	void bagAyarla(void);
	void bagla(char);
	void goruntule(void);
	~Bilesen(){}
};
Bilesen::Bilesen(){
	randomSayi=0;
}
char Bilesen::randomHarf(void){
	randomSayi=rand() % 10 + 1;//1-10 arasýnda sayýlar üretir.
	if(randomSayi<4) return ('A');
	else if(randomSayi>=4 && randomSayi<6) return ('B');
	else if(randomSayi>=6 && randomSayi<8) return ('C');
	else return ('D');
}
void Bilesen::bagAyarla(void){
	for(int i=0;i<8;i++){//15 stun 10 satir olacak.
		for(int j=0;j<15;j++){
			bagla(randomHarf());
			stn++;
		}
		stn=0;
		str++;
	}
}
void Bilesen::bagla(char chr){
	gecici=(bListe*)malloc(sizeof(bListe));
	gecici->c=chr;
	gecici->isaret=0;
	if(str==0){//ilk satir baglanýyorsa,
		if(ilk[0]==NULL){
			gecici->alt=NULL; gecici->ust=NULL; gecici->sag=NULL; gecici->sol=NULL; 
			ilk[0]=gecici;
			son[0]=ilk[0];
		}
		else{
			gecici->alt=NULL; gecici->ust=NULL; gecici->sag=NULL; gecici->sol=son[0]; son[0]->sag=gecici;
			son[0]=gecici;
		}
	}
	else{//1. satýrý baglama islemi bitmis ise,
		if(ilk[str]==NULL){
			gecici->alt=ilk[str-1]; ilk[str-1]->ust=gecici; gecici->ust=NULL; gecici->sag=NULL; gecici->sol=son[str];
			ilk[str]=gecici;
			son[str]=ilk[str];
			gecici2=ilk[str-1];//gecici2, bir alt satýrin baglantýlarý için yardýmcý olacak.
		}
		else{
			gecici2=gecici2->sag;
			gecici->alt=gecici2; gecici2->ust=gecici;//alt satir baglantisi. 
			gecici->ust=NULL; gecici->sag=NULL; gecici->sol=son[str]; son[str]->sag=gecici;
			son[str]=gecici;
		}
	}
}
void Bilesen::goruntule(void){
	int i;
	cout << "\n\t\t\t -------------------------------\n";
	for(i=0;i<15-str;i++) cout<<"\t\t\t|\t\t\t\t|\n";
	i=str-1;
	while(ilk[i]!=NULL){
		SetConsoleTextAttribute(hcon,63);
		cout << "\t\t" << i+1 << "\t| ";
		gecici=ilk[i];
		while(gecici!=NULL){
			if(gecici->c!='-' && gecici->c!='+'){
				if(gecici->c=='A') SetConsoleTextAttribute(hcon,49);
				else if(gecici->c=='B') SetConsoleTextAttribute(hcon,52);
				else if(gecici->c=='C') SetConsoleTextAttribute(hcon,62);
				else if(gecici->c=='D') SetConsoleTextAttribute(hcon,58);
				cout << (char)254;
			}
			else cout << " ";
				cout << " ";
			gecici=gecici->sag;
		}
		SetConsoleTextAttribute(hcon,63); cout << "|" << endl;
		i--;
	}
	SetConsoleTextAttribute(hcon,63);
	cout << "\t\t\t -------------------------------\n\t\t\t  ";
	for(i=0;i<15;i++) if(i<9) cout << i+1 << " ";
					  else cout << i-9 << " ";	
	cout << "\n\n";
}

class Oyun: public Bilesen{
private:
	int x,y,eslesen,puan;
public:
	Oyun();
	void setSatir(void);
	void setStun(void);
	void setPuan(void);
	int getPuan(void);
	void puanHesapla(int);
	int getEslesen(void);
	void konumlan(void);
	void kontrol(bListe*);//silme olup olmayacagýný kontrol edecek.
	bool kontrolEslesen(void);
	void setIsaret(void);//bListe->isaret elemanýný 0'lar.
	void icerikDuzenle(void);
	void harfleriDegistir(bListe*);
	void stunKontrol(void);
	void stunBirlestir(bListe*);
	void yeniSatir(void);
	void yeniSatirBagla(char,int);
	void yeniSatirEkle(void);
	bool bitisKontrol(void);
	bool satirKontrol(void);
	void satirYoket(void);
	~Oyun(){
		int i=0;
		while(ilk[i]!=NULL){
		gecici=ilk[i];
		while(gecici!=NULL){
			gecici2=gecici;
			gecici=gecici->sag;
			free(gecici2);
		}
		ilk[i]=NULL;
		son[i]=NULL;
		gecici=NULL;
		gecici2=NULL;
		i++;
		}
		str=0;
		stn=0;
	}
};
Oyun::Oyun(){
	x=0;
	y=0;
	eslesen=0;
	puan=0;
}
void Oyun::setSatir(void){
	cout << "\t\tsatir : "; cin >> y;
	if(y<=str && y>0) y=y-1;
	else y=0;
}
void Oyun::setStun(void){
	cout << "\t\tsutun : "; cin >> x;
	if(x<=15 && x>0) x=x-1;//stun elemanlarýnda her zaman 15 eleman bulunur. 
	else x=0;
}
void Oyun::setPuan(void){
	puan=0;
}
int Oyun::getPuan(void){
	return puan;
}
void Oyun::puanHesapla(int yikim){
	gotoxy(60,4);
	if(yikim<=4){
		puan += 5*yikim;//x1
		SetConsoleTextAttribute(hcon,58); cout << "x1"; SetConsoleTextAttribute(hcon,63);
	}
	else if(yikim>4 && yikim<8){
		puan += 10*yikim;//2x
		SetConsoleTextAttribute(hcon,49); cout << "x2"; SetConsoleTextAttribute(hcon,63);
	}
	else if(yikim>=8 && yikim<11){
		puan += 15*yikim;//3x
		SetConsoleTextAttribute(hcon,62); cout << "x3 !"; SetConsoleTextAttribute(hcon,63);
	}
	else{
		puan += 25*yikim;//5x
		SetConsoleTextAttribute(hcon,60); cout << "x5 !!"; SetConsoleTextAttribute(hcon,63);
	}
}
int Oyun::getEslesen(void){
	return eslesen;
}
void Oyun::konumlan(void){
	//oyuncunun sectigi karaktere gecici konumlanýr.
	gecici=ilk[y];
	for(int i=0;i<x;i++){
		gecici=gecici->sag;
	}
	kontrol(gecici);//secimi kontrol eder.
}
void Oyun::kontrol(bListe *tmp){
	if(tmp->c!='-' && tmp->c!='+'){
		tmp->isaret=1;//1 kontrol edildi anlamýna gelir.
		if(tmp->sag!=NULL && tmp->sag->isaret!=1 && tmp->sag->c==gecici->c){
			eslesen++; kontrol(tmp->sag);
		}
		if(tmp->sol!=NULL && tmp->sol->isaret!=1 && tmp->sol->c==gecici->c){
			eslesen++; kontrol(tmp->sol);
		}
		if(tmp->ust!=NULL && tmp->ust->isaret!=1 && tmp->ust->c==gecici->c){
			eslesen++; kontrol(tmp->ust);
		}
		if(tmp->alt!=NULL && tmp->alt->isaret!=1 && tmp->alt->c==gecici->c){
			eslesen++; kontrol(tmp->alt);
		}
	}
}
bool Oyun::kontrolEslesen(void){
	if(eslesen>1) {puanHesapla(eslesen+1); eslesen=0; icerikDuzenle(); return true;}
	else {eslesen=0; setIsaret(); return false;}
}
void Oyun::setIsaret(void){
	//bListenin isaret elemanlarýný sýfýrlar.
	int i=0;
	while(ilk[i]!=NULL){
		gecici=ilk[i];
		while(gecici!=NULL){
			gecici->isaret=0;
			gecici=gecici->sag;
		}
		i++;
	}
}
void Oyun::icerikDuzenle(void){
	int i=str-1;
	while(ilk[i]!=NULL){
		gecici=ilk[i];
		while(gecici!=NULL){
			if(gecici->isaret==1){
				if(gecici->alt==NULL && gecici->ust->c=='+') gecici->ust->c='-'; 
				harfleriDegistir(gecici);
			}
			gecici=gecici->sag;
		}
		i--;
	}
}
void Oyun::harfleriDegistir(bListe *tmp){
	while(tmp->ust!=NULL && tmp->ust->c!='-'){
		tmp->c=tmp->ust->c;
		tmp=tmp->ust;
	}
	tmp->c='-';
}
void Oyun::stunKontrol(void){
	gecici=ilk[0];
	while(gecici->sag!=NULL){
		if(gecici->c=='-') {stunBirlestir(gecici); gecici=ilk[0];}
		gecici=gecici->sag;
	}
}
void Oyun::stunBirlestir(bListe *tmp){
	bListe *tmp2;
	if(tmp->sag!=NULL && tmp->sol!=NULL){
		while(tmp!=NULL){
			tmp2=tmp;
			tmp->sag->sol=tmp->sol;
			tmp->sol->sag=tmp->sag;
			tmp=tmp->ust;
			free(tmp2);
		}
		int i=0;
		static int ciftTek=0;//Bu satýrlar collapse elemanlarýnýn ortalanmasýný saglar ve yeni satýr eklenince ise yarar.
		if(ciftTek%2==0){
			while(son[i]!=NULL){//stun sildim ama toplamda 9 stun elde etmem lazým yeni satýr eklemede sorun yasamamak icin.
				gecici2=(bListe*)malloc(sizeof(bListe));
				gecici2->isaret=0;
				gecici2->c='+';
				if(son[i]->alt==NULL){
					son[i]->sag=gecici2; gecici2->sol=son[i]; gecici2->alt=NULL; gecici2->ust=NULL; gecici2->sag=NULL;
					son[i]=gecici2;
				}
				else{
					son[i]->sag=gecici2; gecici2->sol=son[i]; gecici2->alt=son[i]->alt->sag; son[i]->alt->sag->ust=gecici2; gecici2->ust=NULL; gecici2->sag=NULL;
					son[i]=gecici2;
				}
				i++;
			}
			ciftTek++;
		}
		else{
			i=0;
			while(ilk[i]!=NULL){//stun sildim ama toplamda 9 stun elde etmem lazým yeni satýr eklemede sorun yasamamak icin.
				gecici2=(bListe*)malloc(sizeof(bListe));
				gecici2->isaret=0;
				gecici2->c='+';
				if(ilk[i]->alt==NULL){
					ilk[i]->sol=gecici2; gecici2->sag=ilk[i]; gecici2->alt=NULL; gecici2->ust=NULL; gecici2->sol=NULL;
					ilk[i]=gecici2;
				}
				else{
					ilk[i]->sol=gecici2; gecici2->sag=ilk[i]; gecici2->alt=ilk[i]->alt->sol; ilk[i]->alt->sol->ust=gecici2; gecici2->ust=NULL; gecici2->sol=NULL;
					ilk[i]=gecici2;
				}
				i++;
			}
			ciftTek++;
		}
	}
}
void Oyun::yeniSatir(void){
	for(int i=0;i<15;i++){
		yeniSatirBagla(randomHarf(),i);
	}
}
void Oyun::yeniSatirBagla(char chr,int i){
	gecici=(bListe*)malloc(sizeof(bListe));
	gecici->c=chr;
	gecici->isaret=0;
	if(i==0){//yenisatirin ilk elemaný baglanýyor ise.
		gecici->alt=NULL; gecici->sol=NULL; gecici->ust=NULL; gecici->sag=NULL;
		on=gecici;
		arka=gecici;
	}
	else{
		gecici->sol=arka; arka->sag=gecici; gecici->sag=NULL; gecici->alt=NULL; gecici->ust=NULL;
		arka=gecici;
	}
}
void Oyun::yeniSatirEkle(void){
	int i=0;
	yeniSatir();

	gecici=ilk[0];
	gecici2=on;
	while(gecici!=NULL && gecici2!=NULL){//yeni satir collapse içine eklenir.
		gecici->alt=gecici2; gecici2->ust=gecici;
		gecici=gecici->sag; gecici2=gecici2->sag;
	}
	//ilk[] ve son[] ayarlamasý yapýlýr.
	gecici=on;
	gecici2=arka;
	while(gecici!=NULL && gecici2!=NULL){
		ilk[i]=gecici;
		son[i]=gecici2;

		gecici=gecici->ust;
		gecici2=gecici2->ust;
		i++;
	}
	str++;
}
bool Oyun::satirKontrol(void){
	//eger 1 satýrýn tum elemanlarý - yada + olmus ýse o satýrý yok eder.
	if((ilk[str-1]->c=='-' || ilk[str-1]->c=='+') && (son[str-1]->c=='-' || son[str-1]->c=='+')){
		gecici=ilk[str-1];
		while(gecici!=NULL){
			if(gecici->c!='-' && gecici->c!='+') return false;
			gecici=gecici->sag;
		}
		return true;
	}
	return false;
}
void Oyun::satirYoket(){
	if(satirKontrol()){
		gecici=ilk[str-1];
		while(gecici!=NULL){
			gecici->alt->ust=NULL;
			gecici2=gecici;
			gecici=gecici->sag;
			free(gecici2);
		}
		ilk[str-1]=NULL;
		son[str-1]=NULL;
		str--;
		satirYoket();
	}
}
bool Oyun::bitisKontrol(void){
	if(str>=16) return true;
	else return false;
}

class Son: public Collapse{
private:
	int yeniPuan,eskiPuan;
public:
	Son(){yeniPuan=0; eskiPuan=0;}
	void kontrolPuan(int);
	void sonucEkrani(void);
	~Son(){}
};
void Son::kontrolPuan(int yeni){
	yeniPuan=yeni;
	eskiPuan=getMaxPuan();
	getBaslik();
	if(yeniPuan>eskiPuan) {setMaxPuan(yeniPuan); eskiPuan=yeniPuan; cout << "\n\n\t\t\t\tTEBRIKLER,\n\t\t\t\tEN YUKSEK PUANI GECTINIZ!\n";}
	cout << "\n\t\t\t\tPuan : " << yeniPuan << endl << "\t\t\t\tEN YUKSEK PUAN : " << eskiPuan << endl;
}
void Son::sonucEkrani(void){
	char secim;
		cout << "\n\n\n\t\t\t\t1) MENU\n\n\n\t\t\t\t2) CIKIS\n\n\t\t\t\t";
	do{	
		secim=_getch();
		if(secim=='1'){
			menu();
			break;
		}
		if(secim=='2') exit(0);
	}while(secim!='2' || secim!='1');
}

Oyun o;
Son b;

int _tmain(int argc, _TCHAR* argv[])
{
	srand ( (unsigned)time( NULL ) );//sistem saatine gore random sayi almami sagliyor.

	o.getCOLLAPSE();
	menu();

	system("pause");
	return 0;
}

void menu(void){
	SetConsoleTextAttribute(hcon,63);

	system("cls");
	o.getBaslik();
	cout << "\n\n\n\n\t\t\t\t1) YENI OYUN\n\n\n\n\t\t\t\t2) EN YUKSEK PUAN\n\n\n\n\t\t\t\t3) YARDIM\n\n\n\n\t\t\t\t4) CIKIS\n\n\t\t\t\t";

	secim=_getch();

	switch (secim){
	case '1':
		system("cls");
		o.bagAyarla();

		Beep(900,100);
		
		do{
		o.getBaslik();
		SetConsoleTextAttribute(hcon,55);
		cout << "\n\t\tPuan: " << o.getPuan();
		SetConsoleTextAttribute(hcon,63);
		o.goruntule();

		if(bip>1) Beep(698,100);
		else Beep(300,200);

		o.setSatir();
		o.setStun();

	
		o.konumlan();

		bip=o.getEslesen();

		o.kontrolEslesen();
		Sleep(100);
		o.stunKontrol();

		o.setIsaret();

		o.satirYoket();
		if(sayac%4==0) o.yeniSatirEkle();
		if(o.bitisKontrol()){
			gotoxy(32,14);
			SetConsoleTextAttribute(hcon,79); 
			cout << "O Y U N  B I T T I"; 
			SetConsoleTextAttribute(hcon,63);
			gotoxy(25,24);
			Beep(325,200);Beep(300,200);Beep(275,200);Beep(250,200);Beep(225,200);Beep(200,600);
			_getch();
			system("cls");
			break;
		}
		sayac++;

		system("cls");
		}while(1);
		
		o.~Oyun();

		b.kontrolPuan(o.getPuan());
		o.setPuan();
		b.sonucEkrani();

		break;
	case '2':
		system("cls");
		
		o.getBaslik();
		cout << "\n\n\n\t\t\t\tEN YUKSEK PUAN : " << b.getMaxPuan() << endl;
		cout << "\n\n\t\t\t\tENTER: MENU";
		do{
		secim=_getch();
		}while(secim!=13);
		menu();

		break;
	case '3':
		system("cls");
		o.yardim();

		cout << "\n\n\t\t\t\tENTER: MENU";
		do{
		secim=_getch();
		}while(secim!=13);
		menu();

		break;
	case '4':
		exit(0);
		break;
	default: menu();
	}
}

void gotoxy(int x, int y) 
{ 
COORD coord; 
coord.X = x; coord.Y = y; 
SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord); 
}