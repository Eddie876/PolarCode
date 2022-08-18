// PolarCode.cpp: 定義應用程式的進入點。

#include "PolarCode.h"
#include <iostream>
#include <vector>

using namespace std;

const int N = sizeof(ReliabilitySequence) / sizeof(int);

vector<int> CalculateMatrix(vector<int> arrayLeft, vector<int> arrayRight) {
    vector<int> newArray(arrayLeft.size() * 2);
    for (int i = 0; i < arrayLeft.size(); i++)
    {
        newArray[i] = arrayLeft[i] ^= arrayRight[i];
        newArray[i + arrayLeft.size()] = arrayRight[i];
    }
    return newArray;
}

vector<vector<int>> CalculateLayer(vector<vector<int>> matrix) {
    int layer = log2(N);
    while (layer > 0) {
        layer--;
        int size = pow(2, layer);
        vector<vector<int>> newMatrix(size);
        for (int i = 0; i < newMatrix.size(); i++) {
            auto arrayLeft = matrix[2 * i];
            auto arrayRight = matrix[2 * i + 1];
            newMatrix[i] = CalculateMatrix(arrayLeft, arrayRight);
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
    vector<int> newArray(array.size());
    for (int i = 0; i < array.size(); i++) {
        auto position = ReliabilitySequence[i];
        newArray[position] = array[i];
    }
    return newArray;
}

void PrintArray(vector<int> array) {
    cout << "[";
    for (int i = 0; i < array.size(); i++) {
        cout << array[i];
        if (i < array.size() - 1)
            cout << ",";
    }
    cout << "]";
}

void PrintMatrix(vector<vector<int>> matrix) {
    cout << "{";
    for (int i = 0; i < matrix.size(); i++) {
        PrintArray(matrix[i]);
        if (i < matrix.size() - 1)
            cout << ",";
    }
    cout << "}";
}

int main() {
    cout << "請輸入message數：";
    int size;
    cin >> size;

    //產生K個bit的message，並將前面的frozen bits補滿0
    auto message = CreateMessage(size);
    cout << "message：" << endl;
    PrintArray(message);
    cout << endl << endl;

    //將message依Reliability Sequence排序
    auto sortedMessages = SortMessage(message);
    cout << "sorted messages：" << endl;
    PrintArray(sortedMessages);
    cout << endl << endl;

    //將陣列轉為矩陣，以便進行運算
    vector<vector<int>> matrix(N);
    for (int i = 0; i < N; i++) {
        matrix[i] = { sortedMessages[i] };
    }
    cout << "matrix：" << endl;
    PrintMatrix(matrix);
    cout << endl << endl;

    //進行運算
    auto result = CalculateLayer(matrix);
    cout << "result：" << endl;
    PrintMatrix(result);

    return 0;
}

