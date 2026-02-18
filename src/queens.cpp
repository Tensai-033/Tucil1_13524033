// Header file for input and output
#include <iostream>
#include <bits/stdc++.h>
#include <vector>
#include <map>
#include <tuple>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

int q_number = 0;
int nrows = 0;
int ncols = 0;
bool isLevelTwo = false; // adalah level 2 
bool isLevelThree = false;
bool isLevelFour = false;
bool printFile = true;     // untuk aktifin output ke File
ofstream out_file("output.txt");


vector<int> q_pos;
vector<string> inp_file;

// Debugging
// void printMap(map<char, int> &m){
//     for (const auto& content : m){
//         cout << content.first << " : " << content.second << endl;
//     }
// }

map<char, int> countColours(vector<string> &inp, map<char, int> &clr_map){
    int len_vec = inp.size();

    for (int i = 0; i < len_vec; i++){
        int len_str = inp[i].size();
        for (int j = 0; j < len_str; j++){
            if (clr_map.find(inp[i][j]) == clr_map.end()){ // kalau belum ada di map
                clr_map.insert({inp[i][j], 1});
            }
            else{ // kalau sudah ada di map
                clr_map[inp[i][j]] += 1;
            }
        }
    }
    return clr_map;
}

bool isValidInput(vector<string> s){
    int scols = s[0].size();
    for (int i = 0; i<s.size(); i++){
        if (scols != s[i].size()){
            return false;
        }
    }
    return (s.size() == scols);
}

// enumerated: jadi 1 dimensi
vector<bool> createBoolArr(vector<string> &inp){
    int len_vec = inp.size() * inp[0].size();
    return (vector<bool>(len_vec, false));
}

void printBoolArr(vector<bool> &inp){
    for (int i = 0; i< nrows; i++){
        for (int j = 0; j< ncols; j++){
            if (inp[ncols*i + j]){
                cout<<"#";
                if (printFile){
                    out_file << "#";
                }
            }
            else{
                cout << inp_file[i][j];
                if (printFile){
                    out_file << inp_file[i][j];
                }
            }
        }
        cout << endl;
        if (printFile){
            out_file << endl;
        }
    }
}

vector<int> findPos(vector<bool> &q_bool_array){
    vector<int> pos;
    for (int i = 0; i< q_bool_array.size(); i++){
        if (q_bool_array[i]){
            pos.push_back(i);
        }
    }
    return pos;
}

// Debugging
// void printPos(vector<int> &pos){
//     if (pos.size() == 0){
//         cout << "No queens found!" << endl;
//     }
//     for (int i = 0; i<pos.size(); i++){
//         if (i<pos.size()-1){
//             cout << pos[i] << " - ";
//         }
//         else{
//             cout << pos[i] << endl;
//         }
//     }
// }

tuple<int, int> toCoordinates(int idx){
    // tidak menghandle kasus out of bounds
    return make_tuple((idx/ncols), (idx%ncols));
}

int toIndex(int x, int y){
    // tidak menghandle kasus out of bounds
    return (x*ncols+y);
}

bool isSoloRow(vector<bool> &q_bool_array, int idx){
    if (idx >= q_bool_array.size()){
        cout << "Index " << idx << " out of bounds! Expected < " << q_bool_array.size() << endl;
        if (printFile){
            out_file  << "Index " << idx << " out of bounds! Expected < " << q_bool_array.size() << endl;
        }
        return false;
    }
    auto coor = toCoordinates(idx);
    int x = get<0> (coor);
    bool found_one = false;
    for (int i = 0; i<ncols; i++){
        if (q_bool_array[x*ncols+i]){
            if (!found_one){
                found_one = true;
                continue;
            }
            else{
                return false;
            }
        }
    }
    if (!found_one){
        cout << "No queen in idx: " << idx << endl;
        if(printFile){
            out_file << "No queen in idx: " << idx << endl;
        }
        return false;
    }
    return true;
}

bool isSoloCol(vector<bool> &q_bool_array, int idx){
     if (idx >= q_bool_array.size()){
        cout << "Index " << idx << " out of bounds! Expected < " << q_bool_array.size() << endl;
        if(printFile){
            out_file << "Index " << idx << " out of bounds! Expected < " << q_bool_array.size() << endl;
        }
        return false;
    }
    auto coor = toCoordinates(idx);
    int y = get<1> (coor);
    bool found_one = false;
    for (int i = 0; i<ncols; i++){
        if (q_bool_array[i*ncols+y]){
            if (!found_one){
                found_one = true;
                continue;
            }
            else{
                return false;
            }
        }
    }
    if (!found_one){
        cout << "No queen in idx: " << idx << endl;
        if (printFile){
            cout << "No queen in idx: " << idx << endl;
        }
        return false;
    }
    return true;
}

