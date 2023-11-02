const { readFileSync } = require('fs');
const { inspect } = require('util');

/**
 * @typedef {Object} TypeMap
 * @property {string} glType
 * @property {string} stdType
 *
 * @typedef {Object} Def
 * @property {string} match
 * @property {string} glName
 * @property {string} boomName
 * @property {string} value
 *
 * @typedef {Object} Arg
 * @property {string} name
 * @property {string} glType
 * @property {string} stdType
 *
 * @typedef {Object} Func
 * @property {string} match
 * @property {string} name
 * @property {Arg[]} args
 * @property {string} glRet
 * @property {string} stdRet
 * @property {string} type
 */

/**
 * @type {TypeMap[]}
 */
const TYPE_MAP = [
    // order matters !
    { glType: 'GLeglClientBufferEXT', stdType: 'void*'},
    { glType: 'GLeglImageOES', stdType: 'void*'},
    { glType: 'GLsizeiptrARB', stdType: 'std::int64_t'},
    { glType: 'GLDEBUGPROC', stdType: 'void*'},
    { glType: 'GLintptrARB', stdType: 'std::intptr_t'},
    { glType: 'GLuint64EXT', stdType: 'std::uint64_t'},
    { glType: 'GLbitfield', stdType: 'std::uint32_t'},
    { glType: 'GLsizeiptr', stdType: 'std::int64_t'},
    { glType: 'GLint64EXT', stdType: 'std::int64_t'},
    { glType: 'GLboolean', stdType: 'std::uint8_t'},
    { glType: 'GLcharARB', stdType: 'char'},
    { glType: 'GLhalfARB', stdType: 'std::uint16_t'},
    { glType: 'GLintptr', stdType: 'std::intptr_t'},
    { glType: 'GLushort', stdType: 'std::uint16_t'},
    { glType: 'GLclampx', stdType: 'std::int32_t'},
    { glType: 'GLclampf', stdType: 'float'},
    { glType: 'GLclampd', stdType: 'double'},
    { glType: 'GLdouble', stdType: 'double'},
    { glType: 'GLuint64', stdType: 'std::uint64_t'},
    { glType: 'GLint64', stdType: 'std::int64_t'},
    { glType: 'GLfixed', stdType: 'std::int32_t'},
    { glType: 'GLubyte', stdType: 'std::uint8_t'},
    { glType: 'GLshort', stdType: 'std::int16_t'},
    { glType: 'GLsizei', stdType: 'std::int32_t'},
    { glType: 'GLfloat', stdType: 'float'},
    { glType: 'GLchar', stdType: 'char'},
    { glType: 'GLhalf', stdType: 'std::uint16_t'},
    { glType: 'GLsync', stdType: 'void*'},
    { glType: 'GLvoid', stdType: 'void'},
    { glType: 'GLenum', stdType: 'std::uint32_t'},
    { glType: 'GLbyte', stdType: 'std::int32_t'},
    { glType: 'GLuint', stdType: 'std::uint32_t'},
    { glType: 'GLint', stdType: 'std::int32_t'},
    { glType: 'void', stdType: 'void' }
]

/**
 * @param {string} text
 * @returns {string}
 */
const capitalize = text => {
    if (text.length > 0) {
        return text[0].toUpperCase() + text.slice(1);
    } else {
        return '';
    }
}

/**
 * @param {string} text
 * @returns {string}
 */
const decapitalize = text => {
    if (text.length > 0) {
        return text[0].toLowerCase() + text.slice(1);
    } else {
        return '';
    }
}

/**
 * @param {string} message
 * @returns {never}
 */
const abort = message => {
    console.log('ERROR:', message);
    process.exit(-1);
}

/**
 * @param {string} type
 * @returns {string}
 */
const formatArg = type => {
    for (const { glType } of TYPE_MAP) {
        const fromTo = [
            [`const ${glType} *const*`, `${glType} const* const* `],
            [`const ${glType} *`, `${glType} const* `],
            [`const ${glType}`, `${glType} const`],
            [`${glType} **`, `${glType}** `],
            [`${glType} *`, `${glType}* `]
        ];
        for (const [ from, to ] of fromTo) {
            if (type.includes(from)) {
                return type.replace(from, to);
            }
        }
    }
    return type;
}

