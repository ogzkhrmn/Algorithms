#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

struct hash{
	char hashtable[9013][5];
};	
void addtohash(struct hash *myhash){
	char word[6];  //readen word from text file
	int key,i,h1,h2,j;  // i and j for loops
						//h1 and h2 using for finding to address
						//key for keys.
						int tmp;
	FILE *fp;
	fp=fopen("text.txt","r");   
	while(fgets(word,6,fp)!=NULL){
		key=0;
		
		//creating key
		for(i=0;i<4;i++){
			key=key*61+word[i];
		}
		h1=key%9013;
		
		//if first looking addres is empty,the word adding there
		if(!strcmp(myhash->hashtable[h1],"0000")){
			for(j=0;j<4;j++){
			myhash->hashtable[h1][j]=word[j];	
			}
		}
		//else, findinng new address for theese words
				else{
			i=1;
			tmp=h1;
			while(strcmp(myhash->hashtable[tmp],"0000")){
				h2=1+(key%9012);
			tmp=(h1+i*h2)%9013;
			i++;
			}	
			for(j=0;j<4;j++){
			myhash->hashtable[tmp][j]=word[j];	
			}
		}	
	}
	fclose(fp);
	
	//writing struct to file. 
	fp=fopen("struct.ohero","wb");   
	fwrite(myhash, sizeof(struct hash), 1, fp);
	fclose(fp);
}

int play(char word[5],int mode,char knownwords[256][5],char playersug[5],int place,struct hash *myhash){
	int i,j;  //using for loops
	int key;  //using for hash key
	int h1,h2;  //using for find to hash adress
	int checkarray[4];  //control array
	int checkarray2[4];  //control array
	int findchar=0;    //if we can find a equal character,increasing this variable.
	int tmp;
	//do all elements of check arrays 1
	for(i=0;i<4;i++){
		checkarray2[i]=1;
		checkarray[i]=1;
	}
	j=0;
	
	//controlling two words
	while(j<4){
		i=0;
		while(i<4){
			
			//if we can find equal char,i increase.
		if(playersug[i]==word[j] && checkarray[i]){
			checkarray[i]=0;
			checkarray2[j]=0;
			i=5;
			findchar++;
			}	
			else{
				i++;
			}
		}
		j++;
	}
	
	//if all characters equal, that means this words can be anagram
	if(findchar==4){
		for(i=0;i<place;i++){
			
			//controlling this word used before
			if(!strcmp(knownwords[i],playersug)){
				printf("You already use that word.\n");
				return -5;
			}
		}
		
		//if didnt use, we searching this word in hash table
		for(i=0;i<4;i++){
			key=key*61+playersug[i];
		}
		h1=key%9013;
		if(!strcmp(myhash->hashtable[h1],playersug)){
			if(mode==1){
				printf("H1('%s')=%d\n",playersug,h1);
			}
				printf("It is anagram.\n");
			return 5;
		}
		else{
			if(!strcmp(myhash->hashtable[h1],"0000")){
				return -5;	
				printf("It isn't anagram.\n");
			}
			i=1;
		tmp=h1;
			while(strcmp(myhash->hashtable[h1],playersug)&& h2!=h1){
				h2=1+(key%9012);
			tmp=(h1+i*h2)%9013;
			i++;
			if(mode==1){
				printf("H1('%s')=%d\n",playersug,tmp);	
			}
			if(h1==tmp){
				
					printf("It isn't anagram.\n");
				return -5;
			}
			}
			
			if(mode==1)
				printf("It is anagram.\n");
				return 5;
		}
	}
	else{
		printf("It isn't anagram.\n");
		return -5;
	}
	
}

int main(){
	char key; 
	int score=0; //player score
	int i; //for loops
	int r; //random number
	int mode; //debug or normal
	int j=0;
	char knownwords[24][5];
	char playersug[5];
	char word[5];
	printf("Do you want to create a new hash table? Y/N\n");
	key=getch();
	struct hash *myhash;//hash table
	myhash=(struct hash*)malloc(sizeof(struct hash));
	//create a new hash table ?
	if(key=='y' || key=='Y'){
		
	for(i=0;i<9013;i++){
		strcpy(myhash->hashtable[i],"0000"); //resetting table
	}
	//function for create a new table
	addtohash(myhash);	
	}
	
	else{
		//reading hash struct file
	FILE *fp;
	fp=fopen("struct.ohero","rb"); //
	fread(myhash, sizeof(struct hash), 1, fp);
        fclose(fp);	
	}
	
	printf("Do you want to start with debug mode ? Y/N\n");
	key=getch();
		j=0;
		srand(time(NULL));
		r = rand()%9013;
		while(!strcmp(myhash->hashtable[r],"0000")){
			r=rand()%9013;
		}
		
		printf("%s\n",myhash->hashtable[r]);
		strcpy(knownwords[j],myhash->hashtable[r]);
		j++;
		
	if(key=='y' || key=='Y'){
		
	mode = 1;
	}
	
	else{
	mode=0;
	}
	printf("Kelime\n");
	scanf("%s",&word);
	while(1){
	
		printf("A word please.\n");
		scanf("%s",&playersug);
		if(play(word,mode,knownwords,playersug,j,myhash)==5){
			score+=5;
			strcpy(knownwords[j],playersug);
			j++;
		}
		else{
			score-=5;
		}
		printf("Player Score:%d\n",score);
		printf("Do you want to finish game? Y/N\n");
		key=getch();
		if(key=='y' || key=='Y'){
			exit(1);
		}
		printf("Do you want to new word game? Y/N\n");
		key=getch();
		if(key=='y' || key=='Y'){
		j=0;
		srand(time(NULL));
		r = rand()%9013;
		while(!strcmp(myhash->hashtable[r],"0000")){
			r=rand()%9013;
		}
		printf("%s\n",myhash->hashtable[r]);
		strcpy(knownwords[j],myhash->hashtable[r]);
		j++;
		}
	}
	return 0;
}
