#include <stdio.h>
#include <stdlib.h>
#include <graphics.h>


int main(void)
{
	int gd = DETECT, gm;
	int left = 320, top = 200, right = 360, bottom = 240;
	initgraph(&gd, &gm, NULL);

    int i;
    int v = 1;

    for (i=0; i<12; i++)
        line(0, i*40, 640, i*40);

    for (i=0; i<16; i++)
        line(i*40, 0, i*40, 480);

    //�� ����� �������� � ��������� �� 90� �����, �������� ���� �������� �� ������, ������� ��� ������ �� ��������� ������.
    //�� ������ �������� � ��������� �� 90� ������, �������� ���� �������� �� �����, ������� ��� ������ �� ��������� ������.

    while (1) {

        if (v == 1) {   //  �����
            if(getpixel(left+15,top+15) == BLACK) {
                delay(1000);

                setfillstyle(1,WHITE);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                top-=40;
                bottom-=40;

                if(getpixel(left+15,top+15) != BLACK)
                    continue;

                v = 4;
            }
            else
            if(getpixel(left+15,top+15) == WHITE) {
                delay(1000);

                setfillstyle(1,BLACK);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                left-=40;
                right-=40;

                if(getpixel(left+15,top+15) != WHITE)
                    continue;

                v = 3;
            }
        }
        else
        if (v == 2) {   //  ����
            if(getpixel(left+15,top+15) == BLACK) {
                delay(1000);

                setfillstyle(1,WHITE);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                top+=40;
                bottom+=40;

                if(getpixel(left+15,top+15) != BLACK)
                    continue;

                v = 3;
            }
            else
            if(getpixel(left+15,top+15) == WHITE) {
                delay(1000);

                setfillstyle(1,BLACK);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                left+=40;
                right+=40;

                if(getpixel(left+15,top+15) != WHITE)
                    continue;

                v = 4;
            }
        }
        else
        if (v == 3) {   //  �����
            if(getpixel(left+15,top+15) == BLACK) {
                delay(1000);

                setfillstyle(1,WHITE);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                left-=40;
                right-=40;

                if(getpixel(left+15,top+15) != BLACK)
                    continue;

                v = 1;
            }
            else
            if(getpixel(left+15,top+15) == WHITE) {
                delay(1000);

                setfillstyle(1,BLACK);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                top+=40;
                bottom+=40;

                if(getpixel(left+15,top+15) != WHITE)
                    continue;

                v = 2;
            }
        }
        else
        if (v == 4) {   //  ������
            if(getpixel(left+15,top+15) == BLACK) {
                delay(1000);

                setfillstyle(1,WHITE);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                left+=40;
                right+=40;

                if(getpixel(left+15,top+15) != BLACK)
                    continue;

                v = 2;
            }
            else
            if(getpixel(left+15,top+15) == WHITE) {
                delay(1000);

                setfillstyle(1,BLACK);
                bar(left, top, right, bottom);
                rectangle(left, top, right, bottom);

                top-=40;
                bottom-=40;

                if(getpixel(left+15,top+15) != WHITE)
                    continue;

                v = 1;
            }
        }
    }

	getch();
	closegraph();
	return 0;
}
