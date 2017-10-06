#ifndef JALIB_H
#define JALIB_H
namespace jalib {

template<typename T>
inline T max(T a, T b){
 return a*(a>b)+b*(a<=b);
}
template<typename T>
inline T min(T a, T b){
 return a*(a<b)+b*(a>=b);

}
}
#endif // JALIB_H
