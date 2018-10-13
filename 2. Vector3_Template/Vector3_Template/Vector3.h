#ifndef _VECTOR_3_
#define _VECTOR_3_

template <class T>
class Vector3 {
public:
	T x;
	T y;
	T z;

	Vector3(T x, T y, T z) : x(x), y(y), z(z) {};
	Vector3(const Vector3<T> &other) : x(other.x), y(other.y), z(other.z) {};

	Vector3<T> operator+ (const Vector3<T> &other) const	{ return Vector3(this->x + other.x, this->y + other.y, this->z + other.z); }
	Vector3<T> operator- (const Vector3<T> &other) const	{ return Vector3(this->x - other.x, this->y - other.y, this->z - other.z); }

	void Scale(float ratio)									{ x = (T)((float)x * ratio); y = (T)((float)y * ratio); z = (T)((float)z * ratio); }

	double Magnitude() const								{ return sqrt(x*x + y*y + z*z); }

	inline void Normalize();

	double DistanceTo(const Vector3<T> &other) const		{ return Vector3(*this - other).Magnitude(); }
};

template <class T>
inline void Vector3<T>::Normalize() {
	double magnitude = Magnitude();
	if (magnitude == 0) return;

	this->x = (T)(x / magnitude);
	this->y = (T)(y / magnitude);
	this->z = (T)(z / magnitude);
}


#endif
