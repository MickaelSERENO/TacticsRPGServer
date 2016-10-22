#ifndef RECT_INCLUDE
#define RECT_INCLUDE

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 

/** \brief the 2D rectangle operations*/
template<typename T>
class Rectangle2
{
	public:
		/** \brief Init the rectangle coordinates
		 * \param a the x coordinate.
		 * \param b the y coordinate.
		 * \param w the width of the rectangle.
		 * \param h the height of the rectangle.*/
		Rectangle2(T a=0.0f, T b=0.0f, T w=0.0f, T h=0.0f)
		{
			x = a;
			y = b;
			width = w;
			height = h;
		}

		/** \brief Init the rectangle coordinates
		 * \param pos the rectangle y x position
		 * \param size the rectangle width and height*/
		Rectangle2(const glm::vec2& pos, const glm::vec2& size)
		{
			x = pos.x;
			y = pos.y;
			width=size.x;
			height=size.y;
		}

		/** \brief copy Constructor or Rectangle2
		 * \param r the Rectangle2 being to be copied*/
		template<typename S>
		Rectangle2(const Rectangle2<S>& r)
		{
			x = r.x;
			y = r.y;
			width = r.width;
			height = r.height;
		}

		template<typename S>
		Rectangle2& operator=(const Rectangle2<S>& r)
		{
			if((const Rectangle2<S>*)(this) != &r)
			{
				x = r.x;
				y = r.y;
				width = r.width;
				height = r.height;
			}

			return *this;
		}

		T x;
		T y;
		T width;
		T height;
};

template<typename T>
bool operator==(const Rectangle2<T> &a, const Rectangle2<T> &b)
{
	return(a.x == b.x && a.y == b.y && a.width == b.width && a.height == b.height);
}

template<typename T>
bool operator!=(const Rectangle2<T> &a, const Rectangle2<T> &b)
{
	return(!(a==b));
}

template <typename T>
bool rectCollision(const Rectangle2<T> &rect1, const Rectangle2<T> &rect2)
{
	if(rect1.x + rect1.width <= rect2.x
		||rect1.x >= rect2.x + rect2.width
		||rect1.y + rect1.height <= rect2.y
		||rect1.y >= rect2.y+rect2.height)
		return false;
	return true;
}

typedef Rectangle2<float>        FloatRect2;
typedef Rectangle2<float>        Rectangle2f;
typedef Rectangle2<int>          IntRect2;
typedef Rectangle2<int>          Rectangle2i;
typedef Rectangle2<unsigned int> Rectangle2ui;

#endif
