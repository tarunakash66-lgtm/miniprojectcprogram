#include <stdio.h>
#include <stdlib.h>

#define ROWS 20
#define COLS 40
#define MAX_OBJECTS 50

char canvas[ROWS][COLS];

typedef struct {
    int type;
    int r1, c1, r2, c2;
    int height, width, radius;
    int active;
} Object;

Object objects[MAX_OBJECTS];
int objectCount = 0;

void initializeCanvas() {
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            canvas[i][j] = '_';
        }
    }
}

void displayCanvas() {
    printf("\n");
    for(int i = 0; i < ROWS; i++) {
        for(int j = 0; j < COLS; j++) {
            printf("%c ", canvas[i][j]);
        }
        printf("\n");
    }
}

void putPixel(int r, int c) {
    if(r >= 0 && r < ROWS && c >= 0 && c < COLS) {
        canvas[r][c] = '*';
    }
}

void drawRectangle(int row, int col, int height, int width) {
    for(int i = row; i < row + height; i++) {
        for(int j = col; j < col + width; j++) {
            putPixel(i, j);
        }
    }
}

void drawLine(int r1, int c1, int r2, int c2) {
    int dr = abs(r2 - r1);
    int dc = abs(c2 - c1);
    int sr = (r1 < r2) ? 1 : -1;
    int sc = (c1 < c2) ? 1 : -1;
    int err = dr - dc;

    while(1) {
        putPixel(r1, c1);

        if(r1 == r2 && c1 == c2)
            break;

        int e2 = 2 * err;

        if(e2 > -dc) {
            err -= dc;
            r1 += sr;
        }

        if(e2 < dr) {
            err += dr;
            c1 += sc;
        }
    }
}

void drawTriangle(int row, int col, int height) {
    for(int i = 0; i < height; i++) {
        for(int j = -i; j <= i; j++) {
            putPixel(row + i, col + j);
        }
    }
}

void drawCircle(int centerRow, int centerCol, int radius) {
    for(int r = 0; r < ROWS; r++) {
        for(int c = 0; c < COLS; c++) {
            int dx = r - centerRow;
            int dy = c - centerCol;

            if(dx * dx + dy * dy <= radius * radius) {
                putPixel(r, c);
            }
        }
    }
}

void redrawCanvas() {
    initializeCanvas();

    for(int i = 0; i < objectCount; i++) {
        if(objects[i].active == 1) {
            switch(objects[i].type) {
                case 1:
                    drawRectangle(objects[i].r1, objects[i].c1, objects[i].height, objects[i].width);
                    break;

                case 2:
                    drawLine(objects[i].r1, objects[i].c1, objects[i].r2, objects[i].c2);
                    break;

                case 3:
                    drawTriangle(objects[i].r1, objects[i].c1, objects[i].height);
                    break;

                case 4:
                    drawCircle(objects[i].r1, objects[i].c1, objects[i].radius);
                    break;
            }
        }
    }
}

void listObjects() {
    printf("\nObjects List:\n");

    if(objectCount == 0) {
        printf("No objects added yet.\n");
        return;
    }

    for(int i = 0; i < objectCount; i++) {
        if(objects[i].active == 1) {
            printf("%d. ", i + 1);

            switch(objects[i].type) {
                case 1:
                    printf("Rectangle\n");
                    break;
                case 2:
                    printf("Line\n");
                    break;
                case 3:
                    printf("Triangle\n");
                    break;
                case 4:
                    printf("Circle\n");
                    break;
            }
        }
    }
}

