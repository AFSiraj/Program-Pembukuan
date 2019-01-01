//LINK GITHUB:https://github.com/AFSiraj/Program-Pembukuan/

#include <stdio.h>
#include <windows.h>
#include <stdlib.h>

struct clientData{
	int noAccnt;
	char namaDepan[15];
	char namaBelakang[15];
	double balance;
};

void menu();
void newAccount(FILE *fPtr);
void deleteAccount(FILE *fPtr);
void textFile(FILE *readPtr);
void update(FILE *fPtr);
void invalid();
void help();
void close();
void head();
void loading();

int main(){
	FILE *cfPtr;
	int pilih;
	if((cfPtr = fopen("credit.dat", "rb+")) == NULL){
		printf("\n\n\n%s",
		"		        File tidak ditemukan.\n"
		"		Tekan tombol apa saja untuk keluar.\n");
		getch();
	}
	else{
		head();
		menu();
		while(getch()!='6'){	
			switch (getch()){
				case '1':
					newAccount(cfPtr);
					system("cls");
					main();
					break;
				case '2':
					update(cfPtr);
					system("cls");
					main();
					break;
				case '3':
					deleteAccount(cfPtr);
					system("cls");
					main();
					break;
				case '4':
					loading();
					textFile(cfPtr);
					system("cls");
					main();
					break;
				case '5':
					system("COLOR 06");
					help();
					system("cls");
					main();
					break;
				default:
					invalid();
					main();
					break;
			 }
		}
	}close();
	fclose(cfPtr);
	return 0;
}

void textFile(FILE *readPtr){
	system("cls");
	system("COLOR 07");
	FILE *writePtr;
	struct clientData client = {0, "", "", 0.0};		//default data
	if((writePtr = fopen("account.txt", "w")) == NULL){
		printf( "File tidak ditemukan.\n" );
		getch();
		exit(0);
	}
	else{
		rewind(readPtr);	//set pointer ke awal file
		fprintf(writePtr,"%9s %16s%16s%10s\n","No. Acct", "Nama Depan", "Nama Belakang","Balance");
		while(!feof(readPtr)){
			fread(&client, sizeof(struct clientData), 1, readPtr);
			if(client.noAccnt != 0){
				fprintf(writePtr,"%9d %16s%16s%10.2f\n", client.noAccnt, client.namaDepan, client.namaBelakang, client.balance);
			}
		}
		printf("\nTerima kasih. Data sudah dicetak di account.txt");
		fclose(writePtr);
	}
	getch();
}

void update(FILE *fPtr){
	system("cls");
	system("COLOR 07");
	int account;
	double transaction;
	printf("                    Update Akun\n\n");
	struct clientData client = {0, "", "", 0.0};
	printf("Masukkan no. acct yang ingin diupdate: ");
	scanf("%d", &account);
	fseek(fPtr, (account-1) * sizeof(struct clientData), SEEK_SET);
	fread(&client, sizeof(struct clientData), 1, fPtr);
	if (client.noAccnt == 0){
		printf("Tidak ada informasi pada account #%d.\n", account);
	}
	else{
		printf("%9d %16s%16s%10.2f\n\n", client.noAccnt, client.namaDepan, client.namaBelakang, client.balance);
		printf("Masukkan jumlah pemasukkan (+) atau jumlah pengeluaran diawali tanda(-): ");
		scanf("%lf", &transaction);
		client.balance += transaction;
		printf("%9d %16s%16s%10.2f\n", client.noAccnt, client.namaDepan ,client.namaBelakang, client.balance);
		fseek(fPtr, (account - 1) * sizeof(struct clientData),SEEK_SET);
		fwrite(&client, sizeof(struct clientData), 1, fPtr);
	}
	getch();
}

void deleteAccount(FILE *fPtr){
	system("cls");
	system("COLOR 07");
	printf("                    Hapus Akun\n\n");
	struct clientData client;
	struct clientData blankClient = {0, "", "", 0};
	int account;

	printf("Masukkan no. account yang ingin dihapus : ");
	scanf("%d", &account);
	fseek(fPtr, (account - 1) * sizeof(struct clientData),SEEK_SET);
	fread(&client, sizeof(struct clientData), 1, fPtr);
	
	if(client.noAccnt == 0){
		printf("Akun #%d tidak terdaftar.\n", account);
	}
	else {
		fseek(fPtr, (account - 1) * sizeof(struct clientData),SEEK_SET);
		//Mengganti data yg ada dengan data kosong
		fwrite(&blankClient, sizeof(struct clientData), 1, fPtr);
		printf("Akun #%d sudah terhapus.\n", account);
	}
	getch();
}

