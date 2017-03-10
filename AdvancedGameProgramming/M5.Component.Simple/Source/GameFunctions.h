
const float fPRV = 10.0f;

inline float PW2RW(float x){return x*fPRV;}

inline float RW2PW(float x){return x/fPRV;}

inline float RW2PW(int x){return (float)x/fPRV;}

inline float RW2PWAngle(float x){return((float)x*(2.0f*3.14159f)/360.0f);} //degrees to radians

inline float PW2RWAngle(float x){return((float)x*360.0f/(2.0f*3.14159f));} //radians to degrees