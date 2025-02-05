// matrix_mixer (c) by Instruo & Murdo Graham
// 
// matrix_mixer is licensed under a
// Creative Commons Attribution 3.0 Unported License.
// 
// You should have received a copy of the license along with this
// work.  If not, see <https://creativecommons.org/licenses/by/3.0/>.

#ifndef _MATRIX_MIXER_H
#define _MATRIX_MIXER_H

#ifdef __cplusplus
    extern "C" {
#endif

#define MAX_NUM_ROWS 32
#define MAX_NUM_COLUMNS 32

// Unit tests can "peek" into note amplitudes
#ifdef TEST
    extern float node_amplitudes[MAX_NUM_ROWS][MAX_NUM_COLUMNS];
#endif


/**
 * @brief Initialise the matrix mixer, sets all node amplitudes to zero (mute)
 * 
 * @param _num_rows number of rows (outputs)
 * @param _num_columns number of columns (inputs)
 * @return int error code
 */
int matrix_mixer_init(int _num_rows, int _num_columns);

/**
 * @brief return the number of rows in the matrix
 * 
 * @return int number of rows in the matrix
 */
int matrix_mixer_get_num_rows(void);

/**
 * @brief return the number of columns in the matrix
 * 
 * @return int number of columns in the matrix
 */
int matrix_mixer_get_num_columns(void);

/**
 * @brief Return the current aplitude of a node
 * 
 * @param row row
 * @param column column
 * @param err error status
 * @return float amplitude (-1.f to 1.f)
 */
float matrix_mixer_get_node_amplitude(int row, int column, int *err);

/**
 * @brief Set a node amplitude
 * 
 * @param row row
 * @param column column
 * @param amplitude amplitude to set
 * @return int error code
 */
int matrix_mixer_set_node_amplitude(int row, int column, float amplitude);

/**
 * @brief Process an input array into an output array
 * 
 * @param inputs input memory
 * @param outputs output memory
 * @return int error code
 */
int matrix_mixer_process(float *inputs, float *outputs);

#ifdef __cplusplus
    }
#endif

#endif // _MATRIX_MIXER_H