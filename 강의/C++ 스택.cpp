#include <iostream>
#include <stack> // 스택을 사용하기 위한 라이브러리(STL)
using namespace std;

stack<int> S; // stack<자료형> 변수 이름(스택 이름)

int main() {
	cin.tie(0)->sync_with_stdio(0);
	S.push(1); // 스택에 데이터를 넣는다.
	S.pop(); // 스택의 맨 위에 있는 데이터를 꺼낸다.
	S.top(); // 스택의 맨 위에 있는 데이터를 반환한다.
	S.size(); // 스택에 들어있는 데이터의 개수를 반환한다.
	S.empty(); // 스택이 비어있다면 true, 비어있지 않으면 false를 반환한다.

	// 여기서 중요한 점은 pop과 top은 스택이 비어있다면 오류가 난다는 점이다.
	// 따라서 pop과 top을 사용할 때는 항상 if (!S.empty()) S.pop()/S.top(); 이런 식으로 비어있지 않을 때만 실행할 수 있도록 해주자.
	return 0;
}
