#include <doctest/doctest.h>

#include <array>
#include <initializer_list>
#include "figure_counter.hpp"
#include "grid.hpp"

template <size_t SIZE>
using bool_arr = std::array<bool, SIZE>;
template <size_t HEIGHT, size_t WIDTH>
static grid<bool> create_matrix(std::array<bool_arr<WIDTH>, HEIGHT> init_arr);
static grid<bool> create_large_filled();
static grid<bool> create_large_spiral();

static size_t count(grid<bool>& matrix);

TEST_SUITE("figure_counter")
{
    TEST_CASE("can count empty matrix")
    {
        grid<bool> matrix(0, 0);
        REQUIRE(count(matrix) == 0);
    }

    TEST_CASE("can count fully marked matrix")
    {
        auto matrix = create_matrix<3, 3>(
            {
                {
                    {1, 1, 1},
                    {1, 1, 1},
                    {1, 1, 1}
                }
            }
        );
        REQUIRE(count(matrix) == 1);
    }


    TEST_CASE("can count fully unmarked grid")
    {
        auto matrix = create_matrix<3, 3>(
            {
                {
                    {0, 0, 0},
                    {0, 0, 0},
                    {0, 0, 0}
                }
            }
        );
        REQUIRE(count(matrix) == 0);
    }

    TEST_CASE("can count checkerboard pattern")
    {
        auto matrix = create_matrix<3, 3>(
            {
                {
                    {1, 0, 1},
                    {0, 1, 0},
                    {1, 0, 1}
                }
            }
        );
        REQUIRE(count(matrix) == 5);
        matrix = create_matrix<3, 3>(
            {
                {
                    {0, 1, 0},
                    {1, 0, 1},
                    {0, 1, 0},
                }
            }
        );
        REQUIRE(count(matrix) == 4);
    }


    TEST_CASE("can count U shape")
    {
        auto matrix = create_matrix<3, 3>(
            {
                {
                    {1, 0, 1},
                    {1, 0, 1},
                    {1, 1, 1}
                }
            }
        );
        REQUIRE(count(matrix) == 1);

        matrix = create_matrix<3, 3>(
            {
                {
                    {1, 1, 1},
                    {1, 0, 0},
                    {1, 1, 1}
                }
            }
        );
        REQUIRE(count(matrix) == 1);

        matrix = create_matrix<3, 3>(
            {
                {
                    {1, 1, 1},
                    {0, 0, 1},
                    {1, 1, 1}
                }
            }
        );
        REQUIRE(count(matrix) == 1);

        matrix = create_matrix<3, 3>(
            {
                {
                    {1, 1, 1},
                    {1, 0, 1},
                    {1, 0, 1}
                }
            }
        );
        REQUIRE(count(matrix) == 1);
    }

    TEST_CASE("can handle large filled square")
    {
        grid<bool> matrix = create_large_filled();
        REQUIRE(count(matrix) == 1);
    }

    TEST_CASE("can handle large spiral")
    {
        grid<bool> matrix = create_large_spiral();
        REQUIRE(count(matrix) == 1);
    }
}

size_t count(grid<bool>& matrix)
{
    return figure_counter(std::move(matrix));
}

template <size_t HEIGHT, size_t WIDTH>
grid<bool> create_matrix(std::array<bool_arr<WIDTH>, HEIGHT> init_arr)
{
    grid<bool> result(HEIGHT, WIDTH);
    for(size_t row = 0; row < HEIGHT; ++row)
    {
        for(size_t column = 0; column < WIDTH; ++column)
        {
            result.cell_at(row, column).value() = init_arr[row][column];
        }
    }
    return result;
}

constexpr size_t large_size = 12345;

grid<bool> create_large_filled()
{
    grid<bool> result(large_size, large_size);
    for(auto cell = result.first_cell(); cell.is_valid(); ++cell)
    {
        cell.value() = true;
    }
    return result;
}

grid<bool> create_large_spiral()
{
    grid<bool> result(large_size, large_size);
    for(auto cell = result.first_cell(); cell.is_valid(); ++cell)
    {
        auto row = cell.row();
        auto column = cell.column();
        if(row % 2 == 0
           || (column == 0 && row % 4 == 3)
           || (column == (large_size - 1) && row % 4 == 1))
        {
            cell.value() = true;
        }
    }
    return result;
}
