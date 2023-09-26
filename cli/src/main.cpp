#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

int main(int argc, char const *argv[], char const *envp[]) {

    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, argv, argc, envp);

    auto result = context->evaluate("JSON.stringify(process, null, 4)");
    if (result) {
        std::cout << result.value()->toString().value() << std::endl;
    } else {
        std::cerr << result.error()->toString().value() << std::endl;
    }

    return 0;
}
