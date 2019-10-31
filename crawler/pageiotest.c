/* pageiotest.c --- tests loading and saving
 * 
 * 
 * Author: Cynthia J. Bundi
 * Created: Mon Oct 28 18:32:22 2019 (-0400)
 * Version: 1.0
 * 
 * Description: 
 * 
 */

#include <stdio.h>
#include <stdbool.h>
#include <webpage.h>
#include <pageio.h>

int main (void){
	char* pages2= "../pages2/";
	char* pages= "../pages/";
	webpage_t *page;
	bool fetched;

	page= pageload(1, pages);
	printf("loaded!\n");
 
	fetched= webpage_fetch(page);
	if (fetched == true){
		pagesave(page, 2, pages2);
	}
	else{
		printf("html not found\n");
		exit(EXIT_FAILURE);
	}
	printf("saved!\n");  
	exit(EXIT_SUCCESS);
}
