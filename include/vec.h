#ifndef _VEC_H_
#define _VEC_H_

template <typename T>
struct Vec {
    T x, y, z;

    Vec& operator-=(const Vec& rhs) {
       x -= rhs.x; 
       y -= rhs.y; 
       z -= rhs.z; 
       return *this;
    }

    Vec operator-(const Vec& rhs) {
        auto tmp = *this;
        tmp -= rhs;
        return tmp;
    }

    Vec& operator+=(const Vec& rhs) {
       x += rhs.x; 
       y += rhs.y; 
       z += rhs.z; 
       return *this;
    }

    Vec operator+(const Vec& rhs) {
        auto tmp = *this;
        tmp += rhs;
        return tmp;
    }

    T get_size() const {
        return sqrt(sq(x) + sq(y) + sq(z));
    }
};

#endif /* _VEC_H_ */