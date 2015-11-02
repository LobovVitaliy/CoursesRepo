int run(int moves[], int movesLen, int res[], int resLen) {
    int i;
    int j;
    enum N {BREAK=-100,REPEAT=999,POP,CONTINUE};

    int mas1[4][4] = {
    {1,REPEAT,8,BREAK},
    {POP,2,-100,5},
    {6,CONTINUE,3,POP},
    {-100,7,-100,4}
    };

    int mas2[4][4] = {
    {1,1,0,-100},
    {3,2,-100,1},
    {2,1,3,0},
    {-100,3,-100,0}
    };

    int k=-1,q=1;
    i=0;

    do {
        k++;
        if (moves[k]==3) {
            switch(i) {
                case 0: res[k] = mas1[i][0];                 i=mas2[i][0];      break;
                case 1: if (k!=0) {
                            if(res[k-1]==0) res[k-2] = 0;
                            res[k-1] = 0; res[k] = 0;        i=mas2[i][0];}     break;

                case 2: res[k] = mas1[i][0];                 i=mas2[i][0];      break;
                case 3: q=0;                                                    break;
            }
        }
        else
        if (moves[k]==11) {
            switch(i) {
                case 0: k--;                                 i=mas2[i][1];      break;
                case 1: res[k] = mas1[i][1];                 i=mas2[i][1];      break;
                case 2: res[k] = 0;                          i=mas2[i][1];      break;
                case 3: res[k] = mas1[i][1];                 i=mas2[i][1];      break;
            }
        }
        else
        if (moves[k]==21) {
            switch(i) {
                case 0: res[k] = mas1[i][2];                 i=mas2[i][2];      break;
                case 1: q=0;                                                    break;
                case 2: res[k] = mas1[i][2];                 i=mas2[i][2];      break;
                case 3: q=0;                                                    break;
            }
        }
        else
        if (moves[k]==201) {
            switch(i) {
                case 0: q=0;                                                    break;
                case 1: res[k] = mas1[i][3];                 i=mas2[i][3];      break;
                case 2: if (k!=0) {
                            if(res[k-1]==0) res[k-2] = 0;
                            res[k-1] = 0; res[k] = 0;        i=mas2[i][3];}     break;
                case 3: res[k] = mas1[i][3];                 i=mas2[i][3];      break;
            }
        }
        else
        if (moves[k]!=3 || moves[k]!=11 || moves[k]!=21 || moves[k]!=201) q=0;
    } while (k<movesLen && q==1);

    int l,s=0;

    for (l=0;l<k;l++) {
        if (res[l]>0){s++;}
    }

    return s;
}


