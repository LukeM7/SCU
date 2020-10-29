// Key solution
#include "pn.h"

void leaveCS(int i){
    j = (turn+1) % N;
        while (flag[j]==idle)
            j = (j+1)%N;
        turn = j;       
        flag[i]=idle;   
    printf("Thread %d left Critical Section\n", i);
}

void enterCS(int i){
        while (1) {
            flag[i] = want_in;     
            j = turn;

            while (j != i) {
                if (flag[j] != idle)
                    j = turn;
                else
                    j = (j+1) % N; // 
            }
                flag[i] = in_cs;
                j = 0;

                while ( (j<N) && (j==i || flag[j] != in_cs))
                    j++;
                if ( (j>=N) && (turn==i || flag[turn]==idle))
                    break;      
        }
    printf("Thread %d entered Critical Section\n", i);

}

void *thread(void* arg) {
        int i = (int)arg;
        enterCS(i);
        sleep(5);
        leaveCS(i);
        printf("Goodbye\n");
        return 0;
}

int main(){
    int i;
    for (i = 0; i < N; i++)
         pthread_create(&thread_id[i], NULL, thread, (void*)(size_t)i);
    for (i = 0; i < N; i++)
        pthread_join(thread_id[i], NULL);
    return 0;
}
