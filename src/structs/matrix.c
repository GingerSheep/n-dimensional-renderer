#include "matrix.h"

#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

Matrix matrix_create(unsigned int width, unsigned int height)
{
    Matrix matrix;

    matrix.width = width;
    matrix.height = height;

    matrix.data = malloc(width * height * sizeof(double));

    return matrix;
}

void matrix_set(Matrix *a, Matrix b)
{
    free(a->data);

    a->data = b.data;
    a->height = b.height;
    a->width = b.width;
}

void matrix_set_data(Matrix *matrix, double *data)
{
    memcpy(matrix->data, data, matrix->width * matrix->height * sizeof(double));
}

void matrix_set_row(Matrix *matrix, unsigned int row, double *data)
{
    for(unsigned int c = 0; c < matrix->width; c++)
    {
        memcpy(matrix->data + matrix->height * c + row, data + c, sizeof(double));
    }
}

void matrix_set_column(Matrix *matrix, unsigned int column, double *data)
{
    memcpy(matrix->data + matrix->height * column, data, matrix->height);
}

void matrix_set_value(Matrix *matrix, unsigned int row, unsigned int column, double value)
{
    *(matrix->data + matrix->height * column + row) = value;
}

double matrix_get_value(Matrix matrix, unsigned int row, unsigned int column)
{
    return *(matrix.data + matrix.height * column + row);
}

Matrix matrix_add(Matrix a, Matrix b)
{
    Matrix result = matrix_create(a.width, a.height);

    for(unsigned int c = 0; c < a.width; c++)
    {
        for(unsigned int r = 0; r < a.height; r++)
        {
            matrix_set_value(&result, r, c, matrix_get_value(a, r, c) + matrix_get_value(b, r, c));
        }
    }

    return result;
}

Matrix matrix_sub(Matrix a, Matrix b)
{
    Matrix result = matrix_create(a.width, a.height);

    for(unsigned int c = 0; c < a.width; c++)
    {
        for(unsigned int r = 0; r < a.height; r++)
        {
            matrix_set_value(&result, r, c, matrix_get_value(a, r, c) - matrix_get_value(b, r, c));
        }
    }

    return result;
}

Matrix matrix_mul_scalar(Matrix matrix, double scalar)
{
    Matrix result = matrix_create(matrix.width, matrix.height);

    for(unsigned int c = 0; c < matrix.width; c++)
    {
        for(unsigned int r = 0; r < matrix.height; r++)
        {
            matrix_set_value(&result, r, c, matrix_get_value(matrix, r, c) * scalar);
        }
    }

    return result;
}

Matrix matrix_mul(Matrix a, Matrix b)
{
    Matrix result = matrix_create(b.width, a.height);

    for(unsigned int c = 0; c < b.width; c++)
    {
        for(unsigned int r = 0; r < a.height; r++)
        {
            double sum = 0;

            for(unsigned int n = 0; n < a.width; n++)
            {
                sum += matrix_get_value(a, r, n)  * matrix_get_value(b, n, c);
            }

            matrix_set_value(&result, r, c, sum);
        }
    }

    return result;
}

Matrix matrix_transpose(Matrix matrix)
{
    Matrix result = matrix_create(matrix.width, matrix.height);

    for(unsigned int c = 0; c < matrix.width; c++)
    {
        for(unsigned int r = 0; r < matrix.height; r++)
        {
            matrix_set_value(&result, r, c, matrix_get_value(matrix, c, r));
        }
    }

    return result;
}

Matrix matrix_row_add(Matrix matrix, unsigned int originRow, unsigned int targetRow, double scalar)
{
    Matrix result = matrix_create(matrix.width, matrix.height);

    matrix_set_data(&result, matrix.data);

    for(unsigned int c = 0; c < matrix.width; c++)
    {
        matrix_set_value(&result, targetRow, c, matrix_get_value(matrix, targetRow, c) + matrix_get_value(matrix, originRow, c) * scalar);
    }

    return result;
}

Matrix matrix_row_mul(Matrix matrix, unsigned int row, double scalar)
{
    Matrix result = matrix_create(matrix.width, matrix.height);

    matrix_set_data(&result, matrix.data);

    for(unsigned int c = 0; c < matrix.width; c++)
    {
        matrix_set_value(&result, row, c, matrix_get_value(matrix, row, c) * scalar);
    }

    return result;
}

Matrix matrix_row_switch(Matrix matrix, unsigned int rowA, unsigned int rowB)
{
    Matrix result = matrix_create(matrix.width, matrix.height);

    matrix_set_data(&result, matrix.data);

    for(unsigned int c = 0; c < matrix.width; c++)
    {
        matrix_set_value(&result, rowA, c, matrix_get_value(matrix, rowB, c));
        matrix_set_value(&result, rowB, c, matrix_get_value(matrix, rowA, c));

    }

    return result;
}


//using Gauss-Jordan algorithm https://www.csun.edu/~panferov/math262/262_rref.pdf
Matrix matrix_get_reducedRowEchelonForm(Matrix matrix)
{
    Matrix result = matrix_create(matrix.width, matrix.height);

    unsigned int c = 0;

    for(unsigned int r = 0; r < matrix.height && c < matrix.width; r++)
    {
        unsigned int n = r;

        while(matrix_get_value(result, n, c) == 0)
        {
            n++;

            if(n == matrix.height)
            {
                n = r;
                c++;

                if(c == matrix.width)
                {
                    break;
                }
            }
        }

        matrix_set(&result, matrix_row_switch(result, r, n));

        double s = matrix_get_value(result, r, c);

        if(s != 0) matrix_set(&result, matrix_row_mul(result, r, s));

        for(n = 0; n < matrix.height; n++)
        {
            if(n != r) matrix_set(&result, matrix_row_add(result, r, n, -matrix_get_value(result, n, c)));
        }

        c++;
    }

    return result;
}

unsigned int matrix_get_rank(Matrix matrix)
{
    int rank = 0;

    Matrix reducedRowEchelonForm = matrix_get_reducedRowEchelonForm(matrix);

    for(int r = 0; reducedRowEchelonForm.height; r++)
    {
        bool nonZero = false;

        for(int c = 0; reducedRowEchelonForm.width && !nonZero; c++)
        {
            if(matrix_get_value(reducedRowEchelonForm, r, c) != 0) nonZero = true;
        }

        if(nonZero) rank++;
    }

    matrix_destroy(&reducedRowEchelonForm);

    return rank;
}

void matrix_destroy(Matrix *matrix)
{
    free(matrix->data);
    matrix->height = 0;
    matrix->width = 0;
}
