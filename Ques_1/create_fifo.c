#include <sys/types.h>
#include <sys/stat.h>

int main() {
    mkfifo("fifo_name", 0666);
    return 0;
}

