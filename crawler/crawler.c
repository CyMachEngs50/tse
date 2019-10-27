
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
webpage_t *pagefromqueue;

int32_t pagesave(webpage_t *pagep,int id, char *dirname);

<<<<<<< HEAD
bool searchfn(void* pagep, const void* searchkey){
   printf("entered searchfn\n");
   if (strcmp(webpage_getURL((webpage_t*)pagep), (char*)searchkey)==0){
     printf("compared true\n");
=======
bool searchfn(const void* pagep, const void* searchkey){
  if (strcmp(webpage_getURL(pagep), searchkey)==0){
>>>>>>> 838b086c90afd13a4751a38bedded8baef869d23
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
<<<<<<< HEAD
  int32_t p= qput(qp, (webpage_t*)seedwebpage);
  int32_t p2= hput(hp, seedwebpage, argv[1], sizeof(argv[1]));
  printf("put \n");
   
=======
  int32_t p= qput(qp, (void*)seedwebpage);
  int32_t p2= hput(hp, seedwebpage, argv[1], sizeof(argv[1]));
  

>>>>>>> 838b086c90afd13a4751a38bedded8baef869d23
  pagefromqueue=(webpage_t*)qget(qp);
  while (pagefromqueue != NULL){
    printf("entered while loop");
    currwebpage =pagefromqueue;
    fetched = webpage_fetch(currwebpage);
    pagesave(currwebpage, idx, argv[2]);
    idx++;
    depth = webpage_getDepth(currwebpage);
    printf ("%d \n", depth);
    if (depth < atoi(argv[3])){
      printf("passed if condition");
      depth = depth + 1; 
      pos = 0;
      while((pos = webpage_getNextURL(currwebpage, pos, &result)) > 0){
<<<<<<< HEAD
	printf("entered second while loop\n");
	if(IsInternalURL(result)){
	  printf("going into found\n");
	   found = hsearch(hp, searchfn, result, sizeof(result));
	   printf("found\n");
	   if(found == NULL){  
	    printf("internal url: %s\n", result);
	    childwebpage = webpage_new(result, depth , NULL);
	    fetched = webpage_fetch(childwebpage);
	    counter++;
	    pagesave(childwebpage, idx, argv[2]);
	    int32_t p= qput(qp, (void*)childwebpage);
	    int32_t p2= hput(hp, (void*)childwebpage, result, sizeof(result));
	    free(p);
	    free(p2);
	    free (result);
	  }
	}
	else{
	  printf("external url: %s\n", result);
	  free (result);
	}
=======
				if(IsInternalURL(result)){
					found = hsearch(hp, searchfn, result, sizeof(result));
					if(found == NULL){  
						printf("internal url: %s\n", result);
						childwebpage = webpage_new(result, depth , NULL);
						fetched = webpage_fetch(childwebpage);
						counter++;
						pagesave(childwebpage, idx, argv[2]);
						int32_t p= qput(qp, (void*)childwebpage);
						int32_t p2= hput(hp, (void*)childwebpage, result, sizeof(result));
						free(p);
						free(p2);
						free (result);
					}
				}
				else{
					printf("external url: %s\n", result);
					free (result);
				}
>>>>>>> 838b086c90afd13a4751a38bedded8baef869d23
      }
    }
		
		pagefromqueue = (webpage_t*)qget(qp);
    printf("url from queue: %s\n", webpage_getURL(pagefromqueue));
    counter= counter -1;
  }
	
  qclose(qp);
  hclose(hp);
  free(webpage_getHTML(seedwebpage));
  free(seedwebpage);
  free(childwebpage);
  exit(EXIT_SUCCESS);
}



/*int32_t pagesave(webpage_t *pagep, int id, char *dirname){

  char *pathname[60];
  char *urlp= webpage_getURL(pagep);
  char *htmlp= webpage_getHTML(pagep);
  int depth= webpage_getDepth(pagep);
  int HTMLlen= webpage_getHTMLlen(pagep);

  sprintf(pathname, "%s%d",dirname, id);
  fp=fopen(pathname, "w+");
  fprintf(fp, " %s\n %d\n %d\n %s", urlp, depth, HTMLlen, htmlp);
  fclose(fp);
}
*/
<<<<<<< HEAD
=======
 
>>>>>>> 838b086c90afd13a4751a38bedded8baef869d23
