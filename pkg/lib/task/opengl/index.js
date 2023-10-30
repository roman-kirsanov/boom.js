const { writeFileSync } = require('fs');
const { funcs } = require(__dirname + '/defs.json');

const byVersion = [];
const outputHpp = [];
const outputCpp = [];

(() => {
    for (const entry of funcs) {
        const versionObj = byVersion.find(v => v.version === entry.version);
        if (versionObj) {
            versionObj.entries.push(entry);
        } else {
            byVersion.push({
                version: entry.version,
                entries: [entry]
            });
        }
    }
})();

(() => {
    for (const versionEntry of byVersion) {
        for (const entry of versionEntry.entries) {
            outputHpp.push(`using GL${entry.name.slice(2)} = void(*)(${entry.args});`);
        }
    }
    outputHpp.push('');
    for (const versionEntry of byVersion) {
        for (const entry of versionEntry.entries) {
            entry.type = `GL${entry.name.slice(2)}`;
            outputHpp.push(`extern ${entry.type} ${entry.name};`);
            outputCpp.push(`${entry.type} ${entry.name} = nullptr;`);
        }
    }
    outputHpp.push('');
    outputHpp.push('enum class OpenGLVersion {');
    for (const versionEntry of byVersion) {
        outputHpp.push(`    CoreProfile_${versionEntry.version} = ${versionEntry.version},`);
    }
    outputHpp.push('};');
    outputHpp.push('');
    outputHpp.push('void glLoad(boom::OpenGLVersion);');
    outputCpp.push('');
    outputCpp.push('void* glLoadFunc(char const* name) {');
    outputCpp.push('    if (auto res = wglGetProcAddress(name)) {');
    outputCpp.push('        return res;');
    outputCpp.push('    } else {');
    outputCpp.push('        std::cerr << "ERROR: glLoadFunc() failed: Failed to load \\"" << name << "\\" function" << std::endl;');
    outputCpp.push('        std::abort();');
    outputCpp.push('    }');
    outputCpp.push('}');
    outputCpp.push('');
    outputCpp.push('void glLoad(boom::OpenGLVersion version) {');
    for (const versionEntry of byVersion) {
        outputCpp.push(`    if (version < ${versionEntry.version}) return;`);
        for (const entry of versionEntry.entries) {
            outputCpp.push(`    ${entry.name} = (${entry.type})glLoadFunc("${entry.name}");`);
        }
    }
    outputCpp.push('}');
})()

writeFileSync(__dirname + '/OpenGL.hpp', outputHpp.join('\n'));
writeFileSync(__dirname + '/OpenGL.cpp', outputCpp.join('\n'));