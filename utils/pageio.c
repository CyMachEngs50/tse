/* pageio.c --- implements phttpagesave and pageload
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

#include <pageio.h>
#include <queue.h>

#define MAXCHAR 100

int32_t pagesave(webpage_t *pagep, int id, char *dirname){
	
	char pathname[60];                                              
	char *urlp= webpage_getURL(pagep);                               
	char *htmlp= webpage_getHTML(pagep);
	int depth= webpage_getDepth(pagep);                                         
	int HTMLlen= webpage_getHTMLlen(pagep);
	FILE *fp;
	
	sprintf(pathname, "%s%d",dirname, id);
	fp=fopen(pathname, "w+");                                                     
	fprintf(fp, "%s\n%d\n%d\n%s", urlp, depth, HTMLlen, htmlp);
	fclose(fp);
	return 1;
} 

/*                                                                             
 * pageload -- loads the numbered filename <id> in direcory <dirnm>            
 * into a new webpage                                                          
 *    
 * returns: non-NULL for success; NULL otherwise      
 */                                                                                 
webpage_t *pageload(int id, char *dirnm){

	char pathname[60];
	char result [120];
	FILE *fp;
	webpage_t *loaded_webpage;
	char URL[120];
	int depth= 0;
	int i, len;
	char *urlp;

	
	sprintf(pathname, "%s%d",dirnm, id);
	fp=fopen(pathname, "r+");

	if (fp== NULL){
		printf("no such file\n");
		return NULL;
	}
	i=0;
	while (i< 2){
		fgets(result, 100, fp);
		if (i== 0){
			strcpy(URL, result);
			len= strlen(URL   ) -1;
				if (URL[len] == '\n'){
				URL[len]= '\0';
			}
			urlp= URL;
		}
		if(i== 1){
			depth= atoi(result);
		}
		i= i+1;
	}

	fclose(fp);
	loaded_webpage = webpage_new(urlp,depth, NULL);
	return loaded_webpage;
	
}
