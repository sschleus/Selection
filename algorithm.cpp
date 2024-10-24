#include <vector>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;


class AlgorithmRandomized {
    vector<int> list;
    int k;
    int comparisons = 0;
    public:
    AlgorithmRandomized(vector<int>&& list, int k): list(move(list)), k(k) {srand(time(0));}

    /*******
     * QuickSelect Algorithm. Inspired implementation by: https://fr.wikipedia.org/wiki/Quickselect
     ******/
    int quickSelect(int start, int end) {
        if(start == end) {
            return list[start];
        }
        int pivot_id = start + (rand() % (end + 1 - start));
        swap(list[end], list[pivot_id]);

        int seat = start;
        for(int i = start; i <= end-1; i++) {
            comparisons += 1;
            if(list[i] < list[end]) {
                swap(list[i], list[seat]);
                seat += 1;
            }
        }

        swap(list[end], list[seat]);
        if(k == seat) {
            return list[seat];
        }
        else if(k < seat) {
            return quickSelect(start, seat-1);
        }
        else {
            return quickSelect(seat+1, end);
        }
}

   
    /*****
     * QuickSort for LazySelect from https://fr.wikipedia.org/wiki/Tri_rapide
     *****/
    void quickSort(vector<int>& vec, int start=0, int end=-1) {
        if(end == -1) {end = vec.size()-1;}
        if(start < end) {
            int pivot_idx = start + (rand() % (end + 1 - start));
            swap(vec[pivot_idx], vec[end]);

            int seat = start;
            for(int i = start; i <= end - 1; i++) {
                if(vec[i] < vec[end]) {
                    swap(vec[i], vec[seat]);
                    seat++;
                }
                comparisons+=1;
            }
            swap(vec[seat], vec[end]);
            quickSort(vec, start, seat-1);
            quickSort(vec, seat+1, end);

        }
            
        }

    /******
     *  Lazy select algorithm from the book randomized algorithms of motwani and raghavan
     *****/
    int lazySelect() {
        //Step 1
        int r = static_cast<int>(pow(list.size(), 3.0 / 4.0));
        cout << r << endl;
        vector<int> R;
        for(int i = 0; i <= r; i++) {
            R.push_back(list[rand() % list.size()]);
        }

        //Step 2
        quickSort(R, 0, R.size()-1);
        cout << getComparisonsNoReset() << endl;

        //Step 3
        int x = static_cast<int>(k *  pow(list.size(), -1.0/4.0));
        int l = max(static_cast<int>(floor(x-sqrt(list.size()))), 0);
        int h = min(static_cast<int>(ceil(x+sqrt(list.size()))), static_cast<int>(pow(list.size(), 3.0/4.0)));
        int a = R[l];
        int b = R[h];

        int a_seat = 0;
        int b_seat = 0;
        for(int i = 0; i < list.size(); i++) {
            if(a > list[i]) {a_seat++;}
            if(b > list[i]) {b_seat++;}
        }

        //Step 4
        vector<int> P;
        bool condition1 = true;
        int idx_res = k - a_seat;
        if(k < static_cast<int>(pow(list.size(), 1.0/4.0))) {
            if(k <= b_seat) {
                idx_res = k;
                for(int i = 0; i < list.size(); i++) {
                if(list[i] <= b) {
                    P.push_back(list[i]);}
                }
            }
            else {
                condition1 = false;
            }

        }
        else if (k > (list.size()-static_cast<int>(pow(list.size(), 1.0/4.0)))) {
            if(k >= a_seat) {
                for(int i = 0; i < list.size(); i++) {
                    if(list[i] >= a) {
                        P.push_back(list[i]);}
                    }

            }
            else {
                condition1 = false;
            }
        }
        else {
            if(k >= a_seat && k <= b_seat) {
            for(int i = 0; i < list.size(); i++) {
                if(list[i] >= a && list[i] <= b) {
                    P.push_back(list[i]);}
                }
            }
            else {
                condition1 = false;
            }
        }

        bool condition2 = (P.size() <= 4 * pow(list.size(), 3.0/4.0)+2);
        if(!(condition2) || !(condition1)) {
            return lazySelect();
        }

        //Step 5
        cout << getComparisonsNoReset() << endl;
        quickSort(P, 0, P.size()-1);
        cout << getComparisonsNoReset() << endl;
        return P[idx_res];


    }

void print(vector<int> vector) {
    for(auto& i: vector) {
        cout << i << " ";
    }
    cout << endl;
}

int getComparisons() {
    int res = comparisons;
    comparisons = 0;
    return res;
}

int getComparisonsNoReset() {
    int res = comparisons;
    return res;
}

};