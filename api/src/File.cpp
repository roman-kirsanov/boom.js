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

static boom::js::ValueRef FileExists(boom::js::ContextRef context) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });
}

static boom::js::ValueRef FileInfo(boom::js::ContextRef context) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });
}

static boom::js::ValueRef FileIsFile(boom::js::ContextRef context) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });
}

static boom::js::ValueRef FileIsDirectory(boom::js::ContextRef context) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });
}

static boom::js::ValueRef FileIsSymlink(boom::js::ContextRef context) {
    assert(context != nullptr);
    return boom::js::Value::Function(context, [](boom::js::ScopeRef scope) {
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
    });
}

void InitFileAPI(boom::js::ContextRef context) {
    assert(context != nullptr);

    context->globalThis()->setProperty("FileInfo", boom::api::FileInfo(context), { .readOnly = true });
    context->globalThis()->setProperty("FileExists", boom::api::FileExists(context), { .readOnly = true });
    context->globalThis()->setProperty("FileIsFile", boom::api::FileIsFile(context), { .readOnly = true });
    context->globalThis()->setProperty("FileIsSymlink", boom::api::FileIsSymlink(context), { .readOnly = true });
    context->globalThis()->setProperty("FileIsDirectory", boom::api::FileIsDirectory(context), { .readOnly = true });
}

} /* namespace boom::api */