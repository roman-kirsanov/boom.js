#include <iostream>
#include <Boom.hpp>
#include <Boom/API.hpp>

int main(int argc, char const *argv[], char const *envp[]) {

    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, argv, argc, envp);


    auto function = boom::js::Value::Function(context, [](auto context, auto thisObject, auto arguments) {
        thisObject->setProperty("_prop1", boom::js::Value::String(context, "value1"));
        thisObject->setProperty("_prop2", boom::js::Value::String(context, "value2"));
        return boom::js::Value::Undefined(context);
    });

    function->setProperty("prototype", boom::js::Value::Object(context, {
        { "getProp1", boom::js::Value::Function(context, [](auto context, auto thisObject, auto arguments) { return thisObject->getProperty("_prop1"); }) }
    }));

    context->globalThis()->setProperty("Test", function);

    auto result = context->evaluate(
        "process.stdout.write(JSON.stringify({ ...Test }, null, 4));\n"
        "const v = new Test();\n"
        "process.stdout.write(JSON.stringify(v, null, 4));\n"
        "process.stdout.write(v.getProp1())"
    );

    if (result.has_value() == false) {
        std::cerr << result.error()->toString().value() << std::endl;
    }

    auto exit = false;
    auto app = boom::MakeShared<boom::App>();

    app->onExit([&]() { exit = true; });

    for (;;) {
        app->pollEvents();

        if (exit) {
            break;
        }
    }

    return 0;
}
