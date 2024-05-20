#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main() {
    mknod("fifo_question_d", S_IFIFO | 0666, 0);
    return 0;
}
