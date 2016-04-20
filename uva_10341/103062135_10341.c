#include <stdio.h>
#include <math.h>

double bs(int start, int end, double p, double q, double r, double s, double t, double u){
    int mid = (start+end)/2;
    double x = (double)mid/1e8;
    if(start == end-1){
        return start;
    } else if ( p*exp(-x)+q*sin(x)+r*cos(x)+s*tan(x)+t*x*x+u >= 0){
        return bs(mid, end, p, q, r, s, t, u);
    } else {
        return bs(start, mid, p, q, r, s, t, u);
    }
}

int main(){
    double p, q, r, s, t, u;
    while(scanf("%lf%lf%lf%lf%lf%lf", &p, &q, &r, &s, &t, &u) == 6){
        double ans = bs(-2, 1e8+2, p, q, r, s, t, u)/1e8;
        if(ans > 1|| ans < 0)printf("No solution\n");
        else printf("%.4lf\n", ans);
    }
    return 0;
}
