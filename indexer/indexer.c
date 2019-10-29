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
	while((pos = webpage_getNextword(webpage1,pos,$word)) > 0){
		printf(" %s\n", word);
	}
	
}
