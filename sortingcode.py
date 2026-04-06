"""
=============================================================
 Implementasi Algoritma Sorting - Python
 Algoritma: Bubble, Selection, Insertion, Quick, Merge Sort
=============================================================
"""

import time


def print_array(arr, label=""):
    if label:
        print(f"  {label}: {arr}")
    else:
        print(f"  {arr}")


# ─────────────────────────────────────────────
# 1. BUBBLE SORT
# ─────────────────────────────────────────────
def bubble_sort(arr):
    print("\n📌 BUBBLE SORT")
    print("─" * 50)
    n = len(arr)
    data = arr.copy()
    iteration = 1

    for i in range(n - 1):
        swapped = False
        print(f"\n  [Pass {i + 1}]")
        for j in range(0, n - i - 1):
            if data[j] > data[j + 1]:
                data[j], data[j + 1] = data[j + 1], data[j]
                swapped = True
            print_array(data, f"Iterasi {iteration:3d}")
            iteration += 1
        if not swapped:
            print("  → Tidak ada pertukaran, array sudah terurut!")
            break

    print(f"\n  ✅ Hasil: {data}")
    return data


# ─────────────────────────────────────────────
# 2. SELECTION SORT
# ─────────────────────────────────────────────
def selection_sort(arr):
    print("\n📌 SELECTION SORT")
    print("─" * 50)
    n = len(arr)
    data = arr.copy()
    iteration = 1

    for i in range(n - 1):
        min_idx = i
        print(f"\n  [Pass {i + 1}] Mencari minimum dari index {i} ke {n-1}")
        for j in range(i + 1, n):
            if data[j] < data[min_idx]:
                min_idx = j
        if min_idx != i:
            data[i], data[min_idx] = data[min_idx], data[i]
        print_array(data, f"Iterasi {iteration:3d}")
        print(f"           → Min = {data[i]} ditempatkan di index {i}")
        iteration += 1

    print(f"\n  ✅ Hasil: {data}")
    return data


# ─────────────────────────────────────────────
# 3. INSERTION SORT
# ─────────────────────────────────────────────
def insertion_sort(arr):
    print("\n📌 INSERTION SORT")
    print("─" * 50)
    n = len(arr)
    data = arr.copy()
    iteration = 1

    for i in range(1, n):
        key = data[i]
        j = i - 1
        print(f"\n  [Pass {i}] Menyisipkan elemen {key}")
        while j >= 0 and data[j] > key:
            data[j + 1] = data[j]
            j -= 1
        data[j + 1] = key
        print_array(data, f"Iterasi {iteration:3d}")
        iteration += 1

    print(f"\n  ✅ Hasil: {data}")
    return data


# ─────────────────────────────────────────────
# 4. QUICK SORT
# ─────────────────────────────────────────────
_qs_iteration = [0]


def _partition(data, low, high):
    pivot = data[high]
    i = low - 1
    for j in range(low, high):
        if data[j] <= pivot:
            i += 1
            data[i], data[j] = data[j], data[i]
    data[i + 1], data[high] = data[high], data[i + 1]
    return i + 1


def _quick_sort_recursive(data, low, high):
    if low < high:
        pi = _partition(data, low, high)
        _qs_iteration[0] += 1
        print_array(data, f"Iterasi {_qs_iteration[0]:3d}")
        print(f"           → Pivot = {data[pi]} (index {pi})")
        _quick_sort_recursive(data, low, pi - 1)
        _quick_sort_recursive(data, pi + 1, high)


def quick_sort(arr):
    print("\n📌 QUICK SORT")
    print("─" * 50)
    _qs_iteration[0] = 0
    data = arr.copy()
    print(f"\n  Pivot strategy: elemen terakhir")
    _quick_sort_recursive(data, 0, len(data) - 1)
    print(f"\n  ✅ Hasil: {data}")
    return data


# ─────────────────────────────────────────────
# 5. MERGE SORT
# ─────────────────────────────────────────────
_ms_iteration = [0]


def _merge(data, left, mid, right):
    left_part = data[left:mid + 1]
    right_part = data[mid + 1:right + 1]
    i = j = 0
    k = left
    while i < len(left_part) and j < len(right_part):
        if left_part[i] <= right_part[j]:
            data[k] = left_part[i]
            i += 1
        else:
            data[k] = right_part[j]
            j += 1
        k += 1
    while i < len(left_part):
        data[k] = left_part[i]
        i += 1
        k += 1
    while j < len(right_part):
        data[k] = right_part[j]
        j += 1
        k += 1


def _merge_sort_recursive(data, left, right):
    if left < right:
        mid = (left + right) // 2
        _merge_sort_recursive(data, left, mid)
        _merge_sort_recursive(data, mid + 1, right)
        _merge(data, left, mid, right)
        _ms_iteration[0] += 1
        print_array(data, f"Iterasi {_ms_iteration[0]:3d}")
        print(f"           → Merge [{left}..{mid}] & [{mid+1}..{right}]")


def merge_sort(arr):
    print("\n📌 MERGE SORT")
    print("─" * 50)
    _ms_iteration[0] = 0
    data = arr.copy()
    _merge_sort_recursive(data, 0, len(data) - 1)
    print(f"\n  ✅ Hasil: {data}")
    return data


# ─────────────────────────────────────────────
# MAIN PROGRAM
# ─────────────────────────────────────────────
def main():
    print("=" * 60)
    print("   IMPLEMENTASI ALGORITMA SORTING - PYTHON")
    print("=" * 60)

    # Input
    n = int(input("\nMasukkan jumlah data: "))
    print(f"Masukkan {n} angka (pisahkan dengan spasi): ", end="")
    arr = list(map(int, input().split()))

    if len(arr) != n:
        print(f"⚠ Jumlah data tidak sesuai! Menggunakan {len(arr)} data.")

    print(f"\n📋 Data awal: {arr}")

    algorithms = {
        "1": ("Bubble Sort",    bubble_sort),
        "2": ("Selection Sort", selection_sort),
        "3": ("Insertion Sort", insertion_sort),
        "4": ("Quick Sort",     quick_sort),
        "5": ("Merge Sort",     merge_sort),
        "6": ("Semua Algoritma", None),
    }

    print("\nPilih algoritma sorting:")
    for k, (name, _) in algorithms.items():
        print(f"  [{k}] {name}")

    choice = input("\nPilihan Anda: ").strip()

    if choice == "6":
        for k, (name, func) in list(algorithms.items())[:-1]:
            start = time.perf_counter()
            func(arr)
            elapsed = (time.perf_counter() - start) * 1000
            print(f"  ⏱ Waktu: {elapsed:.4f} ms\n")
    elif choice in algorithms and algorithms[choice][1]:
        name, func = algorithms[choice]
        start = time.perf_counter()
        func(arr)
        elapsed = (time.perf_counter() - start) * 1000
        print(f"\n  ⏱ Waktu eksekusi: {elapsed:.4f} ms")
    else:
        print("Pilihan tidak valid!")

    print("\n" + "=" * 60)


if __name__ == "__main__":
    main()