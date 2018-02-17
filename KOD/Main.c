/**
@file

Bu uygulamada Merge Sort siralama algoritmasinda manipulasyonlar yapýlarak onceki durumun korunarak yeni bir duruma göre siralama yapilmasi gerceklestirilmistir.

@author

Name 			 :		Muhammed Yasin SAGLAM	
Student No		 :	 	15011804	
Date 			 :		15/10/2017
E-Mail			 :		myasinsaglam1907@gmail.com
Compiler Used	 :		GCC
IDE			 	 :		DEV-C++(Version 5.11)
Operating System :		Windows 10 Educational Edition
*/
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
#include<strings.h>
#include<string.h>
#include<locale.h>
#define CSIZE 20 //maksimum sehir adi karakter uzunlugunu tutan makro 
#define filename "seferler.txt" //dosya adini tutan makro
//ilgili struct olusturuluyor
typedef struct {
	char city_name[CSIZE]; //sehir adi 
	char hour[6]; //saat bilgisi
}LIST;


void merge(LIST *,int ,int ,int ); //ilk merge modulu sadece sehir ismine gore kontrol yapar
void Merge_sort(LIST *,int, int ); //ilk MergeSort fonksiyonu adece sehir ismine gore siralama yapan merge modulunu cagirir
void merge2(LIST *,int ,int ,int ); //ikinci merge modulu ismin yaninda eklenen bir kosulla saatlere de bakarak kiyaslama yapar 
void Merge_sort2(LIST *,int, int ); //ikinci MergeSort fonksiyonu hem sehir ismine hemde saate  gore siralama yapan merge2 modulunu cagirir
char* time_control();

int main(){
	setlocale(LC_ALL, "Turkish"); 
	FILE *fp; //file pointer
	LIST *list; //list pointer.
	int list_count=0; //baslangicta dosyadan okunacak eleman sayisini tutan degisken
	int choice,i; //while kontrol icin choice ve cevrim degiskeni olan i
	int add_size=0,new_size; //sonradan kullanici input girdiginde eklenecek input sayisini ve toplami tutan degiskenler
	
	list = (LIST*)malloc(sizeof(LIST)); //liste icin 1 elemanlik yer ayriliyor
	if(!list){
		printf("Allocation error!!! Quitting...");
		exit(0);
	}
	
	fp = fopen(filename,"r"); //dosya okuma modunda acilir
	if(!fp){
		printf("file not opened !!! Quitting...");
		exit(0);
	}
	else{
		while(!feof(fp)){
			fscanf(fp,"%s",list[list_count].city_name); //tum sehir adini oku 
		//	printf("%s\n",list[list_count].city_name); 
			fscanf(fp,"%s",list[list_count].hour); //sefer saatini oku
		//	printf("%s\n",list[list_count].hour);
			list_count++;  //liste boyutunu arttir
			list=(LIST*)realloc(list,sizeof(LIST)*(list_count+1));  //listeyi memory allocation yaparak genislet
			if(!list){ 
				printf("Allocation error!!! Quitting...");
				exit(0);
			}
		}
	}
	fclose(fp);
	
	new_size=list_count;
	
	printf("\n1.Add input & Merge Sort\n2.Merge Sort\n\nPlease enter the choice (0 for exit): ");
	scanf("%d",&choice);					//Reading choice from the user
	system("CLS");	
	while(choice!=0){		
		if(choice ==1){ //kullanicinin input girmesini saglayan secenek
			printf("\nHow many city and hour information will you add ?\n");
			scanf("%d",&add_size);  //eklenecek sefer sayisini kullanicidan oku 
			new_size+=add_size; //toplam boyutu arttir
			list=(LIST*)realloc(list,sizeof(LIST)*(new_size)); //listeyi genislet realloc ile
			if(!list){
				printf("Allocation error!!! Quitting...");
				exit(0);
			}
			for(i=new_size-add_size;i<new_size;i++){ //eklenecek sefer sayisi kadar dngu
				printf("\nEnter city name : ");
				scanf("%s",list[i].city_name); //sehir adini ilgili adrese oku 
				printf("\nEnter hour information : ");
				strcpy(list[i].hour,time_control()); //saat bilgisini formata uygun olacak sekilde kontrol ederek oku 
				//printf("%s",list[i].hour);
			}
			printf("\n\nOrder by Cityname\n"); 
			Merge_sort(list,0,new_size-1);//sehre gore sirali halini yazdiran Merge_sort fonksiyonunu cagir
			for	(i=0;i<new_size;i++){  //listeyi ekrana yazdir
				printf("\n%d.\t%-10s\t%s",i,list[i].city_name,list[i].hour);
			}
			printf("\n\nOrder by Cityname and hour\n");
			Merge_sort2(list,0,new_size-1);//hem sehre hemde saate gore sirali halini yazdiran Merge_sort2 fonksiyonunu cagir
			for	(i=0;i<new_size;i++){//listeyi ekrana yazdir
				printf("\n%d.\t%-10s\t%s",i,list[i].city_name,list[i].hour);
			}
			printf("\nTotal times is %d",new_size);
		}
		
		if(choice ==2){ //Input girmeksizin siralama yapan secenek
			printf("\n\nOrder by Cityname\n");
			Merge_sort(list,0,new_size-1); //sehre gore sirali halini yazdiran Merge_sort fonksiyonunu cagir
			for	(i=0;i<new_size;i++){
				printf("\n%d.\t%-10s\t%s",i,list[i].city_name,list[i].hour);
			}
			printf("\n\nOrder by Cityname and hour\n");
			Merge_sort2(list,0,new_size-1); //hem sehre hemde saate gore sirali halini yazdiran Merge_sort2 fonksiyonunu cagir
			for	(i=0;i<new_size;i++){
				printf("\n%d.\t%-10s\t%s",i,list[i].city_name,list[i].hour);
			}
			printf("\nTotal times is %d",new_size);
		}
		printf("\n1.Add input & Merge Sort\n2.Merge Sort\n\nPlease enter the choice (0 for exit): ");
		scanf("%d",&choice);					//kullanicidan secimi oku
		system("CLS");	
	}
	
	free(list); //liste icin ayrilan yeri serbest birak
	system("PAUSE");
	return 0; //program cikisi
}

