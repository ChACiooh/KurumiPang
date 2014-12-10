#ifndef BEJEWLED_H_INCLUDED
#define BEJEWLED_H_INCLUDED

#include <iostream>

#define	NECCESSARY_FOR_DESTROY	3

struct Result {
	int first, second;
	char direct;
};

class KurumiPang {
public:
	KurumiPang(int w, int h);
	~KurumiPang();
	const int Width() const { return width; }
	const int Height() const { return height; }
	const int Score() const { return score; }
	char& operator()(int i, int j);

	int ColCheck(int x1, int y1, int x2, int y2) const;
	int RowCheck(int x1, int y1, int x2, int y2) const;
	Result AI() const;

private:
	int width;
	int height;
	int score;
	char** board;
};

std::ostream& operator<<(std::ostream& os, KurumiPang& kp);
std::istream& operator>>(std::istream& is, KurumiPang& kp);
std::ostream& operator<<(std::ostream& os, Result res);

#endif // BEJEWLED_H_INCLUDED
