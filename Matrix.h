#ifndef MATRIX_H
#define MATRIX_H

#include <iostream>
#include <fstream>
#include <thread>
#include <tgmath.h>
using namespace std;

template < typename Type >
class Matrix { 

    public:
        Matrix();
        Matrix( int, int );
        Matrix( Matrix & );

        ~Matrix();

        void fillMatrix();
        void fillRandom();
        void fillArchive( string );
        void ones();
       
        int getRow();
        int getCol();
        double addAll();
        
        Matrix<Type> columna( int i );
        Matrix<Type> addOnes();
        Matrix<Type> addOnesCol();
        Matrix<Type> addZeros();
        Matrix<Type> cutOnes();
        Matrix<Type> cutOnesCol();
        Matrix<Type> multScalar( double );
        Matrix<Type> sumScalar( double );
        Matrix<Type> powTwice();
        Matrix<Type> multDouble( double );

        Matrix<Type> transpose();
        Matrix<Type> operator+( const Matrix & );
        Matrix<Type> operator-( const Matrix & );
        Matrix<Type> operator*( const Matrix & );
        Matrix<Type> operator=( const Matrix & );
        Matrix<Type> operator/( const Matrix & );
        Matrix<Type> operator%( const Matrix & );

        Type* operator[]( const int i ) {  
            return *( matrix + i );
        }

        template < typename T >
        friend ostream& operator <<( ostream &, const Matrix <T> );
 
    private:
        int row, col;
        Type **matrix;
        Matrix<Type> sumMatrixThread( const Matrix &, const Matrix & );
        
    friend class Sumatoria;

};

class Sumatoria : public Matrix<double> {
    
    public:
        void operator()( const Matrix<double> &A, const Matrix<double> &B, const Matrix<double> *ptr, int bRow, int eRow ) {  
            int pos = 0; 
            for( int i = bRow; i < eRow; ++i ) {
                for( int j = 0; j < A.col; ++j ) {
                    *(*( ptr -> matrix + pos ) + j ) = *(*( A.matrix + i ) + j ) + *(*( B.matrix + i ) + j );
                }
                ++pos;
            }
        }
};

template < typename Type >
Matrix<Type>::Matrix() {
    this -> row = 0;
    this -> col = 0;
    
    matrix = new Type*[ row ];
    for( int i = 0; i < row; ++i )
        *( matrix + i ) = new Type[ col ];
}

template < typename Type >
Matrix<Type>::Matrix( int row, int col ) {
    this -> row = row;
    this -> col = col;

    matrix = new Type*[ row ];
    for( int i = 0; i < row; ++i )
        *( matrix + i ) = new Type[ col ];
    
    for( int i = 0; i < row; i++ ) {
        for( int j = 0; j < col; j++ )
            *(*( matrix + i ) + j ) = 0;
    }
}

template < typename Type >
Matrix<Type>::Matrix( Matrix &M ) {
    this -> row = M.row;
    this -> col = M.col;

    matrix = new Type*[ row ];
    for( int i = 0; i < row; ++i )
        *( matrix + i ) = new Type[ col ];
    
    for( int i = 0; i < row; i++ ) {
        for( int j = 0; j < col; j++ ) 
            *(*( matrix + i ) + j ) = *(*( M.matrix + i ) + j );
    }
}

template < typename Type >
Matrix<Type>::~Matrix() {
    for( int i = 0; i < row; ++i )
        delete[] *( matrix + i );
    delete[] matrix;
}

template < typename Type >
void Matrix<Type>::fillMatrix() {
    for( int i = 0; i < row; i++ )
        for( int j = 0; j < col; j++ ) {
            cout << "Matrix[" << i << "][" << j << "]: ";
            cin >> *(*( matrix + i ) + j );
        }
}

template< typename Type >
void Matrix<Type>::fillRandom()
{
    for( int i = 0; i < row; i++ ) {
        for( int j = 0; j < col; j++ ) {
            *( *( matrix + i ) + j ) = rand() % 30;
        }
    }
}

