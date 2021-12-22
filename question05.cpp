//Question 5 - Class Inheritance, const correctness and operator overloading

// Task 1 : Add a Circle class that has a center point and radius fields, create a base Shape class that both Circle and Rectangle inherit from,
// try to move as many common field/functions to the base class

// Task 2: Create an operator overload that will allow us to chain a point instance to a ostream (std::cout), for example:
////Point point1(5,7);
////std::cout << point1;
//The previous line should output "5/7" to the console

// Task 3: Review the const correctness of the Shape/Circle/Rectangle member functions and modify them where it's required

// Do not change the main function body - it should compile and run without any modifications after completion of all tasks  


#include <iostream>
#include <vector>
#include <string>
#include <cmath>


struct Point {
    int x;
    int y;

	Point()
	{
        x = 0;
        y = 0;
    }

	Point(int x_, int y_)
	{
        x = x_;
        y = y_;
    }
};

inline std::ostream& operator<<(std::ostream& os, const Point& point)
{
    os << point.x << '/' << point.y ;
    return os;
}

struct Size {
    int width;
    int height;

	Size()
    {
        this->width = 0;
        this->height = 0;
    }

	Size(int width_, int height_)
    {
        width = width_;
        height = height_;
    }
};

class Shape{
protected:
    Point point_center;
public:
    explicit Shape(Point p){
        point_center = p;
    }
    virtual std::string name() const = 0;
    virtual Point center() const{
        return point_center;
    }
    virtual size_t area() const = 0;
};

class Rectangle: public Shape{
protected:
    Point m_center;
    Size m_size;

public:

	Rectangle(const Point& center, const Size& size) : Shape(center)
	{
        m_center = center;
        m_size = size;
	}

	const Size& size() {
		return m_size;
	}

	 size_t area() const override{
		return m_size.width *(size_t)m_size.height;
	}

    std::string name() const override{
        return "Rectangle";
    }

};


class Circle: public Shape {
protected:
    float radius;

public:
    Circle(const Point& center, float radius) : Shape(center)
    {
        this->radius = radius;
    }

    std::string name() const override{
        return "Circle";
    }

    size_t area() const override{
        return M_PI * (radius*radius);
    }
};

int main(int argc, char** argv)
{
	//Do not change anything in this function body
	Circle circle1(Point(5, 5), 10);
	Rectangle rect1(Point(5, 5), Size(10, 10));
	Circle circle2(Point(8, 8), 4);

	std::vector<Shape*> shapes{&circle1, &rect1, &circle2};
	for (const Shape* shape : shapes) {
		std::cout << "Shape: " << shape->name() << " center: " << shape->center() << " area: " << shape->area() << std::endl;
	}

	std::cout << "Press enter to exit" << std::endl;
	getchar();
	return 0;
}