//saat bilgisini uygun formatli olarak kullanicidan alan ve disari donduren fonksiyon
char* time_control(){
	char *time,ch;
	time = (char*)malloc(sizeof(char)*5);
	int correct = 0;
	while(!correct){
		ch=getche();
		if(isalpha(ch) || (int)(ch-'0')>2 || (int)(ch-'0')<0){ //girilen saat bilgisininin ilk karakterini kontrol et {0,2 arasinda olmali}
			system("CLS");
			printf("\nPlease enter digits or enter correct values for time\n");
		}
		else{
			time[0]=ch;
			correct=1;
		}
	}

	while(correct){
		ch=getche();
		if(isalpha(ch) || ((int)(time[0]-'0')==2) && (int)(ch-'0')>3 || (int)(ch-'0')<0){//girilen saat bilgisininin ikinci karakterini kontrol et {ilki iki ise 3 ten buyuk olamaz 0 dan kucuk olamaz}
			system("CLS");
			printf("Please enter digits or enter correct values for time\n");
			printf("%c",time[0]);
		}
		else{
			time[1]=ch;
			correct=0;
		}
	}
	printf(":");
	time[2]=':';
	
	while(!correct){
		ch=getche();
		if(isalpha(ch) || (int)(ch-'0')>5 || (int)(ch-'0')<0){//girilen saat bilgisininin ucuncu karakterini kontrol et {0,5 arasinda olmali }
			system("CLS");
			printf("Please enter digits or enter correct values for time\n");
			printf("%s",time);
		}
		else{
			time[3]=ch;
			correct=1;
		}
	}	
	
	while(correct){
		ch=getche();
		if(isalpha(ch)  || (int)(ch-'0')<0){ //girilen saat bilgisininin ucuncu karakterini kontrol et {0,9 arasinda olmali }
			system("CLS");
			printf("Please enter digits or enter correct values for time\n");
			printf("%s",time);
		}
		else{
			time[4]=ch;
			correct=0;
		}
	}
	return time; // dogru alinan input olan saati dondur 
}

