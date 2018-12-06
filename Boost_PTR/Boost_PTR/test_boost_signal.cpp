#include <boost/signal.hpp>
#include <boost/bind.hpp>
#include <iostream> 
#include <typeinfo>

void signalCallback()
{
	std::cout << "signalFunc" << std::endl;
}

void func1()
{
	std::cout << "Hello" << std::flush;
}

void func2()
{
	std::cout << ", world!" << std::endl;
}

/*
int func1()
{
	return 1;
}

int func2()
{
	return 2;
}*/

/*
template <typename T>
struct min_element
{
	typedef T result_type;

	/ *template <typename InputIterator>
	T operator()(InputIterator first, InputIterator last) const
	{
		std::cout << "comb type: " << typeid(combT).name() << std::endl;
		return *std::min_element(first, last);
	}* /

	template <typename InputIterator>
	T operator()(InputIterator first, InputIterator last) const
	{
		std::cout << "input type: " << typeid(first).name() << std::endl;
		auto combT = T(first, last);
		std::cout << "comb type: " << typeid(combT).name() << std::endl;
		return combT;
	}
};*/

class world
{
public:
	void func()
	{
		std::cout << "world::func" << std::endl;
	}
protected:
private:
};

extern void signalFunc()
{
	/*boost::signal<void()> s;
	s.connect(signalCallback);
	s();*/

	/*boost::signal<void()> s;
	s.connect(func1);
	s.connect(func2);
	s();
	s();*/

	/*boost::signal<int(), min_element<int> > s;
	s.connect(func1);
	s.connect(func2);
	std::cout << s() << std::endl;*/
	
	/*boost::signal<int(), min_element<std::vector<int> > > s;
	s.connect(func1);
	s.connect(func2);
	std::vector<int> v = s();
	std::cout << *std::min_element(v.begin(), v.end()) << std::endl;
*/
	
	/*boost::signal<void()> s;
	boost::signals::connection c1 = s.connect(func1);
	auto c2 = s.connect(func2);
	c1.block();
	c2.block();
	s();

	c2.unblock();
	s();*/

	boost::signal<void ()> s;
	std::cout << s.num_slots() << std::endl;
	{
		std::auto_ptr<world> w(new world());
		s.connect(boost::bind(&world::func, w.get()));
	}
	std::cout << s.num_slots() << std::endl;
	s();
}
	
	

