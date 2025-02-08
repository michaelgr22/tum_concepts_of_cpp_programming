#include "stockpiles.hpp"

namespace stockpiles {
int find_largest_stockpile_index(Stockpile *stock_start, unsigned stock_len) {
    int *max_stockpile_indices = new int[stock_len];
    for (unsigned i = 0; i < stock_len; i++) { max_stockpile_indices[i] = -1; }
    int max_stockpile_indices_index = 0;

    unsigned current_max_stockpile = *(stock_start[0].bottles);

    for (unsigned i = 1; i < stock_len; i++) {
        if (*(stock_start[i].bottles) > current_max_stockpile) { current_max_stockpile = *(stock_start[i].bottles); }
    }
    for (unsigned i = 0; i < stock_len; i++) {
        if (*(stock_start[i].bottles) == current_max_stockpile) {
            max_stockpile_indices[max_stockpile_indices_index] = i;
            max_stockpile_indices_index++;
        }
    }
    max_stockpile_indices_index--;
    //std::println("max_points_indices_index {}", max_points_indices_index);

    //for (int i = 0; i < max_points_indices_index + 1; i++) { std::println("max index {}", max_points_indices[i]); }
    //std::println("max_points_indices_index {}", max_points_indices_index);
    if (max_stockpile_indices_index < 1) {
        int max_stockpile_index = max_stockpile_indices[0];
        delete[] max_stockpile_indices;
        return max_stockpile_index;
    }

    unsigned current_lowest_id = stock_start[0].id;
    int index_to_return = max_stockpile_indices[0];
    for (int i = 0; i < max_stockpile_indices_index + 1; i++) {
        if (stock_start[max_stockpile_indices[i]].id < current_lowest_id) {
            current_lowest_id = stock_start[max_stockpile_indices[i]].id;
            index_to_return = max_stockpile_indices[i];
        }
    }

    delete[] max_stockpile_indices;
    return index_to_return;
}

void init(Stockpile * /*stock_start*/, unsigned /*stock_len*/) {
    /*Stockpile *stock_pile = new Stockpile[stock_len];
    for (unsigned i = 0; i < stock_len; i++) { stock_start[i] = stock_pile[i]; }
    stock_start = stock_pile;*/
}
bool serve(Stockpile *stock_start, unsigned stock_len, unsigned amount, Stockpile &which) {
    if ((stock_len) == 0) { return false; }
    int largest_stockpile_index = find_largest_stockpile_index(stock_start, stock_len);

    if (*(stock_start[largest_stockpile_index].bottles) < amount) { return false; }

    *(stock_start[largest_stockpile_index].bottles) -= amount;
    which = stock_start[largest_stockpile_index];
    return true;
}

} // namespace stockpiles