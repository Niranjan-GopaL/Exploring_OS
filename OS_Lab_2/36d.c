/*Description:
create fifo file by mknod library function
*/
#include <sys/stat.h>

int main() {
    mknod("./fifod", S_IFIFO | 0744, 0);
}
