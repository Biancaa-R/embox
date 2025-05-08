#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

static volatile int keep_running = 1;

static void handle_signal(int sig) {
	keep_running = 0;
    printf("HANDLER\n");
    exit(0);
}

int main() {
    keep_running=1;
    signal(SIGTERM, handle_signal);
    while (keep_running) {
        printf("WORKING\n");
        sleep(5);
    }
    printf("END\n");
    return 0;
}