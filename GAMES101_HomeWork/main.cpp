#include <iostream>
#include <cmath>
#include <Eigen/Core>
#include <Eigen/Geometry>

int main()
{
	/*std::cout << "vector:" << std::endl;
	Eigen::Vector3f v1(1.0f, 2.0f, 3.0f);
	Eigen::Vector3f v2(1.0f, 2.0f, 4.0f);

	std::cout << v1 << std::endl;
	std::cout << v1 + v2 << std::endl;
	std::cout << v1 * 2 << std::endl;

	std::cout << "dot:" << std::endl;
	std::cout << v1.dot(v2) << std::endl;
	std::cout << "cross:" << std::endl;

	Eigen::Vector3f v3 = v1.cross(v2);
	std::cout << v3 << std::endl;

	Eigen::Matrix3f i, j;
	i << 1.0, 2.0, 3.0,
		4.0, 5.0, 6.0,
		7.0, 8.0, 9.0;
	j << 2.0, 3.0, 1.0,
		4.0, 6.0, 5.0,
		9.0, 7.0, 8.0;
	std::cout << "matrix" << std::endl;
	std::cout << i << std::endl;
	std::cout << i + j << std::endl;
	std::cout << i * j << std::endl;
	std::cout << (i * v1).transpose() << std::endl;*/
	


	/* 作业描述:
	*  给定一个点 P=(2, 1)，先逆时针旋转45度，再平移(1,2)计算变换后的坐标
	*/


	#define PI 3.1415926f

	Eigen::Vector3f p(2.0, 1.0, 1.0);
	Eigen::Matrix3f r, t;
	r << std::cos(PI / 4), -std::sin(PI / 4), 0,
		std::sin(PI / 4), std::cos(PI / 4), 0,
		0, 0, 1;
	t << 1, 0, 1,
		0, 1, 2,
		0, 0, 1;
	std::cout << r << std::endl;
	std::cout << "-------" << std::endl;
	std::cout << t * (r * p) << std::endl;
		 
	std::cin.get();
}