#ifndef DEF_RECTANGLE3_INCLUDE
#define DEF_RECTANGLE3_INCLUDE

#define GLM_FORCE_RADIANS

#include <glm/glm.hpp>
#include <glm/gtx/norm.hpp>
#include <glm/gtc/matrix_transform.hpp> 
#include "Graphics/Rectangle2.h"

/** \brief the 3D rectangle operations.*/
template<typename T>
class Rectangle3
{
	public:
		/** \brief Init the 3D rectangle coordinates.
		 * \param a the x coordinate
		 * \param b the y coordinate
		 * \param c the z coordinate
		 * \param w the width
		 * \param h the height
		 * \param d the depth*/
		Rectangle3<T>(T a=0.0, T b=0.0, T c=0.0, T w=0.0, T h=0.0, T d=0.0)
		{
			x      = a;
			y      = b;
			z      = c;
			width  = w;
			height = h;
			depth  = d;
		}

		Rectangle3<T>(const glm::vec3& pos, const glm::vec3& size)
		{
			x      = pos.x;
			y      = pos.y;
			z      = pos.z;
			width  = size.x;
			height = size.y;
			depth  = size.z;
		}

		Rectangle3<T>(const Rectangle2<T>& rect, T rZ, T rDepth)
		{
			x = rect.x;
			y = rect.y;
			z = rZ;
			width  = rect.width;
			height = rect.height;
			depth  = rDepth;
		}

		T x;
		T y;
		T z;
		T width;
		T height;
		T depth;
};

template <typename T>
bool rectCollision2(const Rectangle3<T> &rect1, const Rectangle3<T> &rect2)
{
	if(rect1.y + rect1.height <= rect2.y
		||rect1.y >= rect2.y+rect2.height
		||rect1.x + rect1.width <= rect2.x
		||rect1.x >= rect2.x + rect2.width)
		return false;
	return true;
}

template<typename T>
bool operator==(const Rectangle3<T> &a, const Rectangle3<T> &b)
{
	return(a.x == b.x && a.y == b.y && a.z == b.z && a.width == b.width && a.height == b.height && a.depth == b.depth);
}

template<typename T>
bool operator!=(const Rectangle3<T> &a, const Rectangle3<T> &b)
{
	return(!(a==b));
}

typedef Rectangle3<float> FloatRect3;
typedef Rectangle3<int>   IntRect3;

typedef Rectangle3<float> Rectangle3f;
typedef Rectangle3<int>   Rectangle3i;

#endif
