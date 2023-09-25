#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

int main(int argc, char const *argv[], char const *envp[]) {

    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, argv, argc, envp);

    auto result = context->evaluate("process.exit(-1);");

    return 0;
}
