#include <iostream>
#include <stdexcept>
#include <vector>

using namespace std;

class Tower {
public:
    Tower(int disks_num) {
        FillTower(disks_num);
    }

    int GetDisksNum() const {
        return disks_.size();
    }

    void SetDisks(int disks_num) {
        FillTower(disks_num);
    }

    void AddToTop(int disk) {
        int top_disk_num = disks_.size() - 1;
        if (0 != disks_.size() && disk >= disks_[top_disk_num]) {
            throw invalid_argument("Невозможно поместить большой диск на маленький");
        }
        else {
            disks_.push_back(disk);
        }
    }

    void MoveDisk(Tower& destination)
    {
        if (disks_.size() > 0)
        {
            int disk = disks_.back();
            disks_.pop_back();
            destination.AddToTop(disk);
        }
    }

    void MoveDisks(int disks_num, Tower& destination, Tower& buffer) {
        if (disks_num > 0)
        {
            MoveDisks(disks_num - 1, buffer, destination);
            MoveDisk(destination);
            buffer.MoveDisks(disks_num - 1, destination, (*this));
        }
    }

private:
    vector<int> disks_;
    void FillTower(int disks_num) {
        for (int i = disks_num; i > 0; i--) {
            disks_.push_back(i);
        }
    }
};

void SolveHanoi(vector<Tower>& towers) {
    int disks_num = towers[0].GetDisksNum();
    towers[0].MoveDisks(disks_num, towers[2], towers[1]);
}

int main() {
    int towers_num = 3;
    int disks_num = 3;
    vector<Tower> towers;
    for (int i = 0; i < towers_num; ++i) {
        towers.push_back(0);
    }
    towers[0].SetDisks(disks_num);
    try
    {
        SolveHanoi(towers);
    }
    catch (const exception& e)
    {
        cerr << e.what() << endl;
    }    
}
