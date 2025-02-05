/**
 * matrix_mixer (c) by Instruo & Murdo Graham
 * 
 * matrix_mixer is licensed under a
 * Creative Commons Attribution 3.0 Unported License.
 * 
 * You should have received a copy of the license along with this
 * work.  If not, see <https://creativecommons.org/licenses/by/3.0/>.
 */

#include "matrix_mixer.h"

#ifndef TEST
    static float node_amplitudes[MAX_NUM_ROWS][MAX_NUM_COLUMNS];
#else
    float node_amplitudes[MAX_NUM_ROWS][MAX_NUM_COLUMNS] = {0xBEEF}; // init to something silly for unit tests
#endif

static int num_rows = 0;
static int num_columns = 0;

int matrix_mixer_init(int _num_rows, int _num_columns)
{
    num_rows = _num_rows;
    num_columns = _num_columns;

    if(num_rows > MAX_NUM_ROWS)
        num_rows = MAX_NUM_ROWS;

    if(num_columns > MAX_NUM_COLUMNS)
        num_columns = MAX_NUM_COLUMNS;

    if(num_rows < 0)
        num_rows = 0;

    if(num_columns  < 0)
        num_columns = 0;

    for(int row=0; row<num_rows; row++)
    {
        for(int column=0; column<num_columns; column++)
        {
            node_amplitudes[row][column] = 0.f;
        }
    }
    return 0;
}

int matrix_mixer_get_num_rows(void)
{
    return num_rows;
}

int matrix_mixer_get_num_columns(void)
{
    return num_rows;
}

float matrix_mixer_get_node_amplitude(int row, int column, int* err)
{
    if( (row < 0) || (row > num_rows) || (column < 0) || (column > num_columns) )
    {
        *err = 1;
        return 0.f; // do nothing
    }
    *err = 0;
    return node_amplitudes[row][column];
}

int matrix_mixer_set_node_amplitude(int row, int column, float amplitude)
{
    if( (row < 0) || (row > num_rows) || (column < 0) || (column > num_columns) )
    {
        return 1; // do nothing
    }

    if( amplitude < -1.f )
        amplitude = -1.f;

    if( amplitude > 1.f )
        amplitude = 1.f;

    node_amplitudes[row][column] = amplitude; 

    return 0;
}

int matrix_mixer_process(float *inputs, float *outputs)
{
    
    for(int column=0; column<num_columns; column++)
    {
        for(int row=0; row<num_rows; row++)
        {
            outputs[column] += inputs[row] * node_amplitudes[row][column];
        }
    }
    return 0;
}