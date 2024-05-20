#include <sys/types.h>
#include <sys/stat.h>


int main() {
    mkfifo("./fifo_quesiton_e", 0744);
}