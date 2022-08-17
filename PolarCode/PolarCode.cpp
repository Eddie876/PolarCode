// PolarCode.cpp: 定義應用程式的進入點。
//

#include "PolarCode.h"
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <random>
#include <iomanip>
#include <cmath>
#include <vector>

using namespace std;

const int N = sizeof(ReliabilitySequence) / sizeof(int);

vector<vector<int>> Calculate(vector<vector<int>> matrix) {
    int layer = log2(N);
    while (layer > 0) {
        layer--;
        int size = pow(2, layer);
        vector<vector<int>> newMatrix(size);
        for (int i = 0; i < newMatrix.size(); i++) {
            vector<int> arrayLeft = matrix[2 * i];
            vector<int> arrayRight = matrix[2 * i + 1];
            vector<int> newArray(arrayLeft.size() + arrayRight.size());
            for (int j = 0; j < arrayLeft.size(); j++) {
                newArray[j] = (arrayLeft[j] + arrayRight[j]) % 2;
                newArray[j + arrayLeft.size()] = arrayRight[j] % 2;
            }
            newMatrix[i] = newArray;
        }
        matrix = newMatrix;
    }
    return matrix;
}

vector<int> CreateMessage(int size) {
    //第1個到第N-K個是frozen bits；第N-K+1個~第N個是message bits
    //故將0放入第N-K個的位置；將message放入第N-K+1個~第N個的位置
    vector<int> message(N);
    srand((unsigned)time(NULL));
    for (int i = 0; i < N; i++) {
        if (i < N - size)
            message[i] = 0;
        else
            message[i] = rand() % 2;
    }
    return message;
}

vector<int> SortMessage(vector<int> array) {
    return array;
}

void PrintArray(vector<int> array) {
    cout << "[";
    for (int i = 0; i < array.size(); i++) {
        cout << array[i];
        if (i < array.size() - 1)
            cout << ",";
    }
    cout << "]"  << endl;
}

void PrintMatrix(vector<vector<int>> matrix) {
    cout << "{";
    for (int i = 0; i < matrix.size(); i++) {
        cout << "[";
        for (int j = 0; j < matrix[i].size(); j++) {
            cout << matrix[i][j];
            if (j < matrix[i].size() - 1)
                cout << ",";
        }
        cout << "]";
        if (i < matrix.size() - 1)
            cout << ",";
    }
    for (auto array : matrix) {
        
    }
    cout << "}" << endl;
}

int main() {
    cout << "請輸入message數：";
    int size;
    cin >> size;

    //產生K個bit的message，並將前面的frozen bits補滿0
    auto message = CreateMessage(size);
    cout << "message：" << endl;
    PrintArray(message);
    cout << endl;

    //將message依Reliability Sequence排序
    auto sortedMessages = SortMessage(message);
    cout << "sortedMessages：" << endl;
    PrintArray(sortedMessages);
    cout << endl;

    //將陣列轉為矩陣，以便進行運算
    vector<vector<int>> matrix(N);
    for (int i = 0; i < N; i++) {
        matrix[i] = { sortedMessages[i] };
    }
    cout << "matrix：" << endl;
    PrintMatrix(matrix);
    cout << endl;

    //進行運算
    auto result = Calculate(matrix);
    cout << "result：" << endl;
    PrintMatrix(matrix);    

    return 0;
}

