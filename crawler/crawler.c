
//simple hello file
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "webpage.h"
int main(void){
  
  printf("hello\n");
  
  
  char *urlp = "https://thayer.github.io/engs50/";
  webpage_t *webpage1 = webpage_new(urlp, 0, NULL);
  bool p = webpage_fetch(webpage1);
  int pos=0;
  char *result;
  queue_t *qp;
  queue_t *urlq;
  webpage_t *webpage2;

  
  if (!p){ 		      				    
    exit(EXIT_FAILURE);
  }
 
  while((pos = webpage_getNextURL(webpage1, pos, &result))>=0){
    qp = qopen();
   
    if(IsInternalURL(result)){
      //printf("internal url: %s\n", result);
      webpage2 = webpage_new(result, 0, NULL);
      qput(qp,(void*)webpage2);
      free(result);
    }
    else{
      //printf("external url: %s\n", result);
      free (result);
      }
  
   
    //while(qp->front != NULL){
      urlq= (queue_t*)qget(qp);
      while (urlq->front != NULL){ 
      printf("%p\n", urlq->front);
    }  
  }
  qclose(qp);
  free(webpage_getHTML(webpage1));
  free(webpage1);
  free(webpage2);
  exit(EXIT_SUCCESS);
}
                                                                                                                          
  
