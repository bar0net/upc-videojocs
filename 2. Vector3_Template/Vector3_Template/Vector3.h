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

	float Magnitude() const								{ return (float)sqrt(x*x + y*y + z*z); }

	inline void Normalize();

	float DistanceTo(const Vector3<T> &other) const		{ return Vector3(*this - other).Magnitude(); }
};

template <class T>
inline void Vector3<T>::Normalize() {
	float ratio = Magnitude();
	if (ratio == 0) return;
	else ratio = 1 / ratio;

	this->x = (T)(x * ratio);
	this->y = (T)(y * ratio);
	this->z = (T)(z * ratio);
}


#endif
