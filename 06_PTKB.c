#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<windows.h>
#include <dirent.h>

#define RED    			 "\x1b[31m"
#define BOLD_RED 		 "\033[1;31m"
#define GREEN			 "\033[0;32m"
#define BOLD_GREEN   	 "\033[1;32m"
#define YELLOW  		 "\033[0;33m"
#define BOLD_YELLOW		 "\033[01;33m"
#define BLUE   			 "\033[1;34m"
#define MAGENTA			 "\x1b[35m"
#define CYAN   			 "\x1b[36m"
#define RESET   		 "\x1b[0m"
char tanggal[2];
int main()
{
	fullscreen();
	hidecursor();
	splashScreen();
	sleep(2);
	int realPos,posPanah,position,keypress;
	int utama=menu();
	system("pause");
	int panah=iniPanah(realPos,posPanah);	
}

COORD xy = {0,0};


void gotoxy (int x, int y)
{
        xy.X = x; xy.Y = y; // X and Y coordinates
        SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), xy);
}

void fullscreen()
{
    CONSOLE_SCREEN_BUFFER_INFOEX info = {0};
    int width, height;
    HANDLE hConsole = NULL;

    // maximize window
    ShowWindow(GetConsoleWindow(), SW_SHOWMAXIMIZED);

    // print width/height of this window in terms of columns and rows
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    info.cbSize = sizeof(info);
    GetConsoleScreenBufferInfoEx(hConsole, &info);
}

void SetPosition(int X, int Y)
{
HANDLE Screen;
Screen = GetStdHandle(STD_OUTPUT_HANDLE);
COORD Position={X, Y};

SetConsoleCursorPosition(Screen, Position);
}


void iniPanah(int realPos, int posPanah)										//fungsi untuk memetakan kursor 
{
	(realPos==posPanah) ? printf("\t\t===>") : printf("\t\t    ");
}

void hidecursor()
{
   HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
   CONSOLE_CURSOR_INFO info;
   info.dwSize = 100;
   info.bVisible = FALSE;
   SetConsoleCursorInfo(consoleHandle, &info);
//	printf("\e[?25h");															re-enable cursor
}

void SetColor(int ForgC)
{
     WORD wColor;
     HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
     CONSOLE_SCREEN_BUFFER_INFO csbi;
     if(GetConsoleScreenBufferInfo(hStdOut, &csbi))
     {
          wColor = (csbi.wAttributes & 0xF0) + (ForgC & 0x0F);
          SetConsoleTextAttribute(hStdOut, wColor);
     }
     return;
}

void splashScreen() {
	srand(time(0));
	int a,b,w=0;
	while(w<20)
	{
	a=rand()%180+20; b=rand()%35+5;
		gotoxy(a,b);
		
		printf("*");
		Sleep(90);
		w++;
	}
    FILE *fp;
    char str[MAXCHAR];
 	gotoxy(80,10);
    fp = fopen("splash.txt", "r");
    if (fp == NULL){
        printf("Could not open file");
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);

}

void menu()
{
	
	int position=1;
	int keypress=0;
	int MAX=5, MIN=1, p, q, n=2;
	hidecursor();
	while(keypress!=13)
	{
	system("cls");     gotoxy(50, 5);
	gotoxy(57, 6);printf("\t\t\t\t______________________________\n");
	gotoxy(57, 7);printf("\t\t\t\t|                            |\n");
	gotoxy(57, 8);printf("\t\t\t\t|  Program Log book bulanan  |\n");
	gotoxy(57, 9);printf("\t\t\t\t|____________________________|\n");
	gotoxy(57, 10);printf("\t\t\t     Developed by: BROTI€K€VIN & Farhan\n");
	gotoxy(57, 12);printf("\tProgram ini modern, navigasi menggunakan panah atas/bawah dan ENTER untuk select\n\n");
	printf(BOLD_YELLOW);
	gotoxy(70, 14);iniPanah(1,position);printf("1. Entry Baru\n"RESET BLUE); 
	gotoxy(70, 15);iniPanah(2,position);printf("2. Lihat log bulan ini\n"RESET GREEN); 
	gotoxy(70, 16);iniPanah(3,position);printf("3. Ubah log\n" RESET CYAN);
	gotoxy(70, 17);iniPanah(4,position);printf("4. Petunjuk penggunaan program\n" RESET BOLD_RED);
	gotoxy(70, 18);iniPanah(5,position);printf("5. Exit\n\n" RESET);
	keypress=getch();
	if(keypress==80 && position !=MAX) position++;
	else if(keypress==72 && position !=MIN) position--;
	else position==position;
	}
	
	switch(position)
	{
		case 1:
			printf("\e[?25h");
			submenu1();
			break;
			
		case 2:
			calendar();
			logBulanIni();
			system("pause");
			menu();
			break;
			
		case 3:
			system("cls");
			ubah();
			break;
			
		case 4:
			system("cls");
			penggunaan();
			break;
			
		case 5:
			system("cls");
			for(p=0; p<5; p++)													//animasi keren terminate program
			{
				for(q=0; q<5; q++)
				{
					gotoxy(0+(45*q),25);
					system("COLOR 02");
					if(q==p) printf("~goodbye");
				}
	
			Sleep(500);
			system("cls");
			}
			exit(1);
			
		default:
			position==position;
	}	
}

