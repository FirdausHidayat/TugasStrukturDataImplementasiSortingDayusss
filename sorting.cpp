#include <iostream>
#include <vector>
#include <iomanip>
#include <string>

using namespace std;

// ============================================================
// UTILITY FUNCTIONS
// ============================================================

void printArray(const vector<int>& arr) {
    cout << "[ ";
    for (int i = 0; i < (int)arr.size(); i++) {
        cout << setw(3) << arr[i];
        if (i < (int)arr.size() - 1) cout << ",";
    }
    cout << " ]" << endl;
}

void printHeader(const string& title) {
    cout << "\n" << string(60, '=') << endl;
    cout << "  " << title << endl;
    cout << string(60, '=') << endl;
}

void printIterasi(int iterasi, const vector<int>& arr, const string& keterangan = "") {
    cout << "  Iterasi " << setw(3) << iterasi << " : ";
    printArray(arr);
    if (!keterangan.empty()) {
        cout << "              >> " << keterangan << endl;
    }
}

// ============================================================
// 1. BUBBLE SORT
// ============================================================

void bubbleSort(vector<int> arr) {
    printHeader("1. BUBBLE SORT");
    int n = arr.size();
    int iterasi = 0;

    cout << "\n  Data Awal   : ";
    printArray(arr);
    cout << "\n  --- Proses Iterasi ---\n";

    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        iterasi++;
        string ket = "Pass ke-" + to_string(i + 1) + ", elemen terbesar ke posisi akhir";
        printIterasi(iterasi, arr, ket);
        if (!swapped) {
            cout << "  >> Array sudah terurut, berhenti lebih awal.\n";
            break;
        }
    }

    cout << "\n  Data Hasil  : ";
    printArray(arr);
    cout << "  Total Iterasi: " << iterasi << endl;
}

// ============================================================
// 2. SELECTION SORT
// ============================================================

void selectionSort(vector<int> arr) {
    printHeader("2. SELECTION SORT");
    int n = arr.size();
    int iterasi = 0;

    cout << "\n  Data Awal   : ";
    printArray(arr);
    cout << "\n  --- Proses Iterasi ---\n";

    for (int i = 0; i < n - 1; i++) {
        int minIdx = i;
        for (int j = i + 1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        if (minIdx != i) {
            swap(arr[i], arr[minIdx]);
        }
        iterasi++;
        string ket = "Elemen minimum " + to_string(arr[i]) + " dipindahkan ke posisi " + to_string(i);
        printIterasi(iterasi, arr, ket);
    }

    cout << "\n  Data Hasil  : ";
    printArray(arr);
    cout << "  Total Iterasi: " << iterasi << endl;
}

// ============================================================
// 3. INSERTION SORT
// ============================================================

void insertionSort(vector<int> arr) {
    printHeader("3. INSERTION SORT");
    int n = arr.size();
    int iterasi = 0;

    cout << "\n  Data Awal   : ";
    printArray(arr);
    cout << "\n  --- Proses Iterasi ---\n";

    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key;
        iterasi++;
        string ket = "Menyisipkan " + to_string(key) + " ke posisi yang tepat";
        printIterasi(iterasi, arr, ket);
    }

    cout << "\n  Data Hasil  : ";
    printArray(arr);
    cout << "  Total Iterasi: " << iterasi << endl;
}

// ============================================================
// 4. QUICK SORT
// ============================================================

int quickSortIterasi = 0;

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[arr[j] == arr[i] ? i : j]); // Swap aman
            if (i != j) {
                // Hanya swap jika indeks berbeda
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSortHelper(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSortIterasi++;
        string ket = "Pivot=" + to_string(arr[pi]) + " di indeks " + to_string(pi);
        printIterasi(quickSortIterasi, arr, ket);
        quickSortHelper(arr, low, pi - 1);
        quickSortHelper(arr, pi + 1, high);
    }
}

void quickSort(vector<int> arr) {
    printHeader("4. QUICK SORT");
    quickSortIterasi = 0;

    cout << "\n  Data Awal   : ";
    printArray(arr);
    cout << "\n  --- Proses Iterasi ---\n";

    quickSortHelper(arr, 0, (int)arr.size() - 1);

    cout << "\n  Data Hasil  : ";
    printArray(arr);
    cout << "  Total Iterasi (partisi): " << quickSortIterasi << endl;
}

// ============================================================
// 5. MERGE SORT
// ============================================================

int mergeSortIterasi = 0;

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    mergeSortIterasi++;
    string ket = "Merge [" + to_string(left) + ".." + to_string(mid) + "] & [" + to_string(mid+1) + ".." + to_string(right) + "]";
    printIterasi(mergeSortIterasi, arr, ket);
}

void mergeSortHelper(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid);
        mergeSortHelper(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

void mergeSort(vector<int> arr) {
    printHeader("5. MERGE SORT");
    mergeSortIterasi = 0;

    cout << "\n  Data Awal   : ";
    printArray(arr);
    cout << "\n  --- Proses Iterasi ---\n";

    mergeSortHelper(arr, 0, (int)arr.size() - 1);

    cout << "\n  Data Hasil  : ";
    printArray(arr);
    cout << "  Total Iterasi (merge): " << mergeSortIterasi << endl;
}

// ============================================================
// MAIN PROGRAM
// ============================================================

int main() {
    cout << string(60, '*') << endl;
    cout << "  PROGRAM IMPLEMENTASI ALGORITMA SORTING - C++" << endl;
    cout << "  Bubble | Selection | Insertion | Quick | Merge" << endl;
    cout << string(60, '*') << endl;

    int n;
    cout << "\nMasukkan jumlah data: ";
    if (!(cin >> n) || n <= 0) {
        cout << "Input tidak valid! Harap masukkan angka > 0.\n";
        return 1;
    }

    vector<int> data(n);
    cout << "Masukkan " << n << " data (pisahkan dengan spasi):\n> ";
    for (int i = 0; i < n; i++) {
        cin >> data[i];
    }

    cout << "\n  Data yang diinput: ";
    printArray(data);

    // Jalankan semua algoritma
    bubbleSort(data);
    selectionSort(data);
    insertionSort(data);
    quickSort(data);
    mergeSort(data);

    cout << "\n" << string(60, '=') << endl;
    cout << "  SELESAI - Semua algoritma telah dijalankan!" << endl;
    cout << string(60, '=') << "\n" << endl;

    return 0;
}