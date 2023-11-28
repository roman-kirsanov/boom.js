#include <Boom/Application.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/Error.hpp>
#include <Boom/File.hpp>
#include <Boom/JS.hpp>
#include <Boom/API.hpp>
#include "Run.hpp"

namespace boom::cli {

void Run(std::map<std::string, std::string> const& envs, std::vector<std::string> const& args) {
    if (args.size() == 0) {
        boom::Abort("File path must be specified");
    }
    if (boom::File::Exists(args[0]) == false) {
        boom::Abort("File not found at path \"" + args[0] + "\"");
    }

    auto script = boom::File::Read(args[0])->toString();
    auto context = boom::MakeShared<boom::js::Context>();

    boom::api::InitProcessAPI(context, args, envs);
    boom::api::InitConsoleAPI(context);
    boom::api::InitFileAPI(context);
    boom::api::InitApplicationAPI(context);
    boom::api::InitWindowAPI(context);

    context->evaluate(script);

    boom::Application::Default()->run();
}

} /* namespace boom::cli */