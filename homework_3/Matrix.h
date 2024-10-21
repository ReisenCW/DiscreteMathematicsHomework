#pragma once
#include <iostream>
#include <vector>
using namespace std;

class Matrix {
private:
	vector<vector<int>> matrix;
	vector<vector<int>> transposeMatrix;
	int row;
	int col;
public:
	Matrix() : row(0), col(0) {};
	Matrix(const vector<vector<int>>& matrix) : matrix(matrix), row((int)matrix.size()),col((int)matrix[0].size()) {}
	void PrintMatrix();
	int GetElement(int i, int j) { return matrix[i][j]; }
	void ModifyElement(int i, int j, int value) { matrix[i][j] = value; }
	Matrix Transpose();
	Matrix LogicalAdd(const Matrix& other);//Âß¼­¼Ó

	Matrix GetReflexiveClosure();
	Matrix GetSymmetricClosure();
	Matrix GetTransitiveClosure();
};
