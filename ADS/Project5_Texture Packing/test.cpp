#include "stdafx.h"
#include "packing.h"

struct rec {
	int w;
	int h;
}r[10000];

int cmp(const void* a, const void* b) {
	return (*(struct rec*)b).w - (*(struct rec*)a).w;
}

int main()
{
	clock_t start, stop;//the start and end of the runtime
	time_t tim;//random variety
	double runtime;
	int x, y;
	int width;//the width given for the bin
	int num;//the number of rectangles given
	int minheight;//the final result--the min height of the bin
	int RectWidth, RectHeight;//size of the rectangle
	int op;//the heuristic rule
	int recarea = 0, binarea = 0;//compare the sum area of all rectangles and the area of the bin
	double ratio;

	cout << "Input the width of the bin and the number of rectangles:";
	cin >> width >> num;

	srand((unsigned)time(&tim));//random seed
	for (int i = 0; i < num; i++)
	{
		x = (int)(rand() % width + 1);//restrict the length of one edge to the bin's width
		y = (int)(rand() % (2 * width) + 1);
		if (x < y) {	//assume w is shorter than h
			r[i].w = x;
			r[i].h = y;
		}
		else {
			r[i].w = y;
			r[i].h = x;
		}
	}
	qsort(r, num, sizeof(r[0]), cmp);//sort in descending order by the shorter edge
	for (int i = 0; i < num; i++) {
		recarea += r[i].w * r[i].h;
	}

	//the following program test 7 different heuristic rules
	ShelfBinPack Bin0(width);//create a bin of given width
	enum ShelfBinPack::ShelfChoiceHeuristic choice = (enum ShelfBinPack::ShelfChoiceHeuristic)0;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin0.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);//calculate the runtime of insertion
	cout << "The runtime of ShelfNextFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin0.GetHeight() << endl;
	binarea = width * Bin0.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << setprecision(4) << ratio << endl;
	cout << endl;

	ShelfBinPack Bin1(width);
	choice = (enum ShelfBinPack::ShelfChoiceHeuristic)1;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin1.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);
	cout << "The runtime of ShelfFirstFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin1.GetHeight() << endl;
	binarea = width * Bin1.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << ratio << endl;
	cout << endl;

	ShelfBinPack Bin2(width);
	choice = (enum ShelfBinPack::ShelfChoiceHeuristic)2;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin2.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);
	cout << "The runtime of ShelfBestAreaFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin2.GetHeight() << endl;
	binarea = width * Bin2.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << ratio << endl;
	cout << endl;

	ShelfBinPack Bin3(width);
	choice = (enum ShelfBinPack::ShelfChoiceHeuristic)3;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin3.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);
	cout << "The runtime of ShelfWorstAreaFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin3.GetHeight() << endl;
	binarea = width * Bin3.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << ratio << endl;
	cout << endl;

	ShelfBinPack Bin4(width);
	choice = (enum ShelfBinPack::ShelfChoiceHeuristic)4;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin4.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);
	cout << "The runtime of ShelfBestHeightFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin4.GetHeight() << endl;
	binarea = width * Bin4.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << ratio << endl;
	cout << endl;

	ShelfBinPack Bin5(width);
	choice = (enum ShelfBinPack::ShelfChoiceHeuristic)5;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin5.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);
	cout << "The runtime of ShelfBestWidthFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin5.GetHeight() << endl;
	binarea = width * Bin5.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << ratio << endl;
	cout << endl;

	ShelfBinPack Bin6(width);
	choice = (enum ShelfBinPack::ShelfChoiceHeuristic)6;
	start = clock();
	for (int i = 0; i < num; i++) {
		Rect newnode = Bin6.Insert(r[i].w, r[i].h, choice);
	}
	stop = clock();
	runtime = (double)(stop - start);
	cout << "The runtime of ShelfWorstWidthFit is " << runtime << " ms" << endl;
	cout << "The MinHeight is " << Bin6.GetHeight() << endl;
	binarea = width * Bin6.GetHeight();
	ratio = (double)binarea / recarea;
	cout << "The ratio is " << ratio << endl;
	cout << endl;

	system("pause");
	return 0;
}