#include <iostream>
#include <vector>
#include <algorithm> // sort, reverse 사용을 위한 라이브러리
using namespace std;

// 구조체 정렬은 추후 업데이트

const int SIZE = 10; // 또는 #define SIZE 10

int arr[SIZE] = { 5, 2, 9, 1, 5, 6, 3, 8, 4, 7 }; // 배열 초기화
vector<int> V = { 5, 2, 9, 1, 5, 6, 3, 8, 4, 7 }; // 벡터 초기화

int main() {
    cin.tie(0)->sync_with_stdio(0);

    // 벡터 정렬
    sort(V.begin(), V.end()); // 오름차순 정렬
    sort(V.begin(), V.end(), greater<>()); // 내림차순 정렬
    reverse(V.begin(), V.end()); // 역순

    // 배열 정렬
    sort(arr, arr + SIZE); // 오름차순 정렬
    sort(arr, arr + SIZE, greater<>()); // 내림차순 정렬
    reverse(arr, arr + SIZE); // 역순

    return 0;
}
