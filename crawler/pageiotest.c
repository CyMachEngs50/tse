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
//#include "pageio.h"
#include "webpage.c"
#include "pageio.c"

int main (void){
	char* test= "../test";
	char* pages= "../pages";
	webpage_t *page;

	page= pageload(1, pages);
	printf("loaded!\n");
	pagesave(page, 2, pages);
	printf("saved!\n");  
	exit(EXIT_SUCCESS);
}
