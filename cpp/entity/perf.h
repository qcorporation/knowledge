#include <chrono>

using namespace std::chrono;

class Perf
{
public:
    Perf() = default;
    virtual ~Perf() = default;

    void start_timer()
    {
        perf_begin = steady_clock::now();
    }
    void end_timer()
    {
        perf_end = steady_clock::now();
    }

    template <typename duration>
    int64_t diff()
    {
        return duration_cast<duration>(perf_end - perf_begin).count();
    }

protected:
    steady_clock::time_point perf_begin{};
    steady_clock::time_point perf_end{};
};