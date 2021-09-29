#include "lfu_cache.hpp"

int main() {
    LFUCache<int> lfu(3);
    lfu.put(1);
    lfu.print_cache();
    lfu.put(2);
    lfu.print_cache();
    lfu.put(3);
    lfu.print_cache();
    lfu.put(4);
    lfu.print_cache();
    lfu.get(2);
    lfu.print_cache();
    lfu.get(2);
    lfu.get(2);
    lfu.get(4);
    lfu.get(3);
    lfu.print_cache();
}