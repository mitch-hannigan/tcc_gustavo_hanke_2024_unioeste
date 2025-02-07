#include <math.h>
#include <stdio.h>
constexpr const char *pos_to_char(int pos)
{
    switch (pos)
    {
    case 0:
        return "px";
    case 3:
        return "ox";
    case 1:
        return "py";
    case 4:
        return "oy";
    case 2:
        return "pz";
    case 5:
        return "oz";
    default:
        return "w";
    }
}
int main(int argc, char *argv[])
{
    if (argc == 3)
    {
        FILE *f1 = fopen64(argv[1], "r"), *f2 = fopen64(argv[2], "r");
        if (f1 && f2)
        {
            float tempo_dif = 0.0f, tempp_dif = 0.0f;
            float sums[7] = {0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f};
            float max_dif[7] = {-1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f};
            float v1[7], v2[7];
            size_t total = 0;
            size_t maxo_dif_iter = -1, maxp_dif_iter = -1;
            while (fread(&v1, sizeof(v1), 1, f1) && fread(&v2, sizeof(v2), 1, f2))
            {
                total++;
                for (int i = 0; i < 3; i++)
                {
                    tempp_dif = fabs(v2[i] - v1[i]);
                    sums[i] += tempp_dif;
                    if (tempp_dif > max_dif[i])
                    {
                        max_dif[i] = tempp_dif;
                        maxp_dif_iter = total/10000;
                    }
                }
                for (int i = 3; i < 7; i++)
                {
                    tempo_dif = fabs(v2[i] - v1[i]);
                    sums[i] += tempo_dif;
                    if (tempo_dif > max_dif[i])
                    {
                        max_dif[i] = tempo_dif;
                        maxo_dif_iter = total/10000;
                    }
                }
            }
            for (int i = 0; i < 7; i++)
            {
                sums[i] /= total;
                printf("Max %s dif %f\nMean %s dif %f\n", pos_to_char(i), max_dif[i], pos_to_char(i), sums[i]);
            }
            printf("Max o dif iter %zu\nMax p dif iter %zu\n", maxo_dif_iter, maxp_dif_iter);
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