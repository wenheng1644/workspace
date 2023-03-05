//
// Created by нд╨Ц on 2022/7/9.
//

#include "excise1.h"

int read_colums(int colums[], int col)
{
    if(col > MAXCOL)
        return -1;

    int nums = 0;
    while(scanf("%d", &colums[nums]) == 1 && colums[nums] >= 0)
        nums++;

//    if(nums % 2 != 0)
//        return -1;

    int ch;
    while((ch = getchar()) != EOF && ch != '\n') ;
    return nums;
}

void rerange(char * output, const char* input, const int* colums, int cols)
{
    int outputCol = 0;
    int inputLen = strlen(input);

    for(int i = 0; i < cols; i+=2)
    {
        if(colums[i] > inputLen)
            continue;

        int nchars;

        if(i == cols - 1 && cols % 2 == 1)
        {
            nchars = inputLen - colums[i] + 1;
        }
        else
        {
            nchars = colums[i + 1] > inputLen ? inputLen - colums[i] + 1 : colums[i + 1] - colums[i] + 1;
        }


        if(outputCol >= MAXCOL || outputCol + nchars >= MAXCOL)
            break;

        strncpy(output + outputCol, input + colums[i], nchars);
        outputCol += nchars;
    }

//    if(1 == cols % 2 && colums[cols - 1] < inputLen)
//    {
//        strncpy(output + outputCol, input + colums[cols - 1], (inputLen - 1) - colums[cols - 1] + 1);
//    }

}
