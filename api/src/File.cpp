#include <cassert>
#include <iostream>
#include <Boom/File.hpp>
#include <Boom/Utilities.hpp>
#include <Boom/API/File.hpp>

namespace boom::api {

static boom::js::ValueRef FileEntryToValue(boom::js::ContextRef context, boom::FileEntry fileEntry) {
    if (context == nullptr) {
        boom::Abort("ERROR: boom::js::FileEntryToValue() failed: \"context\" cannot be nullptr");
    }
    return boom::js::Value::Object(context, {
        { "exists", boom::js::Value::Boolean(context, fileEntry.exists) },
        { "isFile", boom::js::Value::Boolean(context, fileEntry.isFile) },
        { "isSymlink", boom::js::Value::Boolean(context, fileEntry.isSymlink) },
        { "isDirectory", boom::js::Value::Boolean(context, fileEntry.isDirectory) },
        { "createdAt", boom::js::Value::Number(context, fileEntry.createdAt) },
        { "modifiedAt", boom::js::Value::Number(context, fileEntry.modifiedAt) },
        { "accessedAt", boom::js::Value::Number(context, fileEntry.accessedAt) },
        { "size", boom::js::Value::Number(context, fileEntry.size) }
    });
}

void InitFileAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    static auto const ctor = [](boom::js::ScopeRef scope) {
        try {
            auto const path = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const mode = [&]{
                try {
                    auto const arg = scope->getArg(1);
                    if (arg->isObject()) {
                        auto const read = arg->getProperty("read")->isEqual(boom::js::Value::Boolean(scope->context(), true));
                        auto const write = arg->getProperty("write")->isEqual(boom::js::Value::Boolean(scope->context(), true));
                        ;
                        return 0;
                    } else if (arg->isUndefined()) {
                        ;
                        return 0;
                    } else {
                        throw boom::Error("");
                    }
                } catch (boom::Error& e) {
                    throw e.extend("Second argument must be an object or undefined");
                }
            }();
            ;
        } catch (boom::Error& e) {
            throw e.extend("Failed to create a File");
        }
        return boom::js::Value::Undefined(scope->context());
    };

    static auto const exists = [](boom::js::ScopeRef scope) {
        try {
            auto const path = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const exists = boom::FileExists(path);
            return boom::js::Value::Boolean(scope->context(), exists);
        } catch (boom::Error& e) {
            throw e.extend("Failed to check file exists");
        }
    };

    static auto const info = [](boom::js::ScopeRef scope) {
        try {
            auto const path = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            return boom::api::FileEntryToValue(
                scope->context(),
                boom::FileInfo(path)
            );
        } catch (boom::Error& e) {
            throw e.extend("Failed to get file info");
        }
    };

    static auto const isFile = [](boom::js::ScopeRef scope) {
        try {
            auto const path = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const isFile = boom::FileIsFile(path);
            return boom::js::Value::Boolean(scope->context(), isFile);
        } catch (boom::Error& e) {
            throw e.extend("Failed to check file is file");
        }
    };

    static auto const isDirectory = [](boom::js::ScopeRef scope) {
        try {
            auto const path = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const isDirectory = boom::FileIsDirectory(path);
            return boom::js::Value::Boolean(scope->context(), isDirectory);
        } catch (boom::Error& e) {
            throw e.extend("Failed to check file is directory");
        }
    };

    static auto const isSymlink = [](boom::js::ScopeRef scope) {
        try {
            auto const path = [&]{
                try {
                    return scope->getArg(0)->stringValue();
                } catch (boom::Error& e) {
                    throw e.extend("First argument must be a string");
                }
            }();
            auto const isSymlink = boom::FileIsSymlink(path);
            return boom::js::Value::Boolean(scope->context(), isSymlink);
        } catch (boom::Error& e) {
            throw e.extend("Failed to check file is symlink");
        }
    };

    auto fileProto = boom::js::Value::Object(context);
    fileProto->setProperty("Info", boom::js::Value::Function(context, info), { .readOnly = true });
    fileProto->setProperty("Exists", boom::js::Value::Function(context, exists), { .readOnly = true });
    fileProto->setProperty("IsFile", boom::js::Value::Function(context, isFile), { .readOnly = true });
    fileProto->setProperty("IsSymlink", boom::js::Value::Function(context, isSymlink), { .readOnly = true });
    fileProto->setProperty("IsDirectory", boom::js::Value::Function(context, isDirectory), { .readOnly = true });

    auto fileClass = boom::js::Value::Function(context, ctor);
    fileClass->setPrototypeOf(fileProto);

    context->globalThis()->setProperty("File", fileClass);
}

} /* namespace boom::api */