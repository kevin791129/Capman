#pragma once
#include <math.h>

namespace MathHelper
{
	template <typename T>
	class Vector2
	{
	public:
		T _x;
		T _y;
	public:
		//--------------------------------------------------------------------------------------------
		// Constructor for vector 2
		//--------------------------------------------------------------------------------------------
		Vector2() : _x(0), _y(0) { }
		Vector2(T x, T y) : _x(x), _y(y) { }
		//--------------------------------------------------------------------------------------------
		// Simple algebra with vectors
		//--------------------------------------------------------------------------------------------
		template <typename T>
		Vector2<T>& operator=(const Vector2<T>& rhs)
		{
			this->_x = rhs._x;
			this->_y = rhs._y;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator+=(const Vector2<T>& rhs)
		{
			this->_x += rhs._x;
			this->_y += rhs._y;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator-=(const Vector2<T>& rhs)
		{
			this->_x -= rhs._x;
			this->_y -= rhs._y;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator*=(const T& value)
		{
			this->_x *= value;
			this->_y *= value;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator/=(const T& value)
		{
			this->_x /= value;
			this->_y /= value;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator+(const Vector2<T>& rhs)
		{
			*this += rhs;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator-(const Vector2<T>& rhs)
		{
			*this -= rhs;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator*(const T& rhs)
		{
			*this *= rhs;
			return *this;
		}
		template <typename T>
		Vector2<T>& operator/(const T& rhs)
		{
			*this /= rhs;
			return *this;
		}
		//--------------------------------------------------------------------------------------------
		// Comparison of vectors
		//--------------------------------------------------------------------------------------------
		template <typename T>
		bool operator==(const Vector2<T>& rhs) 
		{
			return this->_x == rhs._x && this->_y == rhs._y;
		}
		template <typename T>
		bool operator!=(const Vector2<T>& rhs)
		{
			return ! (*this == rhs);
		}
		//--------------------------------------------------------------------------------------------
		// Get length of vector
		//--------------------------------------------------------------------------------------------
		float Length() const;
		//--------------------------------------------------------------------------------------------
		// Get normalized vector, length of 1
		//--------------------------------------------------------------------------------------------
		void Normalize();
		//--------------------------------------------------------------------------------------------
		// String vector
		//--------------------------------------------------------------------------------------------
		std::string ToString() const;
		//--------------------------------------------------------------------------------------------
		// Lerp vector
		//--------------------------------------------------------------------------------------------
		static Vector2<T> Lerp(Vector2<T> a, Vector2<T> b, const float t);
	};

	template <typename T>
	float Vector2<T>::Length() const
	{
		return sqrt((float)_x * (float)_x + (float)_y * (float)_y);
	}

	template<typename T>
	void Vector2<T>::Normalize()
	{
		float length = this->Length();
		*this /= length;
	}

	template <typename T>
	std::string Vector2<T>::ToString() const
	{
		std::string msg = "(";
		msg.append(std::to_string(_x).c_str());
		msg.append(",");
		msg.append(std::to_string(_y).c_str());
		msg.append(")");
		return msg;
	}

	template<typename T>
	Vector2<T> Vector2<T>::Lerp(Vector2<T> a, Vector2<T> b, const float t)
	{
		if (t <= 0.0f)
		{
			return a;
		}
		else if (t >= 1.0f)
		{
			return b;
		}
		else
		{
			return a + (b - a) * t;
		}
	}

};