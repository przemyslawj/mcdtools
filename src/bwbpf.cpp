/*
 *                            COPYRIGHT
 *
 *  Copyright (C) 2014 Exstrom Laboratories LLC
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  A copy of the GNU General Public License is available on the internet at:
 *  http://www.gnu.org/copyleft/gpl.html
 *
 *  or you can write to:
 *
 *  The Free Software Foundation, Inc.
 *  675 Mass Ave
 *  Cambridge, MA 02139, USA
 *
 *  Exstrom Laboratories LLC contact:
 *  stefan(AT)exstrom.com
 *
 *  Exstrom Laboratories LLC
 *  Longmont, CO 80503, USA
 *
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <vector>

#define NZEROS 4
#define NPOLES 4
#define GAIN   2.437914552e+00

static float xv[NZEROS+1], yv[NPOLES+1];

/**
 * Butterworth highpass filter applied inplace
 * n - filter order (multiple of 4)
 * s - sampling frequency
 * f1 - upper half power frequency
 * f2 - lower half power frequency
 */
void butterworh_bandpass_filter(std::vector<double> &v, int n, double s, double f1, double f2) {
  double a = tan(M_PI*f1/s);
  double a2 = a*a;
  double r;
  double *A = (double *)malloc(n*sizeof(double));
  double *d1 = (double *)malloc(n*sizeof(double));
  double *d2 = (double *)malloc(n*sizeof(double));
  double *w0 = (double *)calloc(n, sizeof(double));
  double *w1 = (double *)calloc(n, sizeof(double));
  double *w2 = (double *)calloc(n, sizeof(double));

  for(int i=0; i<n; ++i) {
    r = sin(M_PI*(2.0*i+1.0)/(4.0*n));
    s = a2 + 2.0*a*r + 1.0;
    A[i] = 1.0/s;
    d1[i] = 2.0*(1-a2)/s;
    d2[i] = -(a2 - 2.0*a*r + 1.0)/s;
  }

  for (int j=0; j<v.size(); ++j) {
    double x = v[j];
    for(int i=0; i<n; ++i) {
      w0[i] = d1[i]*w1[i] + d2[i]*w2[i] + x;
      x = A[i]*(w0[i] - 2.0*w1[i] + w2[i]);
      w2[i] = w1[i];
      w1[i] = w0[i];
    }
    v[j] = x;
  }
    /*
  double a = cos(M_PI*((double) f1+f2)/s)/cos(M_PI*((double) f1-f2)/s);
  double a2 = a*a;
  double b = tan(M_PI*((double) f1-f2)/s);
  double b2 = b*b;
  double r;

  n = n/4;
  double *A = (double *)malloc(n*sizeof(double));
  double *d1 = (double *)malloc(n*sizeof(double));
  double *d2 = (double *)malloc(n*sizeof(double));
  double *d3 = (double *)malloc(n*sizeof(double));
  double *d4 = (double *)malloc(n*sizeof(double));
  double *w0 = (double *)calloc(n, sizeof(double));
  double *w1 = (double *)calloc(n, sizeof(double));
  double *w2 = (double *)calloc(n, sizeof(double));
  double *w3 = (double *)calloc(n, sizeof(double));
  double *w4 = (double *)calloc(n, sizeof(double));

  printf("\n\nHello! %.6f, %.6f", a, b);
  for(int i=0; i<n; ++i) {
    r = sin(M_PI*(2.0*i+1.0)/(4.0*n));
    s = b2 + 2.0*b*r + 1.0;
    A[i] = b2/s;
    d1[i] = 4.0*a*(1.0+b*r)/s;
    d2[i] = 2.0*(b2-2.0*a2-1.0)/s;
    d3[i] = 4.0*a*(1.0-b*r)/s;
    d4[i] = -(b2 - 2.0*b*r + 1.0)/s;
    printf("\nParams %.6f, %.6f, %.6f, %.6f, %.6f\n", s, d1[0], d2[0], d3[0], d4[0]);
  }

  for(int j=0; j < v.size(); ++j) {
    double x = v[j];
    for(int i=0; i<n; ++i) {
      w0[i] = d1[i]*w1[i] + d2[i]*w2[i]+ d3[i]*w3[i]+ d4[i]*w4[i] + x;
      x = A[i]*(w0[i] - 2.0*w2[i] + w4[i]);
      w4[i] = w3[i];
      w3[i] = w2[i];
      w2[i] = w1[i];
      w1[i] = w0[i];
    }
    v[j] = x;
  }
  */
}
/* Digital filter designed by mkfilter/mkshape/gencode   A.J. Fisher
   Command line: /www/usr/fisher/helpers/mkfilter -Bu -Bp -o 2 -a 1.2000000000e-02 3.2000000000e-01 -l */

/*

	for (long j = 0; j < v.size(); ++j) {
		xv[0] = xv[1]; xv[1] = xv[2]; xv[2] = xv[3]; xv[3] = xv[4];
        xv[4] = v[j] / GAIN;
        yv[0] = yv[1]; yv[1] = yv[2]; yv[2] = yv[3]; yv[3] = yv[4];
        yv[4] =   (xv[0] + xv[4]) - 2 * xv[2]
                     + ( -0.2043329507 * yv[0]) + ( -0.0182644811 * yv[1])
                     + ( -0.1816866080 * yv[2]) + (  1.3945270613 * yv[3]);
        v[j] = yv[4];

	}
}
*/