/**
	@param *arr		array that will be merged
	@param l_index		left index of array
	@param mid		middle index of array
	@param r_index		right index of array
*/
void merge(LIST *arr, int l_index, int mid, int r_index){
	LIST *temp;
		temp=(LIST*)malloc(sizeof(LIST)*(r_index-l_index+1)); //yedek dizi icin memory allocation
			if(!temp){
				system("COLOR c");
				printf("Not enough space for merge sort!!! Quitting...");
				exit(0);
			}
	int i,j,k;
	i=l_index; 
	j=mid+1; 
	k=0;
	while(i<=mid && j<=r_index){

		if(	strcasecmp(arr[i].city_name,arr[j].city_name)<0) // isme gore sirali olacak sekilde buyuk kucuk harf dikkate onemsiz olarak kontrol yapiliyor
			temp[k++]=arr[i++]; //ismen kucuk olan yedek dizide ilk siralara aliniyor 
		else
			temp[k++]=arr[j++];	//ismen kucuk olan yedek dizide ilk siralara aliniyor 
	}
	while(i<=mid) //eleman kalmissa solda atama yap 
		temp[k++]=arr[i++];
	while(j<=r_index) //eleman kalmissa sagda atama yap
		temp[k++]=arr[j++];
	k--;	
	while(k>=0){ //yedek diziyi gercege yaz
		arr[l_index+k]=temp[k];
		k--;				
	}

free(temp); //yedek diziyi free yap
}

/**
	@param *arr		array that will be merge sorted
	@param	left		start index of array
	@param right		end index of array
*/
void Merge_sort(LIST *arr,int left,int right){
    if(left<right){ //durma kosulu 
        int mid =(left+right)/2; //ortayi bul
        Merge_sort(arr,left,mid); //sol taraf icin cagir
        Merge_sort(arr,mid+1,right); //sag taraf icin cagir
        merge(arr,left,mid,right); //merge modulu ile kontrol ve atamalari yap
    }
}

/**
	@param *arr		array that will be merged
	@param l_index		left index of array
	@param mid		middle index of array
	@param r_index		right index of array
*/
void merge2(LIST *arr, int l_index, int mid, int r_index){
	LIST *temp;
		temp=(LIST*)malloc(sizeof(LIST)*(r_index-l_index+1));//yedek dizi icin memory allocation
			if(!temp){
				system("COLOR c");
				printf("Not enough space for merge sort!!! Quitting...");
				exit(0);
			}
	int i,j,k;
	i=l_index; 
	j=mid+1; 
	k=0;
	while(i<=mid && j<=r_index){
		if(	strcasecmp(arr[i].city_name,arr[j].city_name)==0 && strcmp(arr[i].hour,arr[j].hour)<0) //sehir adlari ayni ise saatlere gore kiyasla
			temp[k++]=arr[i++];
		else if(strcasecmp(arr[i].city_name,arr[j].city_name)<0) //farkli ise isme gore sirali olacak sekilde buyuk kucuk harf dikkate onemsiz olarak kontrol yapiliyor
			temp[k++]=arr[i++]; //ismen kucuk olan yedek dizide ilk siralara aliniyor
		else
			temp[k++]=arr[j++];	//ismen kucuk olan yedek dizide ilk siralara aliniyor
	}
	while(i<=mid)//eleman kalmissa solda atama yap bitir
		temp[k++]=arr[i++];
	while(j<=r_index)//eleman kalmissa sagda atama yap bitir
		temp[k++]=arr[j++];
	k--;	
	while(k>=0){  //yedek diziyi gercege yaz
		arr[l_index+k]=temp[k];
		k--;				
	}

free(temp);//yedek diziyi free yap
}

/**
	@param *arr		array that will be merge sorted
	@param	left		start index of array
	@param right		end index of array
*/
void Merge_sort2(LIST *arr,int left,int right){
    if(left<right){//durma kosulu 
        int mid =(left+right)/2;//ortayi bul
        Merge_sort2(arr,left,mid); //sol taraf icin cagir
        Merge_sort2(arr,mid+1,right);//sag taraf icin cagir
        merge2(arr,left,mid,right);//merge modulu ile kontrol ve atamalari yap
    }
}

