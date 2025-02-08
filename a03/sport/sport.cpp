#include "sport.hpp"
#include <print>

namespace sport {

int find_index_max(const unsigned **points_start, const unsigned **times_start, unsigned size) {
    int *max_points_indices = new int[size];
    for (unsigned i = 0; i < size; i++) { max_points_indices[i] = -1; }
    int max_points_indices_index = 0;

    unsigned current_max_points = *points_start[0];

    for (unsigned i = 1; i < size; i++) {
        if (*points_start[i] > current_max_points) { current_max_points = *points_start[i]; }
    }
    for (unsigned i = 0; i < size; i++) {
        if (*points_start[i] == current_max_points) {
            max_points_indices[max_points_indices_index] = i;
            max_points_indices_index++;
        }
    }
    max_points_indices_index--;
    //std::println("max_points_indices_index {}", max_points_indices_index);

    //for (int i = 0; i < max_points_indices_index + 1; i++) { std::println("max index {}", max_points_indices[i]); }
    //std::println("max_points_indices_index {}", max_points_indices_index);
    if (max_points_indices_index < 1) {
        int max_point_index = max_points_indices[0];
        delete[] max_points_indices;
        return max_point_index;
    }

    unsigned current_lowest_time = *times_start[max_points_indices[0]];
    int index_to_return = max_points_indices[0];
    for (int i = 0; i < max_points_indices_index + 1; i++) {
        if (*times_start[max_points_indices[i]] < current_lowest_time) {
            current_lowest_time = *times_start[max_points_indices[i]];
            index_to_return = max_points_indices[i];
        }
    }

    delete[] max_points_indices;
    return index_to_return;
}

void sort(const unsigned **points_start, const unsigned **times_start, unsigned size) {
    for (unsigned i = 0; i < size; i++) {
        //for (unsigned i = 0; i < size; i++) { std::println("order {}", *points_start[i]); }
        int index_max_points = find_index_max(&points_start[i], &times_start[i], size - i);
        index_max_points += i;
        const unsigned *tmp_points = points_start[i];
        const unsigned *tmp_times = times_start[i];
        points_start[i] = points_start[index_max_points];
        times_start[i] = times_start[index_max_points];
        points_start[index_max_points] = tmp_points;
        times_start[index_max_points] = tmp_times;
    }
}

} // namespace sport