
//simple hello file
#include <stdio.h>
#include <string.h>
#include "queue.h"
#include "hash.h"
#include "webpage.h"

int main(void){
  
  printf("hello\n");
  
  
  char *urlp = "https://thayer.github.io/engs50/";
  webpage_t *webpage1, *webpage2;
  int pos=0;
  char *result;
  queue_t *qp;
  int counter=0;
  //hashtable_t *hp;
  
  qp = qopen();
  // hp = hopen(10);
  
  webpage1 = webpage_new(urlp, 0, NULL);

  if (webpage_fetch(webpage1)!=true){ 		      			       
    exit(EXIT_FAILURE);
  }
  
  while((pos = webpage_getNextURL(webpage1, pos, &result))>=0){
    if(IsInternalURL(result)){
      printf("internal url: %s\n", result);
      webpage2 = webpage_new(result, 0, NULL);
      //if(((char*)found=hsearch()) == NULL){
      
      int32_t p= qput(qp, (void*)result);
      counter++;
	//int32_t p2= hput(hp, (void*)result, const char *key, int keylen);
	printf(" %d \n", p);
	//free(result);
	//}
    }
  
    else{
      printf("external url: %s\n", result);
      free (result);
    }
  }
  
  while(counter >= 0){
    // print(qp.isEmpty);
    printf("in queue: %s\n", (char*) qget(qp));
    counter= counter -1;
  }
  
  qclose(qp);
  // hclose(hp);
  free(webpage_getHTML(webpage1));
  free(webpage1);
  free(webpage2);
  exit(EXIT_SUCCESS);
}
                                                                                                                          
  
