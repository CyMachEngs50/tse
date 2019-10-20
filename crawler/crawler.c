<<<<<<< HEAD
//simple hello file
#include <stdio.h>
#include <string.h>
#include "webpage.h"


int main(void){
  
  printf("hello\n");
  
  char *urlp = "https://thayer.github.io/engs50/";
  webpage_t *webpage1 = webpage_new(urlp, 0, NULL);
  bool p = webpage_fetch(webpage1);
  int pos=0;
  char *result;
  
  if (!p){ 		      				    
    exit(EXIT_FAILURE);
  }
 
  while((pos = webpage_getNextURL(webpage1, pos, &result))>=0){
    if(IsInternalURL(result)){
      printf("internal url: %s\n", result);
      free(result);
    }
    else{
      printf("external url: %s\n", result);
      free (result);
      }
  }
  
  free(webpage_getHTML(webpage1));
  free(webpage1);
  exit(EXIT_SUCCESS);
}
=======
/* crawler.c --- 
 * 
 * 
 * Author: Gregory Macharia and Cynthia Jeruto
 * Created: Sat Oct 19 15:12:25 2019 (-0400)
 * Version: 
 * 
 * Description: 
 * 
 */
#include <stdio.h>                                                                                                                             
#include <string.h>                                                                                                                            
                                                                                                                                               
                                                                                                                                               
int main(void){                                                                                                                                
                                                                                                                                               
  printf("hello\n");                                                                                                                           
  return 0;                                                                                                                                    
                                                                                                                                               
}      
>>>>>>> 093563e937804e887ca00b140fe9fa4780201699
