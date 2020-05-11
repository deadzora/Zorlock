#pragma once
#include <cmath>
#include <math.h> 

#define VERTEX Zorlock::Vertex
#define VECTOR2 Zorlock::Vector2
#define VECTOR3 Zorlock::Vector3
#define VECTOR4 Zorlock::Vector4
#define LINE Zorlock::Line
#define PLANE Zorlock::Plane
#define MATRIX3 Zorlock::Matrix
#define MATRIX4 Zorlock::Matrix4
#define MATHTRANSFORM Zorlock::MathTransform
#define BOX Zorlock::Box
#define QUATERNION Zorlock::Quaternion
typedef float MATRIX3ARRAY[3][3];
typedef float MATRIX4ARRAY[4][4];


#ifndef M_PI
// You can extend this approximation as far as you need to;
// this version was copied from the MINGW GCC headers
#define M_PI 3.14159265358979323846f  
#endif
#define DEG_CIRCLE 360
#define DEG_TO_RAD (M_PI / (DEG_CIRCLE / 2))
#define RAD_TO_DEG ((DEG_CIRCLE / 2) / M_PI)
#define TWOPI M_PI * 2.0f;			//360 degrees
#define HALFPI M_PI * .5f;			//90  degrees
#define QUARTERPI  M_PI * .25f;		//45  degrees
#define EPSILON 0.000001f


namespace Zorlock {


	enum ZORLOCK_ZERO { Zero };
	enum ZORLOCK_IDENTITY { Identity };

	struct Vector2
	{
		float x, y;

		Vector2() : x(0), y(0) {}
		Vector2(float x, float y) : x(x), y(y)
		{}
		//for template compatability
		Vector2(float x, float y, float z) : x(x), y(y)
		{
		//we ignore Z
		}
		Vector2(float x, float y, float z, float w) : x(x), y(y)
		{
			//we ignore Z and W
		}
		float distance(const Vector2* vec)
		{
			float d = sqrt(pow(vec->x - this->x, 2) +
				pow(vec->y - this->y, 2) * 1.0f);
			return d;
		}


		
	};

	struct Vector3 : public Vector2
	{
		float z;

		float distance(const Vector3* vec)
		{
			float d = sqrt(pow(vec->x - this->x, 2) +
				pow(vec->y - this->y, 2) +
				pow(vec->z - this->z, 2) * 1.0f);
			return d;
		}

		Vector3() : Vector2() , z(0) {

		}


		Vector3(float x, float y, float z) : Vector2(x, y), z(z) 
		{				
		}
		//for template compatability
		Vector3(float x, float y, float z, float w) : Vector2(x, y), z(z)
		{
			//we ignore Z and W
		}

		Vector3 operator-()const {
			return Vector3(-x, -y, -z);
		}
		Vector3 operator*(float scale)const {
			return Vector3(x * scale, y * scale, z * scale);
		}
		Vector3 operator*(const Vector3& q)const {
			return Vector3(x * q.x, y * q.y, z * q.z);
		}
		Vector3 operator/(float scale)const {
			return Vector3(x / scale, y / scale, z / scale);
		}
		Vector3 operator/(const Vector3& q)const {
			return Vector3(x / q.x, y / q.y, z / q.z);
		}
		Vector3 operator+(const Vector3& q)const {
			return Vector3(x + q.x, y + q.y, z + q.z);
		}
		Vector3 operator-(const Vector3& q)const {
			return Vector3(x - q.x, y - q.y, z - q.z);
		}
		Vector3& operator*=(float scale) {
			x *= scale; y *= scale; z *= scale; return *this;
		}
		Vector3& operator*=(const Vector3& q) {
			x *= q.x; y *= q.y; z *= q.z; return *this;
		}
		Vector3& operator/=(float scale) {
			x /= scale; y /= scale; z /= scale; return *this;
		}
		Vector3& operator/=(const Vector3& q) {
			x /= q.x; y /= q.y; z /= q.z; return *this;
		}
		Vector3& operator+=(const Vector3& q) {
			x += q.x; y += q.y; z += q.z; return *this;
		}
		Vector3& operator-=(const Vector3& q) {
			x -= q.x; y -= q.y; z -= q.z; return *this;
		}
		bool operator<(const Vector3& q)const {
			if (fabs(x - q.x) > EPSILON) return x < q.x ? true : false;
			if (fabs(y - q.y) > EPSILON) return y < q.y ? true : false;
			return fabs(z - q.z) > EPSILON&& z < q.z;
		}
		bool operator==(const Vector3& q)const {
			return fabs(x - q.x) <= EPSILON && fabs(y - q.y) <= EPSILON && fabs(z - q.z) <= EPSILON;
		}
		bool operator!=(const Vector3& q)const {
			return fabs(x - q.x) > EPSILON || fabs(y - q.y) > EPSILON || fabs(z - q.z) > EPSILON;
		}
		float dot(const Vector3& q)const {
			return x * q.x + y * q.y + z * q.z;
		}
		Vector3 cross(const Vector3& q)const {
			return Vector3(y * q.z - z * q.y, z * q.x - x * q.z, x * q.y - y * q.x);
		}
		float length()const {
			return sqrtf(x * x + y * y + z * z);
		}
		float distance(const Vector3& q)const {
			float dx = x - q.x, dy = y - q.y, dz = z - q.z; return sqrtf(dx * dx + dy * dy + dz * dz);
		}
		Vector3 normalized()const {
			float l = length(); return Vector3(x / l, y / l, z / l);
		}
		void normalize() {
			float l = length(); x /= l; y /= l; z /= l;
		}
		float yaw()const {
			return -atan2f(x, z);
		}
		float pitch()const {
			return -atan2f(y, sqrtf(x * x + z * z));
		}
		void clear() {
			x = y = z = 0;
		}
		static Vector3 Up()
		{
			return Vector3(0,1,0);
		}
		static Vector3 Down()
		{
			return Vector3(0, -1, 0);
		}
		static Vector3 Forward()
		{
			return Vector3(0, 0, 1);
		}
		static Vector3 Back()
		{
			return Vector3(0, 0, -1);
		}
		static Vector3 Left()
		{
			return Vector3(-1, 0, 0);
		}
		static Vector3 Right()
		{
			return Vector3(1, 0, 0);
		}
		static Vector3 Zero()
		{
			return Vector3(0, 0, 0);
		}
	};