void addObject() {
    if(objectCount >= MAX_OBJECTS) {
        printf("Object limit reached!\n");
        return;
    }

    Object obj;
    obj.active = 1;

    printf("\nAdd Object\n");
    printf("1. Rectangle\n");
    printf("2. Line\n");
    printf("3. Triangle\n");
    printf("4. Circle\n");
    printf("Enter object type: ");
    scanf("%d", &obj.type);

    switch(obj.type) {
        case 1:
            printf("Row: ");
            scanf("%d", &obj.r1);
            printf("Column: ");
            scanf("%d", &obj.c1);
            printf("Height: ");
            scanf("%d", &obj.height);
            printf("Width: ");
            scanf("%d", &obj.width);
            break;

        case 2:
            printf("Start Row: ");
            scanf("%d", &obj.r1);
            printf("Start Column: ");
            scanf("%d", &obj.c1);
            printf("End Row: ");
            scanf("%d", &obj.r2);
            printf("End Column: ");
            scanf("%d", &obj.c2);
            break;

        case 3:
            printf("Row: ");
            scanf("%d", &obj.r1);
            printf("Column: ");
            scanf("%d", &obj.c1);
            printf("Height: ");
            scanf("%d", &obj.height);
            break;

        case 4:
            printf("Center Row: ");
            scanf("%d", &obj.r1);
            printf("Center Column: ");
            scanf("%d", &obj.c1);
            printf("Radius: ");
            scanf("%d", &obj.radius);
            break;

        default:
            printf("Invalid object type!\n");
            return;
    }

    objects[objectCount] = obj;
    objectCount++;

    redrawCanvas();
    printf("Object added successfully!\n");
}

void deleteObject() {
    int index;

    listObjects();

    printf("Enter object number to delete: ");
    scanf("%d", &index);

    index--;

    if(index >= 0 && index < objectCount && objects[index].active == 1) {
        objects[index].active = 0;
        redrawCanvas();
        printf("Object deleted successfully!\n");
    } else {
        printf("Invalid object number!\n");
    }
}

void modifyObject() {
    int index;

    listObjects();

    printf("Enter object number to modify: ");
    scanf("%d", &index);

    index--;

    if(index >= 0 && index < objectCount && objects[index].active == 1) {
        printf("Enter new details for this object:\n");

        switch(objects[index].type) {
            case 1:
                printf("New Row: ");
                scanf("%d", &objects[index].r1);
                printf("New Column: ");
                scanf("%d", &objects[index].c1);
                printf("New Height: ");
                scanf("%d", &objects[index].height);
                printf("New Width: ");
                scanf("%d", &objects[index].width);
                break;

            case 2:
                printf("New Start Row: ");
                scanf("%d", &objects[index].r1);
                printf("New Start Column: ");
                scanf("%d", &objects[index].c1);
                printf("New End Row: ");
                scanf("%d", &objects[index].r2);
                printf("New End Column: ");
                scanf("%d", &objects[index].c2);
                break;

            case 3:
                printf("New Row: ");
                scanf("%d", &objects[index].r1);
                printf("New Column: ");
                scanf("%d", &objects[index].c1);
                printf("New Height: ");
                scanf("%d", &objects[index].height);
                break;

            case 4:
                printf("New Center Row: ");
                scanf("%d", &objects[index].r1);
                printf("New Center Column: ");
                scanf("%d", &objects[index].c1);
                printf("New Radius: ");
                scanf("%d", &objects[index].radius);
                break;
        }

        redrawCanvas();
        printf("Object modified successfully!\n");
    } else {
        printf("Invalid object number!\n");
    }
}

int main() {
    int choice;

    initializeCanvas();

    while(1) {
        printf("\n===== 2D Graphics Editor in C =====\n");
        printf("1. Display Canvas\n");
        printf("2. Add Object\n");
        printf("3. Delete Object\n");
        printf("4. Modify Object\n");
        printf("5. List Objects\n");
        printf("6. Clear Canvas\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch(choice) {
            case 1:
                displayCanvas();
                break;

            case 2:
                addObject();
                break;

            case 3:
                deleteObject();
                break;

            case 4:
                modifyObject();
                break;

            case 5:
                listObjects();
                break;

            case 6:
                objectCount = 0;
                initializeCanvas();
                printf("Canvas cleared successfully!\n");
                break;

            case 7:
                printf("Exiting program...\n");
                return 0;

            default:
                printf("Invalid choice! Try again.\n");
        }
    }

    return 0;
}
