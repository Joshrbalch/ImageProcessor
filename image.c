#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"

//gcc -Wall main.c image.c -lm
ImagePPM *cpyData(ImagePPM *pImagePPM);
ImagePPM *flipPPM(ImagePPM *pImagePPM);

ImagePPM *readPPM(char *filename) {
    FILE *fp = fopen(filename, "r");

    ImagePPM *data = malloc(sizeof(ImagePPM));

    fscanf(fp, "%c", &data->magic[0]);
    fscanf(fp, "%c", &data->magic[1]);
    fscanf(fp, "%d", &data->width);
    fscanf(fp, "%d", &data->height);
    fscanf(fp, "%d", &data->max_value);

    data->pixels = malloc(sizeof(Pixel *) * data->height);

    for(int i = 0; i < data->height; i++) {
        data->pixels[i] = malloc(sizeof(Pixel) * data->width);
        for(int j = 0; j < data->width; j++) {
            fscanf(fp, "%d\n", &data->pixels[i][j].red);
            fscanf(fp, "%d\n", &data->pixels[i][j].green);
            fscanf(fp, "%d\n", &data->pixels[i][j].blue);
        }
    }

    fclose(fp);

	return data;
}

int writePPM(ImagePPM *pImagePPM, char *filename) {
    FILE *fp = fopen(filename, "w");

    if(!fp) {
        return 0;
    }

    else {
        fprintf(fp, "%s\n", pImagePPM->magic);
        fprintf(fp, "%d %d\n", pImagePPM->width, pImagePPM->height);
        fprintf(fp, "%d\n", pImagePPM->max_value);

        for(int i = 0; i < pImagePPM->height; i++) {
            for(int j = 0; j < pImagePPM->width; j++) {
                if((pImagePPM->pixels[i][j].red / 100) >= 1) {
                    fprintf(fp, " %d", pImagePPM->pixels[i][j].red);
                }

                else if((pImagePPM->pixels[i][j].red / 10) >= 1) {
                    fprintf(fp, "  %d", pImagePPM->pixels[i][j].red);
                }

                else {
                    fprintf(fp, "   %d", pImagePPM->pixels[i][j].red);
                }

                if((pImagePPM->pixels[i][j].green / 100) >= 1) {
                    fprintf(fp, " %d", pImagePPM->pixels[i][j].green);
                }

                else if(((pImagePPM->pixels[i][j].green) / 10) >= 1) {
                    fprintf(fp, "  %d", pImagePPM->pixels[i][j].green);
                }

                else {
                    fprintf(fp, "   %d", pImagePPM->pixels[i][j].green);
                }

                if((pImagePPM->pixels[i][j].blue / 100) >= 1) {
                    fprintf(fp, " %d", pImagePPM->pixels[i][j].blue);
                }

                else if(((pImagePPM->pixels[i][j].blue) / 10) >= 1) {
                    fprintf(fp, "  %d", pImagePPM->pixels[i][j].blue);
                }

                else {
                    fprintf(fp, "   %d", pImagePPM->pixels[i][j].blue);

                }
            }
            fprintf(fp, "\n");
        }
    }

    fclose(fp);

	return 1;
}

ImagePPM *rotatePPM(ImagePPM *pImagePPM) {
    ImagePPM *data2;
    ImagePPM *data3;

    data2 = cpyData(pImagePPM);

    data2->height = pImagePPM->width;
    data2->width = pImagePPM->height;

    data3 = cpyData(data2);
    data2->pixels = malloc(sizeof(Pixel *) * pImagePPM->width);

    int cpyH = (data2->height) - 1;

    for(int i = 0; i < pImagePPM->width; i++) {
        data2->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->height);
        for(int j = 0; j < pImagePPM->height; j++) {
            data2->pixels[i][j].red = pImagePPM->pixels[j][i].red;
            data2->pixels[i][j].green = pImagePPM->pixels[j][i].green;
            data2->pixels[i][j].blue = pImagePPM->pixels[j][i].blue;
            cpyH--;
        }
        cpyH = data2->height - 1;
    }

    data3 = flipPPM(data2);

	return data3;
}

ImagePPM *flipPPM(ImagePPM *pImagePPM) {
    ImagePPM *data3;

    data3 = cpyData(pImagePPM);

    int cpyW = (pImagePPM->width) - 1;

    data3->pixels = malloc(sizeof(Pixel *) * pImagePPM->height);

    for(int i = 0; i < pImagePPM->height; i++) {
        data3->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->width);
        for(int j = 0; j < pImagePPM->width; j++) {
            data3->pixels[i][cpyW].red = pImagePPM->pixels[i][j].red;
            data3->pixels[i][cpyW].green = pImagePPM->pixels[i][j].green;
            data3->pixels[i][cpyW].blue = pImagePPM->pixels[i][j].blue;
            cpyW--;
        }
        cpyW = (pImagePPM->width) - 1;
    }

    return data3;
}

