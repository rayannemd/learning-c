#include <stdio.h>

int main()
{
    int d1, m1, a1, d2, m2, a2, rd, rm, ra, df, md, ad;

    printf("Insira duas datas de nascimento no formato dd/mm/aaaa: ");
    scanf("%d/%d/%d %d/%d/%d", &d1, &m1, &a1, &d2, &m2, &a2);

    if(d1 >= d2){
        rd = d1 - d2;
    } else {
        rd = d2 - d1;
    }

    if(m1 >= m2){
        rm = m1 - m2;
    } else {
        rm = m2 - m1;
    }

    if(a1 >= a2){
        ra = a1 - a2;
    } else {
        ra = a2 - a1;
    }

    md = rm * 30;
    ad = ra * 360;

    df = rd + md + ad;

    printf("Os dias entre as datas sao: %d", df);

    return 0;
}
