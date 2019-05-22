#include<iostream>
#include<math.h>
#include<string.h>
#define eps 0.000001
using namespace std;
float x[1005];
int  n, N, k;
struct Complex
{
       float r,i;
       Complex(float x = 0, float y = 0)
       {
              r = x;
              i = y;
              if (fabs(r) <= eps)
                 r = 0;
              if (fabs(i) <= eps)
                 i = 0;
       } 
       void printNumber()
       {
            if (r == 0 && i == 0)
               cout << 0;
            if (r != 0)
               cout << r; 
            if (i < 0)
               cout << "-";
            else if (i > 0 && r != 0)
               cout << "+";
            if (i != 0)
               cout <<  fabs(i) << "j";
            cout << " "; 
       }      
};
Complex produceNumber(int n, int N)
{
        float PI = acos(-1);
        Complex ret(cos((2 * PI * n) / N), -1 *  sin((2 * PI * n) / N));
        return ret;
}
Complex mulNumber(Complex c, float i)
{       Complex ret(i * c.r, i * c.i);
        return ret;
}
Complex addComplex(Complex n1, Complex n2)
{
        Complex ret(n1.r + n2.r, n1.i + n2.i);
        return ret;
}
Complex difComplex(Complex n1, Complex n2)
{
        Complex ret(n1.r - n2.r, n1.i - n2.i);
        return ret;
}
Complex mulComplex(Complex n1, Complex n2)
{
        Complex ret((n1.r * n2.r) - (n1.i * n2.i), (n1.r * n2.i) + (n2.r * n1.i));
        return ret;
}
void FFT(Complex *fft, int s, int e)
{
        if (s == e)
           return;
        int mid = (s + e) / 2;
        int n = (e - s + 1);
        Complex *even = new Complex[n / 2];
        Complex *odd = new Complex[n / 2];
        int idx1 = 0, idx2 = 0;
        for (int i = 0; i < n; ++i)
            if (i % 2 == 0)
               even[idx1++] = fft[i];
            else
               odd[idx2++] = fft[i];
        FFT(even, s, mid);
        FFT(odd, mid + 1, e);
        for (int i = 0; i < n / 2; ++i)
        {
            fft[i] = addComplex(even[i], mulComplex(produceNumber(i, n), odd[i]));
            fft[(n / 2) + i] = difComplex(even[i], mulComplex(produceNumber(i, n), odd[i]));
        }
        delete[] even;
        delete[] odd;
}
int main()
{
    int n, x;
    Complex c[1000];
    cout << "Please, enter number of discrete siganls:\n";
    cin >> n;
    cout << "Please, enter the discrete signals:\n";
    for (int i = 0; i < n; ++i)
    {
        cin >> x;
        c[i].r = x;
        c[i].i = 0;
    }
    FFT(c, 0, n - 1);
    cout << "Output:\n";
    for (int i = 0; i < n; ++i)
        c[i].printNumber();
    cout << "\n";
    return 0;
}
