#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED

//stored in column major
typedef struct
{
    double *data;
    unsigned int width;
    unsigned int height;
} Matrix;

Matrix matrix_create(unsigned int width, unsigned int height);

void matrix_set(Matrix *a, Matrix b);

void matrix_set_data(Matrix *matrix, double *data);

void matrix_set_row(Matrix *matrix, unsigned int row, double *data);

void matrix_set_column(Matrix *matrix, unsigned int column, double *data);

void matrix_set_value(Matrix *matrix, unsigned int row, unsigned int column, double value);

double matrix_get_value(Matrix matrix, unsigned int row, unsigned int column);

Matrix matrix_add(Matrix a, Matrix b);

Matrix matrix_sub(Matrix a, Matrix b);

Matrix matrix_mul_scalar(Matrix matrix, double scalar);

Matrix matrix_mul(Matrix a, Matrix b);

Matrix matrix_transpose(Matrix matrix);

Matrix matrix_row_add(Matrix matrix, unsigned int originRow, unsigned int targetRow, double scalar);

Matrix matrix_row_mul(Matrix matrix, unsigned int row, double scalar);

Matrix matrix_row_switch(Matrix matrix, unsigned int rowA, unsigned int rowB);

Matrix matrix_get_reducedRowEchelonForm(Matrix matrix);

unsigned int matrix_get_rank(Matrix matrix);

void matrix_destroy(Matrix *matrix);

#endif // MATRIX_H_INCLUDED