/**
 * @param {string} type
 * @returns {string}
 */
const convertType = type => {
    for (const { glType, stdType } of TYPE_MAP) {
        const fromTo = [
            [`${glType} const* const*`, `${stdType} const* const*`],
            [`${glType} const*`, `${stdType} const*`],
            [`${glType} const`, `${stdType} const`],
            [`${glType}*`, `${stdType}*`],
            [glType, stdType]
        ];
        for (const [ from, to ] of fromTo) {
            if (type === from) {
                return to;
            }
        }
    }
    return type;
}

/**
 * @param {string} name
 * @returns {string}
 */
const defNameToBoomName = name => {
    return ('OpenGL' + (
        name.toLowerCase()
            .slice(3)
            .split('_')
            .map(word => word.charAt(0).toUpperCase() + word.slice(1))
            .join('')
            .replace('Rgba', 'RGBA')
            .replace('Rgb', 'Rgb')
            .replace('Bgra', 'BGRA')
            .replace('Brg', 'BGR')
            .replace('Lsb', 'LSB')
            .replace('Srgb', 'SRGB')
            .replace('mask', 'Mask')
            .replace('1d', '1D')
            .replace('2d', '2D')
            .replace('3d', '3D')
    ))
}

/**
 * @param {string} content
 * @returns {Def[]}
 */