	struct Vector4 : public Vector3
	{
		float w;

		Vector4() : Vector3(), w(0)
		{}
		Vector4(float x, float y, float z, float w) : Vector3(x,y,z), w(0)
		{

		}
		Vector4(Vector3 a, float w) : Vector3(a), w(w)
		{

		}
		float distance(const Vector4* vec)
		{
			float d = sqrt(pow(vec->x - this->x, 2) +
				pow(vec->y - this->y, 2) +
				pow(vec->z - this->z, 2) +
				pow(vec->w - this->w, 2) * 1.0f);
			return d;
		}
		static Vector4 Zero()
		{
			return Vector4(0,0, 0, 0);
		}

		
	};

	struct VertexP
	{
		Vector3 value;
		VertexP() {};
		VertexP(float x, float y, float z) : value(Vector3(x,y,z))
		{
		}
		//for template compatability
		VertexP(float x, float y, float z, float w) : value(Vector3(x, y, z))
		{
			//ignore w
		}
		VertexP(float x, float y) : value(Vector3(x, y, 0))
		{
		}
	};

	struct VertexN
	{
		Vector3 value;
		VertexN() {};
		VertexN(float x, float y, float z) : value(Vector3(x, y, z))
		{
		}
		//for template compatability
		VertexN(float x, float y, float z, float w) : value(Vector3(x, y, z))
		{
			//ignore w
		}
		VertexN(float x, float y) : value(Vector3(x, y, 0))
		{
		}
		
	};

	struct UV {
		Vector2 value;

		UV() : value(Vector2())
		{};
		UV(float x, float y) : value(Vector2(x,y))
		{
			this->value.x = x;
			this->value.y = y;

		}
		UV(float x, float y, float z) : value(Vector2(x, y))
		{
		}
		//for template compatability
		UV(float x, float y, float z, float w) : value(Vector2(x, y))
		{
			//ignore w
		}
		
	};

	struct UVW {
		Vector3 value;

		UVW() : value(Vector3()) {};
		UVW(float x, float y, float z) : value(Vector3(x, y, z))
		{
			this->value.x = x;
			this->value.y = y;
			this->value.z = z;
		}
		UVW(float x, float y) : value(Vector3(x, y, 0))
		{
			this->value.x = x;
			this->value.y = y;

		}
		//for template compatability
		UVW(float x, float y, float z, float w) : value(Vector3(x, y, z))
		{
			//ignore w
		}
	};




	template <class... T>
	class VertexT : public T...
	{
	public:
		VertexT(T&&... base_classes) : T(base_classes)...{
		}
		VertexT(T&&... base_classes, T... params) : T(base_classes(params...))...{
		}
	};





	/*
	template <class A, class B, class C, class D>
	struct Vertex4 : public A, public B, public C, public D
	{

		Vertex4() : valueA(A()), valueB(B()), valueC(C()), valueD(D())
		{}
		Vertex4(A aa, B bb, C cc, D dd) : valueA(aa), valueB(bb), valueC(cc), valueD(dd)
		{}

		A valueA;
		B valueB;
		C valueC;
		D valueD;
	};

	template <class A, class B, class C>
	struct Vertex3 : public A, public B, public C
	{
		A valueA;
		B valueB;
		C valueC;
	};

	template <class A, class B>
	struct Vertex2 : public A, public B
	{
		A valueA;
		B valueB;

	};
	template <class A>
	struct Vertex1 : public A
	{
		A valueA;
	};
	*/

