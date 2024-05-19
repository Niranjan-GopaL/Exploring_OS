/*Description:program to print the created thread ids.
*/
#include<stdio.h>
#include<pthread.h>
void * fun(){
    printf("%lu\n",pthread_self());
}


int main(){
    pthread_t t;
    for(int i = 0 ; i<3 ; i++){
        pthread_create(&t,NULL,fun,NULL);

    }
    pthread_exit(NULL); 
}