template< typename Type >
void Matrix<Type>::fillArchive( string name ) {
    ifstream archive;
    string text;
    bool control = true;

    archive.open( name, ios::in );

    if( archive.fail()) {
        cout << "Incapaz de abrir el archivo... " << endl;
        exit( EXIT_FAILURE );
    }

    Matrix<Type> M( row, col );
    int a = 0, b = 0;
    while( !archive .eof()) {
        char dig[ 30 ] = {'\0'};
        getline( archive, text );
        unsigned long i = 0, j = 0;
        while( text[ i ] != '\0' ) {
            if( text[ i ] == ',') {
                M.matrix[ a ][ b ] = atof( dig );
                ++b;
                for( int i = 0; i < 30; ++i )
                    dig[ i ] = '\0';
                j = 0;
                ++i;
            }
            dig[ j ] = text[ i ];
            ++i;
            ++j;
        }
        M.matrix[ a ][ b ] = atof( dig );
        ++a;
        b = 0;
    }

    *this = M;
    archive.close();
}

template < typename Type >
void Matrix<Type>::ones() {
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < col; ++j )
            *( *( matrix + i ) + j ) = 1;
}

template < typename Type >
Matrix<Type> Matrix<Type>::columna( int ind ) {
    Matrix<Type> M( row, 1 );
    for( int i = 0; i < row; ++i )
        *(*( M.matrix + i )) = *(*( matrix + i ) + ind );
    return M;
}

template < typename Type >
Matrix<Type> Matrix<Type>::addZeros() {
    Matrix<Type> M( row, col + 1 );
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < col; ++j )
            *( *( M.matrix + i ) + j + 1 ) = *( *( matrix + i ) + j );
    return M;
}


template < typename Type >
Matrix<Type> Matrix<Type>::addOnes() {
    Matrix<Type> M( row, col + 1 );
    M.ones();
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < col; ++j )
            *( *( M.matrix + i ) + j + 1 ) = *( *( matrix + i ) + j );
    return M;
}

template < typename Type >
Matrix<Type> Matrix<Type>::addOnesCol() {
    Matrix<Type> M( row + 1, col );
    M.ones();
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < col; ++j )
            *(*( M.matrix + i + 1 ) + j ) = *(*( matrix + i ) + j );
    return M;
}

template < typename Type >
Matrix<Type> Matrix<Type>::cutOnes() {
    Matrix<Type> M( row, col - 1 );
    for( int i = 0; i < row; ++i )
        for( int j = col - 1; j != 0; --j )
            *( *( M.matrix + i ) + j - 1 ) = *( *( matrix + i ) + j );
    return M;
}

template < typename Type >
Matrix<Type> Matrix<Type>::cutOnesCol() {
    Matrix<Type> M( row - 1, col );
    for( int i = row - 1; i != 0; --i )
        for( int j = 0; j < col; ++j )
            *( *( M.matrix + i - 1 ) + j ) = *( *( matrix + i ) + j );
    return M;
}

template < typename Type >
int Matrix<Type>::getRow() {
    return row;
}

template < typename Type >
int Matrix<Type>::getCol() {
    return col;
}

template < typename Type >
Matrix<Type> Matrix<Type>::transpose() {
    Matrix<Type> A( col, row );

    for( int i = 0; i < col; ++i )
        for( int j = 0; j < row; ++j )
            *(*( A.matrix + i ) + j ) = *(*( matrix + j ) + i );
    return A;
}


template < typename Type >
Matrix<Type> Matrix<Type>::operator+( const Matrix &A ) {
    Matrix<Type> B( row, col );
    if( row == A.row && col == A.col ) {
        for( int i = 0; i < row; ++i )
            for( int j = 0; j < col; ++j )
                *(*( B.matrix + i ) + j ) = *(*( matrix + i ) + j ) + *(*( A.matrix + i ) + j );
    }

    else
        cout << "No se pueden sumar..." << endl;
    
    return B;
}

template < typename Type >
Matrix<Type> Matrix<Type>::operator-( const Matrix &A ) {
    Matrix<Type> B( row, col );

    if( row == A.row && col == A.col ) {
        for( int i = 0; i < row; ++i )
            for( int j = 0; j < col; ++j )
                *(*( B.matrix + i ) + j ) = *(*( matrix + i ) + j ) - *(*( A.matrix + i ) + j );
    }

    else
        cout << "No se pueden restar..." << endl;
    
    return B;
}

template < typename Type >
Matrix<Type> Matrix<Type>::operator*( const Matrix &A ) {
    Matrix<Type> B( row, A.col );
    
    if( col == A.row ) {
        for( int i = 0; i < row; ++i )
            for( int j = 0; j < A.col; ++j )
                for( int k = 0; k < col; ++k )
                    *(*( B.matrix + i ) + j ) += *(*( matrix + i ) + k ) * *(*( A.matrix + k ) + j );
    }

    else 
        cout << "No se pueden multiplicar..." << endl;
    
    return B;  
}

