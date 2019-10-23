
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
webpage_t *webpage1, *webpage2, *webpage3;
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


int32_t pagesave(webpage_t *pagep,int id, char *dirname);

bool searchfn(const webpage_t *pagep, const char searchkey[10]){
  if (strcmp(webpage_getURL(pagep), searchkey)==0){
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

  
  printf("hello\n");
  qp = qopen();
  hp = hopen(100); 
  webpage1 = webpage_new(argv[1], depth, NULL);
  int32_t p= qput(qp, (void*)argv[1]);
  int32_t p2= hput(hp, (void*)webpage1, argv[1], sizeof(argv[1]));
  
  if (argv[3] ==0){
  fetched = webpage_fetch(webpage1);		      			       
  pagesave(webpage1, idx, argv[2]);
  }

  else{
 
    while (depth < atoi(argv[3])){
      webpage2 = webpage_new((char*)qget(qp),depth , NULL);
      fetched = webpage_fetch(webpage2);
      
      depth++;
      
      while((pos = webpage_getNextURL(webpage2, pos, &result))>=0){
	if(IsInternalURL(result)){
	  printf("internal url: %s\n", result);
	  webpage3 = webpage_new(result, depth , NULL);
	  fetched = webpage_fetch(webpage3);
	  found = hsearch(hp, searchfn, result, sizeof(result));
	  if(found == NULL){
	    idx++;
	    pagesave(webpage3, idx, argv[2]);
	    int32_t p= qput(qp, (void*)result);
	    counter++;
	    int32_t p2= hput(hp, (void*)webpage3, result, sizeof(result));
	    free(p);
	    free(p2);
	    //free(result);
	  }
	}
      
	else{
	  printf("external url: %s\n", result);
	  free (result);
	}
      }
    }
  }
  
  printf("The urls that were added to the queue: \n");
  while(counter >= 0){
    printf("in queue: %s\n", (char*) qget(qp));
    counter= counter -1;
  }
  
  qclose(qp);
  hclose(hp);
  free(webpage_getHTML(webpage1));
  free(webpage1);
  free(webpage2);
  free(webpage3);
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


 
