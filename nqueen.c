#include <stdio.h>
#include <stdlib.h>

struct yigin{
	int top;//Stack pointer�n yeri
	int veri[128];//Stack bilgilerinin oldu�u matris.
};
typedef struct yigin yigin;

//�lk ba�ta stack bo� oldu�u i�in top 0 olmal�. 
void yigin_init(yigin *y)
{
	y->top = 0;
}

//stackten bilgi alma fonksiyon�
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

//burda yeni vezir eklenince o vezirin ba�ka bir veziri tehdit edip etmed�ine bak�yor.
//bunun i�in ise sadece vezirin �st�ne, sol �st �apraz�na ve sa� �st �apraz�na bak�l�yor.
//t�m bunlar�n sebebi ise yeni bir vezirin alt�nda ya da onla e� sat�r�nda eski vezirlerden birinin olamam�s�d�r.
int yenivezir(int i, int j, int **m, int n){
	int k = i; //matriste ki vezirleri kontrol etmek i�in gezinmemizde sat�r adresini g�steriyor.
	int l = j; //matriste ki vezirleri kontrol etmek i�in gezinmemizde s�tun adresini g�steriyor.
	k--;
	//sadece vezirin �st�ndeki sat�rlara bak�l�yor.
	while (k >= 0){
		if (m[k][l] == 1)
			return 0;
		k--;
	}
	k = i;
	k--;
	l++;
	//vezirin sa� �st �apraz�na bak�l�yor.
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
	//vezirin sol �st �apraz�na bak�l�yor.
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
	int n, i, j;//n vezri say�s�, i ve j d�ng�lerde kullan�l�yor.
	int durum = 0;//matrisin o durumdaki yere koyulup koyulamayaca��na bak�yor.
	int **vm;//vezirlerin tutuldu�u tahta matrisi
	printf("Vezir sayisini giriniz: ");
	scanf("%d", &n);
	while (n<4){
		printf("Vezir sayisi 3 ten buyuk olmali lutfen tekrar giriniz: ");
		scanf("%d", &n);
	}
	//vezir say�s� * vezir say�s� n*n lik matris allocate ediliyor.
	vm = (int**)calloc(sizeof(int*), n);
	for (i = 0; i<n; i++){
		vm[i] = (int*)calloc(sizeof(int), n);
	}
	
	
	//matris s�f�rlan�yor.
	for (i = 0; i<n; i++){
		for (j = 0; j<n; j++){
			vm[i][j] = 0;
		}
	}
	
	
	vm[0][0] = 1; //�lk g�z 1 yap�l�yor .��nk� ilk vezir hep buraya koyuluyor.
	push(yiginim, 0);//y���na ilk vezirin sat�r� ekleniyor.
	i = 1; //ilk vezir eklendi�i i�in 2. vezirden yani 1. sat�rdan i�lemlere ba�lamak i�in i 1 oluyor.
	j = 0;//her durumda yeni vezir gelince 0. s�tundan bakmaya ba�lan�yor.
	
	//t�m vezirler yel�ene kadar while devam ediyor.
	while (i != n){
		//eklenen vezir ba�ka bir veziri tehdit etmeyinceye kadar while devam ediyor.
		while (j<n && durum == 0){
				durum = yenivezir(i, j, vm, n);
				j++;
		}
		
		j--;
		
		//durum 1 olursa yeni vezir ekleniyor.
		if (durum == 1){
			//vezir bilgiler stacke yaz�l�yor.
			push(yiginim, j);
			vm[i][j] = 1;
			durum = 0;
			i++;
			j = 0;
		}
		else{
			//durum 0 olursa yeni vezir eklenemedi diyor ve �stteki vezir pop ediliyor.
			j = pop(yiginim);
			i--;
			vm[i][j] = 0;
			j++;	
		}

	}
	//matris ekrana yaz�l�yor.
	for (i = 0; i<n; i++){
		for (j = 0; j<n; j++){
			printf("%d", vm[i][j]);
		}
		printf("\n");
	}
	return 0;
}