const extractDefs = content => {
    const REGEXP = new RegExp(/#define\s+(GL_.+)\s+(0x[0-9a-fA-F]+)/);
    return (content.match(new RegExp(REGEXP, 'g')) ?? []).map(match => {
        /**
         * @type {(string | undefined)[]}
         */
        const [ , name, value ] = match.match(REGEXP);
        if (name && value) {
            return {
                match,
                glName: name,
                boomName: defNameToBoomName(name),
                value: value.toLowerCase()
            }
        } else {
            abort(`Failed to extract definition info from "${match}"`);
        }
    }).sort((a, b) => {
        if ( a.boomName < b.boomName ){
            return -1;
        } else if ( a.boomName > b.boomName ){
            return 1;
        } else {
            return 0;
        }
    })
}

/**
 * @param {string} content
 * @returns {Func[]}
 */
const extractFuncs = content => {
    const REGEXP = new RegExp(/typedef\s+(.+)\s+\(APIENTRY.*\)\((.*)\);\s*\nGLAPI\s*.*\s*glad_gl(.*);/);
    return (content.match(new RegExp(REGEXP, 'g')) ?? []).map(match => {
        /**
         * @type {(string | undefined)[]}
         */
        const [ , glRet, signature, name ] = match.match(REGEXP);
        if (glRet && signature && name) {
            const stdRet = convertType(formatArg(glRet).trim());
            const args = (
                signature
                    .split(',')
                    .map(i => i.trim())
                    .map(i => formatArg(i))
                    .map(i => {
                        const parts = i.split(' ');
                        const type = parts.slice(0, -1).join(' ');
                        const name = parts.slice(-1)[0];
                        return {
                            name,
                            glType: type,
                            stdType: convertType(type)
                        }
                    })
            );
            if ((args.length === 1)
            && (args[0].name.trim() === 'void')) {
                args.splice(0, 1);
            }
            return {
                match,
                name: decapitalize(name),
                glRet,
                stdRet,
                type: `${stdRet} (*)(${args.map(a => a.stdType).join(', ')})`,
                args
            }
        } else {
            abort(`Failed to extract function info from "${match}"`);
        }
    }).sort((a, b) => {
        if ( a.name < b.name ){
            return -1;
        } else if ( a.name > b.name ){
            return 1;
        } else {
            return 0;
        }
    })
}

/**
 * @param {Func[]} funcs
 * @returns {string[]}
 */
const reportTypes = funcs => {
    /**
     * @type {string[]}
     */
    const res = [];
    for (const { args } of funcs) {
        for (const { glType, stdType } of args) {
            const rec = `${glType.padEnd(18, ' ')} ->  ${stdType}`;
            if (!res.includes(rec)) {
                res.push(rec);
            }
        }
    }
    return res;
}

/**
 * @param {Func[]} funcs
 * @returns {string[]}
 */
const makeTypes = funcs => {
    return funcs.map(({ name, type }) => `using OpenGL${capitalize(name)}Fn = ${type};`)
}

/**
 * @param {Func[]} funcs
 * @returns {string[]}
 */
const makeVars = funcs => {
    return funcs.map(({ name }) => `boom::OpenGL${capitalize(name)}Fn gl${capitalize(name)} = nullptr;`)
}

/**
 * @param {Func[]} funcs
 * @returns {string[]}
 */
const makeExterns = funcs => {
    return funcs.map(({ name }) => `extern boom::OpenGL${capitalize(name)}Fn gl${capitalize(name)};`)
}

/**
 * @param {Func[]} funcs
 * @returns {string[]}
 */
const makeMethodsHpp = funcs => {
    return funcs.map(({ name, args, stdRet }) => `${stdRet} ${name}(${args.map(a => `${a.stdType} ${a.name}`).join(', ')}) const;`)
}

/**
 * @param {Func[]} funcs
 * @returns {string[]}
 */
const makeMethodsCpp = funcs => {
    return funcs.map(({ name, args, stdRet }) => {
        return`${stdRet} OpenGL::${name}(${args.map(a => `${a.stdType} ${a.name}`).join(', ')}) const {\n`
            + `#ifndef NDEBUG\n`
            + `    if (boom::gl${capitalize(name)} == nullptr) {\n`
            + `        boom::Abort("ERROR: boom::OpenGL::${name}() failed: OpenGL function \\"gl${capitalize(name)}\\" not loaded");\n`
            + `    }\n`
            + `#endif\n`
            + `    _current();\n`
            + `    ${stdRet !== 'void' ? 'return ' : ''}boom::gl${capitalize(name)}(${args.map(a => a.name).join(', ')});\n`
            + `}`;
    })
}

/**
 * @param {Def[]} defs
 * @returns {string[]}
 */
const makeConsts = defs => {
    return [
        `auto constexpr OpenGLTrue = 1;`,
        `auto constexpr OpenGLFalse = 0;`,
        ...defs.map(({ boomName, value }) => `auto constexpr ${boomName} = ${value};`)
    ]
}

/**
 * @param {Func[]} funcs
 * @param {'win32' | 'macos' | 'xlib'} lib
 * @returns {string}
 */
const makeLoader = (funcs, lib) => {
    return funcs.map(({ name }) => {
        return `boom::gl${capitalize(name)} = (boom::OpenGL${capitalize(name)}Fn)wglGetProcAddress("gl${capitalize(name)}");`
    }).join('\n');
}

// Main...
(() => {
    const content = readFileSync(__dirname + '/glad.h').toString();
    const funcs = extractFuncs(content);
    const defs = extractDefs(content);
    if (process.argv.includes('--consts')) {
        const contest = makeConsts(defs);
        console.log(contest.join('\n'));
    } else if (process.argv.includes('--types')) {
        const types = makeTypes(funcs);
        console.log(types.join('\n'));
    } else if (process.argv.includes('--externs')) {
        const externs = makeExterns(funcs);
        console.log(externs.join('\n'));
    } else if (process.argv.includes('--vars')) {
        const vars = makeVars(funcs);
        console.log(vars.join('\n'));
    } else if (process.argv.includes('--methods-hpp')) {
        const hpp = makeMethodsHpp(funcs);
        console.log(hpp.join('\n'));
    } else if (process.argv.includes('--methods-cpp')) {
        const cpp = makeMethodsCpp(funcs);
        console.log(cpp.join('\n\n'));
    } else if (process.argv.includes('--loader')) {
        console.log(makeLoader(funcs, 'win32'));
    } else {
        abort("Specify a command");
    }
})()