#pragma once

// wrapper around float versions of functions
// in gta they are in CMaths but that makes the code rather noisy

inline float Sin(float x) { return sinf(x); }
inline float Cos(float x) { return cosf(x); }
inline float Abs(float x) { return fabs(x); }
inline float Sqrt(float x) { return sqrtf(x); }
inline float Atan2(float y, float x) { return atan2f(y, x); }
inline float RecipSqrt(float x) { return 1.0f/sqrtf(x); }
inline float Pow(float x, float y) { return powf(x, y); }
