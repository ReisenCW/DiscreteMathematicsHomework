#include "Matrix.h"

void Matrix::PrintMatrix() {
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			cout << matrix[i][j] << " ";
		}
		cout << endl;
	}
	cout << endl;
}

Matrix Matrix::Transpose() {
	if (transposeMatrix.size() != 0) {
		return Matrix(transposeMatrix);
	}
	vector<vector<int>> result(row, vector<int>(col, 0));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result[j][i] = matrix[i][j];
		}
	}
	transposeMatrix = result;
	return Matrix(result);
}

Matrix Matrix::LogicalAdd(const Matrix& other) {
	if (row != other.row || col != other.col) {
		cout << "����ά�Ȳ�ƥ��,�޷����" << endl;
		return Matrix();
	}
	vector<vector<int>> result(row, vector<int>(col, 0));
	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			result[i][j] = matrix[i][j] | other.matrix[i][j];
		}
	}
	return Matrix(result);
}


//���Է��հ�,ֻ��Ҫ���Խ����ϵ�Ԫ����Ϊ1����
Matrix Matrix::GetReflexiveClosure() {
	Matrix result(this->matrix);
	for (int i = 0; i < row; i++) {
		result.matrix[i][i] = 1;
	}
	return result;
}

//��ԳƱհ�,ֻ��Ҫ�ɹ�ϵ���������ת�þ���õ�(�߼���)
Matrix Matrix::GetSymmetricClosure() {
	Matrix result = this->LogicalAdd(this->Transpose());
	return result;
}

//�󴫵ݱհ�
Matrix Matrix::GetTransitiveClosure() {
	Matrix result(this->matrix);
	for (int k = 0; k < row; k++) {
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				result.matrix[i][j] = result.matrix[i][j] || (result.matrix[i][k] && result.matrix[k][j]);
			}
		}
	}
	return result;
}