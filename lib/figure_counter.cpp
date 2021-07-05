#include <stack>
#include "figure_counter.hpp"

figure_counter::figure_counter(grid_t&& matrix)
{
    _count(matrix);
    matrix.clear();
}

size_t figure_counter::value() const { return _counter; }

figure_counter::operator size_t() const { return value(); }

void figure_counter::_count(grid_t matrix)
{
    for(cell_t current_cell = matrix.first_cell();
        current_cell.is_valid();
        ++current_cell)
    {
        if(_is_marked(current_cell))
        {
            ++_counter;
            _unmark_figure(current_cell);
        }
    }
}

void figure_counter::_unmark_figure(cell_t& cell)
{
    _unmark(cell);
    std::stack<cell_t> cells_to_process;
    cells_to_process.push(cell);
    while(!cells_to_process.empty())
    {
        auto current_cell = cells_to_process.top();
        cells_to_process.pop();
        auto neighbours = current_cell.neighbors();
        for(cell_t& neighbour : neighbours)
        {
            if(_is_marked(neighbour))
            {
                cells_to_process.push(neighbour);
                _unmark(neighbour);
            }
        }
    }
}

bool figure_counter::_is_marked(const cell_t& cell)
{
    return cell.value();
}

void figure_counter::_unmark(cell_t& cell)
{
    cell.value() = false;
}
