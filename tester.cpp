#include <math.h>
#include <stdio.h>
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        FILE *f1 = fopen64(argv[1], "r"), *f2 = fopen64(argv[2], "r");
        if (f1 && f2)
        {
            float max_dif = 0.0f, temp_dif = 0.0f;
            float v1, v2;
            while (fread(&v1, sizeof(v1), 1, f1) && fread(&v2, sizeof(v2), 1, f2))
            {
                temp_dif = fabs(v2 - v1);
                if (temp_dif > max_dif)
                    max_dif = temp_dif;
            }
            printf("max dif: %f\n", max_dif);
        }
        if (f1)
            fclose(f1);
        else
            printf("can't open file %s\n", argv[1]);
        if (f2)
            fclose(f2);
        else
            printf("can't open file %s\n", argv[2]);
    }
    else
        printf("Invalid arguments\n");
}