
/* indexer.c --- 
 * 
 * 
 * Author:char *word;                                                                                       
 Gregory G. Macharia
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

#include <hash.h>
#include <pageio.h>
#include <webpage.h>
#include <queue.h>

char *word;
//wordcounter_t word_count;
//hashtable_t *htwords;

/*typedef struct index{
	hashtable_t *htwords;
	int htsize;
	}index_t;*/

/*typedef struct wordcounter {
	struct wordcounter *head;
	struct wordcounter *next;
	int wcount;
	} wordcounter_t;*/

/*index_t* index_new(const int htsize){
	index_t *index = malloc(sizeof(index_t)); 
	index->htwords = hopen(htsize); 
	index->htsize = htsize;
	return index;
}
*/
typedef struct entry_t{                                                                                      
  char *id;                                                                                                  
  int count;                                                                                                 
}entry_t;    

bool qsearchfn(void* entryp, const void* searchkey){
	entry_t *entry= (entry_t*) entryp;
	if (strcmp(entry->id, searchkey)==0){          
    return true;
  }                                                                   
  else {
    return false;
  }
}

typedef struct word_t{                                                                                       
  queue_t *queue;                                                                                            
  char* name;                                                                                                
}word_t;      

bool hsearchfn(void* wordp, const void* searchkey){
	word_t *word= (word_t*) wordp;
	if (strcmp(word->name, searchkey)== 0){
		return true;
	}
	else{
		return false;
	}
}

entry_t* new_entry(char *docid){
	entry_t *entryp;
	if (!(entryp=malloc(sizeof(entry_t)))){
		printf("Error: no memory was allocated to the entry\n");
		return NULL;
	}
	entryp->id= docid;
	entryp->count=1;
	return entryp;
}

word_t* new_word(char *word){
	word_t* wordp;
	if (!(wordp=malloc(sizeof(word_t)))){
		printf("Error: no memory was allocated to the word_t\n");
		return NULL;
	}
	wordp->name= word;
	wordp->queue= qopen();
	return wordp;
}

bool add_to_index(hashtable_t *index, char *word, char* docid){
	entry_t *searched_entry;
	entry_t *entryp;
	int32_t p,p2;
	bool result=false;
	word_t *searched_word;
	word_t *currword;
	
	searched_word= hsearch(index,hsearchfn,word,sizeof(word));
	if (searched_word != NULL){
		printf(" in hashtable\n");  
		searched_entry= qsearch(searched_word->queue, qsearchfn, docid);
		if (searched_entry != NULL){
			printf(" in queue\n");
			searched_entry->count = searched_entry->count +1;
			result= true;
		}
		else{
			printf(" not in queue\n");
			entryp= new_entry(docid);
			qput(searched_word->queue,entryp);
			result=true;
		}
		printf(" count: %d\n", searched_entry->count);
	}
	else{
		currword= new_word(word);
		printf(" not in hash table\n");
		p=hput(index, currword, word, sizeof(word));
		entryp=new_entry(docid);
		p2=qput(currword->queue, entryp);
		result = true;
		if (p !=0 || p2 !=0){
			result=false;
		}
	}
 
	return result;
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
	int pos=0;
	char *word;
	webpage_t *webpage;
	bool fetched, lowered, added; 
	char *pages= "../pages/";
	char *docid= "../pages/1";
	hashtable_t *index= NULL;

	
	webpage= pageload(1, pages);
	fetched= webpage_fetch(webpage);
	index= hopen(400);
	if (fetched == true){
		index= hopen(100);
		while((pos = webpage_getNextWord(webpage,pos,&word)) > 0){
			lowered= NormalizeWord(word);
			if(lowered){
				printf("word to add: %s\n", word); 
				added= add_to_index(index, word, docid);
				if (added != true){
					printf("failed to add to the index\n");
				}
			}
		}
		free(word);
	}
	else{
		printf("html not found\n");
    exit(EXIT_FAILURE);
  }
	hclose(index);
	exit(EXIT_SUCCESS);
}
