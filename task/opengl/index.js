const { readFileSync } = require('fs');

/**
 * @typedef {Object} TypeMap
 * @property {string} glType
 * @property {string} boomType
 *
 * @typedef {Object} Def
 * @property {string} match
 * @property {string} glName
 * @property {string} boomName
 * @property {string} jsName
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
    { glType: 'GLeglClientBufferEXT', boomType: 'boom::OpenGLEGLClientBufferEXT'},
    { glType: 'GLeglImageOES', boomType: 'boom::OpenGLEGLImageOES'},
    { glType: 'GLsizeiptrARB', boomType: 'boom::OpenGLSizeiptrARB'},
    { glType: 'GLDEBUGPROC', boomType: 'boom::OpenGLDebugProc'},
    { glType: 'GLintptrARB', boomType: 'boom::OpenGLIntptrARB'},
    { glType: 'GLuint64EXT', boomType: 'boom::OpenGLUInt64EXT'},
    { glType: 'GLbitfield', boomType: 'boom::OpenGLBitfield'},
    { glType: 'GLsizeiptr', boomType: 'boom::OpenGLSizeiptr'},
    { glType: 'GLint64EXT', boomType: 'boom::OpenGLInt64EXT'},
    { glType: 'GLboolean', boomType: 'boom::OpenGLBoolean'},
    { glType: 'GLcharARB', boomType: 'boom::OpenGLCharARB'},
    { glType: 'GLhalfARB', boomType: 'boom::OpenGLHalfARB'},
    { glType: 'GLintptr', boomType: 'boom::OpenGLIntptr'},
    { glType: 'GLushort', boomType: 'boom::OpenGLUShort'},
    { glType: 'GLclampx', boomType: 'boom::OpenGLClampx'},
    { glType: 'GLclampf', boomType: 'boom::OpenGLClampf'},
    { glType: 'GLclampd', boomType: 'boom::OpenGLClampd'},
    { glType: 'GLdouble', boomType: 'boom::OpenGLDouble'},
    { glType: 'GLuint64', boomType: 'boom::OpenGLUInt64'},
    { glType: 'GLint64', boomType: 'boom::OpenGLInt64'},
    { glType: 'GLfixed', boomType: 'boom::OpenGLFixed'},
    { glType: 'GLubyte', boomType: 'boom::OpenGLUbyte'},
    { glType: 'GLshort', boomType: 'boom::OpenGLShort'},
    { glType: 'GLsizei', boomType: 'boom::OpenGLSizei'},
    { glType: 'GLfloat', boomType: 'boom::OpenGLFloat'},
    { glType: 'GLchar', boomType: 'boom::OpenGLChar'},
    { glType: 'GLhalf', boomType: 'boom::OpenGLHalf'},
    { glType: 'GLsync', boomType: 'boom::OpenGLSync'},
    { glType: 'GLvoid', boomType: 'boom::OpenGLVoid'},
    { glType: 'GLenum', boomType: 'boom::OpenGLEnum'},
    { glType: 'GLbyte', boomType: 'boom::OpenGLByte'},
    { glType: 'GLuint', boomType: 'boom::OpenGLUint'},
    { glType: 'GLint', boomType: 'boom::OpenGLInt'},
    { glType: 'void', boomType: 'void' }
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
    for (const { glType, boomType: stdType } of TYPE_MAP) {
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
                jsName: name.slice(3),
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
            + `        boom::Abort("boom::OpenGL::${name}() failed: OpenGL function \\"gl${capitalize(name)}\\" not loaded");\n`
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
const makeConstsCpp = defs => {
    return [
        `auto constexpr kOpenGLTrue = 1;`,
        `auto constexpr kOpenGLFalse = 0;`,
        ...defs.map(({ boomName, value }) => `auto constexpr k${boomName} = ${value};`)
    ]
}

/**
 * @param {Def[]} defs
 * @returns {string[]}
 */
const makeConstsJs = defs => {
    return [
        `readonly TRUE = 1;`,
        `readonly FALSE = 0;`,
        ...defs.map(({ jsName, value }) => `readonly ${jsName} = ${value};`)
    ]
}

/**
 * @param {Func[]} funcs
 * @param {'win32' | 'macos' | 'xlib'} lib
 * @returns {string}
 */
const makeLoader = (funcs, lib) => {
    if (lib === 'win32') {
        return funcs.map(({ name }) => {
            return `boom::gl${capitalize(name)} = (boom::OpenGL${capitalize(name)}Fn)wglGetProcAddress("gl${capitalize(name)}");`
        }).join('\n');
    } else if (lib === 'macos') {
        return funcs.map(({ name }) => {
            return `boom::gl${capitalize(name)} = gl${capitalize(name)};`
        }).join('\n');
    } else if (lib === 'xlib') {
        return '';
    } else {
        return '';
    }
}

// Main...
(() => {
    const content = readFileSync(__dirname + '/glad.h').toString();
    const funcs = extractFuncs(content);
    const defs = extractDefs(content);
    if (process.argv.includes('--consts-js')) {
        const consts = makeConstsJs(defs);
        console.log(consts.join('\n'));
    } else if (process.argv.includes('--consts-cpp')) {
        const consts = makeConstsCpp(defs);
        console.log(consts.join('\n'));
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
    } else if (process.argv.includes('--loader-win32')) {
        console.log(makeLoader(funcs, 'win32'));
    } else if (process.argv.includes('--loader-macos')) {
        console.log(makeLoader(funcs, 'macos'));
    } else if (process.argv.includes('--loader-xlib')) {
        console.log(makeLoader(funcs, 'xlib'));
    } else {
        abort("Specify a command");
    }
})()