#pragma once

#include <cstdint>
#include <stdexcept>
#include <vector>

template <class T>
class grid
{
    using value_t = T;
    using row_t = std::vector<value_t>;
    using ref_t = typename row_t::reference;
    using const_ref_t = typename row_t::const_reference;

    std::vector<row_t> _grid;
    std::uint32_t _height;
    std::uint32_t _width;
public:
    class cell
    {
        friend class grid<value_t>;
        using owner_ptr_t = grid<value_t>*;

        owner_ptr_t _owner;
        std::uint32_t _row;
        std::uint32_t _column;

        cell(owner_ptr_t owner, std::uint32_t row, std::uint32_t column)
            : _owner{owner}
            , _row{row}
            , _column{column}
        {
        }
    public:
        std::uint32_t row() { return _row; }
        std::uint32_t column() { return _column; }

        ref_t value()
        {
            return _owner->_grid[_row][_column];
        }

        const_ref_t value() const
        {
            return _owner->_grid[_row][_column];
        }

        bool is_valid() const
        {
            return (*this) != _owner->invalid_cell();
        }

        cell up() const
        {
            return _owner->cell_at(_row - 1, _column);
        }

        cell down() const
        {
            return _owner->cell_at(_row + 1, _column);
        }

        cell left() const
        {
            return _owner->cell_at(_row, _column - 1);
        }

        cell right() const
        {
            return _owner->cell_at(_row, _column + 1);
        }

        std::vector<cell> neighbors() const
        {
            std::vector<cell> result{up(), right(), down(), left()};
            erase_if(result, [](cell c) { return !c.is_valid(); });
            return result;
        }

        cell& operator++()
        {
            ++_column;
            if(_column >= _owner->_width)
            {
                _column = 0;
                ++_row;
                if(_row >= _owner->_height)
                {
                    _column = _owner->_width;
                }
            }
            return *this;
        }

        cell operator++(int)
        {
            cell old_value = *this;
            ++(*this);
            return old_value;
        }

        bool operator ==(const cell& other) const
        {
            return _owner == other._owner
                && _row == other._row
                && _column == other._column;
        }

        bool operator !=(const cell& other) const
        {
            return !(*this == other);
        }
    };

    grid(std::uint32_t height, std::uint32_t width)
        : _height{height}
        , _width{width}
    {
        _grid.resize(height);
        for(row_t& a_row : _grid)
        {
            a_row.resize(width);
        }
    }

    void clear()
    {
        _grid.clear();
        _height = 0;
        _width = 0;
    }

    cell first_cell()
    {
        return cell(this, 0, 0);
    }

    cell invalid_cell()
    {
        return cell(this, _height, _width);
    }

    cell cell_at(std::uint32_t row, std::uint32_t column)
    {
        if(row < _height && column < _width)
        {
            return cell{this, row, column};
        }
        return invalid_cell();
    }

    void set_row(std::uint32_t row, std::vector<value_t>&& values)
    {
        if(row >= _height)
        {
            throw std::out_of_range{"[grid::set_row] @row out of range"};
        }
        if(values.size() != _width)
        {
            throw std::invalid_argument(
                "[grid::set_row] "
                "@values length does not match grid width"
            );
        }
        _grid[row] = std::move(values);
    }
};
