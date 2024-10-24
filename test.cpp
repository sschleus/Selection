#include "algorithm.cpp"
#include <algorithm>
#include <cassert>
#include <random>

vector<int> getRandomVector(int n) {
    //from: https://www.geeksforgeeks.org/how-to-generate-a-vector-with-random-values-in-c/
    vector<int> vector(n, 0); 
    srand(time(0)); 
    generate(vector.begin(), vector.end(), rand); 
    return vector;

}

void testQuickSort() {
    vector<int> vec_fk;
    AlgorithmRandomized algo = AlgorithmRandomized(move(vec_fk), 0);
    int counter = 0;

    while(counter < 1) {
    vector<int> vec = getRandomVector(177);
    vector<int> vec2 = vec;
    cout << counter << endl;
    algo.quickSort(vec, 0, vec.size()-1);
    sort(vec2.begin(), vec2.end());
    for(int i = 0; i < vec.size(); i++) {
        assert(vec[i] == vec2[i]);
    }
    counter++;
    }
    cout << algo.getComparisons() << endl;
    cout << "**********" << endl;

};

void testAlgo() {
    int counter = 0;
    while(counter < 100) {
        vector<int> vec;
        int k = 1 + rand() % 19;
        int num_k = rand();
        int how_many = 0;
        for(int i = 0; i < k-1; ++i) {
            vec.push_back(rand()%num_k);
            how_many++;
        }
        vec.push_back(num_k);
        for(int j = k; j < 100; ++j) {
            vec.push_back(num_k + (rand()%10000));
        }

        random_device rd; 
        mt19937 g(rd()); 
        shuffle(vec.begin(), vec.end(), g);
        int size = vec.size();
        AlgorithmRandomized algo = AlgorithmRandomized(move(vec), k-1);

        int res_quick = algo.quickSelect(0, size-1);
        int res_lazy = algo.lazySelect();
        assert(res_quick == res_lazy);
        assert(res_lazy == num_k);
        counter += 1;
    };

}

int main() {
    srand(time(0));
    //testAlgo();
    testQuickSort();
    return 0;
}