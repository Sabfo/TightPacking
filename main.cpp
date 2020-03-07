#include <QCoreApplication>
#include <iostream>
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

vector<int> fillRandomValue(vector<int> arr) {
    for(auto& el: arr)
        el = rand() % (MAX_CAPACITY/2);
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
        cout << "Disk " << i++ << " " << MAX_CAPACITY - disk.sum << ": ";
        for(auto file: disk.files)
            cout << file << " ";
        cout<<endl;
    }
}

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
    cin>>N;
    vector<int> inputFiles;
    inputFiles.resize(N);
    srand(5);
    inputFiles = fillRandomValue(inputFiles);
    //inputFiles = fillConstValue();
    outputVector(inputFiles);
    outputDisks(heuristic_1(inputFiles));

    //a.exec();
    return 0;
}
