#ifndef LFU_CACHE_H
#define LFU_CACHE_H

#include <algorithm>
#include <iostream>
#include <list>
#include <stdlib.h>
#include <map>
#include "lru_cache.hpp"

template <class T>
class LFUCache {
    public:
        LFUCache(int n) {
            csize = 0;
            capacity = n;
            minFreq = 1;
            maxFreq = 1;
        }

        bool get(const T& item) {
            if (!valToFreq.count(item)) {
                return false;
            }

            int* freq = &valToFreq[item];
            LRUCache<T>* lru = freqToVal[*freq];
            lru->remove(item);

            (*freq)++;
            if (!freqToVal.count(*freq)) {
                LRUCache<T>* lru_ = new LRUCache<T>(csize);
                freqToVal[*freq] = lru_;
            }

            lru = freqToVal[*freq];
            lru->put(item);

            // if minimum frequency changed, this frequency is the new min
            if (!freqToVal.count(minFreq)) {
                minFreq = *freq;
            }
            maxFreq = std::max(*freq, maxFreq);
            return true;
        }
        
        void print_cache() {
            std::cout << "Cache: ";
            typename std::map<int, LRUCache<T>* >::iterator it = freqToVal.end();
            while (it != freqToVal.begin()) {
                it--;
                it->second->print_cache();
            }
            std::cout << '\n';
        }

        void put(const T& item) {
            if (!get(item)) {
                if (csize == capacity) {
                    LRUCache<T>* lru_ = freqToVal[minFreq];
                    lru_->removeLast();
                    csize--;
                }
                int freq = 1;
                valToFreq[item] = freq;

                if (!freqToVal.count(freq)) {
                    LRUCache<T>* lru_ = new LRUCache<T>(csize);
                    freqToVal[freq] = lru_;
                }

                LRUCache<T>* lru = freqToVal[freq];
                lru->put(item);

                csize++;
            }
        }

    private:
        int csize;
        int capacity;
        int minFreq;
        int maxFreq;
        std::map<int, LRUCache<T>* > freqToVal;
        std::unordered_map<T, int> valToFreq;
};

#endif