template< typename Type >
Matrix<Type> Matrix<Type>::operator/( const Matrix &A ) {
    Matrix<Type> B( row, col );

    if( row == A.row && col == A.col ) {
        for( int i = 0; i < row; ++i )
            for( int j = 0; j < col; ++j )
                *(*( B.matrix + i ) + j ) = *(*( matrix + i ) + j ) / *(*( A.matrix + i ) + j );
    }

    else
        cout << "No se pueden dividir..." << endl;
    
    return B;
}

template < typename Type >
Matrix<Type> Matrix<Type>::operator%( const Matrix &A ) {
    Matrix<Type> B( row, col );

    if( row == A.row && col == A.col ) {
        for( int i = 0; i < row; ++i )
            for( int j = 0; j < col; ++j )
                *(*( B.matrix + i ) + j ) = *(*( matrix + i ) + j ) * *(*( A.matrix + i ) + j );
    }

    else
        cout << "No se pueden multiplicar..." << endl;
    
    return B;
}

template < typename Type >
Matrix<Type> Matrix<Type>::operator=( const Matrix &M ) {
    this -> ~Matrix();
       
    this -> row = M.row;
    this -> col = M.col;

    matrix = new Type*[ row ];
    for( int i = 0; i < row; ++i )
        *( matrix + i ) = new Type[ col ];
    
    for( int i = 0; i < row; i++ ) {
        for( int j = 0; j < col; j++ ) 
            *(*( matrix + i ) + j ) = *(*( M.matrix + i ) + j );
    }
    
    return *this;
}

template < typename Type>
Matrix<Type> Matrix<Type>::sumMatrixThread( const Matrix &M1, const Matrix &M2 ) {
    int nThreads = 2;
    int tRow = M1.getRow() / nThreads;    
    Matrix<Type> R1( tRow, M1.getCol());
    Matrix<Type> *r1Ptr = &R1;
    Matrix<Type> R2( tRow, M1.getCol());
    Matrix<Type> *r2Ptr = &R2;
    Matrix<Type> R( M1.getRow(), M1.getRow());
    Sumatoria S1 = Sumatoria();
    std::thread t1( S1, M1, M2, r1Ptr, 0, tRow );
    std::thread t2( S1, M1, M2, r2Ptr, tRow , M1.getRow());
    t1.join();
    t2.join();
    
    for( int i = 0; i < R1.row; ++i )
        for( int j = 0; j < R1.col; ++j )
            *( *( R.matrix + i ) + j ) = *( *( R1.matrix + i ) + j );
    int pos = 0;
    for( int i = tRow; i < M1.getRow(); ++i ) {
        for( int j = 0; j < R2.col; ++j )
            *( *( R.matrix + i ) + j ) = *( *( R2.matrix + pos ) + j );
        ++pos;
    }
    return R;
    
}

template<typename Type>
Matrix<Type> Matrix<Type>::multScalar( double scalar ) {
    for( int i = 0; i < row; i++ ) 
        for( int j = 0; j < col; j++ )
            *( *( matrix + i ) + j ) = *( *( matrix + i ) + j ) * scalar;
    return *this;
}

template<typename Type>
Matrix<Type> Matrix<Type>::multDouble( double n){
	Matrix<Type> aux(this->getRow(),this->getCol());
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			*(*(aux.matrix+i)+j) = *(*(this->matrix+i)+j) * n;
		}
	}
	return aux;
}

template< typename Type >
Matrix<Type> Matrix<Type>::sumScalar( double scalar ) {
    for( int i = 0; i < row; i++ ) 
        for( int j = 0; j < col; j++ )
            *(*( matrix + i ) + j ) = *(*( matrix + i ) + j ) + scalar;
    return *this;
}

template< typename Type >
Matrix<Type> Matrix<Type>::powTwice() {
    Matrix<Type> B( row, col );  
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < col; ++j )
            *(*( B.matrix + i ) + j ) =  *(*( matrix + i ) + j ) *  *(*( matrix + i ) + j );
    return B;
}

template < typename Type >
double Matrix<Type>::addAll() {
    double acc = 0;
    for( int i = 0; i < row; ++i )
        for( int j = 0; j < col; ++j )
            acc += *(*( matrix + i ) + j );
    return acc;
}

template < typename Type >
ostream& operator <<( ostream &o, const Matrix <Type> M ) {
	for( int i = 0; i < M.row; i++ ) {
        for( int j = 0; j < M.col; j++ )
            o << *(*( M.matrix + i ) + j ) << " ";
        cout << endl;
    }
	return o;
}


#endif
