#ifndef VECTOR2_INCLUDE
#define VECTOR2_INCLUDE

template<typename T>
class Vector2
{
	public:
		Vector2(T a, T b)
		{
			x=a;
			y=b;
		}

		Vector2()
		{
			x=0;
			y=0;
		}

		Vector2(const Vector2<T>& v)
		{
			x = v.x;
			y = v.y;
		}

		Vector2& operator=(const Vector2<T>& copy)
		{
			if(&copy != this)
			{
				x = copy.x;
				y = copy.y;
			}

			return *this;
		}

		T x;
		T y;
};


template<typename T>
bool operator==(const Vector2<T> &a, const Vector2<T> &b)
{
	return(a.x == b.x && a.y == b.y);
}

template<typename T>
bool operator!=(const Vector2<T> &a, const Vector2<T> &b)
{
	return(!a==b);
}

template<typename T>
Vector2<T> operator+(const Vector2<T> &a, const Vector2<T> &b)
{
	return Vector2<T>(a.x + b.x, a.y + b.y);
}

template<typename T>
Vector2<T> operator-(const Vector2<T> &a, const Vector2<T> &b)
{
	return Vector2<T>(a.x - b.x, a.y - b.y, a.z - b.z);
}

template<typename T>
Vector2<T> operator*(const Vector2<T> &a, float x)
{
	return Vector2<T>(a.x * x, a.y * x);
}

template<typename T>
Vector2<T> operator*(float x, const Vector2<T> &a)
{
	return a*x;
}

template<typename T>
Vector2<T> operator/(const Vector2<T> &a, float x)
{
	return a * (1.0f/x);
}

typedef Vector2<float> Vector2f;
typedef Vector2<int> Vector2i;
typedef Vector2<unsigned int> Vector2ui;
#endif
