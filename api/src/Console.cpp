#include <cassert>
#include <iostream>
#include <Boom/API/Console.hpp>

namespace boom::api {

void InitConsoleAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    static auto const log = [](boom::js::ScopeRef scope) {
        for (std::size_t i = 0; i < scope->argCount(); i++) {
            try {
                auto string = scope->getArg(i)->toString();
                if (i != 0) {
                    std::cout << " ";
                }
                std::cout << string;
            } catch (boom::Error& e) {}
        }
        std::cout << std::endl;
        return boom::js::Value::Undefined(scope->context());
    };

    auto console = boom::js::Value::Object(context);
    console->setProperty("log", boom::js::Value::Function(context, log), { .readOnly = true });
    context->globalThis()->setProperty("console", console);
}

} /* namespace boom::api */