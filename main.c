#include <stdio.h>

#define ROWS 20
#define COLS 40

char canvas[ROWS][COLS];

void initializeCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas()
{
    int i, j;

    for(i = 0; i < ROWS; i++)
    {
        for(j = 0; j < COLS; j++)
        {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

void drawRectangle(int row, int col, int height, int width)
{
    int i, j;

    for(i = row; i < row + height && i < ROWS; i++)
    {
        for(j = col; j < col + width && j < COLS; j++)
        {
            canvas[i][j] = '*';
        }
    }
}

void drawLine(int row1, int col1, int row2, int col2)
{
    int i;

    if(row1 == row2)
    {
        for(i = col1; i <= col2 && i < COLS; i++)
        {
            canvas[row1][i] = '*';
        }
    }
    else if(col1 == col2)
    {
        for(i = row1; i <= row2 && i < ROWS; i++)
        {
            canvas[i][col1] = '*';
        }
    }
}

void drawTriangle(int row, int col, int height)
{
    int i, j;

    for(i = 0; i < height; i++)
    {
        for(j = 0; j <= i; j++)
        {
            if(row + i < ROWS && col + j < COLS)
            {
                canvas[row + i][col + j] = '*';
            }
        }
    }
}

void drawCircle(int centerRow, int centerCol, int radius)
{
    int r, c;

    for(r = 0; r < ROWS; r++)
    {
        for(c = 0; c < COLS; c++)
        {
            int dx = r - centerRow;
            int dy = c - centerCol;

            if(dx * dx + dy * dy <= radius * radius)
            {
                canvas[r][c] = '*';
            }
        }
    }
}

int main()
{
    int choice;

    initializeCanvas();

    while(1)
    {
        printf("\n");
        printf("===== 2D Graphics Editor =====\n");
        printf("1. Display Canvas\n");
        printf("2. Draw Rectangle\n");
        printf("3. Draw Line\n");
        printf("4. Draw Triangle\n");
        printf("5. Draw Circle\n");
        printf("6. Clear Canvas\n");
        printf("7. Exit\n");

        printf("Enter Choice: ");
        scanf("%d", &choice);

        if(choice == 1)
        {
            displayCanvas();
        }
        else if(choice == 2)
        {
            int r, c, h, w;

            printf("Row: ");
            scanf("%d", &r);

            printf("Column: ");
            scanf("%d", &c);

            printf("Height: ");
            scanf("%d", &h);

            printf("Width: ");
            scanf("%d", &w);

            drawRectangle(r, c, h, w);
        }
        else if(choice == 3)
        {
            int r1, c1, r2, c2;

            printf("Start Row: ");
            scanf("%d", &r1);

            printf("Start Column: ");
            scanf("%d", &c1);

            printf("End Row: ");
            scanf("%d", &r2);

            printf("End Column: ");
            scanf("%d", &c2);

            drawLine(r1, c1, r2, c2);
        }
        else if(choice == 4)
        {
            int r, c, h;

            printf("Row: ");
            scanf("%d", &r);

            printf("Column: ");
            scanf("%d", &c);

            printf("Height: ");
            scanf("%d", &h);

            drawTriangle(r, c, h);
        }
        else if(choice == 5)
        {
            int r, c, radius;

            printf("Center Row: ");
            scanf("%d", &r);

            printf("Center Column: ");
            scanf("%d", &c);

            printf("Radius: ");
            scanf("%d", &radius);

            drawCircle(r, c, radius);
        }
        else if(choice == 6)
        {
            initializeCanvas();
            printf("Canvas Cleared!\n");
        }
        else if(choice == 7)
        {
            break;
        }
        else
        {
            printf("Invalid Choice!\n");
        }
    }

    return 0;
}