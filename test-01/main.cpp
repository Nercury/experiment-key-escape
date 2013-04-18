//#include <functional>

//using namespace std;

template<typename ... Args>
struct Event {
};

int main(int argc, char* argv[])
{
	//auto a = new other();

	/*std::function<void(std::string)> f;
	std::function<void(std::string)>::*/

	Event<int> e;

	/*e.addHandler(std::bind(&other::myhandler, a, std::placeholders::_1));*/

	//e.invoke("world");

	//delete a;

	return 0;
}