ImagePPM *enlargePPM(ImagePPM *pImagePPM) {
    ImagePPM *data2;

    int i1 = 0;
    int j1 = 0;

    data2 = cpyData(pImagePPM);

    data2->width = pImagePPM->width * 2;
    data2->height = pImagePPM->height * 2;

    data2->pixels = malloc(sizeof(Pixel *) * data2->height);

    for(int i = 0; i < (data2->height) - 1; i++) {
        data2->pixels[i1] = malloc(sizeof(Pixel) * data2->width);
        j1 = 0;
        for(int j = 0; j < pImagePPM->width; j++) {
            data2->pixels[i1][j1].red = pImagePPM->pixels[i][j].red;
            data2->pixels[i1][j1].green = pImagePPM->pixels[i][j].green;
            data2->pixels[i1][j1].blue = pImagePPM->pixels[i][j].blue;
            j1++;
            data2->pixels[i1][j1].red = pImagePPM->pixels[i][j].red;
            data2->pixels[i1][j1].green = pImagePPM->pixels[i][j].green;
            data2->pixels[i1][j1].blue = pImagePPM->pixels[i][j].blue;
            j1++;
        }

        i1++;

        data2->pixels[i1] = malloc(sizeof(Pixel) * data2->width);

        for(int j = 0; j < data2->width; j++) {
            data2->pixels[i1][j].red = data2->pixels[i1 - 1][j].red;
            data2->pixels[i1][j].green = data2->pixels[i1 - 1][j].green;
            data2->pixels[i1][j].blue = data2->pixels[i1 - 1][j].blue;
        }

        if(i1 + 1 == data2->height) {
            break;
        }

        i1++;
    }

    return data2;
}

ImagePPM *shrinkPPM(ImagePPM *pImagePPM) {
    ImagePPM *data2;
    double avg;
    int j1 = 0;
    int i1 = 0;

    data2 = cpyData(pImagePPM);

    data2->height = pImagePPM->height / 2;
    data2->width = pImagePPM->width / 2;

    data2->pixels = malloc(sizeof(Pixel *) * data2->height);

    for(int i = 0; i < data2->height; i++) {
        data2->pixels[i] = malloc(sizeof(Pixel *) * data2->height);
        for(int j = 0; j < data2->width; j++) {
            avg = (pImagePPM->pixels[i1][j1].red + pImagePPM->pixels[i1][j1 + 1].red + pImagePPM->pixels[i1 + 1][j1 + 1].red + pImagePPM->pixels[i1 + 1][j1].red) / 4.0;
            data2->pixels[i][j].red = round(avg);
            avg = (pImagePPM->pixels[i1][j1].green + pImagePPM->pixels[i1][j1 + 1].green + pImagePPM->pixels[i1 + 1][j1 + 1].green + pImagePPM->pixels[i1 + 1][j1].green) / 4.0;
            data2->pixels[i][j].green = round(avg);
            avg = (pImagePPM->pixels[i1][j1].blue + pImagePPM->pixels[i1][j1 + 1].blue + pImagePPM->pixels[i1 + 1][j1 + 1].blue + pImagePPM->pixels[i1 + 1][j1].blue) / 4.0;
            data2->pixels[i][j].blue = round(avg);
            j1 = j1 + 2;
        }

        j1 = 0;
        i1 = i1 + 2;
    }

    return data2;
}

ImagePPM *invertPPM(ImagePPM *pImagePPM) {
    ImagePPM *data2;

    data2 = cpyData(pImagePPM);

    data2->pixels = malloc(sizeof(Pixel *) * pImagePPM->height);

    for(int i = 0; i < pImagePPM->height; i++) {
        data2->pixels[i] = malloc(sizeof(Pixel) * pImagePPM->width);
        for(int j = 0; j < pImagePPM->width; j++) {
            data2->pixels[i][j].red = pImagePPM->max_value - (pImagePPM->pixels[i][j].red);
            data2->pixels[i][j].green = pImagePPM->max_value - (pImagePPM->pixels[i][j].green);
            data2->pixels[i][j].blue = pImagePPM->max_value - (pImagePPM->pixels[i][j].blue);
        }
    }

    return data2;
}

ImagePPM *cropPPM(ImagePPM *pImagePPM, int r1, int c1, int r2, int c2) {
    //FIXME
    int wid = (r2 - r1) + 1;
    int hte = (c2 - c1) + 1;
    int i1 = 0;
    int j1 = 0;
 
    ImagePPM *data2;

    data2 = cpyData(pImagePPM);

    data2->height = wid;
    data2->width = hte;

    data2->pixels = malloc(sizeof(Pixel *) * data2->height);

    for(int i = r1; i <= r2; i++) {
        data2->pixels[i1] = malloc(sizeof(Pixel) * data2->width);
        for(int j = c1; j <= c2; j++) {
            data2->pixels[i1][j1].red = pImagePPM->pixels[i][j].red;
            data2->pixels[i1][j1].green = pImagePPM->pixels[i][j].green;
            data2->pixels[i1][j1].blue = pImagePPM->pixels[i][j].blue;
            j1++;
        }

        j1 = 0;

        if(i1 == data2->height - 1) {
            break;
        }

        i1++;
    }

    return data2;
}

void freeSpacePPM(ImagePPM *pImagePPM) {
    for(int i = 0; i < pImagePPM->height; i++) {
        free(pImagePPM->pixels[i]);
    }
    free(pImagePPM->pixels);
    free(pImagePPM);
}

ImagePPM *cpyData(ImagePPM *pImagePPM) {
    ImagePPM *data2 = malloc(sizeof(ImagePPM));

    char magic[2];

    magic[0] = pImagePPM->magic[0];
    magic[1] = pImagePPM->magic[1];
    magic[2] = '\0';

    strcpy(data2->magic, magic);

    data2->width = pImagePPM->width;
    data2->height = pImagePPM->height;
    data2->max_value = pImagePPM->max_value;

    return data2;
}
