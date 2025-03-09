#include <iostream>
#include <deque> // 덱을 사용하기 위한 라이브러리(STL)
using namespace std;

deque<int> DQ; // deque<자료형> 변수 이름(덱 이름);

int main() {
	cin.tie(0)->sync_with_stdio(0);
	DQ.push_back(1); // 덱의 맨 뒤에 데이터를 넣는다.
	DQ.push_front(1); // 덱의 맨 앞에 데이터를 넣는다.
	DQ.pop_back(); // 덱의 맨 뒤에서 데이터를 꺼낸다.
	DQ.pop_front(); // 덱의 맨 앞에서 데이터를 꺼낸다.
	DQ.front(); // 덱의 맨 앞에 있는 데이터를 반환한다.
	DQ.back(); // 덱의 맨 뒤에 있는 데이터를 반환한다.
	DQ.size(); // 덱에 들어있는 데이터의 개수를 반환한다.
	DQ.empty(); // 덱이 비어있다면 true, 비어있지 않으면 false를 반환한다.
	
	// 이 외에도 begin, end, insert, clear 등이 있지만 써본 적이 없다.
	// 궁금하면 필요한 매개변수들과 사용법을 찾아보도록 하자.
	// begin : 덱의 시작 주소를 반환.
	// end : 덱의 끝 주소를 반환.
	// insert : 덱의 중간에 데이터를 삽입.
	// clear : 덱에 있는 모든 데이터를 삭제.

	// 여기서 중요한 점은 pop_back, pop_front, front, back은 덱이 비어있다면 오류가 난다는 점이다.
	// 따라서 pop_back, pop_front, front, back을 사용할 때는 항상 if (!DQ.empty()) DQ.pop_back()/DQ.pop_front()/DQ.front()/DQ.back();
  // 이런 식으로 비어있지 않을 때만 실행할 수 있도록 해주자.
	return 0;
}
