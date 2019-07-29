/*
 * WGS84_TMLib.h
 *
 *  Created on: 2013. 5. 15.
 *      Author: jiwon
 */

#ifndef WGS84_TMLIB_H_
#define WGS84_TMLIB_H_

//Bessel 1841 ellipsoid datum
// e_squre(e^2) = 2*f - f*f;
const double a = 6377397.155;
const double e_squre = 0.006674372227347433;
 const double e_prime_squre= 0.006719218794659982;

// TM 계산을 위한 계수들, A-F;
 const double nTMScaleFacter = 1.0;
 const double nKatecScaleFacter = 0.9999;

 const double A = 1.005037306048555;
 const double B = 0.005047849240300;
 const double C = 0.000010563786831;
 const double D = 0.000000020633322;
 const double E = 0.000000000038865;
 const double F = 0.000000000000075;

#define M_PI		3.14159265358979323846	// pi
#endif /* WGS84_TMLIB_H_ */
