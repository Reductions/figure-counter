#pragma once

#include "grid.hpp"

class figure_counter
{
    #ifdef COMPACT_GRID
    using grid_t = grid<bool>;
    #else
    using grid_t = grid<unsigned char>;
    #endif

    using cell_t = grid_t::cell;
    size_t _counter = 0;
public:
    figure_counter(grid_t&& matrix);
    size_t value() const;
    operator size_t() const;
private:
    void _count(grid_t gird);
    void _unmark_figure(cell_t& cell);
    static inline bool _is_marked(const cell_t& cell);
    static inline void _unmark(cell_t& cell);
};