void calendar()
{
	int month, day, i,check;
	FILE *fp;
	fp=fopen("tanggal.txt","r");
	for ( i=0 ;i<1; i++)
	{
		printf("May");
		printf("\n\nMon  Tue  Wed  Thu  Fri  Sat  Sun\n" );
		
		// Correct the position for the first date
		for ( day = 1; day <= 1 + 2 * 5; day++ )
		{
			printf(" ");
		}
		
		// Print all the dates for one month
		for ( day = 1; day <= 31; day++ )
		{
		//	if(mark==day) printf(RED"%d"RESET, day);
					printf("%2d", day);
			// Is day before Sat? Else start next line Sun.
			if ( ( day + 2 ) % 7 > 0 )
				printf("   " );
			else
				printf("\n " );
		}
	}
	fclose(fp);
}

int submenu1(){
	int date;
	char *filename;
	char strdate[2];
	system("cls");
	printf("\nJika anda ingin ke menu utama input 00");
	gotoxy(50,7);
	printf("Masukkan tanggal: ");
	scanf("%d", &date);
	if (date >=31){
		printf("Tanggal yang anda input salah !\n");
		system("pause");
		submenu1();
	}
	if (date == 00){
		menu();
	}
	int dates=date;
	itoa(date,strdate,10);
	filename=strcat(strdate,".txt");
	int i, j, a, b, x, y, count, countIn, countOut, in, out, sumDebit=0, sumKredit=0, saldo=0;
	int arrIn[1000]= {};
	int arrOut[1000] = {};
	FILE *ftxt;
	
	ftxt=fopen(filename,"a+");
	gotoxy(50,10);
	printf(BOLD_GREEN"Berapa banyak item PEMASUKAN tanggal %d?  ", dates);
	scanf("%d", &countIn);
	gotoxy(60,12);
	printf("====INPUT DEBIT====");
		for(i = 0; i < countIn; i++){
			gotoxy(50,14+(2*i));
	 		printf("Masukkan pemasukkan:  ");
			scanf("%d"RESET, &in);
			arrIn[i]=in;
			sumDebit+=in;
			}
	gotoxy(120,10);
	printf(YELLOW"Berapa banyak item PENGELUARAN tanggal %d?  ", dates);
	scanf("%d", &countOut);
	gotoxy(130,12);
	printf("====INPUT KREDIT====");
		for(j = 0; j < countOut; j++){
			gotoxy(120,14+(2*j));
			 printf("Masukkan pengeluaran:  ");
	 		scanf("%d", &out);
	 		arrOut[j]=out;
	 		sumKredit+=out;
			}
		
		for(count=0;count<countOut;count++)
		{
	 		fprintf(ftxt,"\t%d\t\t%d\n",arrIn[count],arrOut[count]);
		}
		saldo=sumDebit-sumKredit;
		gotoxy(80,16+(2*j));
		printf("=================================================");
		gotoxy(80,17+(2*j));
		printf("Total PEMASUKAN: %d", sumDebit);
		gotoxy(80,18+(2*j));
		printf("Total PENGELUARAN: %d", sumKredit);
		gotoxy(80,19+(2*j));
		printf("Saldo di tanggal %d: %d", dates, saldo);
		gotoxy(80,20+(2*j));
		printf("================================================="RESET);
	fclose(ftxt);
	gotoxy(80, 23+(2*j));
	printd("File tanggal ", 20); printf("%d", dates); printd(" berhasil dibuat", 20);
	gotoxy(80, 25+(2*j));
	printf(">Tekan tombol apapun untuk kembali ke menu<");
	getch();
	menu();
}

