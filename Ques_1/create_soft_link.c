#include <unistd.h>

int main() {
    symlink("source_file", "soft_link_name");
    return 0;
}

