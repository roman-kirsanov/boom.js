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
 * @property {string} ret
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
    { glType: 'GLint', stdType: 'std::int32_t'}
]

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
            [`const ${glType} *`, `${glType} const* `],
            [`const ${glType}`, `${glType} const`],
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
            .replace('mask', 'Mask')
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
         * @type {string[]}
         */
        const [ , name, value ] = match.match(REGEXP);
        if (name && value) {
            return {
                match,
                glName: name,
                boomName: defNameToBoomName(name),
                value
            }
        } else {
            abort(`Failed to extract definition info from "${match}"`);
        }
    })
}

/**
 * @param {string} content
 * @returns {Func[]}
 */
const extractFuncs = content => {
    const REGEXP = new RegExp(/typedef\s+(.+)\s+\(APIENTRY.*\)\((.*)\);\s*\nGLAPI\s*.*\s*glad_(.*);/);
    return (content.match(new RegExp(REGEXP, 'g')) ?? []).map(match => {
        /**
         * @type {string[]}
         */
        const [ , ret, args, name ] = match.match(REGEXP);
        if (ret && args && name) {
            return {
                match,
                name,
                ret,
                args: (
                    args.split(',')
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
                )
            }
        } else {
            abort(`Failed to extract function info from "${match}"`);
        }
    })
}

// Main...
(() => {
    const content = readFileSync(__dirname + '/glad.h').toString();
    const funcs = extractFuncs(content);
    const defs = extractDefs(content);
    console.log(inspect(defs, { depth: 999, colors: true }));
})()