#include <boost/test/unit_test.hpp>
#include <osgviz/Dummy.hpp>

using namespace osgviz;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    osgviz::DummyClass dummy;
    dummy.welcome();
}
