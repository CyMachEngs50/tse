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
#include "pageio.h"
#include "webpage.h"


typedef struct index{
	hashtable_t *htwords;
	int htsize;
}index_t;

typedef struct wordcounter {
    struct wordcounter *head;
} wordcounter_t

index_t *index_new(const int htsize){
	index_t *index = malloc(sizeof(index_t)); 
	index->htwords = hopen(htsize); 
	index->htsize = htsize;
	return index;
}

bool searchfn(const void* pagep, const void* searchkey){                       
  if (strcmp(webpage_getNextWord(pagep), searchkey)==0){                       
    return true;                                                               
  }                                                                            
  else {                                                                       
    return false;                                                              
  }                                                                            
}      

index_t index = index_new(200);

if (index != NULL && word != NULL && id >= 0) {
	wordcounter_t *word_count = hsearch(htwords,searchfn, wordsizeof(word));
	if (word_count != NULL) {
	}
	else {


	}
 }



bool Normalizeword(const char* word[20]){
	bool status = true;
	int valid_ext;
	int i;
	if 

	for(i=0; i<strln(word); i++){
		word[i]= tolower(word[i]);
	}	
}
										
int main (void){
	webpage_t* webpage1;
	bool fetched;
	char* pages= "../pages/";
	char* word;
	int pos=0;

	webpage1= pageload(1, pages);
	fetched= webpage_fetch(webpage1);
	
	while((pos = webpage_getNextword(webpage1,pos,&word)) > 0){
		Normalizeword(word);
		printf(" %s\n", word);
		free(word);
	}
	
}
