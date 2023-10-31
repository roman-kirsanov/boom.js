const { writeFileSync } = require('fs');
const { defs, funcs } = require(__dirname + '/defs.json');

const TYPE_MAP = [
    ['GLvoid', 'void'],
    ['GLenum', 'std::uint32_t'],
    ['GLboolean', 'std::uint8_t'],
    ['GLbitfield', 'std::uint32_t'],
    ['GLbyte', 'std::int32_t'],
    ['GLubyte', 'std::uint8_t'],
    ['GLshort', 'std::int16_t'],
    ['GLushort', 'std::uint16_t'],
    ['GLint', 'std::int32_t'],
    ['GLuint', 'std::uint32_t'],
    ['GLclampx', 'std::int32_t'],
    ['GLsizei', 'std::int32_t'],
    ['GLfloat', 'float'],
    ['GLclampf', 'float'],
    ['GLdouble', 'double'],
    ['GLclampd', 'double'],
    ['GLeglClientBufferEXT', 'void*'],
    ['GLeglImageOES', 'void*'],
    ['GLchar', 'char'],
    ['GLcharARB', 'char'],
    ['GLhalf', 'std::uint16_t'],
    ['GLhalfARB', 'std::uint16_t'],
    ['GLfixed', 'std::int32_t'],
    ['GLintptr', 'std::intptr_t'],
    ['GLintptrARB', 'std::intptr_t'],
    ['GLsizeiptr', 'std::int64_t'],
    ['GLsizeiptrARB', 'std::int64_t'],
    ['GLint64', 'std::int64_t'],
    ['GLint64EXT', 'std::int64_t'],
    ['GLuint64', 'std::uint64_t'],
    ['GLuint64EXT', 'std::uint64_t'],
    ['GLsync', 'void*'],
    ['GLDEBUGPROC', 'void*']
];

for (const [ from, to ] of [ ...TYPE_MAP ]) {
    TYPE_MAP.push([ `${from}*`, `${to}*` ]);
    TYPE_MAP.push([ `${from}**`, `${to}**` ]);
    TYPE_MAP.push([ `${from} const*`, `${to} const*` ]);
    TYPE_MAP.push([ `${from} const**`, `${to} const**` ]);
    TYPE_MAP.push([ `${from} const* const*`, `${to} const* const*` ]);
}

const retype = type => {
    for (const [ from, to ] of TYPE_MAP) {
        if (type === from) {
            return to;
        }
    }
    return type;
}

const formatName = name => (name[2].toLowerCase() + name.slice(3));

const formatArgs = args => (
    args.split(',')
        .map(i => i.trim())
        .map(i => i.replace(/\ \*/g, '* '))
        .map(i => i.split(' '))
        .map(parts => [ parts.slice(0, -1).join(' '), ...parts.slice(-1) ])
        .map(([ type, name ]) => ([
            retype(type),
            name
        ]))
)

if (process.argv.includes('--defs')) {
    const convertName = value => {
        let sliced = value.slice(3);
        let result = '';
        for (let i = 0; i < sliced.length; i++) {
            if (i === 0) {
                result += sliced[i].toUpperCase();
            } else if (sliced[i] === '_') {
                i += 1;
                result += sliced[i].toUpperCase();
            } else {
                result += sliced[i].toLowerCase();
            }
        }
        return ('OpenGL' + result);
    }

    for (const def of defs) {
        console.log(`auto constexpr ${convertName(def.name)} = ${def.value};`);
    }
}

if (process.argv.includes('--check-types')) {
    const types = [];
    for (const func of funcs) {
        const args = formatArgs(func.args);
        for (const [ type ] of args) {
            if (!types.includes(retype(type))) {
                types.push(retype(type));
            }
        }
    }
    console.log(types);
}

if (process.argv.includes('--check-names')) {
    const errors = [];
    for (const func of funcs) {
        const args = formatArgs(func.args);
        for (const [ , name ] of args) {
            if (name.includes('*')) {
                if (!errors.includes(name)) {
                    errors.push(name);
                }
            }
        }
    }
    console.log(errors);
}

if (process.argv.includes('--methods-def')) {
    for (const func of funcs) {
        const name = formatName(func.name)
        const args = formatArgs(func.args);
        console.log(`void ${name}(${args.map(([ type, name ]) => `${type} ${name}`).join(', ')});`);
    }
}

if (process.argv.includes('--methods-impl')) {
    for (const func of funcs) {
        const name = formatName(func.name)
        const args = formatArgs(func.args);
        console.log(`void OpenGL::${name}(${args.map(([ type, name ]) => `${type} ${name}`).join(', ')}) {`);
        console.log(`    _current();`);
        console.log(`    boom::${func.name}(${args.map(([ , name ]) => name).join(', ')});`);
        console.log(`}`);
        console.log('');
    }
}