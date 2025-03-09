// C++로 문제를 푼다면 아래 5줄 정도는 눈 감고도 입력할 수 있도록 하자.
// 살기 위해서는 숨을 쉬듯 너무나도 당연한 기본적인 코드이다.

#include <iostream> // C++에서는 stdio.h 대신 iostream 사용
using namespace std; // cin, cout 등의 함수의 위치는 std에 있음. 매번 std::cin, std::cout으로 써주기 귀찮기 때문에 자동으로 std 채우는 코드

int main() {
	cin.tie(0)->sync_with_stdio(0); // C의 입출력(scanf, printf)를 절대 사용 불가능하지만, 코드의 실행 속도가 빨라지므로 필수.
	return 0;
}
