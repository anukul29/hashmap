#include <iostream>
#include<deque>
using namespace std;

template<typename k, typename v>
class hashmap{
    class hmnode{
        public:
        k key;
        v value;
        hmnode(k key, v value){
            this->key = key;
            this->value = value;
        }
    };
    public:
    int size;
    deque<deque<hmnode *>> buckets;

    hashmap(){
        initbuckets(4);
        size = 0;
    }

    void initbuckets(int n){
        buckets.resize(n);
        size = 0;
    }

    void rehash(){
        deque<deque<hmnode *>> oba = buckets;
        initbuckets(oba.size() * 2);
        size = 0;

        for(int i = 0; i <oba.size(); i++){
            for(auto node : oba[i]){
                put(node->key, node->value);
            }
        }
    }
    void put(k key, v value){
        int bi = hashfn(key);
        int di = getidxwithinbucket(key, bi);

        if(di != -1){
            hmnode *node = new hmnode(key, value);
            // node->value = value;
            buckets[bi][di] = node;
        }
        else{
            hmnode *node = new hmnode(key, value);
            buckets[bi].push_back(node);
            size++;
        }
        double lambda = size *1.0 /buckets.size();
        if(lambda > 2.0){
            rehash();
        }
    }
    int hashfn(k key){
        int hc = hash<k>{}(key);
        return abs(hc) % buckets.size();
    }
    int getidxwithinbucket(k key, int bi){
        int di = 0;
        for(auto node : buckets[bi]){
            if(node->key == key){
                return di;
            }
            di++;
        }
        return -1;
    }

    bool containskey(k key){
        int bi = hashfn(key);
        int di = getidxwithinbucket(key, bi);

        if(di != -1){
            return true;
        }
        else{
            return false; 
        }
    }

    v get(k key){
        int bi = hashfn(key);
        int di = getidxwithinbucket(key, bi);

        if(di != -1){
            hmnode *node = buckets[bi][di];
            return node->value;
        }
        else{
            return NULL;
        }
    }
    int sizemap(){
        return size;
    }
};

int main(){

    hashmap<std::string, int> myHashMap;

    // Insert some key-value pairs
    myHashMap.put("one", 1);
    myHashMap.put("two", 2);
    myHashMap.put("three", 3);
    std::cout << "size of hashmap: " << myHashMap.sizemap() << std::endl;
    myHashMap.put("four", 4);
    myHashMap.put("five", 5);
    myHashMap.put("six", 6);
    myHashMap.put("sss", 0);
    myHashMap.put("aa", 99);

    std::cout << "Value of 'one': " << myHashMap.get("one") << std::endl;
    std::cout << "Value of 'aa': " << myHashMap.get("aa") << std::endl;
    std::cout << "size of hashmap: " << myHashMap.sizemap() << std::endl;

    return 0;
}