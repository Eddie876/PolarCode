// PolarCode.cpp: 定義應用程式的進入點。

#include "PolarCode.h"
#include <iostream>
#include <vector>

using namespace std;

const int N = sizeof(ReliabilitySequence) / sizeof(int);

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

#pragma region Encode
vector<int> EncodeArray(vector<int> arrayLeft, vector<int> arrayRight) {
    vector<int> newArray(arrayLeft.size() * 2);
    for (int i = 0; i < arrayLeft.size(); i++)
    {
        newArray[i] = arrayLeft[i] ^= arrayRight[i];
        newArray[i + arrayLeft.size()] = arrayRight[i];
    }
    return newArray;
}

vector<vector<int>> EncodeMatrix(vector<vector<int>> oldMatrix) {
    int size = oldMatrix.size() / 2;
    vector<vector<int>> newMatrix(size);

    for (int i = 0; i < newMatrix.size(); i++)
    {
        auto arrayLeft = oldMatrix[2 * i];
        auto arrayRight = oldMatrix[2 * i + 1];
        newMatrix[i] = EncodeArray(arrayLeft, arrayRight);
    }

    if (newMatrix.size() > 1)
    {
        return EncodeMatrix(newMatrix);
    }
    return newMatrix;
}
#pragma endregion


void Calculate(int size) {
    //產生K個bit的message，並將前面的frozen bits補滿0
    auto message = CreateMessage(size);
    cout << "Message：" << endl;
    PrintArray(message);
    cout << endl << endl;

    //將message依Reliability Sequence排序
    auto sortedMessages = SortMessage(message);
    cout << "Sorted Message：" << endl;
    PrintArray(sortedMessages);
    cout << endl << endl;

    //將陣列轉為矩陣，以便進行運算
    vector<vector<int>> matrix(N);
    for (int i = 0; i < N; i++) {
        matrix[i] = { sortedMessages[i] };
    }
    cout << "Message Matrix：" << endl;
    PrintMatrix(matrix);
    cout << endl << endl;

    //進行編碼
    auto encodedMessage = EncodeMatrix(matrix);
    cout << "Encoded Message：" << endl;
    PrintMatrix(encodedMessage);
    cout << endl << endl;

    //進行BPSK變換
    auto bpsk = BPSK(encodedMessage);
    cout << "BPSK Message：" << endl;
    PrintMatrix(bpsk);
    cout << endl << endl;

    //進行解碼
    auto decodedMessage = DecodeMatrix(bpsk);
    cout << "Decoded Message：" << endl;
    PrintMatrix(decodedMessage);
    cout << endl << endl << "============================================================" << endl << endl;
}

int main() {
    while (true) {
        cout << "請輸入message數：";
        int size;
        cin >> size;
        Calculate(size);
    }
}