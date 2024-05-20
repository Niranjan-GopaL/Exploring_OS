#include <sys/types.h>
#include <sys/stat.h>


int main() {
    mkfifo("./fifoe", 0744);
}