#include <cassert>
#include <iostream>
#include <Boom/API/Console.hpp>

namespace boom::api {

void InitConsoleAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    static auto const log = [](boom::js::ScopeRef scope) {
        for (std::size_t i = 0; i < scope->argCount(); i++) {
            auto string = scope->getArg(i)->stringValue();
            if (string) {
                if (i != 0) {
                    std::cout << " ";
                }
                std::cout << string.value();
            }
        }
        std::cout << std::endl;
    };

    auto console = boom::js::Value::Object(context);
    console->setProperty("log", boom::js::Value::Function(context, log), { .readOnly = true }).value();
}

} /* namespace boom::api */