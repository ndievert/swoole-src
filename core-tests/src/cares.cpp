#ifdef SW_USE_CARES
#include "tests.h"
#include "cares.h"

using namespace swoole;
using namespace std;

TEST(cares, resolve)
{
    coro_test([](void *arg)
    {
        auto result = CAres::resolve("www.swoole.com", AF_INET, 5);
        ASSERT_EQ(result, "47.244.108.17");
    });
}

TEST(cares, resolve_timeout)
{
    coro_test([](void *arg)
    {
        auto result = CAres::resolve("www.swoole.com", AF_INET, 0.001);
        ASSERT_EQ(result, "");
    });
}

TEST(cares, resolve_inet6)
{
    coro_test([](void *arg)
    {
        auto result = CAres::resolve("ipv6.sjtu.edu.cn", AF_INET6, 5);
        ASSERT_EQ(result, "2001:da8:8000:1::80");
    });
}

TEST(cares, concurrency)
{
    coroutine_func_t fns[3];
    
    fns[0] = [](void *arg)
    {
        auto result = CAres::resolve("www.swoole.com", AF_INET, 5);
        ASSERT_EQ(result, "47.244.108.17");
    };

    fns[1] = [](void *arg)
    {
        auto result = CAres::resolve("www.swoole.com", AF_INET, 0.001);
        ASSERT_EQ(result, "");
    };

    fns[2] = [](void *arg)
    {
        auto result = CAres::resolve("ipv6.sjtu.edu.cn", AF_INET6, 5);
        ASSERT_EQ(result, "2001:da8:8000:1::80");
    };

    coro_test(fns, 3);
}
#endif