	struct Vertex
	{
		Vertex() {};
		Vertex(float x, float y, float z)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
		};
		Vertex(float x, float y, float z, float u, float v, float w)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->uvw.x = u;
			this->uvw.y = v;
			this->uvw.z = w;
		};
		Vertex(float x, float y, float z, float nx, float ny, float nz, float u, float v, float w)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->normal.x = nx;
			this->normal.y = ny;
			this->normal.z = nz;
			this->uvw.x = u;
			this->uvw.y = v;
			this->uvw.z = w;
		};
		Vertex(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float u, float v, float w)
		{
			this->position.x = x;
			this->position.y = y;
			this->position.z = z;
			this->normal.x = nx;
			this->normal.y = ny;
			this->normal.z = nz;
			this->uvw.x = u;
			this->uvw.y = v;
			this->uvw.z = w;
			this->color.x = r;
			this->color.y = b;
			this->color.z = g;
		};
		Vector3 position;
		Vector3 normal;
		Vector3 color;
		Vector3 uvw;

	};


	class Line {
	public:
		Vector3 o, d;
		Line() {
		}
		Line(const Vector3& o, const Vector3& d) :o(o), d(d) {
		}
		Line operator+(const Vector3& q)const {
			return Line(o + q, d);
		}
		Line operator-(const Vector3& q)const {
			return Line(o - q, d);
		}
		Vector3 operator*(float q)const {
			return o + d * q;
		}
		Vector3 nearest(const Vector3& q)const {
			return o + d * (d.dot(q - o) / d.dot(d));
		}
	};

	class Plane {
	public:
		Vector3 n;
		float d;

		Plane() :d(0) {
		}
		//normal/offset form
		Plane(const Vector3& n, float d) :n(n), d(d) {
		}
		//point/normal form
		Plane(const Vector3& p, const Vector3& n) :n(n), d(-n.dot(p)) {
		}
		//create plane from tri
		Plane(const Vector3& v0, const Vector3& v1, const Vector3& v2) {
			n = (v1 - v0).cross(v2 - v0).normalized(); d = -n.dot(v0);
		}
		Plane operator-()const {
			return Plane(-n, -d);
		}
		float t_intersect(const Line& q)const {
			return -distance(q.o) / n.dot(q.d);
		}
		Vector3 intersect(const Line& q)const {
			return q * t_intersect(q);
		}
		Line intersect(const Plane& q)const {
			Vector3 lv = n.cross(q.n).normalized();
			return Line(q.intersect(Line(nearest(n * -d), n.cross(lv))), lv);
		}
		Vector3 nearest(const Vector3& q)const {
			return q - n * distance(q);
		}
		void negate() {
			n = -n; d = -d;
		}
		float distance(const Vector3& q)const {
			return n.dot(q) + d;
		}
	};

	struct Quaternion
	{
		float w;
		Vector3 v;

		Quaternion() :v(Vector3()), w(1) {
		}
		Quaternion(float w, const Vector3& v) :w(w), v(v) {
		}
		Quaternion FromEulerAngles(const Vector3& q) const {
			Vector3 ypr = Vector3(q);
			ypr.y *= DEG_TO_RAD;
			ypr.x *= DEG_TO_RAD;
			ypr.z *= DEG_TO_RAD;
			float rollOver2 = ypr.z * 0.5f;
			float sinRollOver2 = (float)sin((double)rollOver2);
			float cosRollOver2 = (float)cos((double)rollOver2);
			float pitchOver2 = ypr.x * 0.5f;
			float sinPitchOver2 = (float)sin((double)pitchOver2);
			float cosPitchOver2 = (float)cos((double)pitchOver2);
			float yawOver2 = ypr.y * 0.5f;
			float sinYawOver2 = (float)sin((double)yawOver2);
			float cosYawOver2 = (float)cos((double)yawOver2);
			Quaternion result;
			result.w = cosYawOver2 * cosPitchOver2 * cosRollOver2 + sinYawOver2 * sinPitchOver2 * sinRollOver2;
			result.v.x = cosYawOver2 * sinPitchOver2 * cosRollOver2 + sinYawOver2 * cosPitchOver2 * sinRollOver2;
			result.v.y = sinYawOver2 * cosPitchOver2 * cosRollOver2 - cosYawOver2 * sinPitchOver2 * sinRollOver2;
			result.v.z = cosYawOver2 * cosPitchOver2 * sinRollOver2 - sinYawOver2 * sinPitchOver2 * cosRollOver2;
			return result;
		}
		Quaternion operator-()const {
			return Quaternion(w, -v);
		}
		Quaternion operator+(const Quaternion& q)const {
			return Quaternion(w + q.w, v + q.v);
		}
		Quaternion operator-(const Quaternion& q)const {
			return Quaternion(w - q.w, v - q.v);
		}
		Quaternion operator*(const Quaternion& q)const {
			return Quaternion(w * q.w - v.dot(q.v), q.v.cross(v) + q.v * w + v * q.w);
		}
		Vector3 operator*(const Vector3& q)const {
			return (*this * Quaternion(0, q) * -*this).v;
		}
		Quaternion operator*(float q)const {
			return Quaternion(w * q, v * q);
		}
		Quaternion operator/(float q)const {
			return Quaternion(w / q, v / q);
		}
		float dot(const Quaternion& q)const {
			return v.x * q.v.x + v.y * q.v.y + v.z * q.v.z + w * q.w;
		}
		float length()const {
			return sqrtf(w * w + v.x * v.x + v.y * v.y + v.z * v.z);
		}
		void normalize() {
			*this = *this / length();
		}
		Quaternion normalized()const {
			return *this / length();
		}
		Quaternion slerpTo(const Quaternion& q, float a)const {
			Quaternion t = q;
			float d = dot(q), b = 1 - a;
			if (d < 0) { t.w = -t.w; t.v = -t.v; d = -d; }
			if (d < 1 - EPSILON) {
				float om = acosf(d);
				float si = sinf(om);
				a = sinf(a * om) / si;
				b = sinf(b * om) / si;
			}
			return *this * b + t * a;
		}
		Vector3 i()const {
			float xz = v.x * v.z, wy = w * v.y;
			float xy = v.x * v.y, wz = w * v.z;
			float yy = v.y * v.y, zz = v.z * v.z;
			return Vector3(1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy));
		}
		Vector3 j()const {
			float yz = v.y * v.z, wx = w * v.x;
			float xy = v.x * v.y, wz = w * v.z;
			float xx = v.x * v.x, zz = v.z * v.z;
			return Vector3(2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx));
		}
		Vector3 k()const {
			float xz = v.x * v.z, wy = w * v.y;
			float yz = v.y * v.z, wx = w * v.x;
			float xx = v.x * v.x, yy = v.y * v.y;
			return Vector3(2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy));
		}

		Vector3 ToEulerAngles()const {
			Vector3 pitchYawRoll;
			pitchYawRoll.y = (float)atan2(2.0f * v.x * w + 2.0f * v.y * v.z, 1 - 2.0f * (v.z * v.z + w * w));     // Yaw 
			pitchYawRoll.x = (float)asin(2.0f * (v.x * v.z - w * v.y));                             // Pitch 
			pitchYawRoll.z = (float)atan2(2.0f * v.x * v.y + 2.0f * v.z * w, 1 - 2.0f * (v.y * v.y + v.z * v.z));      // Roll 
			return pitchYawRoll;
		}

	};

	class Matrix {
		static Matrix tmps[64];
		//static Matrix& alloc_tmp() { static int tmp = 0; return tmps[tmp++ & 63]; }
		friend class Transform;
	public:
		Vector3 i, j, k;

		Matrix() :i(Vector3(1, 0, 0)), j(Vector3(0, 1, 0)), k(Vector3(0, 0, 1)) {
		}
		Matrix(const Vector3& i, const Vector3& j, const Vector3& k) :i(i), j(j), k(k) {
		}
		Matrix(const Quaternion& q) {
			float xx = q.v.x * q.v.x, yy = q.v.y * q.v.y, zz = q.v.z * q.v.z;
			float xy = q.v.x * q.v.y, xz = q.v.x * q.v.z, yz = q.v.y * q.v.z;
			float wx = q.w * q.v.x, wy = q.w * q.v.y, wz = q.w * q.v.z;
			i = Vector3(1 - 2 * (yy + zz), 2 * (xy - wz), 2 * (xz + wy)),
				j = Vector3(2 * (xy + wz), 1 - 2 * (xx + zz), 2 * (yz - wx)),
				k = Vector3(2 * (xz - wy), 2 * (yz + wx), 1 - 2 * (xx + yy));
		}
		Matrix(float angle, const Vector3& axis) {
			const Vector3& u = axis;
			float c = cosf(angle), s = sinf(angle);
			float x2 = axis.x * axis.x, y2 = axis.y * axis.y, z2 = axis.z * axis.z;
			i = Vector3(x2 + c * (1 - x2), u.x * u.y * (1 - c) - u.z * s, u.z * u.x * (1 - c) + u.y * s);
			j = Vector3(u.x * u.y * (1 - c) + u.z * s, y2 + c * (1 - y2), u.y * u.z * (1 - c) - u.x * s);
			k = Vector3(u.z * u.x * (1 - c) - u.y * s, u.y * u.z * (1 - c) + u.x * s, z2 + c * (1 - z2));
		}
		Vector3& operator[](int n) {
			return (&i)[n];
		}
		const Vector3& operator[](int n)const {
			return (&i)[n];
		}
		Matrix operator~()const {
			Matrix m;
			m.i.x = i.x; m.i.y = j.x; m.i.z = k.x;
			m.j.x = i.y; m.j.y = j.y; m.j.z = k.y;
			m.k.x = i.z; m.k.y = j.z; m.k.z = k.z;
			return m;
		}
		float determinant()const {
			return i.x * (j.y * k.z - j.z * k.y) - i.y * (j.x * k.z - j.z * k.x) + i.z * (j.x * k.y - j.y * k.x);
		}
		Matrix operator-()const {
			Matrix m;
			float t = 1.0f / determinant();
			m.i.x = t * (j.y * k.z - j.z * k.y); m.i.y = -t * (i.y * k.z - i.z * k.y); m.i.z = t * (i.y * j.z - i.z * j.y);
			m.j.x = -t * (j.x * k.z - j.z * k.x); m.j.y = t * (i.x * k.z - i.z * k.x); m.j.z = -t * (i.x * j.z - i.z * j.x);
			m.k.x = t * (j.x * k.y - j.y * k.x); m.k.y = -t * (i.x * k.y - i.y * k.x); m.k.z = t * (i.x * j.y - i.y * j.x);
			return m;
		}
		Matrix cofactor()const {
			Matrix m;
			m.i.x = (j.y * k.z - j.z * k.y); m.i.y = -(j.x * k.z - j.z * k.x); m.i.z = (j.x * k.y - j.y * k.x);
			m.j.x = -(i.y * k.z - i.z * k.y); m.j.y = (i.x * k.z - i.z * k.x); m.j.z = -(i.x * k.y - i.y * k.x);
			m.k.x = (i.y * j.z - i.z * j.y); m.k.y = -(i.x * j.z - i.z * j.x); m.k.z = (i.x * j.y - i.y * j.x);
			return m;
		}
		bool operator==(const Matrix& q)const {
			return i == q.i && j == q.j && k == q.k;
		}
		bool operator!=(const Matrix& q)const {
			return i != q.i || j != q.j || k != q.k;
		}
		Vector3 operator*(const Vector3& q)const {
			return Vector3(i.x * q.x + j.x * q.y + k.x * q.z, i.y * q.x + j.y * q.y + k.y * q.z, i.z * q.x + j.z * q.y + k.z * q.z);
		}
		Matrix operator*(const Matrix& q)const {
			Matrix m;
			m.i.x = i.x * q.i.x + j.x * q.i.y + k.x * q.i.z; m.i.y = i.y * q.i.x + j.y * q.i.y + k.y * q.i.z; m.i.z = i.z * q.i.x + j.z * q.i.y + k.z * q.i.z;
			m.j.x = i.x * q.j.x + j.x * q.j.y + k.x * q.j.z; m.j.y = i.y * q.j.x + j.y * q.j.y + k.y * q.j.z; m.j.z = i.z * q.j.x + j.z * q.j.y + k.z * q.j.z;
			m.k.x = i.x * q.k.x + j.x * q.k.y + k.x * q.k.z; m.k.y = i.y * q.k.x + j.y * q.k.y + k.y * q.k.z; m.k.z = i.z * q.k.x + j.z * q.k.y + k.z * q.k.z;
			return m;
		}
		void orthogonalize() {
			k.normalize();
			i = j.cross(k).normalized();
			j = k.cross(i);
		}
		Matrix orthogonalized()const {
			Matrix m;
			m = *this; m.orthogonalize();
			return m;
		}

		static Matrix ZERO()
		{
			return Matrix(Vector3(),Vector3(),Vector3());
		}

		static Matrix IDENTITY()
		{
			return Matrix(Vector3(1, 0, 0), Vector3(0, 1, 0), Vector3(0, 0, 1));
		}

	};

	class Matrix4 {
	public:
		Vector4 i, j, k, l;
		Matrix4() = default;
		constexpr Matrix4(const Matrix4&) = default;
		constexpr Matrix4& operator=(const Matrix4&) = default;



		Matrix4(const Matrix& mat3)
		{
			i = Vector4(mat3.i,0.0f);
			j = Vector4(mat3.j, 0.0f);
			k = Vector4(mat3.k, 0.0f);
			l = Vector4(0.0f, 0.0f, 0.0f, 1.0f);

		}

		Matrix4(const Vector4& i, const Vector4& j, const Vector4& k, const Vector4& l) : i(i), j(j), k(k), l(l)
		{

		}
		
		Matrix4(float ix, float iy, float iz, float iw,
			float jx, float jy, float jz, float jw,
			float kx, float ky, float kz, float kw,
			float lx, float ly, float lz, float lw) : i(Vector4(ix,iy,iz,iw)), j(Vector4(jx, jy, jz, jw)), k(Vector4(kx, ky, kz, kw)), l(Vector4(lx, ly, lz, lw))
		{

		}

		MATRIX4ARRAY& ToArray()
		{
			MATRIX4ARRAY mat4;
			mat4[0][0] = i.x; mat4[0][1] = i.y; mat4[0][2] = i.z; mat4[0][3] = i.w;
			mat4[1][0] = j.x; mat4[1][1] = j.y; mat4[1][2] = j.z; mat4[1][3] = j.w;
			mat4[2][0] = k.x; mat4[2][1] = k.y; mat4[2][2] = k.z; mat4[2][3] = k.w;
			mat4[3][0] = l.x; mat4[3][1] = l.y; mat4[3][2] = l.z; mat4[3][3] = l.w;

			return mat4;

		}

		bool operator==(const Matrix4& rhs) const
		{
			if (i.x != rhs.i.x || i.y != rhs.i.y || i.z != rhs.i.z || i.w != rhs.i.w ||
				j.x != rhs.j.x || j.y != rhs.j.y || j.z != rhs.j.z || j.w != rhs.j.w ||
				k.x != rhs.k.x || k.y != rhs.k.y || k.z != rhs.k.z || k.w != rhs.k.w ||
				l.x != rhs.l.x || l.y != rhs.l.y || l.z != rhs.l.z || l.w != rhs.l.w)
			{
				return false;
			}

			return true;
		}

		bool operator!=(const Matrix4& rhs) const
		{
			return !operator==(rhs);
		}

		Matrix4 operator*(const Matrix4& rhs)const {
			Matrix4 r;

			r.i.x = i.x * rhs.i.x + i.y * rhs.j.x + i.z * rhs.k.x + i.w * rhs.l.x;
			r.i.y = i.x * rhs.i.y + i.y * rhs.j.y + i.z * rhs.k.y + i.w * rhs.l.y;
			r.i.z = i.x * rhs.i.z + i.y * rhs.j.z + i.z * rhs.k.z + i.w * rhs.l.z;
			r.i.w = i.x * rhs.i.w + i.y * rhs.j.w + i.z * rhs.k.w + i.w * rhs.l.w;

			r.j.x = j.x * rhs.i.x + j.y * rhs.j.x + j.z * rhs.k.x + j.w * rhs.l.x;
			r.j.y = j.x * rhs.i.y + j.y * rhs.j.y + j.z * rhs.k.y + j.w * rhs.l.y;
			r.j.z = j.x * rhs.i.z + j.y * rhs.j.z + j.z * rhs.k.z + j.w * rhs.l.z;
			r.j.w = j.x * rhs.i.w + j.y * rhs.j.w + j.z * rhs.k.w + j.w * rhs.l.w;

			r.k.x = k.x * rhs.i.x + k.y * rhs.j.x + k.z * rhs.k.x + k.w * rhs.l.x;
			r.k.y = k.x * rhs.i.y + k.y * rhs.j.y + k.z * rhs.k.y + k.w * rhs.l.y;
			r.k.z = k.x * rhs.i.z + k.y * rhs.j.z + k.z * rhs.k.z + k.w * rhs.l.z;
			r.k.w = k.x * rhs.i.w + k.y * rhs.j.w + k.z * rhs.k.w + k.w * rhs.l.w;

			r.l.x = l.x * rhs.i.x + l.y * rhs.j.x + l.z * rhs.k.x + l.w * rhs.l.x;
			r.l.y = l.x * rhs.i.y + l.y * rhs.j.y + l.z * rhs.k.y + l.w * rhs.l.y;
			r.l.z = l.x * rhs.i.z + l.y * rhs.j.z + l.z * rhs.k.z + l.w * rhs.l.z;
			r.l.w = l.x * rhs.i.w + l.y * rhs.j.w + l.z * rhs.k.w + l.w * rhs.l.w;
			

			return r;
		}

		Matrix4 operator+ (const Matrix4& rhs) const
		{
			Matrix4 r;

			r.i.x = i.x + rhs.i.x;
			r.i.y = i.y + rhs.i.y;
			r.i.z = i.z + rhs.i.z;
			r.i.w = i.w + rhs.i.w;

			r.j.x = j.x + rhs.j.x;
			r.j.y = j.y + rhs.j.y;
			r.j.z = j.z + rhs.j.z;
			r.j.w = j.w + rhs.j.w;

			r.k.x = k.x + rhs.k.x;
			r.k.y = k.y + rhs.k.y;
			r.k.z = k.z + rhs.k.z;
			r.k.w = k.w + rhs.k.w;

			r.l.x = l.x + rhs.l.x;
			r.l.y = l.y + rhs.l.y;
			r.l.z = l.z + rhs.l.z;
			r.l.w = l.w + rhs.l.w;

			return r;
		}

		Matrix4 operator-(const Matrix4& rhs) const
		{
			Matrix4 r;
			r.i.x = i.x - rhs.i.x;
			r.i.y = i.y - rhs.i.y;
			r.i.z = i.z - rhs.i.z;
			r.i.w = i.w - rhs.i.w;

			r.j.x = j.x - rhs.j.x;
			r.j.y = j.y - rhs.j.y;
			r.j.z = j.z - rhs.j.z;
			r.j.w = j.w - rhs.j.w;

			r.k.x = k.x - rhs.k.x;
			r.k.y = k.y - rhs.k.y;
			r.k.z = k.z - rhs.k.z;
			r.k.w = k.w - rhs.k.w;

			r.l.x = l.x - rhs.l.x;
			r.l.y = l.y - rhs.l.y;
			r.l.z = l.z - rhs.l.z;
			r.l.w = l.w - rhs.l.w;

			return r;
		}



		Matrix4 operator*(float rhs) const
		{
			return Matrix4(rhs * i.x, rhs * i.y, rhs * i.z, rhs * i.w,
				rhs * j.x, rhs * j.y, rhs * j.z, rhs * j.w,
				rhs * k.x, rhs * k.y, rhs * k.z, rhs * k.w,
				rhs * l.x, rhs * l.y, rhs * l.z, rhs * l.w);
		}

		Vector3 operator*(const Vector3& v)const {

			Vector3 r = Vector3::Zero();

			float fInvW = 1.0f / (l.x * v.x + l.y * v.y + l.z * v.z + l.w);

			r.x = (i.x * v.x + i.y * v.y + i.z * v.z + i.w) * fInvW;
			r.y = (j.x * v.x + j.y * v.y + j.z * v.z + j.w) * fInvW;
			r.z = (k.x * v.x + k.y * v.y + k.z * v.z + k.w) * fInvW;

			return r;
		}
		Vector4 operator*(const Vector4& v)const {

			return Vector4(
				i.x * v.x + i.y * v.y + i.z * v.z + i.w * v.w,
				j.x * v.x + j.y * v.y + j.z * v.z + j.w * v.w,
				k.x * v.x + k.y * v.y + k.z * v.z + k.w * v.w,
				l.x * v.x + l.y * v.y + l.z * v.z + l.w * v.w
			);
		}


		Matrix4 transpose() const
		{
			return Matrix4(i.x, j.x, k.x, l.x,
				i.y, j.y, k.y, l.y,
				i.z, j.z, k.z, l.z,
				i.w, j.w, k.w, l.w);
		}

		Matrix get3x3() const
		{
			Matrix m3x3;
			m3x3.i.x = i.x;
			m3x3.i.y = i.y;
			m3x3.i.z = i.z;
			m3x3.j.x = j.x;
			m3x3.j.y = j.y;
			m3x3.j.z = j.z;
			m3x3.k.x = k.x;
			m3x3.k.y = k.y;
			m3x3.k.z = k.z;

			return m3x3;
		}

		static Matrix4 lookAt(const Vector3& from, const Vector3& to, const Vector3& tmp = Vector3(0, 1, 0))
		{
			Vector3 dis = from - to;
			Vector3 forward = dis.normalized();
			Vector3 right = tmp.normalized().cross(forward);
			Vector3 up = forward.cross(right);

			Matrix4 camToWorld;

			camToWorld.i.x = right.x;
			camToWorld.i.y = right.y;
			camToWorld.i.z = right.z;
			camToWorld.j.x = up.x;
			camToWorld.j.y = up.y;
			camToWorld.j.z = up.z;
			camToWorld.k.x = forward.x;
			camToWorld.k.y = forward.y;
			camToWorld.k.z = forward.z;

			camToWorld.l.x = from.x;
			camToWorld.l.y = from.y;
			camToWorld.l.z = from.z;

			return camToWorld;
		}



		static Matrix4 ZERO()
		{
			return Matrix4(Vector4(), Vector4(), Vector4(), Vector4());
		}
		static Matrix4 IDENTITY()
		{
			return Matrix4(Vector4(1,0,0,0), Vector4(0,1,0,0), Vector4(0,0,1,0), Vector4(0,0,0,1));
		}

	};


	class Box {
	public:
		Vector3 a, b;
		Box() :a(Vector3(INFINITY, INFINITY, INFINITY)), b(Vector3(-INFINITY, -INFINITY, -INFINITY)) {
		}
		Box(const Vector3& q) :a(q), b(q) {
		}
		Box(const Vector3& a, const Vector3& b) :a(a), b(b) {
		}
		Box(const Line& l) :a(l.o), b(l.o) {
			update(l.o + l.d);
		}
		void clear() {
			a.x = a.y = a.z = INFINITY;
			b.x = b.y = b.z = -INFINITY;
		}
		bool empty()const {
			return b.x < a.x || b.y < a.y || b.z < a.z;
		}
		Vector3 centre()const {
			return Vector3((a.x + b.x) * .5f, (a.y + b.y) * .5f, (a.z + b.z) * .5f);
		}
		Vector3 corner(int n)const {
			return Vector3(((n & 1) ? b : a).x, ((n & 2) ? b : a).y, ((n & 4) ? b : a).z);
		}
		void update(const Vector3& q) {
			if (q.x < a.x) a.x = q.x; if (q.y < a.y) a.y = q.y; if (q.z < a.z) a.z = q.z;
			if (q.x > b.x) b.x = q.x; if (q.y > b.y) b.y = q.y; if (q.z > b.z) b.z = q.z;
		}
		void update(const Box& q) {
			if (q.a.x < a.x) a.x = q.a.x; if (q.a.y < a.y) a.y = q.a.y; if (q.a.z < a.z) a.z = q.a.z;
			if (q.b.x > b.x) b.x = q.b.x; if (q.b.y > b.y) b.y = q.b.y; if (q.b.z > b.z) b.z = q.b.z;
		}
		bool overlaps(const Box& q)const {
			return
				(b.x < q.b.x ? b.x : q.b.x) >= (a.x > q.a.x ? a.x : q.a.x) &&
				(b.y < q.b.y ? b.y : q.b.y) >= (a.y > q.a.y ? a.y : q.a.y) &&
				(b.z < q.b.z ? b.z : q.b.z) >= (a.z > q.a.z ? a.z : q.a.z);
		}
		void expand(float n) {
			a.x -= n; a.y -= n; a.z -= n; b.x += n; b.y += n; b.z += n;
		}
		float width()const {
			return b.x - a.x;
		}
		float height()const {
			return b.y - a.y;
		}
		float depth()const {
			return b.z - a.z;
		}
		bool contains(const Vector3& q) {
			return q.x >= a.x && q.x <= b.x && q.y >= a.y && q.y <= b.y && q.z >= a.z && q.z <= b.z;
		}
	};



	class MathTransform {
		static MathTransform tmps[64];
		static MathTransform& alloc_tmp() { static int tmp = 0; return tmps[tmp++ & 63]; }
	public:
		Matrix m;
		Vector3 v;



		MathTransform() {
		}
		MathTransform(const Matrix& m) :m(m) {
		}
		MathTransform(const Vector3& v) :v(v) {
		}
		MathTransform(const Matrix& m, const Vector3& v) :m(m), v(v) {
		}
		MathTransform& operator-()const {
			MathTransform& t = alloc_tmp();
			t.m = -m; t.v = t.m * -v;
			return t;
		}
		MathTransform& operator~()const {
			MathTransform& t = alloc_tmp();
			t.m = ~m; t.v = t.m * -v;
			return t;
		}
		Vector3 operator*(const Vector3& q)const {
			return m * q + v;
		}
		Line operator*(const Line& q)const {
			Vector3 t = (*this) * q.o;
			return Line(t, (*this) * (q.o + q.d) - t);
		}
		Box operator*(const Box& q)const {
			Box t((*this * q.corner(0)));
			for (int k = 1; k < 8; ++k) t.update(*this * q.corner(k));
			return t;
		}
		MathTransform& operator*(const MathTransform& q)const {
			MathTransform& t = alloc_tmp();
			t.m = m * q.m; t.v = m * q.v + v;
			return t;
		}
		bool operator==(const MathTransform& q)const {
			return m == q.m && v == q.v;
		}
		bool operator!=(const MathTransform& q)const {
			return !operator==(q);
		}


	};

	class MathF
	{
	public:
		static float DegreesFromRadians(float r)
		{
			return r * 180.0f / 3.141592653589793238463f;
		}

		static float RadiansFromDegrees(float d)
		{
			return d * 3.141592653589793238463f / 180;
		}
		static float transformRadius(float r, const Matrix& t) {
			static const float sq_3 = sqrtf(1.0f / 3.0f);
			return (t * Vector3(sq_3, sq_3, sq_3)).length() * r;
		}

		static Matrix pitchMatrix(float q) {
			return Matrix(Vector3(1, 0, 0), Vector3(0, cosf(q), sinf(q)), Vector3(0, -sinf(q), cosf(q)));
		}

		static Matrix yawMatrix(float q) {
			return Matrix(Vector3(cosf(q), 0, sinf(q)), Vector3(0, 1, 0), Vector3(-sinf(q), 0, cosf(q)));
		}

		static Matrix rollMatrix(float q) {
			return Matrix(Vector3(cosf(q), sinf(q), 0), Vector3(-sinf(q), cosf(q), 0), Vector3(0, 0, 1));
		}

		static float matrixPitch(const Matrix& m) {
			return m.k.pitch();
			//	return asinf( -m.k.y );
		}

		static float matrixYaw(const Matrix& m) {
			return m.k.yaw();
			//return atan2f( -m.k.x,m.k.z );
		}

		static float matrixRoll(const Matrix& m) {
			return atan2f(m.i.y, m.j.y);
			//Matrix t=pitchMatrix( -matrixPitch(m) )*yawMatrix( -matrixYaw(m) )*m;
			//return atan2f( t.i.y,t.i.x );
		}

		static Matrix scaleMatrix(float x, float y, float z) {
			return Matrix(Vector3(x, 0, 0), Vector3(0, y, 0), Vector3(0, 0, z));
		}

		static Matrix scaleMatrix(const Vector3& scale) {
			return Matrix(Vector3(scale.x, 0, 0), Vector3(0, scale.y, 0), Vector3(0, 0, scale.z));
		}

		static Quaternion pitchQuat(float p) {
			return Quaternion(cosf(p / -2), Vector3(sinf(p / -2), 0, 0));
		}

		static Quaternion yawQuat(float y) {
			return Quaternion(cosf(y / 2), Vector3(0, sinf(y / 2), 0));
		}

		static Quaternion rollQuat(float r) {
			return Quaternion(cosf(r / -2), Vector3(0, 0, sinf(r / -2)));
		}

		static Quaternion rotationQuat(float p, float y, float r) {
			return yawQuat(y) * pitchQuat(p) * rollQuat(r);
		}

		//Quaternion rotationQuat(float p, float y, float r);

		static Matrix rotationMatrix(float p, float y, float r) {
			return yawMatrix(y) * pitchMatrix(p) * rollMatrix(r);
		}

		static Matrix rotationMatrix(const Vector3& rot) {
			return yawMatrix(rot.y) * pitchMatrix(rot.x) * rollMatrix(rot.z);
		}

		static float quatPitch(const Quaternion& q) {
			return q.k().pitch();
		}

		static float quatYaw(const Quaternion& q) {
			return q.k().yaw();
		}

		static float quatRoll(const Quaternion& q) {
			//	Vector i=q.i(),j=q.j();
			//	return atan2f( i.y,j.y );
			return matrixRoll(q);
		}

		static Quaternion matrixQuat(const Matrix& p) {
			Matrix m = p;
			m.orthogonalize();
			float t = m.i.x + m.j.y + m.k.z, w, x, y, z;
			if (t > EPSILON) {
				t = sqrtf(t + 1) * 2;
				x = (m.k.y - m.j.z) / t;
				y = (m.i.z - m.k.x) / t;
				z = (m.j.x - m.i.y) / t;
				w = t / 4;
			}
			else if (m.i.x > m.j.y&& m.i.x > m.k.z) {
				t = sqrtf(m.i.x - m.j.y - m.k.z + 1) * 2;
				x = t / 4;
				y = (m.j.x + m.i.y) / t;
				z = (m.i.z + m.k.x) / t;
				w = (m.k.y - m.j.z) / t;
			}
			else if (m.j.y > m.k.z) {
				t = sqrtf(m.j.y - m.k.z - m.i.x + 1) * 2;
				x = (m.j.x + m.i.y) / t;
				y = t / 4;
				z = (m.k.y + m.j.z) / t;
				w = (m.i.z - m.k.x) / t;
			}
			else {
				t = sqrtf(m.k.z - m.j.y - m.i.x + 1) * 2;
				x = (m.i.z + m.k.x) / t;
				y = (m.k.y + m.j.z) / t;
				z = t / 4;
				w = (m.j.x - m.i.y) / t;
			}
			return Quaternion(w, Vector3(x, y, z));
		}


	};


	
	

}