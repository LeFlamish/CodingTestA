#include <iostream>
#include <queue> // 큐를 사용하기 위한 라이브러리(STL)
using namespace std;

queue<int> Q; // queue<자료형> 변수 이름(큐 이름);

int main() {
	cin.tie(0)->sync_with_stdio(0);
	Q.push(1); // 큐에 데이터를 넣는다.
	Q.pop(); // 큐의 맨 앞에 있는 데이터를 꺼낸다.
	Q.front(); // 큐의 맨 앞에 있는 데이터를 반환한다.
	Q.back(); // 큐의 맨 뒤에 있는 데이터를 반환한다.
	Q.size(); // 큐에 들어있는 데이터의 개수를 반환한다.
	Q.empty(); // 큐가 비어있다면 true, 비어있지 않으면 false를 반환한다.

	// 여기서 중요한 점은 pop과 front, back은 큐가 비어있다면 오류가 난다는 점이다.
	// 따라서 pop과 front, back을 사용할 때는 항상 if (!Q.empty()) Q.pop()/Q.front()/Q.back(); 이런 식으로 비어있지 않을 때만 실행할 수 있도록 해주자.
	return 0;
}