//lihat log bulan ini
int logBulanIni()
{
	int kredit=0, debit=0, a=1, i=0, check,saldo=0;
	char b[2]= "00";
	printf("\e[?25h");
    FILE *fp;
    char str[MAXCHAR];
    char *filename;
    printf("\n(Jika ingin kembali ke menu utama tekan 00)");
    printf(YELLOW"\nMasukkan tanggal log yang ingin dilihat: ");
    scanf("%s", &tanggal);
    if(strcmp(tanggal,b) == 0){
    	menu();
	}
   	printf(RESET"\n\t     %s MAY 2019\n\n", tanggal);
 	filename=strcat(tanggal,".txt");
    fp = fopen(filename, "r");
    if (fp == NULL){
        printf(RED"Tidak ada log tanggal ini\n"RESET);
        return 1;
    }
    else
    {
	printf(GREEN"\tDEBIT"RESET);
    printf(YELLOW"\t\tKREDIT\n"RESET);
	}
    while (fgets(str, MAXCHAR, fp) != NULL)
       printf("%s", str);
       
    printf("===================================\n\t\tTOTAL\n====================================");
   
    FILE *ft=fopen(filename,"r");
	while(!feof(ft))
	{
		check=a%2;
		if(check==0) debit+=i;
		else kredit+=i;
//		printf("%d\n", i);
		fscanf(ft,"%d",&i);
		a++;
		
	}
    fclose(fp);
    fclose(ft);
	saldo=debit-kredit;
	printf("\n\t%d\t\t%d", debit, kredit);
	printf(BOLD_YELLOW"\n====================================\nSaldo: Rp%d"RESET, saldo);
    printf("\n\n");
	system("pause");
   menu();
}
void penggunaan(){
	headerpenggunaan();
	sleep(1);
	printd("\tProgram ini dibuat oleh Mahasiswa Teknik Komputer bernama Kevin Darmawan dan Muhammad Farhan Almasyhur\n",20);
	printd("\n1. Program ini dapat mencatat Pemasukan dan Pengeluaran yang dilakukan selama 1 bulan\n",40);
	printd("2. Program ini akan mengeluarkan file \".txt\" yang akan sesuai dengan tanggal pemasukan atau pengeluaran\n",40);
	printd("3. Target dari program ini yaitu Mahasiswa untuk mengetahui besaran pemasukan dan pengeluaran pada 1 bulannya\n",40);
	printd("4. Langkah-Langkah menggunakan program\n",40);
	printd("\t a. Jika ingin menambahkan suatu pemasukan ataupun pengeluaran pada suatu tanggal, maka arahkan arrow keys pada pilihan no. 1\n",40);
	printd("\t b. Jika ingin melihat kalender bulan ini, dan melihat pemasukan dan pengeluaran pada suatu tanggal, maka arahkan arrow keys pada pilihan no. 2\n",40);
	printd("\t c. Jika ingin mengubah dan melihat log apa saja yang telah dibuat maka arahkan arrow keys pada pilihan no. 3\n",40);
	printd("\t d. Jika ingin keluar, arahkan arrow keys pada pilihan no. 5\n",40);
	printd("Tekan tombol apapun untuk kembali ke menu utama\n",40);
	system("pause");
	sleep(1);
	menu();
}
void printd(char* x, int y)
{
	int i;
	for(i=0;i<strlen(x);i++)
	{
		printf("%c",x[i]);
		Sleep(y);
	}
}
void headerpenggunaan() {
    FILE *fp;
    char str[MAXCHAR];
    fp = fopen("Headerpenggunaan.txt", "r");
    if (fp == NULL){
        printf("Could not open file");
        return 1;
    }
    while (fgets(str, MAXCHAR, fp) != NULL)
        printf("%s", str);
    fclose(fp);
}
int ubah(){
	int date;
	printf("\e[?25h");
    DIR *d;
    struct dirent *dir;
    d = opendir(".");
    if (d)
    {
        while ((dir = readdir(d)) != NULL)
        {
            printf("%s\n", dir->d_name);
        }
        system("pause");
        closedir(d);
    }
    return submenu1();
}
