#include <iostream>
#include <queue> // 큐를 사용하기 위한 라이브러리(STL)
using namespace std;

// 큐는 BFS(너비 우선 탐색)에 핵심으로 사용되기 때문에 코딩테스트에서 필수로 나온다.
queue<int> Q; // queue<자료형> 변수 이름(큐 이름);

// 당연하게도 구조체 등의 모든 자료형이 들어갈 수 있다. 큐뿐만이 아니라 스택, 덱, 벡터 등의 자료구조에도 모든 자료형이 들어갈 수 있다.
// ex.1
struct Human {
	int x, y, age;
	bool isAlive;
};
queue<Human> human;

// ex.2
typedef pair<int, int> PI;
#define X first
#define Y second
queue<PI> QQ;

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
