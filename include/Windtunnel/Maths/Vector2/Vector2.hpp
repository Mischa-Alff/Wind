#ifndef __WINDTUNNEL_MATHS_VECTOR2_VECTOR2_HPP__
#define __WINDTUNNEL_MATHS_VECTOR2_VECTOR2_HPP__

namespace wind
{
	template<typename T>
	class Vector2
	{
	public:
		Vector2();
		Vector2(const T &_x, const T &_y);
		template<typename U>
		explicit Vector2(const Vector2<U> &other);
		template<typename U>
		operator Vector2<U>();

		T x,y;
	};

	template<typename T>
	Vector2<T> operator-(const Vector2<T> &rhs);

	template<typename T>
	Vector2<T> operator+(const Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> operator-(const Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> operator*(const Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> operator/(const Vector2<T> &lhs, const Vector2<T> &rhs);

	template<typename T>
	Vector2<T> &operator+=(Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> &operator-=(Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> &operator/=(Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> &operator*=(Vector2<T> &lhs, const Vector2<T> &rhs);

	template<typename T>
	Vector2<T> operator*(const Vector2<T> &lhs, const T &rhs);
	template<typename T>
	Vector2<T> operator*(const T &lhs, const Vector2<T> &rhs);
	template<typename T>
	Vector2<T> operator/(const Vector2<T> &lhs, const T &rhs);
	template<typename T>
	Vector2<T> &operator/=(Vector2<T> &lhs, const T &rhs);
	template<typename T>
	Vector2<T> &operator*=(Vector2<T> &lhs, const T &rhs);

	template<typename T, typename U>
	Vector2<T> operator*(const Vector2<T> &lhs, const U &rhs);
	template<typename T, typename U>
	Vector2<T> operator*(const U &lhs, const Vector2<T> &rhs);
	template<typename T, typename U>
	Vector2<T> operator/(const Vector2<T> &lhs, const U &rhs);
	template<typename T, typename U>
	Vector2<T> &operator/=(Vector2<T> &lhs, const U &rhs);
	template<typename T, typename U>
	Vector2<T> &operator*=(Vector2<T> &lhs, const U &rhs);

	template<typename T>
	bool operator==(const Vector2<T> &lhs, const Vector2<T> &rhs);
	template<typename T>
	bool operator!=(const Vector2<T> &lhs, const Vector2<T> &rhs);
}

#include <Windtunnel/Maths/Vector2/Vector2.inl>

namespace wind
{
	using Vector2f = Vector2<float>;
	using Vector2i = Vector2<int>;
	using Vector2d = Vector2<double>;
	using Vector2u = Vector2<unsigned int>;
	using Vector2l = Vector2<long>;
	using Vector2ll = Vector2<long long>;
	using Vector2ul = Vector2<unsigned long>;
	using Vector2ull = Vector2<unsigned long long>;
	using Vector2ld = Vector2<long double>;
}

#endif