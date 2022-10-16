#pragma once
#include <iostream>

template<typename T>
class TMatrix final
{
public:
	TMatrix(int rows,int cols);
	~TMatrix();

	TMatrix(const TMatrix& other) = delete;
	TMatrix(TMatrix&& other) noexcept = delete;
	TMatrix& operator=(const TMatrix& other) = delete;
	TMatrix& operator=(TMatrix&& other) noexcept = delete;

	T& operator[](const int& index) const;
	T& Get(int x, int y) { return m_pGrid[x][y]; }
	int Rows()const { return m_Rows; }
	int Cols()const { return m_Cols; }
private:
	T** m_pGrid;
	const int m_Rows, m_Cols;
};

template<typename T>
inline TMatrix<T>::TMatrix(int rows, int cols)
	:m_Rows{ rows },m_Cols{cols}
{
	m_pGrid = new T*[rows];
	for (int i = 0; i < rows; ++i)
		m_pGrid[i] = new T[cols];
}

template<typename T>
inline TMatrix<T>::~TMatrix()
{
	for (int i = 0; i < m_Rows; ++i)
		delete[] m_pGrid[i];
	delete[] m_pGrid;
}

template<typename T>
inline T& TMatrix<T>::operator[](const int& index) const
{
	return *m_pGrid[index];
}
