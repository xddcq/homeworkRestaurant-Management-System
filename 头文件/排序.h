#pragma once
template<typename T, typename Compare>
void bubbleSort(T* head, T* tail, Compare comp) {
    for (T* i = head; i != tail; ++i) {
        for (T* j = i + 1; j <= tail; ++j) {
            if (comp(*j, *i)) {
                T temp = *i;
                *i = *j;
                *j = temp;
            }
        }
    }
}