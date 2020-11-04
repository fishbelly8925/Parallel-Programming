#include <algorithm>
#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <cstdio>
#include <vector>
#include <thread>
#include <string>
#include <pthread.h>
#include <climits>
#include <ctime>
#include <cmath>
#include <queue>
#include <set>

using namespace std;
using std::string;
using std::thread;

int cnt;
int thread_num;
long long n;

pthread_mutex_t mutex;

void* pp(void* rank) {
    long local_rank = (long)rank;
    long iter_num = (local_rank > n % thread_num) ? n / thread_num: n / thread_num + 1;

    double x, y, d;
    long local = 0;

    for (long i = 0; i < iter_num; i++) {

        x = (double)rand() / RAND_MAX;
        y = (double)rand() / RAND_MAX;
        d = x * x + y * y;

        if (d < 1) local++;
    }

    pthread_mutex_lock(&mutex);
    cnt += local;
    pthread_mutex_unlock(&mutex);
    return NULL;
}


int main(int argc, char* argv[]) {
    //cin.sync_with_stdio(0);
    //cin.tie(0);
    pthread_t* ppthread;

    thread_num = stoi(argv[1], NULL, 10);
    n = stoll(argv[2], NULL, 10);
    ppthread = (pthread_t*) malloc(thread_num * sizeof(pthread_t));
    pthread_mutex_init(&mutex, NULL);
    cnt = 0;

    srand(time(NULL));
    
    for (long i = 0; i < thread_num; i++) {
        pthread_create(&ppthread[i], NULL, pp, (void*)i);
    }

    for (int i = 0; i < thread_num; i++) {
        pthread_join(ppthread[i], NULL);
    }

    double ans = (double) cnt / (double) n;
    cout << setprecision(20) << ans * 4 << '\n';

    pthread_mutex_destroy(&mutex);
    free(ppthread);
    return 0;
}
