#ifndef LRU_CACHE_H
#define LRU_CACHE_H

#include <iostream>
#include <list>
#include <stdlib.h>
#include <unordered_map>

template <class T>
class LRUCache {
    public:
        LRUCache(int n) {
            csize = n;
        }

        bool get(const T& item) {
            if (!refs.count(item)) {
                return false;
            } 
            q.erase(refs[item]);
            q.push_front(item);
            refs[item] = q.begin();
            return true;
        }

        void print_cache() {
            std::cout << "";
            typename std::list<T>::iterator i = q.begin();
            while (i != q.end()) {
                T item = *i;
                std::cout << item << " ";
                i++;
            }
        }

        void put(const T& item) {
            if (!get(item)) {
                if (q.size() == csize) {
                    removeLast();
                }

                q.push_front(item);
                refs[item] = q.begin();
            }
        }


        void remove(const T& item) {
            if (refs.count(item)) {
                q.erase(refs[item]);
                refs.erase(item);
            }
        }


        void removeLast() {
            if (q.size() > 0) {
                T last = q.back();
                q.pop_back();
                refs.erase(last);
            }
        }

    private:
        unsigned int csize;
        std::list<T> q;
        std::unordered_map<T, typename std::list<T>::iterator> refs;
};

#endif