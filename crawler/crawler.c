
//simple hello file
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>
#include <unistd.h>
#include "queue.h"
#include "hash.h"
#include "webpage.h"

FILE *fp;
char *urlp = "https://thayer.github.io/engs50/";
webpage_t *seedwebpage, *currwebpage, *childwebpage;
int pos=0;
char *result;
queue_t *qp;
int counter=0;
hashtable_t *hp;
void* found;
char *pages= "../pages/";
int res;
int idx=1;
int depth = 0;
bool fetched;
char *pagefromqueue;

int32_t pagesave(webpage_t *pagep,int id, char *dirname);

bool searchfn(const char *result, const char searchkey[10]){
  if (strcmp(result, searchkey)==0){
    return true;
  }
  else {
    return false;
  }
}

int main(int argc, char *argv[]){
  if (argc != 4){
    printf("usage: crawler <seedurl> <pagedir> <maxdepth>\n");
    exit(EXIT_FAILURE);
  }
  
  res = access(argv[2], F_OK);
  if (res != 0){
    printf("usage: crawler <seedurl> <pagedir> <maxdepth>\n");
    exit (EXIT_FAILURE);
  }

  if(atoi(argv[3]) < 0){
    printf("usage: crawler <seedurl> <pagedir> <maxdepth>\n");
    exit (EXIT_FAILURE);
  }

  qp = qopen();
  hp = hopen(100); 
  seedwebpage = webpage_new(argv[1], depth, NULL);
  int32_t p= qput(qp, (void*)seedwebpage);
  int32_t p2= hput(hp, (void*)argv[1], argv[1], sizeof(argv[1]));
  
  /*if (argv[3] ==0){
    fetched = webpage_fetch(seedURLpage);		      			       
    pagesave(seedURLpage, idx, argv[2]);
    }*/

  pagefromqueue=(webpage_t*)qget(qp);
  while (pagefromqueue != NULL){
    currwebpage =pagefromqueue;
    fetched = webpage_fetch(currwebpage);
    pagesave(currwebpage, idx, argv[2]);
    idx++;
    depth = webpage_getDepth(currwebpage);
    printf (" %d \n", depth);
    if (depth < atoi(argv[3])){
      depth = depth + 1; 
      pos = 0;
      while((pos = webpage_getNextURL(currwebpage, pos, &result)) > 0){
	if(IsInternalURL(result)){
	   found = hsearch(hp, searchfn, result, sizeof(result));
	   if(found == NULL){  
	    printf("internal url: %s\n", result);
	    childwebpage = webpage_new(result, depth , NULL);
	    fetched = webpage_fetch(childwebpage);
	    counter++;
	    pagesave(childwebpage, idx, argv[2]);
	    int32_t p= qput(qp, (void*)childwebpage);
	    int32_t p2= hput(hp, (void*)result, result, sizeof(result));
	    free(p);
	    free(p2);
	    free (result);
	  }
	}
	else{
	  printf("external url: %s\n", result);
	  free (result);
	}
      }
    }
		
    /*printf("The urls that are in the queue: \n");
      while(counter > 0){
      printf("i//n queue: %s\n", (char*) qget(qp));
      counter= counter -1;
      }*/
	 
    pagefromqueue = (webpage_t*)qget(qp);
    printf("url from queue: %s\n", webpage_getURL(pagefromqueue));
    counter= counter -1;
  }
	
  qclose(qp);
  hclose(hp);
  free(webpage_getHTML(seedwebpage));
  free(seedwebpage);
  free(childwebpage);
  free(currwebpage);
  exit(EXIT_SUCCESS);
}



int32_t pagesave(webpage_t *pagep, int id, char *dirname){

  const char pathname[60];
  char *urlp= webpage_getURL(pagep);
  char *htmlp= webpage_getHTML(pagep);
  int depth= webpage_getDepth(pagep);
  int HTMLlen= webpage_getHTMLlen(pagep);

  sprintf(pathname, "%s%d",dirname, id);
  fp=fopen(pathname, "w+");
  fprintf(fp, " %s\n %d\n %d\n %s", urlp, depth, HTMLlen, htmlp);
  fclose(fp);
}

 
