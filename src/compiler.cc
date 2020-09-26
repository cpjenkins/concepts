// get basic compiler info

#include <cstring>
#include <cstdio>
#include <string>

int main() {
    fprintf(stderr, "[compiler]:     %s\n", "gcc");
    fprintf(stderr, "[cpp-standard]: %ld\n", __cplusplus);
    return 0;
}
