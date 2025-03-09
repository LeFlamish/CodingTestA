#include <iostream>
#include <vector> // 벡터를 사용하기 위한 라이브러리(STL)
using namespace std;

// 벡터는 사이즈를 동적으로 바꿀 수 있는 배열이라고 생각하면 된다.
// 즉, 더 편리해진 배열 정도로만 생각하면 된다.
vector<int> V; // vector<자료형> 변수 이름(벡터 이름);
// 배열처럼 V[0], V[1]과 같이 인덱싱이 가능하다.

int main() {
	cin.tie(0)->sync_with_stdio(0);
	V.push_back(1); // 벡터의 맨 뒤에 데이터를 추가한다.
	V.pop_back(); // 벡터의 맨 뒤에서 데이터를 꺼낸다.
	V.front(); // 벡터의 맨 앞에 있는 데이터를 반환한다.
	V.back(); // 벡터의 맨 뒤에 있는 데이터를 반환한다.
	V.size(); // 벡터에 들어있는 데이터의 개수를 반환한다.
	V.empty(); // 벡터가 비어있다면 true, 비어있지 않으면 false를 반환한다.
	V.begin(); // 벡터의 시작 주소를 반환한다.
	V.end(); // 벡터의 끝 주소를 반환한다.

	// 여기서 중요한 점은 pop_back과 front, back은 벡터가 비어있다면 오류가 난다는 점이다.
	// 따라서 pop_back과 front, back을 사용할 때는 항상 if (!V.empty()) V.pop_back()/V.front()/V.back(); 이런 식으로 비어있지 않을 때만 실행할 수 있도록 해주자.

	return 0;
}
