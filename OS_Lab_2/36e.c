/*Description:
create fifo file by mkfifo library function
*/
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    mkfifo("./fifoe", 0744);
}
