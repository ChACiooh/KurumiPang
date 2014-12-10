#include "Bejewled.h"

using namespace std;

int process();

int main() { return process(); }

int process()
{
	int w, h, num;
	cin >> w >> h >> num;
	KurumiPang kp(w,h);
	while(true)
	{
		cin >> kp;
		cout << kp.AI() << endl;
		int score;	cin >> score;
	}
	return 0;
}
