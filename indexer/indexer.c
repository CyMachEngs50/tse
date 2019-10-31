/* indexer.c --- 
 * 
 * 
 * Author: Gregory G. Macharia
 * Created: Mon Oct 28 16:33:30 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <unistd.h>
#include <pageio.h>
#include <webpage.h>
#include <hash.h>

int pos, id;
char *word;
//wordcounter_t word_count;
hashtable_t *htwords;

typedef struct index{
	hashtable_t *htwords;
	int htsize;
}index_t;

typedef struct wordcounter {
	struct wordcounter *head;
	struct wordcounter *next;
	int wcount;
} wordcounter_t;

index_t* index_new(const int htsize){
	index_t *index = malloc(sizeof(index_t)); 
	index->htwords = hopen(htsize); 
	index->htsize = htsize;
	return index;
}

bool searchfn(const void* pagep, const void* searchkey){                       
  if (strcmp(webpage_getNextWord(pagep,pos,word), searchkey)==0){          
    return true;                                                               
  }                                                                            
  else {                                                                       
    return false;                                                              
  }                                                                            
}      

//index_t *index = index_new(200);

int wcount = 0;

void Addindex(index_t *index, const char *word, const int id){
	if (index != NULL && word != NULL && id >= 0) {
		htwords = hopen(100);
		wordcounter_t *word_count = hsearch(htwords,searchfn, word, sizeof(word));
		if (word_count == NULL) {
			wordcounter_t *word_count = malloc(sizeof(wordcounter_t));
			word_count = word_count->head;
				wcount = 1;
        return word_count;
    }
		
		else {
		word_count = word_count->next;
		wcount+=1;
	}
	}
}

bool NormalizeWord(char word[20]){
	int i, isalpha;
	bool result=false;
	
	if (word != NULL){
		for(i=0; i<strlen(word); i++){
			word[i]=	tolower(word[i]);
		}
		result=true;
		if (strlen(word)< 3){
			result= false;
		}
		for(i=0; i<strlen(word); i++){                                                            
      isalpha=  isalpha(word[i]);
			if (isalpha == 0){
				result= false;
			}
    } 
	}
	return result;
}


int main (void){
	webpage_t *webpage;
	bool fetched, lowered;
	char *pages= "../pages/";
	
	webpage= pageload(1, pages);
	fetched= webpage_fetch(webpage);
	if (fetched == true){                                                                 
		while((pos = webpage_getNextWord(webpage,pos,&word)) > 0){
			lowered= NormalizeWord(word);
			if(lowered){
				/*  Addindex(index, word, id);*/
				printf(" %s\n", word);
			}
			free(word);
		} 
	}                                                                                     
  else{                                                                                 
    printf("html not found\n");                                                         
    exit(EXIT_FAILURE);                                                                 
  }  
}