void newAccount(FILE *fPtr){
	system("cls");
	system("COLOR 07");
	printf("                    Tambah Akun\n\n");
	struct clientData client = {0, "", "", 0.0};
	int accountNum;
	
	printf("%s", "Masukkan no. akun yang ingin ditambah: ");
	scanf("%d", &accountNum);
	fseek(fPtr, (accountNum - 1) * sizeof(struct clientData), SEEK_SET);
	fread(&client, sizeof(struct clientData), 1, fPtr);
	if (client.noAccnt != 0){
 		printf("Akun #%d sudah terdaftar.\n", accountNum);
	}
	else {
		printf("Masukkan nama depan, nama belakang, balance\n? ");
		scanf("%14s%14s%lf", &client.namaDepan, &client.namaBelakang,&client.balance);
		client.noAccnt = accountNum;
		fseek(fPtr, (client.noAccnt - 1) * sizeof(struct clientData), SEEK_SET);
		fwrite(&client,sizeof(struct clientData), 1, fPtr);
		printf("\n\nTerima Kasih, data telah tersimpan");
	}
	getch();
}

void head(){
	system("COLOR 06");
	printf("%s",
	"                   Pembukuan Transaksi            \n\n\n"); //nama program
}

void menu(){
	system("COLOR 06");
	printf("%s",
	"======================Menu Utama======================\n"
	"|                                                    |\n"
	"|         [1] - Tambah akun baru                     |\n"
	"|         [2] - Update saldo akun                    |\n"
	"|         [3] - Hapus akun                           |\n"
	"|         [4] - Cetak data ke file account.txt       |\n"
	"|         [5] - Bantuan                              |\n"
	"|         [6] - Tutup program                        |\n"
	"|                                                    |\n"
	"======================================================\n");
}

void close(){
	system("cls");
    printf("\n\n\n");
    	printf("%s",
	"====================Tutup Program=====================\n"
	"|                                                    |\n"
	"|                                                    |\n"
	"|             Anda yakin ingin keluar?               |\n"
	"|         [1] - Ya                                   |\n"
	"|         [2] - Tidak                                |\n"
	"|                                                    |\n"
	"|                                                    |\n"
	"|                                                    |\n"
	"======================================================\n");
	switch(getch()){
    	case '1':
			system("cls");
			printf("\n\n\n");
	        printf("             Terima Kasih.\n\n");
			exit(1);
	        break;
        case '2':
        	system("cls");
        	printf("\n\n\n");
        	printf("\n\n");
	        printf("         Kembali ke menu utama\n\n\n\n");
            system("PAUSE");
            system("cls");
            main();
            break;
        default:
        	system("cls");
			invalid();
            system("cls");
            close();
	}
}

void help(){
	system("cls");
	printf("\n\n%s",
	"=======================Bantuan========================\n"
	"|                                                    |\n"
	"|         Program ini dibuat untuk menghitung        |\n"
	"|   dan mencatat perubahan aktivitas pada akun yang  |\n"
	"|     melakukan penyimpanan. Program ini menyimpan   |\n"
	"|    perubahan yang anda buat pada file account.txt  |\n"
	"|    yang dapat anda temukan pada folder yang sama   |\n"
	"|                  dengan program ini.               |\n"
	"|                                                    |\n"
	"======================================================\n");
	getch();
}

void invalid(){
	system("cls");
	system("COLOR 4F");
	printf("\n\n\n\n\n%s",
	"                                Pilihan Salah!\n\n\n"
	"             Masukkan salah satu pilihan yang tertera pada menu \n\n");

	getch();
	system("cls");
}

void loading(){															
	int i;		
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n");
	printf("\t\t\t\t\t\t\t\t\t\tSedang dalam proses ");
	for (i=0;i<5;i++){
		printf(". ");
		Sleep(200);
	}
	system("cls");
}
