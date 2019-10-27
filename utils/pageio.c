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
#include "pageio.h"

FILE *fp;
char *pathname;
int32_t pagesave(webpage_t *pagep, int id, char *dirname){
	
  char *urlp= webpage_getURL(pagep);
  char *htmlp= webpage_getHTML(pagep);
  int depth= webpage_getDepth(pagep);
  int HTMLlen= webpage_getHTMLlen(pagep);

  sprintf(pathname, "%s%d",dirname, id);
  fp=fopen(pathname, "w+");
  fprintf(fp, " %s\n %d\n %d\n %s", urlp, depth, HTMLlen, htmlp);
  fclose(fp);
}

 
