#include "stdlib.h"
#include "stdio.h"
float dim_p[7][7] = {
    3, 3, 2, 2, 1, 0, 0,
    3, 3, 2, 1, 1, 0, -1,
    2, 2, 2, 1, 0, -1, -1,
    2, 2, 1, 0, -1, -2, -2,
    1, 1, 0, -1, -1, -2, -2,
    1, 0, -1, -2, -2, -2, -3,
    0, 0, -2, -2, -2, -3, -3};
float dim_i[7][7] = {
    -3, -3, -2, -2, -1, 0, 0,
    -3, -3, -2, -1, -1, 0, 0,
    -3, -2, -1, -1, 0, 1, 1,
    -2, -2, -1, 0, 1, 2, 2,
    -2, -1, 0, 1, 1, 2, 3,
    0, 0, 1, 1, 2, 3, 3,
    0, 0, 1, 2, 2, 3, 3};
float dim_d[7][7] = {
    1, -1, -3, -3, -3, -2, 1,
    1, -1, -3, -2, -2, -1, 0,
    0, -1, -2, -2, -1, -1, 0,
    0, -1, -1, -1, -1, -1, 0,
    0, 0, 0, 0, 0, 0, 0,
    3, -1, 1, 1, 1, 1, 3,
    3, 2, 2, 2, 1, 1, 3};

float dim_par_p = 10;
float dim_par_i = 0.05;
float dim_par_d = 10;

float e_bound = 60 / 3;
float ec_bound = 10 / 3;

void dim_PID(float e, float ec, float *kp, float *ki, float *kd)
{
    float e1 = ((e / e_bound)) > 2.999999 ? 2.999999 : ((e / e_bound)) < -2.999999 ? -2.999999
                                                                                   : ((e / e_bound));
    float ec1 = ((ec / ec_bound)) > 2.999999 ? 2.999999 : ((ec / ec_bound)) < -2.999999 ? -2.999999
                                                                                        : ((ec / ec_bound));
    e1 += 3;
    ec1 += 3;
    float a = e1 - (int)e1;
    float b = ec1 - (int)ec1;
    int x = (int)e1;
    int y = (int)ec1;

    float t1 = (a * b * dim_p[x + 1][y + 1] +
                (1 - a) * b * dim_p[x][y + 1] +
                a * (1 - b) * dim_p[x + 1][y] +
                (1 - a) * (1 - b) * dim_p[x][y]);
    *kp += dim_par_p * t1;
    float t2 = (a * b * dim_i[x + 1][y + 1] +
                (1 - a) * b * dim_i[x][y + 1] +
                a * (1 - b) * dim_i[x + 1][y] +
                (1 - a) * (1 - b) * dim_i[x][y]);
    *ki += dim_par_i * t2;

    float t3 = (a * b * dim_d[x + 1][y + 1] +
                (1 - a) * b * dim_d[x][y + 1] +
                a * (1 - b) * dim_d[x + 1][y] +
                (1 - a) * (1 - b) * dim_d[x][y]);

    *kd += dim_par_d * t3;
    printf("dp=%.5f di=%.5f dd=%.5f\n", t1, t2, t3);
}

void Json_get_value(const char *str, const char *key, char *out_value)
{
    int J_len = strlen(str);
    int K_len = strlen(key);
    if (J_len == 0 || K_len == 0)
        return;
    for (int i = 0; i < J_len; i++)
    {
        if (str[i] == key[0])
        {
            int j;
            for (j = 0; j < K_len; j++)
            {
                if (str[i + j] != key[j])
                    break;
            }
            if (j == K_len)
            {
                j += i;
                int flag = 0;
                int k = 0;
                while (str[j] != '\0')
                {
                    if (str[j++] == '\"')
                        flag++;
                    if (flag == 2)
                    {
                        out_value[k] = str[j];
                        k++;
                    }

                    if (flag == 3)
                    {
                        out_value[k - 1] = '\0';
                        break;
                    }
                }
            }
        }
    }
}

void Time_Prase(const char *str)
{
    char tem[20];
    for (int i = 0; i < 20; i++)
    {
        if (str[i] == '-' || str[i] == ':' || str[i] == ' ')
        {
            tem[i] = 0;
        }
        else
        {
            tem[i] = str[i];
        }
    }

    printf("%s %s %s %s %s %s", tem, tem + 5, tem + 8, tem + 11, tem + 14, tem + 17);
}

int main()
{
// float p, i, d;
// float e, ec;
// printf("p=%.5f i=%.5f d=%.5f\n", p, i, d);
// while (1)
// {
//     scanf("%f %f", &e, &ec);
//     dim_PID(e, ec, &p, &i, &d);
//     printf("p=%.5f i=%.5f d=%.5f\n", p, i, d);
// }
#pragma region ss

#pragma endregion
    FILE *f = fopen("test.json", "r");
    char *tt[1000];
    fseek(f, 0, SEEK_END);
    int len = ftell(f);
    rewind(f);
    printf("%d\n", len);
    fread(tt, sizeof(char), len, f);
    tt[len + 1] = '\0';
    char out[100] = {"0"};
    printf("1");
    Json_get_value(tt, "timestamp", out);
    printf("\n%s\n", out);
    Json_get_value(tt, "week_1", out);
    printf("\n%s\n", out);

    printf("%d", 10 ^ 6);
    // Time_Prase(out);
}