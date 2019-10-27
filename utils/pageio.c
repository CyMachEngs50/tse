
#include <inttypes.h>
#include "pageio.h"


int32_t pagesave(webpage_t *pagep, int id, char *dirname){
  FILE *fp;
  char *pathname;
  char *urlp= webpage_getURL(pagep);
  char *htmlp= webpage_getHTML(pagep);
  int depth= webpage_getDepth(pagep);
  int HTMLlen= webpage_getHTMLlen(pagep);

  sprintf(pathname, "%s%d",dirname, id);
  fp=fopen(pathname, "w+");
  fprintf(fp, " %s\n %d\n %d\n %s", urlp, depth, HTMLlen, htmlp);
  fclose(fp);
}