bool isNoDNeighbour(vector<bool> &q_bool_array, int idx){
    auto coor = toCoordinates(idx);
    int x = get<0> (coor);
    int y = get<1> (coor);
    bool cond1 = false; //x-1, y-1
    bool cond2 = false; //x-1, y+1
    bool cond3 = false; //x+1, y-1
    bool cond4 = false; //x+1, y+1

    if (y != 0){ //bukan ujung kiri
        if (x!=0){ // bukan ujung atas
            cond1 = q_bool_array[toIndex(x-1, y-1)];
        }
        if (x!=nrows-1){ // bukan ujung bawah
            cond3 = q_bool_array[toIndex(x+1, y-1)];
        }
    }

    if (y!= ncols-1){ // bukan ujung kanan 
        if (x!=0){ // bukan ujung atas
            cond2 = q_bool_array[toIndex(x-1, y+1)];
        }
        if (x!=nrows-1){ // bukan ujung bawah
            cond4 = q_bool_array[toIndex(x+1, y+1)];
        }
    }
    return (!(cond1 || cond2 || cond3 || cond4));
}

bool isSoloColour(vector<bool> &q_bool_array, vector<string> &inp){
    map<char, bool> clr_map;
    int len_vec = inp.size();

    for (int i = 0; i<q_number; i++){
        auto coor = toCoordinates(q_pos[i]);
        int x = get<0> (coor);
        int y = get<1> (coor);
        if (clr_map.find(inp[x][y]) == clr_map.end()){ // kalau belum ada di map
            clr_map.insert({inp[x][y], true});
        }
        else{ // kalau sudah ada di map
            return false;
        }
    }
    return true;
}

bool isRuleValid(vector<bool> &q_bool_array){
    for (int i = 0; i<q_number; i++){
        if (!isSoloRow(q_bool_array, q_pos[i]) || 
            !isSoloCol(q_bool_array, q_pos[i]) || 
            !isNoDNeighbour(q_bool_array, q_pos[i])){
            return false;
        }
    }
    return (isSoloColour(q_bool_array, inp_file));
}

int nextPoss(vector<bool> &q_bool_array, int n_queens, bool isPrint)
{
    int arr_len = q_bool_array.size();

    if (isLevelFour){
        vector<int> col(nrows); // simpan posisi sekarang
        for (int i = 0; i < nrows; i++){
            auto coor = toCoordinates(q_pos[i]);
            col[i] = get<1>(coor);
        }

        int i = nrows - 1; // Mulai dari belakang

        while (i >= 0){
            if (col[i] < ncols - 1){ // kalau bisa gerak ke kanan, ke kanan
                col[i]++;
                break;
            }
            else{ // kalau mentok, balek ke paling kiri
                col[i] = 0;
                i--;
            }
        }

        if (i < 0){
            cout << "Semua hasil berhasil ditunjukkan" << endl;
            if (printFile){
                out_file << "Semua hasil berhasil ditunjukkan" << endl;
            }
            return 0;
        }

        for (int j = 0; j < q_bool_array.size(); j++){ // reset papan
            q_bool_array[j] = false;
        }

        q_pos.clear(); // reset q_pos juga

        for (int r = 0; r < nrows; r++){
            int idx = r * ncols + col[r];
            q_bool_array[idx] = true;
            q_pos.push_back(idx); // masukin kembali queens yang sesuai ke q_pos
        }
    }
    else{
        while (1){
            // Cari posisi pivot (queen ter-kanan yang bisa bergerak ke kanan)
            int i;
            for (i = n_queens - 1; i >= 0; i--) {
                if (q_pos[i] < arr_len - (n_queens - i)) {
                    break;
                }
            }

            // Jika semua kemungkinan udah diperiksa
            if (i < 0) {
                cout << "Semua hasil berhasil ditunjukkan" << endl;
                if (printFile){
                    out_file << "Semua hasil berhasil ditunjukkan" << endl;
                }
                return 0;
            }

            q_pos[i]++;

            // reset posisi setelah pivot
            for (int j = i + 1; j < n_queens; j++) {
                q_pos[j] = q_pos[j - 1] + 1;
            }
            for (int j = 0; j < q_bool_array.size(); j++){
                q_bool_array[j] = false;
            }
            for (int j = 0; j < n_queens; j++) {
                q_bool_array[q_pos[j]] = true;
            }

            if (isLevelTwo || isLevelThree) {
                bool allRowColValid = true;
                for (int r = 0; r < n_queens; r++) {
                    allRowColValid = (isSoloRow(q_bool_array, q_pos[r]) && isSoloCol(q_bool_array, q_pos[r]));
                    if (isLevelThree){
                        allRowColValid = allRowColValid && (isNoDNeighbour(q_bool_array, q_pos[r]));
                    }
                    if (!allRowColValid){
                        break;
                    }
                }
                if (!allRowColValid) {
                    continue; 
                }
            }
            break;
        }
    }

    bool isValidSolution = isRuleValid(q_bool_array);
    if (isPrint || isValidSolution){
        printBoolArr(q_bool_array);
        if (isValidSolution){
            return -1;
        }
    }
    return 1;
}




