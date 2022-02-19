#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
int count = 0;
int loop_step = 0;
int loop_action = 0;
sem_t sem_action;
sem_t sem_step;
void* step(  )
{
 while( count <= 1000 )
 {
 if( (count % 10) == 0 )
 {
 sem_post( &sem_action );
 sem_wait( &sem_step );
 }
 count += 1;
 loop_step += 1;
 }
 pthread_exit( NULL );
}
void* action( )
{
    while( count <= 1000 )
    {
        sem_wait( &sem_action );
        count += rand() % 6;
        loop_action += 1;
        sem_post( &sem_step );
    }
    pthread_exit( NULL );
}
int main()
{
    pthread_t t1, t2;
    pthread_create( &t1, NULL, step, NULL );
    pthread_create( &t2, NULL, action, NULL );
    pthread_join( t1, NULL );
    pthread_join( t2, NULL );
    printf( "step: %d\n", loop_step );
    printf( "action %d\n", loop_action );
    exit(0);
}

