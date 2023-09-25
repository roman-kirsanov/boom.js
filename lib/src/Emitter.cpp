#include <Boom/Emitter.hpp>

namespace boom {

std::int64_t __EmitterNextId() {
    static auto __nextid = 1000ll;
    return __nextid++;
}

} /* namespace boom */
