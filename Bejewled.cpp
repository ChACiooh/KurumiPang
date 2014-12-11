#include "Bejewled.h"

using namespace std;

KurumiPang::KurumiPang(int w, int h) : width(w), height(h)
{
	board = new char*[h];
	for(int i=0;i<h;i++)	board[i] = new char[w];
}
KurumiPang::~KurumiPang()
{
	for(int i=0;i<height;i++)	delete[] board[i];
	delete[] board;
}

char& KurumiPang::operator()(int i, int j)
{
	return board[j][i];
}

int KurumiPang::ColCheck(int x1, int y1, int x2, int y2) const
{
	int rcnt = 0, cnt = 1;

	char** temp = new char*[height];
	for(int i=0;i<height;i++)	temp[i] = new char[width];
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)	temp[i][j] = board[i][j]; // 복사.

	char tc = temp[y1][x1];
	temp[y1][x1] = temp[y2][x2];
	temp[y2][x2] = tc;

	/*** x1의 열 ***/
	tc = temp[0][x1];
	for(int i=1;i<height;i++)
	{
		char ttc = temp[i][x1];
		if(ttc == tc)
		{
			cnt++;
		}
		else if(cnt < NECCESSARY_FOR_DESTROY)	cnt = 1; // 없애는 조건을 충족시키지 못한 채 다른 문자 만남.
		else // 없애는 조건을 충족 시켰을 때
		{
			rcnt += cnt;
			cnt = 1;
		}

		tc = ttc;
	}
	if(cnt >= NECCESSARY_FOR_DESTROY)	rcnt += cnt;

	/*** x2의 열 ***/
	if(x1 != x2) // 위아래로만 바뀌었을 경우 한 번만 체크하면 됨.
	{
		tc = temp[0][x2];
		cnt = 1;
		for(int i=1;i<height;i++)
		{
			char ttc = temp[i][x2];
			if(ttc == tc)
			{
				cnt++;
			}
			else if(cnt < NECCESSARY_FOR_DESTROY)	cnt = 1; // 없애는 조건을 충족시키지 못한 채 다른 문자 만남.
			else // 없애는 조건을 충족 시켰을 때
			{
				rcnt += cnt;
				cnt = 1;
			}

			tc = ttc;
		}
		if(cnt >= NECCESSARY_FOR_DESTROY)	rcnt += cnt;
	}

	for(int i=0;i<height;i++)	delete[] temp[i];
	delete[] temp;
	return rcnt;
} // int KurumiPang::ColCheck end.

int KurumiPang::RowCheck(int x1, int y1, int x2, int y2) const
{
	int rcnt = 0, cnt = 1;

	char** temp = new char*[height];
	for(int i=0;i<height;i++)	temp[i] = new char[width];
	for(int i=0;i<height;i++)
		for(int j=0;j<width;j++)	temp[i][j] = board[i][j]; // 복사.

	char tc = temp[y1][x1];
	temp[y1][x1] = temp[y2][x2];
	temp[y2][x2] = tc;

	/*** y1의 행 ***/
	tc = temp[y1][0];
	for(int i=1;i<width;i++)
	{
		char ttc = temp[y1][i];
		if(ttc == tc)
		{
			cnt++;
		}
		else if(cnt < NECCESSARY_FOR_DESTROY)	cnt = 1; // 없애는 조건을 충족시키지 못한 채 다른 문자 만남.
		else // 없애는 조건을 충족 시켰을 때
		{
			rcnt += cnt;
			cnt = 1;
		}

		tc = ttc;
	}

	if(cnt >= NECCESSARY_FOR_DESTROY)	rcnt += cnt;

	/*** y2의 행 ***/
	if(y1 != y2) // 양옆으로만 바뀌었을 경우 한 번만 체크하면 됨.
	{
		tc = temp[y2][0];
		cnt = 1;
		for(int i=1;i<width;i++)
		{
			char ttc = temp[y2][i];
			if(ttc == tc)
			{
				cnt++;
			}
			else if(cnt < NECCESSARY_FOR_DESTROY)	cnt = 1; // 없애는 조건을 충족시키지 못한 채 다른 문자 만남.
			else // 없애는 조건을 충족 시켰을 때
			{
				rcnt += cnt;
				cnt = 1;
			}

			tc = ttc;
		}
		if(cnt >= NECCESSARY_FOR_DESTROY)	rcnt += cnt;
	}

	for(int i=0;i<height;i++)	delete[] temp[i];
	delete[] temp;
	return rcnt;
} // int KurumiPang::RowCheck end.

Result KurumiPang::AI() const
{
	Result res;
	int rcnt = 0;
	for(int y=0;y<height-1;y++)
	{
		int cnt = 0;
		int x;
		for(x=0;x<width-1;x++)
		{
			cnt = ColCheck(x, y, x+1, y);
			if(rcnt <= cnt)
			{
				rcnt = cnt;
				res.first = x;
				res.second = y;
				res.direct = 'R';
			}

			cnt = RowCheck(x, y, x+1, y);
			if(rcnt <= cnt)
			{
				rcnt = cnt;
				res.first = x;
				res.second = y;
				res.direct = 'R';
			}

			cnt = ColCheck(x, y, x, y+1);
			if(rcnt <= cnt)
			{
				rcnt = cnt;
				res.first = x;
				res.second = y;
				res.direct = 'D';
			}

			cnt = RowCheck(x, y, x, y+1);
			if(rcnt <= cnt)
			{
				rcnt = cnt;
				res.first = x;
				res.second = y;
				res.direct = 'D';
			}
		}

		x = width - 1;
		cnt = ColCheck(x, y, x, y+1);
		if(rcnt <= cnt)
		{
			rcnt = cnt;
			res.first = x;
			res.second = y;
			res.direct = 'D';
		}

		cnt = RowCheck(x, y, x, y+1);
		if(rcnt <= cnt)
		{
			rcnt = cnt;
			res.first = x;
			res.second = y;
			res.direct = 'D';
		}
	} // height - 2번째까지 모두 체크한다.

	// height - 1번째 줄에 대한 경우.
	for(int x=0;x<width-1;x++)
	{
		int y = height - 1;
		int cnt = ColCheck(x, y, x+1, y);
		if(rcnt <= cnt)
		{
			rcnt = cnt;
			res.first = x;
			res.second = y;
			res.direct = 'R';
		}

		cnt = RowCheck(x, y, x+1, y);
		if(rcnt <= cnt)
		{
			rcnt = cnt;
			res.first = x;
			res.second = y;
			res.direct = 'R';
		}
	}

	return res;
}

ostream& operator<<(ostream& os, KurumiPang& kp)
{
	for(int y = 0; y < kp.Height(); y++)
	{
		for(int x = 0; x < kp.Width(); x++)
			os << kp(x,y) << " ";
		os << endl;
	}
	os << endl;
	return os;
}

istream& operator>>(istream& is, KurumiPang& kp)
{
	for(int y=0;y<kp.Height();y++)
		for(int x=0;x<kp.Width();x++)	is >> kp(x,y);
	return is;
}

ostream& operator<<(ostream& os, Result res)
{
	os << res.first << " " << res.second << " " << res.direct;
	return os;
}
