const { readFileSync } = require('fs');

/**
 * @typedef {Object} TypeMap
 * @property {string} glType
 * @property {string} stdType
 *
 * @typedef {Object} Def
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
 * @property {string} name
 * @property {Arg[]} args
 * @property {string} returns
 */

/**
 * @type {TypeMap[]}
 */
const TYPE_MAP = [
    { glType: 'GLvoid', stdType: 'void'},
    { glType: 'GLenum', stdType: 'std::uint32_t'},
    { glType: 'GLboolean', stdType: 'std::uint8_t'},
    { glType: 'GLbitfield', stdType: 'std::uint32_t'},
    { glType: 'GLbyte', stdType: 'std::int32_t'},
    { glType: 'GLubyte', stdType: 'std::uint8_t'},
    { glType: 'GLshort', stdType: 'std::int16_t'},
    { glType: 'GLushort', stdType: 'std::uint16_t'},
    { glType: 'GLint', stdType: 'std::int32_t'},
    { glType: 'GLuint', stdType: 'std::uint32_t'},
    { glType: 'GLclampx', stdType: 'std::int32_t'},
    { glType: 'GLsizei', stdType: 'std::int32_t'},
    { glType: 'GLfloat', stdType: 'float'},
    { glType: 'GLclampf', stdType: 'float'},
    { glType: 'GLdouble', stdType: 'double'},
    { glType: 'GLclampd', stdType: 'double'},
    { glType: 'GLeglClientBufferEXT', stdType: 'void*'},
    { glType: 'GLeglImageOES', stdType: 'void*'},
    { glType: 'GLchar', stdType: 'char'},
    { glType: 'GLcharARB', stdType: 'char'},
    { glType: 'GLhalf', stdType: 'std::uint16_t'},
    { glType: 'GLhalfARB', stdType: 'std::uint16_t'},
    { glType: 'GLfixed', stdType: 'std::int32_t'},
    { glType: 'GLintptr', stdType: 'std::intptr_t'},
    { glType: 'GLintptrARB', stdType: 'std::intptr_t'},
    { glType: 'GLsizeiptr', stdType: 'std::int64_t'},
    { glType: 'GLsizeiptrARB', stdType: 'std::int64_t'},
    { glType: 'GLint64', stdType: 'std::int64_t'},
    { glType: 'GLint64EXT', stdType: 'std::int64_t'},
    { glType: 'GLuint64', stdType: 'std::uint64_t'},
    { glType: 'GLuint64EXT', stdType: 'std::uint64_t'},
    { glType: 'GLsync', stdType: 'void*'},
    { glType: 'GLDEBUGPROC', stdType: 'void*'}
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
 *
 * @param {string} type
 * @returns {string}
 */
const formatArgType = type => {
    for (const { glType } of TYPE_MAP) {
        if (type === `const ${glType} *`) return `${glType} const*`;
        else if (type === `const ${glType} *`) return `${glType} const`;
        else if (type === `const ${glType}`) return `${glType} const`;
        else if (type === `${glType} *`) return `${glType}*`;
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
    const REGEXP = new RegExp(/#define\s+GL_([^\s]+)\s+(0x[0-9a-fA-F]+)/);
    return (content.match(new RegExp(REGEXP, 'g')) ?? []).map(match => {
        const [ , name, value ] = match.match(REGEXP);
        if (name && value) {
            return {
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
    const REGEXP = new RegExp(/typedef\s+([^\s]+)\s+\(APIENTRY.*\)\((.*)\);\s*\nGLAPI\s*.*\s*glad_(.*);/);
    return (content.match(new RegExp(REGEXP, 'g')) ?? []).map(match => {
        const [ , returns, args, name ] = match.match(REGEXP);
        if (returns && args && name) {
            return {
                name,
                args: args.split(',').map(i => i.trim()),
                returns
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
    console.log(funcs);
})()

