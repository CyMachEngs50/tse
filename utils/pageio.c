/* pageio.c --- implements pagesave and pageload
 * 
 * 
 * Author: Gregory G. Macharia & Cynthia Bundi
 * Created: Sun Oct 27 15:38:19 2019 (-0400)
 * Version: 1.0
 * 
 * Description: 
 * 
 */


#include <inttypes.h>
#include <stdio.h>
#include "pageio.h"


int32_t pagesave(webpage_t *pagep, int id, char *dirname){
	
	const char pathname[60];                                              
	char *urlp= webpage_getURL(pagep);                               
	char *htmlp= webpage_getHTML(pagep);                                           
	int depth= webpage_getDepth(pagep);                                         
	int HTMLlen= webpage_getHTMLlen(pagep);
	FILE *fp;
	sprintf(pathname, "%s%d",dirname, id);                             
	fp=fopen(pathname, "w+");                                                     
	fprintf(fp, " %s\n %d\n %d\n %s", urlp, depth, HTMLlen, htmlp);
	fclose(fp);                                    
} 

/*                                                                             
 * pageload -- loads the numbered filename <id> in direcory <dirnm>            
 * into a new webpage                                                          
 *    
 * returns: non-NULL for success; NULL otherwise      
 */                                                                                 
webpage_t *pageload(int id, char *dirnm){

	const char pathname[60];
	FILE *fp;
	webpage_t *loaded_webpage;
	char URL;
	int depth;
	
	sprintf(pathname, "%s%d",dirnm, id);
	fp=fopen(pathname, "r+");
	
	//	printf("outside while\n");
	while(fscanf(fp, " %s",)== 1){
		//printf("inside while\n");
		URL = fgets(id, 0, stdin);
		//printf("fgets 1 \n");
		depth = fgets(id, 1, stdin);
	}
	
	loaded_webpage = webpage_new(URL,depth, NULL);
	return loaded_webpage;
	
}
