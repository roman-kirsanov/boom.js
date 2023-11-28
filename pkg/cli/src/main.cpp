#include <cassert>
#include <optional>
#include <iostream>
#include <Boom/Error.hpp>
#include <Boom/Utilities.hpp>
#include "Help/Help.hpp"
#include "Init/Init.hpp"
#include "Run/Run.hpp"

int main(int argc, char const* argv[], char const* envp[]) {
    try {
        auto const envs = boom::ParseEnvs(envp);
        auto const args = boom::ParseArgs(argv, argc);
        auto const command = boom::ItemOr(args, 1, std::string());
        auto const subargs = boom::Slice(args, 2);

        if (command == "run") boom::cli::Run(envs, subargs);
        else if (command == "init") boom::cli::Init(envs, subargs);
        else if (command == "help") boom::cli::Help(envs, subargs);
        else boom::cli::Help(envs, subargs);
    } catch (boom::Error& e) {
        boom::Abort(e.what());
    }
    return 0;
}