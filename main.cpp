
#include <iterator>
#include <utility>
#include <vector>
#include <iostream>
#include <numeric>
#include <thread>

using namespace std;

template <typename It, typename UFunc, typename BFunc>
auto map_reduce(It p, It q, UFunc f1, BFunc f2,  size_t threads) -> decltype(f2(f1(*p), f1(*p)))
{
    using RetType = decltype(f2(f1(*p), f1(*p)));
    vector<RetType> t_res(threads);
    int length = distance(p, q);

    auto eval_part = [&t_res](size_t ret_ind, It p, It q, UFunc f1, BFunc f2)
    {
        auto res = f1(*p);
        while (++p != q)
            res = f2(res, f1(*p));
        t_res[ret_ind] = res;
    };
    
    vector<thread> t(threads);
    
    for (size_t i = 0; i < threads; i++)
    {
        auto p1 = p;
        auto q1 = p;
        advance(p1, static_cast<int>(i * length / threads));
        advance(q1, static_cast<int>((i + 1) * length / threads));
        t[i] = thread(eval_part, i, p1, q1, ref(f1), ref(f2));
    }
    for (size_t i = 0; i < threads; i++)
        t[i].join();

  //return accumulate(next(t_res.begin()), t_res.end(), t_res[0], f2);
  
    auto res = *t_res.begin();
    
    for (auto i = ++t_res.begin(); i != t_res.end(); i++)
        res = f2(res, *i);
    
    return res;
}
