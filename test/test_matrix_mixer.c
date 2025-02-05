/**
 * matrix_mixer (c) by Instruo & Murdo Graham
 * 
 * matrix_mixer is licensed under a
 * Creative Commons Attribution 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <https://creativecommons.org/licenses/by/3.0/>.
 */

#ifdef TEST

#include "unity.h"

#include "matrix_mixer.h"

#define NUM_ROWS 8
#define NUM_COLUMNS 8


void setUp(void)
{
}

void tearDown(void)
{
}

void test_matrix_mixer_init_should_init_all_nodes_to_zero(void)
{
    TEST_ASSERT_EQUAL(0, matrix_mixer_init(NUM_ROWS, NUM_COLUMNS));

    for(int row=0; row<NUM_ROWS; row++)
        {
        for(int column=0; column<NUM_COLUMNS; column++)
            {
            TEST_ASSERT_EQUAL_FLOAT(0.f, node_amplitudes[row][column]);
        }
    }
}

void test_matrix_mixer_init_should_clamp_matrix_dimensions_greater_than_max(void)
{
    TEST_ASSERT_EQUAL(0, matrix_mixer_init(MAX_NUM_ROWS, MAX_NUM_COLUMNS));

    TEST_ASSERT_EQUAL(MAX_NUM_ROWS, matrix_mixer_get_num_rows());

    TEST_ASSERT_EQUAL(MAX_NUM_COLUMNS, matrix_mixer_get_num_columns());

    TEST_ASSERT_EQUAL(0, matrix_mixer_init(-1, -1));

    TEST_ASSERT_EQUAL(0, matrix_mixer_get_num_rows());

    TEST_ASSERT_EQUAL(0, matrix_mixer_get_num_columns());
}

void test_matrix_mixer_set_node_amplitude_should_set_only_one_node(void)
{
    matrix_mixer_init(NUM_ROWS, NUM_COLUMNS);

    int test_row = 5;
    int test_column = 4;

    TEST_ASSERT_EQUAL(0, matrix_mixer_set_node_amplitude(test_row, test_column, 0.5f));

    for(int row=0; row<NUM_ROWS; row++)
    {
        for(int column=0; column<NUM_COLUMNS; column++)
        {
            if((row == test_row) && (column == test_column))
            {
                TEST_ASSERT_EQUAL_FLOAT(0.5f, node_amplitudes[row][column]);
            }
            else
            {
                TEST_ASSERT_EQUAL_FLOAT(0.f, node_amplitudes[row][column]);
            }
        }
    }
}

void test_matrix_mixer_set_node_amplitude_Should_return_error_for_out_of_bounds_coordinate(void)
{
    matrix_mixer_init(NUM_ROWS, NUM_COLUMNS);

    TEST_ASSERT_EQUAL(1, matrix_mixer_set_node_amplitude(NUM_ROWS+1, NUM_COLUMNS+1, 0.5f));

    TEST_ASSERT_EQUAL(1, matrix_mixer_set_node_amplitude(-1, -1, 0.5f));
}

void test_matrix_mixer_set_node_amplitude_Should_clamp_out_of_bounds_amplitude(void)
{
    matrix_mixer_init(NUM_ROWS, NUM_COLUMNS);

    TEST_ASSERT_EQUAL(0, matrix_mixer_set_node_amplitude(0, 0, 1.5f));

    TEST_ASSERT_EQUAL_FLOAT(1.f, node_amplitudes[0][0]);

    TEST_ASSERT_EQUAL(0, matrix_mixer_set_node_amplitude(0, 0, -1.5f));

    TEST_ASSERT_EQUAL_FLOAT(-1.f, node_amplitudes[0][0]);
}

void test_matrix_mixer_get_node_amplitude_Should_return_correct_amplitudes(void)
{
    matrix_mixer_init(NUM_ROWS, NUM_COLUMNS);

    int test_row = 2;
    int test_column = 3;

    TEST_ASSERT_EQUAL(0, matrix_mixer_set_node_amplitude(test_row, test_column, 0.5f));

    int err = 1;

    for(int row=0; row<NUM_ROWS; row++)
    {
        for(int column=0; column<NUM_COLUMNS; column++)
        {
            if((row == test_row) && (column == test_column))
            {
                TEST_ASSERT_EQUAL_FLOAT(0.5f, matrix_mixer_get_node_amplitude(row, column, &err));
                TEST_ASSERT_EQUAL(0, err);
            }
            else
            {
                TEST_ASSERT_EQUAL_FLOAT(0.f, matrix_mixer_get_node_amplitude(row, column, &err));
                TEST_ASSERT_EQUAL(0, err);
            }
        }
    }
}

void test_matrix_mixer_get_node_amplitude_Should_return_error_for_out_of_bounds_coordinate(void)
{
    matrix_mixer_init(NUM_ROWS, NUM_COLUMNS);

    int err = 0;

    matrix_mixer_get_node_amplitude(NUM_ROWS+1, NUM_COLUMNS+1, &err);

    TEST_ASSERT_EQUAL(1, err);

    err = 0;

    matrix_mixer_get_node_amplitude(NUM_ROWS+1, NUM_COLUMNS+1, &err);

    TEST_ASSERT_EQUAL(1, err);
}

void test_matrix_process_Should_handle_io_correctly(void)
{
    float input[NUM_ROWS] = {1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f, 1.f};
    float output[NUM_COLUMNS] = {0.f};

    matrix_mixer_set_node_amplitude(0, 0, 0.0f);
    matrix_mixer_set_node_amplitude(1, 1, 0.1f);
    matrix_mixer_set_node_amplitude(2, 2, 0.2f);
    matrix_mixer_set_node_amplitude(3, 3, 0.3f);
    matrix_mixer_set_node_amplitude(4, 4, 0.4f);
    matrix_mixer_set_node_amplitude(5, 5, 0.5f);
    matrix_mixer_set_node_amplitude(6, 6, 0.6f);
    matrix_mixer_set_node_amplitude(7, 7, 0.7f);

    matrix_mixer_process(input, output);

    TEST_ASSERT_EQUAL_FLOAT(0.f, output[0]);
    TEST_ASSERT_EQUAL_FLOAT(0.1f, output[1]);
    TEST_ASSERT_EQUAL_FLOAT(0.2f, output[2]);
    TEST_ASSERT_EQUAL_FLOAT(0.3f, output[3]);
    TEST_ASSERT_EQUAL_FLOAT(0.4f, output[4]);
    TEST_ASSERT_EQUAL_FLOAT(0.5f, output[5]);
    TEST_ASSERT_EQUAL_FLOAT(0.6f, output[6]);
    TEST_ASSERT_EQUAL_FLOAT(0.7f, output[7]);

}

#endif