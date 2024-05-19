#include <unistd.h>

int main() {
    link("source_file", "hard_link_name");
    return 0;
}

