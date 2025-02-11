#include "disjoint_sets.hpp"

disjoint_sets::DisjointSets::DisjointSets(unsigned size) {
    parents.resize(size);
    for (unsigned i = 0; i < size; i++) { parents[i] = i; }
}

unsigned disjoint_sets::DisjointSets::add() {
    parents.push_back(parents.size());
    return parents.back();
}

unsigned disjoint_sets::DisjointSets::find(unsigned entry) {
    unsigned current = entry;
    while (parents[current] != current) { current = parents[current]; }
    return current;
}

unsigned disjoint_sets::DisjointSets::unionSets(unsigned entry1, unsigned entry2) {
    unsigned x = find(entry1);
    unsigned y = find(entry2);

    parents[y] = x;
    return x;
}

bool disjoint_sets::DisjointSets::disjoint(unsigned entry1, unsigned entry2) { return find(entry1) != find(entry2); }