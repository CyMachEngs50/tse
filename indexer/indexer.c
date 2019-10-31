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
#include "hash.h"

int pos, id;
char word;
wordcounter_t word_count;
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

index_t *index = index_new(200);

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
/*
bool Normalizeword(char *word[20]){
	bool status = true;
	int valid_ext;
	int i;
	if 

	for(i=0; i<strln(word); i++){
		word[i]= tolower(word[i]);
	}	
}
*/

char *NormalizeWord (char *word){
  if (word != NULL) {
    for (char *w = word; *w != '\0'; w++)
      *w = tolower(*w);
  }
  return word;
}

int main (void){
	webpage_t* webpage1;
	bool fetched;
	char* pages= "../pages/";

	webpage1= pageload(1, pages);
	fetched= webpage_fetch(webpage1);
	
	while((pos = webpage_getNextWord(webpage1,pos,&word)) > 0){
		NormalizeWord(word);
		Addindex(index, word, id);
		printf(" %d\n", word);
		free(word);
	}
	
}
