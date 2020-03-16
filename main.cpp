#include <QCoreApplication>
#include <iostream>
#include <iomanip> //setw
#include <random>
#include <vector>
using namespace std;

const int MAX_CAPACITY = 1000000;
struct Disk {
    list<int> files;
    int sum = 0;
    void updateSum(){
        sum += files.back();
    }
};

vector<int> fillConstValue() {
    vector<int> arr = {484802, 420713, 396295, 392019, 262926, 254274,
                       230973, 204065, 324387, 320414, 311011, 347661,
                       347560, 286309, 340190, 331812, 326585, 383972,
                       351543, 263485};
    return arr;
}

vector<int> fillRandomValue(uint N) {
    vector<int> arr;
    arr.resize(N);
    for(auto& el: arr)
        el = rand() % (MAX_CAPACITY) + 1;
    return arr;
}

void outputVector(vector<int> vec){
    for(auto el: vec)
        cout << el << " ";
    cout<<endl;
}

void outputDisks(vector<Disk> disks){
    int i = 0;
    cout<<endl;
    for(auto disk: disks){
        cout << "Disk " << setw(3) << i++ << " " << setw(7);
        cout<< MAX_CAPACITY - disk.sum << ": ";
        for(auto file: disk.files)
            cout << file << " ";
        cout<<endl;
    }
}

void testMethods(vector<Disk> (*fstFunc)(vector<int>), vector<Disk> (*secFunc)(vector<int>)){
    vector<uint> testN = {10, 100, 1000, 10000, 100000, 1000000};
    for(uint N : testN){
        vector<int> files = fillRandomValue(N);
        cout << "N = " << N << endl;
        uint start = clock();
        vector<Disk> disks = fstFunc(files);
        uint end = clock() - start;
        cout << " Heuristic 1 used disks: " << disks.size() << endl;
        cout << " Time spent: " << end << endl;
        start = clock();
        disks = secFunc(files);
        end = clock() - start;
        cout << " Heuristic 2 used disks: " << disks.size() << endl;
        cout << " Time spent: " << end << endl;
    }
}

// Best Fit Decreasing
vector<Disk> heuristic_2(vector<int> vec){
    sort(vec.begin(), vec.end(), greater<int>());
    vector<Disk> disks;
    Disk first;
    disks.push_back(first);

    for(auto file: vec){
        int index = -1, min = MAX_CAPACITY + 1;
        for(uint i = 0; i < disks.size(); i++){
            if(disks[i].sum + file <= MAX_CAPACITY && MAX_CAPACITY - disks[i].sum - file < min){
                min = MAX_CAPACITY - disks[i].sum - file;
                index = i;
                if(min == 0)
                    break;
            }
        }
        if(index != -1){
            disks[index].files.push_back(file);
            disks[index].updateSum();
        } else{
            Disk newDisk;
            newDisk.files.push_back(file);
            newDisk.updateSum();
            disks.push_back(newDisk);
        }
    }

    return disks;
}

// First Fit Decreasing
vector<Disk> heuristic_1(vector<int> vec){
    sort(vec.begin(), vec.end(), greater<int>());
    vector<Disk> disks;
    Disk first;
    disks.push_back(first);

    for(auto file: vec){
        bool success = false;
        for(auto &disk: disks)
            if(disk.sum + file <= MAX_CAPACITY){
                disk.files.push_back(file);
                disk.updateSum();
                success = true;
                break;
            }
        if(success) continue;
        Disk newDisk;
        newDisk.files.push_back(file);
        newDisk.updateSum();
        disks.push_back(newDisk);
    }
    return disks;
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    std::cout<<"Entry amount of files"<<std::endl;
    uint N;
    cin >> N;
    vector<int> inputFiles;
    srand(time(nullptr));
    inputFiles = fillRandomValue(N);
    //inputFiles = fillConstValue();

    //outputVector(inputFiles);
    //outputDisks(heuristic_1(inputFiles));
    //outputDisks(heuristic_2(inputFiles));
    testMethods(heuristic_1, heuristic_2);

    return 0;
}
