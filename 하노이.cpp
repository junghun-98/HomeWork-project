#include "std_lib_facilities.h"

vector<vector<int>> Createtower(int disk_num)
{
    vector<vector<int>> Tower(3);
    vector<int> disk_size;

    for (int i = disk_num; i > 0; i--)
        disk_size.push_back(i);

    Tower[0] = disk_size;

    return Tower;
}
int Allowmove(int from, int to, int size, vector<vector<int>> Tower) //�̵� ���� ���� �Լ�
{
    if (from < 1 || to < 1 || from > size || to > size) return 0;    //ž�� �������� ����

    else if (from == to) return 0;                                   //�ű�� ž�� �ű���� ž�� ����

    else if (Tower[from - 1].size() == 0) return 0;                  //�ű���� ž�� ��ũ�� ����

    else if (Tower[to - 1].size() > 0                                //ū ��ũ�� �� ���� ��ũ���� �ö�
        &&
        Tower[from - 1][Tower[from - 1].size() - 1] > Tower[to - 1][Tower[to - 1].size() - 1])
        return 0;

    else return 1;
}
string Decide()
{
    string decision = " ";

    while (true) { //����� ���� Ȯ��, �ڵ� Ǯ�� ����
        cin >> decision;
        if (decision != "Y" && decision != "N")
            cout << "This is an invalid answer. Please input again : ";
        else break;
    }
    return decision;
}
void Sloveautohanoi(int disk, int from, int temp, int to) {
    if (disk == 1) {
        cout << '\n' << "Move disk " << disk << " from tower " << from << " to tower " << to << "\n";
    }
    else {
        Sloveautohanoi(disk - 1, from, to, temp);
        cout << '\n' << "Move disk " << disk << " from tower " << from << " to tower " << to << "\n";
        Sloveautohanoi(disk - 1, temp, from, to);
    }
}
void PrintTower(vector<vector<int>> Tower) //Ÿ�� ��Ȳ ���
{
    int sizeofTower = Tower.size();

    for (int i = 0; i < sizeofTower; i++) {
        cout << "Tower[" << i + 1 << "] : ";

        int Tower_I_size = Tower[i].size();
        for (int j = 0; j < Tower_I_size; j++) {
            if (Tower[i][j] != 0)
                cout << Tower[i][j] << " ";
        }
        cout << '\n';
    }
}
void MoveDisk(vector<vector<int>>& Tower, int from, int to) //��ũ�̵� �Լ�
{
    Tower[to - 1].push_back(Tower[from - 1][Tower[from - 1].size() - 1]);
    Tower[from - 1].pop_back();
}
void ReEntermove(int& from, int& to) //�ٽ� �Է�
{
    while (!cin)
    {
        cout << "You entered an incorrect value!" << '\n';
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Please input again : ";
        cin >> from >> to;
    }
}
void ReEnterdisk(int& disk) //�ٽ� �Է�
{
    while (!cin || disk < 3)
    {
        cout << "You entered a value less than 3 or an incorrect value!" << '\n';
        cin.clear();
        cin.ignore(100, '\n');
        cout << "Please input again : ";
        cin >> disk;
    }
}

int main() {
    while (true) { //���� ����
        vector<vector<int>> HanoiTower = {};
        vector<int> first_tower;             //���� ���� ���� Ȯ���� ���� ù ��° ž
        int number_of_disk = 0;              //������ ����
        int movecount = 1;                   //�̵� Ƚ��

        cout << "Please select the number of disks(3 or more) : ";

        cin >> number_of_disk;
       
        if (!cin) ReEnterdisk(number_of_disk);  
        else if (number_of_disk < 3) ReEnterdisk(number_of_disk);

        HanoiTower = Createtower(number_of_disk);
        first_tower = HanoiTower[0];
        PrintTower(HanoiTower);

        //�ڵ� Ǯ�� �ǻ� ������
        cout << "Would you like to slove it automatically? If ""Y"", the program will be terminated. (Y/N) : ";                
        if (Decide() == "Y") {
            PrintTower(HanoiTower);
            Sloveautohanoi(number_of_disk, 1, 2, 3);
            cout << '\n' << "The minimum number of times to move the disk is " << (1 << number_of_disk) - 1 << "times." << '\n';
            break;
        }

        while (true) { //���� �̵�
            int size_of_Hanoi = HanoiTower.size();
            int from = 0, to = 0;                   //�ű� ��� ����, ���� ��� ���� 
            int movecheck = 0;                      //���� �̵� ���� ���� �Ǵ� ����

            //���� ���� ���� Ȯ�� ��
            if (first_tower == HanoiTower[2]) {
                cout << "Congratulation! You Slove it in "
                    << movecount - 1 << " times!" << '\n';
                cout << " Do you play again? (Y/N): ";
        
                if (Decide() == "Y") {
                    cout << '\n' << "-----PLAY AGAIN!-----" << "\n\n";
                    HanoiTower.clear();
                    break;
                }
                else if (Decide() == "N") {
                    cout << '\n' << "-----Thank you for playing!-----" << '\n';
                    exit(true);
                }
            }

            cout << "[" << movecount << "] Which tower will you move from which tower? (From (1|2|3), to (1|2|3)) : ";

            cin >> from >> to;
            if (!cin) ReEntermove(from, to);

            movecheck = Allowmove(from, to, size_of_Hanoi, HanoiTower);

            if (movecheck == 1) {                                   //�̵�����
                MoveDisk(HanoiTower, from, to);
                cout << '\n' << "---Move succeeded !---" << "\n\n";
                PrintTower(HanoiTower);
                movecount++;
            }
            else cout << '\n' << "---Move failed !---" << '\n';     //�̵��Ұ�

            cout << '\n';
        }
    }
}