int putQueens(vector<bool> &q_bool_array, int n_queens){
    if (isLevelFour){
        q_pos.clear();
        for (int r = 0; r < nrows; r++){
            int idx = r * ncols;
            q_bool_array[idx] = true;
            q_pos.push_back(idx);
        }
    }
    else{        
        for (int i = 0; i< n_queens; i++){
            int j = i;
            int k = 0;
            while (j >= ncols){ // lanjut ke baris selanjutnya
                j -= ncols;
                k++;
            }
            for (j; j < nrows; j++){
                if (!q_bool_array[k*ncols+j]){
                    q_bool_array[k*ncols+j] = true;
                    break;
                }
            }
        }
    }

    q_pos = findPos(q_bool_array);
    if (q_pos.size() == 0){
        cout << "No queens found!" << endl;
        if (printFile){
            out_file << "No queens found!" << endl;
        }
        return -1;
    }

    int ctr = 0; //counter banyak posisi baru
    int err = 0;
    bool isModZ = true;
    int Z = pow(10, nrows/2); // Bisa diatur tergantung kebutuhan
    if (!isLevelTwo && nrows > 5){
        if (isLevelFour){
            Z *= 10;
        }
        else{
            Z *= 100;
        }
    }
    if (isLevelThree){
        Z /= 10;
    }
    do{
        isModZ = (ctr%Z == 0);
        err = nextPoss(q_bool_array, n_queens, isModZ);
        if (err == 1 || err == -1){
            ctr++;
            if (isModZ || err == -1){
                cout << "Hasil ke-" << ctr << endl << endl;
                if (printFile){
                    out_file << "Hasil ke-" << ctr << endl << endl;
                }
            }
        }
    }
    while (err == 1); 

    q_pos = findPos(q_bool_array);
    if (q_pos.size() == 0){
        cout << "No queens found!" << endl;
        if (printFile){
            out_file << "No queens found!" << endl;
        }
        return -1;
    }

    if (err == -1){
        cout << "Solution found!" << endl;
        if (printFile){
            out_file << "Solution found!" << endl;
        }
    }
    cout << endl;
    if (printFile){
        out_file << endl;
    }
    return 0;
}



int main()
{
    ifstream file("input_7.txt");
    string s;
    char c;
    int i = 0;
    cout << "Reading input: " << endl;
    while (getline(file, s)) {
        inp_file.push_back(s); 
        inp_file[i] = s;
        cout << s << endl;
        i++;
    }
    file.close();

    if (!isValidInput(inp_file)){
        cout << "Error: jumlah kolom tiap baris tidak sama!" << endl;
        return 0;
    }

    
    map<char, int> colour_map;
    colour_map = countColours(inp_file, colour_map);

    q_number = colour_map.size();

    nrows = i;
    ncols = inp_file[0].size();

    if (colour_map.size() != nrows){
        cout << "Error: jumlah warna tidak sesuai!" << endl;
        return 0;
    }

    int inp_digit;

    for (;;) {
        cout << "Pilih level program (1-4; 0 untuk bantuan): ";
        if (cin >> inp_digit) {
            if (inp_digit >= 0 && inp_digit <= 4){
                if (inp_digit == 0){
                    cout << "Level 1: Pure brute force kombinasi" << endl;
                    cout << "Level 2: Validate row and column before outputs" << endl;
                    cout << "Level 3: Validate diagonals before outputs" << endl;
                    cout << "Level 4: Brute force permutasi (langsung skip baris yang sama)" << endl;
                    continue;
                }
                if (inp_digit >= 2){
                    if (inp_digit == 3){
                        isLevelThree = true;
                        cout << "Anda memilih level 3" << endl;
                    }
                    else if (inp_digit == 4){
                        isLevelFour = true;
                        cout << "Anda memilih level 4" << endl;
                    }
                    else{
                        isLevelTwo = true;
                        cout << "Anda memilih level 2" << endl;
                    }
                    break;
                }
                break;
            }
        }
        cout << "Masukkan angka yang valid" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }


    cout << endl << "Finding solutions..." << endl << endl;
    if (printFile){
        out_file << endl << "Finding solutions..." << endl << endl;
    }

    auto start = high_resolution_clock::now();
    vector<bool> q_bool_array;
    q_bool_array = createBoolArr(inp_file);
    
    putQueens(q_bool_array, q_number);

    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop-start);
    cout << "Durasi program: " << duration.count() << "ms" << endl;
    if (printFile){
        out_file << "Durasi program: " << duration.count() << "ms" << endl;
    }
    out_file.close();
    return 0;
}