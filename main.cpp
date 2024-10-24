#include "algorithm.cpp"
#include <chrono>
#include <random>


vector<int> getRandomVector(int n) {
    //from: https://www.geeksforgeeks.org/how-to-generate-a-vector-with-random-values-in-c/
    vector<int> vector(n, 0); 
    generate(vector.begin(), vector.end(), rand); 
    random_device rd; 
    mt19937 g(rd()); 
    shuffle(vector.begin(), vector.end(), g);
    return vector;

}

void testAlgorithms() {
    int size = 10000;
    int bount_quick = 3.386 * size;
    int bount_lazy = 2 * size;
    vector<int> vec = getRandomVector(size);
    vector<int> vec2 = vec;
    int k = 1 + rand() % 998;
    AlgorithmRandomized algorithm1 = AlgorithmRandomized(move(vec), k);
    AlgorithmRandomized algorithm2 = AlgorithmRandomized(move(vec2), k);
    auto start = std::chrono::high_resolution_clock::now();
    algorithm1.quickSelect(0, size-1);
    auto stop = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Quick --> Number of comparisons:"  << algorithm1.getComparisons() << endl;
    cout << "Time: " <<  duration.count() << endl;
    cout << "Max allowed:" << bount_quick <<  endl;
    cout << "****" << endl;
    auto start2 = std::chrono::high_resolution_clock::now();
    algorithm2.lazySelect();
    auto stop2 = std::chrono::high_resolution_clock::now();
    auto duration2 = std::chrono::duration_cast<std::chrono::microseconds>(stop - start);
    cout << "Time: " <<  duration2.count() << endl;
    cout << "Lazy --> Number of comparisons:"  << algorithm2.getComparisons() << endl;
    cout << "Average allowed:" << bount_lazy <<  endl;


}

int main() {
    srand(time(0)); 
    testAlgorithms();
    return 0;
}