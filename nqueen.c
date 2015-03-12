#include <stdio.h>
#include <stdlib.h>

struct yigin{
	int top;//Stack pointerýn yeri
	int veri[128];//Stack bilgilerinin olduðu matris.
};
typedef struct yigin yigin;

//Ýlk baþta stack boþ olduðu için top 0 olmalý. 
void yigin_init(yigin *y)
{
	y->top = 0;
}

//stackten bilgi alma fonksiyoný
int pop(yigin *y){
	if (y->top == 0){
		printf("Hata:Stack Bos\n");
		return 0;
	}
	y->top--;
	return y->veri[y->top];
}

//stack e veri koyma fonksiyonu
int push(yigin *y, int j){
	if (y->top == 128){
		printf("Hata:Stack Dolu\n");
		return -1;
	}
	y->top += 1;
	y->veri[y->top - 1] = j;
	return 0;
}

//burda yeni vezir eklenince o vezirin baþka bir veziri tehdit edip etmedðine bakýyor.
//bunun için ise sadece vezirin üstüne, sol üst çaprazýna ve sað üst çaprazýna bakýlýyor.
//tüm bunlarýn sebebi ise yeni bir vezirin altýnda ya da onla eþ satýrýnda eski vezirlerden birinin olamamýsýdýr.
int yenivezir(int i, int j, int **m, int n){
	int k = i; //matriste ki vezirleri kontrol etmek için gezinmemizde satýr adresini gösteriyor.
	int l = j; //matriste ki vezirleri kontrol etmek için gezinmemizde sütun adresini gösteriyor.
	k--;
	//sadece vezirin üstündeki satýrlara bakýlýyor.
	while (k >= 0){
		if (m[k][l] == 1)
			return 0;
		k--;
	}
	k = i;
	k--;
	l++;
	//vezirin sað üst çaprazýna bakýlýyor.
	while (k >= 0 && l<n){
		if (m[k][l] == 1)
			return 0;
		k--;
		l++;
	}
	k = i;
	l = j;
	k--;
	l--;
	//vezirin sol üst çaprazýna bakýlýyor.
	while (k >= 0 && l >= 0){
		if (m[k][l] == 1)
			return 0;
		k--;
		l--;
	}
	return 1;

}

int main(){
	yigin *yiginim;
	yiginim = (yigin*)malloc(sizeof(yigin));
	yigin_init(yiginim);
	int n, i, j;//n vezri sayýsý, i ve j döngülerde kullanýlýyor.
	int durum = 0;//matrisin o durumdaki yere koyulup koyulamayacaðýna bakýyor.
	int **vm;//vezirlerin tutulduðu tahta matrisi
	printf("Vezir sayisini giriniz: ");
	scanf("%d", &n);
	while (n<4){
		printf("Vezir sayisi 3 ten buyuk olmali lutfen tekrar giriniz: ");
		scanf("%d", &n);
	}
	//vezir sayýsý * vezir sayýsý n*n lik matris allocate ediliyor.
	vm = (int**)calloc(sizeof(int*), n);
	for (i = 0; i<n; i++){
		vm[i] = (int*)calloc(sizeof(int), n);
	}
	
	
	//matris sýfýrlanýyor.
	for (i = 0; i<n; i++){
		for (j = 0; j<n; j++){
			vm[i][j] = 0;
		}
	}
	
	
	vm[0][0] = 1; //Ýlk göz 1 yapýlýyor .çünkü ilk vezir hep buraya koyuluyor.
	push(yiginim, 0);//yýðýna ilk vezirin satýrý ekleniyor.
	i = 1; //ilk vezir eklendiði için 2. vezirden yani 1. satýrdan iþlemlere baþlamak için i 1 oluyor.
	j = 0;//her durumda yeni vezir gelince 0. sütundan bakmaya baþlanýyor.
	
	//tüm vezirler yelþene kadar while devam ediyor.
	while (i != n){
		//eklenen vezir baþka bir veziri tehdit etmeyinceye kadar while devam ediyor.
		while (j<n && durum == 0){
				durum = yenivezir(i, j, vm, n);
				j++;
		}
		
		j--;
		
		//durum 1 olursa yeni vezir ekleniyor.
		if (durum == 1){
			//vezir bilgiler stacke yazýlýyor.
			push(yiginim, j);
			vm[i][j] = 1;
			durum = 0;
			i++;
			j = 0;
		}
		else{
			//durum 0 olursa yeni vezir eklenemedi diyor ve üstteki vezir pop ediliyor.
			j = pop(yiginim);
			i--;
			vm[i][j] = 0;
			j++;	
		}

	}
	//matris ekrana yazýlýyor.
	for (i = 0; i<n; i++){
		for (j = 0; j<n; j++){
			printf("%d", vm[i][j]);
		}
		printf("\n");
	}
	return 0;
}

