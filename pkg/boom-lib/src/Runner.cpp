#include <Boom/File.hpp>
#include <Boom/Error.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/Application.hpp>
#include <Boom/API.hpp>

int main(int argc, char const* argv[], char const* envp[]) {
    try {
        auto const envs = boom::ParseEnvs(envp);
        auto const args = boom::ParseArgs(argv, argc);

        if (args.size() < 2) {
            boom::Abort("File path must be specified");
        }
        if (boom::File::Exists(args[1]) == false) {
            boom::Abort("File not found at path \"" + args[0] + "\"");
        }

        auto const script = boom::File::Read(args[0])->toString();
        auto const context = boom::MakeShared<boom::js::Context>();

        boom::api::InitProcessAPI(context, args, envs);
        boom::api::InitConsoleAPI(context);
        boom::api::InitFileAPI(context);
        boom::api::InitApplicationAPI(context);
        boom::api::InitWindowAPI(context);
        boom::api::InitViewAPI(context);

        context->evaluate(script);

        boom::Application::Default()->run();
    } catch (boom::Error& e) {
        boom::Abort(e.what());
    }

    return 0;
}