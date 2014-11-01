#ifndef WIND_MATHS_VECTOR2_VECTOR2_INL
#define WIND_MATHS_VECTOR2_VECTOR2_INL
#include <Wind/Maths/Vector2/Vector2.hpp>

namespace wind
{
	template<typename T>
	Vector2<T>::Vector2(){}

	template<typename T>
	Vector2<T>::Vector2(const T &_x, const T &_y):x(_x), y(_y){}

	template<typename T>
	T Vector2<T>::dot(const Vector2<T> &other) const
	{
		return x*other.x + y*other.y;
	}

	template<typename T>
	T Vector2<T>::cross(const Vector2<T> &other) const
	{
		return x*other.y - y*other.x;
	}

	template<typename T>
	Vector2<T> Vector2<T>::cross() const
	{
		return {y, -x};
	}

	template<typename T>
	template<typename U>
	Vector2<T>::Vector2(const Vector2<U> &other)
	{
		x=static_cast<T>(other.x);
		y=static_cast<T>(other.y);
	}
	
	template<typename T>
	template<typename U>
	Vector2<T>::operator Vector2<U>()
	{
		return {static_cast<U>(x), static_cast<U>(y)};
	}

	template<typename T>
	Vector2<T> operator-(const Vector2<T> &rhs)
	{
		return {-rhs.x, -rhs.y};
	}

	template<typename T>
	Vector2<T> operator+(const Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		return {lhs.x+rhs.x, lhs.y+rhs.y};
	}

	template<typename T>
	Vector2<T> operator-(const Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		return {lhs.x-rhs.x, lhs.y-rhs.y};
	}

	template<typename T>
	Vector2<T> operator*(const Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		return {lhs.x*rhs.x, lhs.y*rhs.y};
	}
	
	template<typename T>
	Vector2<T> operator/(const Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		return {lhs.x/rhs.x, lhs.y/rhs.y};
	}

	template<typename T>
	Vector2<T> &operator+=(Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		return lhs;
	}

	template<typename T>
	Vector2<T> &operator-=(Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		return lhs;
	}

	template<typename T>
	Vector2<T> &operator/=(Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		return lhs;
	}

	template<typename T>
	Vector2<T> &operator*=(Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		return lhs;
	}

	template<typename T>
	Vector2<T> operator*(const Vector2<T> &lhs, const T &rhs)
	{
		return {lhs.x*rhs, lhs.y*rhs};
	}

	template<typename T>
	Vector2<T> operator*(const T &lhs, const Vector2<T> &rhs)
	{
		return {lhs*rhs.x, lhs*rhs.y};
	}

	template<typename T>
	Vector2<T> operator/(const Vector2<T> &lhs, const T &rhs)
	{
		return {lhs.x/rhs, lhs.y/rhs};	
	}

	template<typename T>
	Vector2<T> &operator/=(Vector2<T> &lhs, const T &rhs)
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		return lhs;
	}

	template<typename T>
	Vector2<T> &operator*=(Vector2<T> &lhs, const T &rhs)
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		return lhs;
	}

	template<typename T, typename U>
	Vector2<T> operator*(const Vector2<T> &lhs, const U &rhs)
	{
		return {lhs.x*static_cast<T>(rhs), lhs.y*static_cast<T>(rhs)};
	}

	template<typename T, typename U>
	Vector2<T> operator*(const U &lhs, const Vector2<T> &rhs)
	{
		return {static_cast<T>(lhs)*rhs.x, static_cast<T>(lhs)*rhs.y};
	}

	template<typename T, typename U>
	Vector2<T> operator/(const Vector2<T> &lhs, const U &rhs)
	{
		return {lhs.x/static_cast<T>(rhs), lhs.y/static_cast<T>(rhs)};
	}

	template<typename T, typename U>
	Vector2<T> &operator/=(Vector2<T> &lhs, const U &rhs)
	{
		lhs.x /= static_cast<T>(rhs);
		lhs.y /= static_cast<T>(rhs);
		return lhs;
	}

	template<typename T, typename U>
	Vector2<T> &operator*=(Vector2<T> &lhs, const U &rhs)
	{
		lhs.x *= static_cast<T>(rhs);
		lhs.y *= static_cast<T>(rhs);
		return lhs;
	}

	template<typename T>
	bool operator==(const Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		return (lhs.x==rhs.x) && (lhs.x==rhs.x);
	}

	template<typename T>
	bool operator!=(const Vector2<T> &lhs, const Vector2<T> &rhs)
	{
		return (lhs.x!=rhs.x) || (lhs.x!=rhs.x);
	}
}
#endif