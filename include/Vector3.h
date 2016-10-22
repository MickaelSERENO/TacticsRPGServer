#ifndef VECTOR3_INCLUDE
#define VECTOR3_INCLUDE

template<typename T>
class Vector3<T>
{
	public:
		Vector3<T>(T a=0, T b=0, T c=0)
		{
			x=a;
			y=b;
			z=c;
		}

		Vector3<T>(const Vector3<T>& v)
		{
			x = v.x;
			y = v.y;
			z = v.z;
		}

		Vector2<T>& operator=(const Vector2<T>& copy)
		{
			if(*copy != this)
			{
				x = v.x;
				y = v.y;
				z = v.z;
			}

			return *this;
		}

		T x;
		T y;
		T z;
};


template<typename T>
bool operator==(const Vector3<T> &a, const Vector3<T> &b)
{
	return(a.x == b.x && a.y == b.y && a.z == b.z);
}

template<typename T>
bool operator!=(const Vector3<T> &a, const Vector3<T> &b)
{
	return(!a==b);
}


template<typename T>
Vector3<T> operator+(const Vector3<T> &a, const Vector3<T> &b)
{
	return Vector3<T>(a.x + b.x, a.y + b.y, a.z + b.z);
}

template<typename T>
Vector3<T> operator-(const Vector3<T> &a, const Vector3<T> &b)
{
	return Vector3<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename T>
Vector3<T> operator*(const Vector3<T> &a, float x)
{
	return Vector3<T>(a.x * x, a.y * x, a.z * x);
}

template<typename T>
Vector3<T> operator*(float x, const Vector3<T> &a)
{
	return a*x;
}

template<typename T>
Vector3<T> operator/(const Vector3<T> &a, float x)
{
	return a * (1/x);
}

typedef Vector3<float> Vector3f;
typedef Vector3<int> Vector3i;
#endif
