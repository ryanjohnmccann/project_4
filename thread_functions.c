
#include "thread_functions.h"

#include <pthread.h>

void *Process(void *id) {
    pthread_exit((void *) id);
}
