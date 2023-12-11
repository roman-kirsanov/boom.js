// @ts-check

const libfs = require('fs');
const libxmldom = require(__dirname + '/xmldom');

/**
 * @typedef {(
 *   'CoreProfile_32' |
 *   'CoreProfile_33' |
 *   'CoreProfile_40' |
 *   'CoreProfile_41' |
 *   'CoreProfile_42' |
 *   'CoreProfile_43' |
 *   'CoreProfile_44' |
 *   'CoreProfile_45' |
 *   'CoreProfile_46' |
 *   'CompatibilityProfile_32' |
 *   'CompatibilityProfile_33' |
 *   'CompatibilityProfile_40' |
 *   'CompatibilityProfile_41' |
 *   'CompatibilityProfile_42' |
 *   'CompatibilityProfile_43' |
 *   'CompatibilityProfile_44' |
 *   'CompatibilityProfile_45' |
 *   'CompatibilityProfile_46' |
 *   'ES_10' |
 *   'ES_11' |
 *   'ES_20' |
 *   'ES_30' |
 *   'ES_31' |
 *   'ES_32'
 * )} Version
 *
 * @typedef {{
 *   name: string;
 *   value: string;
 *   versions: Version[];
 *   extensions: string[];
 * }} Define
 *
 * @typedef {{
 *   name: string;
 * } & ({
 *   type: 'scalar';
 *   variant: {
 *     platform: string;
 *     name: string;
 *   }[];
 * } | {
 *   type: 'struct';
 *   fields: {
 *     name: string;
 *     type: Type;
 *   }[];
 * } | {
 *   type: 'function';
 *   params: Proto[];
 *   returns: Proto;
 * })} Type
 *
 * @typedef {{
 *   name: string;
 *   type: Type;
 *   qualifiers: string[];
 * }} Proto
 *
 * @typedef {{
 *   name: string;
 *   params: Proto[];
 *   returns: Proto;
 *   versions: Version[];
 *   extensions: string[];
 * }} Func
 */

/**
 * @param {string} name
 * @returns {Type}
 */
const getType = name => {
    const type = TYPES.find(t => t.name === name);
    if (type) return type;
    else throw new Error(`Type "${name}" not found`);
}

/** @type {Type[]} */
const TYPES = [];

TYPES.push({ name: 'void', type: 'scalar', variant: [{ platform: '*', name: 'void' }] });
TYPES.push({ name: 'GLint', type: 'scalar', variant: [{ platform: '*', name: 'std::int32_t' }] });
TYPES.push({ name: 'GLuint', type: 'scalar', variant: [{ platform: '*', name: 'std::uint32_t' }] });
TYPES.push({ name: 'GLsizei', type: 'scalar', variant: [{ platform: '*', name: 'std::int32_t' }] });
TYPES.push({ name: 'GLchar', type: 'scalar', variant: [{ platform: '*', name: 'char' }] });
TYPES.push({ name: 'GLcharARB', type: 'scalar', variant: [{ platform: '*', name: 'char' }] });
TYPES.push({ name: 'GLboolean', type: 'scalar', variant: [{ platform: '*', name: 'std::uint8_t' }] });
TYPES.push({ name: 'GLbitfield', type: 'scalar', variant: [{ platform: '*', name: 'std::uint32_t' }] });
TYPES.push({ name: 'GLvoid', type: 'scalar', variant: [{ platform: '*', name: 'void' }] });
TYPES.push({ name: 'GLbyte', type: 'scalar', variant: [{ platform: '*', name: 'std::int8_t' }] });
TYPES.push({ name: 'GLubyte', type: 'scalar', variant: [{ platform: '*', name: 'std::uint8_t' }] });
TYPES.push({ name: 'GLshort', type: 'scalar', variant: [{ platform: '*', name: 'std::int16_t' }] });
TYPES.push({ name: 'GLushort', type: 'scalar', variant: [{ platform: '*', name: 'std::uint16_t' }] });
TYPES.push({ name: 'GLclampx', type: 'scalar', variant: [{ platform: '*', name: 'std::int32_t' }] });
TYPES.push({ name: 'GLclampf', type: 'scalar', variant: [{ platform: '*', name: 'float' }] });
TYPES.push({ name: 'GLdouble', type: 'scalar', variant: [{ platform: '*', name: 'double' }] });
TYPES.push({ name: 'GLclampd', type: 'scalar', variant: [{ platform: '*', name: 'double' }] });
TYPES.push({ name: 'GLfloat', type: 'scalar', variant: [{ platform: '*', name: 'float' }] })
TYPES.push({ name: 'GLenum', type: 'scalar', variant: [{ platform: '*', name: 'std::uint32_t' }] });
TYPES.push({ name: 'GLhalf', type: 'scalar', variant: [{ platform: '*', name: 'std::uint16_t' }] });
TYPES.push({ name: 'GLhalfARB', type: 'scalar', variant: [{ platform: '*', name: 'std::uint16_t' }] });
TYPES.push({ name: 'GLfixed', type: 'scalar', variant: [{ platform: '*', name: 'std::int32_t' }] });
TYPES.push({ name: 'GLintptr', type: 'scalar', variant: [{ platform: '*', name: 'std::intptr_t' }] });
TYPES.push({ name: 'GLintptrARB', type: 'scalar', variant: [{ platform: '*', name: 'std::intptr_t' }] });
TYPES.push({ name: 'GLsizeiptrARB', type: 'scalar', variant: [{ platform: '*', name: 'std::ssize_t' }] });
TYPES.push({ name: 'GLint64', type: 'scalar', variant: [{ platform: '*', name: 'std::int64_t' }] });
TYPES.push({ name: 'GLint64EXT', type: 'scalar', variant: [{ platform: '*', name: 'std::int64_t' }] });
TYPES.push({ name: 'GLuint64', type: 'scalar', variant: [{ platform: '*', name: 'std::uint64_t' }] });
TYPES.push({ name: 'GLuint64EXT', type: 'scalar', variant: [{ platform: '*', name: 'std::uint64_t' }] });
TYPES.push({ name: 'GLsync', type: 'scalar', variant: [{ platform: '*', name: 'void*' }] });
TYPES.push({ name: 'GLeglImageOES', type: 'scalar', variant: [{ platform: '*', name: 'void*' }] });
TYPES.push({ name: 'GLeglClientBufferEXT', type: 'scalar', variant: [{ platform: '*', name: 'void*' }] });
TYPES.push({ name: 'GLhalfNV', type: 'scalar', variant: [{ platform: '*', name: 'std::uint16_t' }] });
TYPES.push({ name: 'GLvdpauSurfaceNV', type: 'scalar', variant: [{ platform: '*', name: 'std::intptr_t' }] });
TYPES.push({ name: 'struct _cl_context', type: 'scalar', variant: [{ platform: '*', name: 'void*' }] });
TYPES.push({ name: 'struct _cl_event', type: 'scalar', variant: [{ platform: '*', name: 'void*' }] });

TYPES.push({ name: 'GLsizeiptr', type: 'scalar', variant: [{ platform: 'windows-x64', name: 'std::int64_t' },
                                                           { platform: 'windows-arm64', name: 'std::int64_t' },
                                                           { platform: '*', name: 'long' }] });

TYPES.push({ name: 'GLhandleARB', type: 'scalar', variant: [{ platform: 'macos-*', name: 'void*' },
                                                            { platform: '*', name: 'std::uint32_t' }] });

TYPES.push({
    name: 'GLsync',
    type: 'struct',
    fields: []
});

TYPES.push({
    name: 'GLDEBUGPROC',
    type: 'function',
    returns: { name: 'GLDEBUGPROC', type: getType('void'), qualifiers: ['*'] },
    params: [
        { name: 'source', type: getType('GLenum'), qualifiers: [] },
        { name: 'type', type: getType('GLenum'), qualifiers: [] },
        { name: 'id', type: getType('GLuint'), qualifiers: [] },
        { name: 'severity', type: getType('GLenum'), qualifiers: [] },
        { name: 'length', type: getType('GLsizei'), qualifiers: [] },
        { name: 'message', type: getType('GLchar'), qualifiers: ['const', '*'] },
        { name: 'userParam', type: getType('void'), qualifiers: ['const', '*'] }
    ]
});

TYPES.push({
    name: 'GLDEBUGPROCARB',
    type: 'function',
    returns: { name: 'GLDEBUGPROCARB', type: getType('void'), qualifiers: ['*'] },
    params: [
        { name: 'source', type: getType('GLenum'), qualifiers: [] },
        { name: 'type', type: getType('GLenum'), qualifiers: [] },
        { name: 'id', type: getType('GLuint'), qualifiers: [] },
        { name: 'severity', type: getType('GLenum'), qualifiers: [] },
        { name: 'length', type: getType('GLsizei'), qualifiers: [] },
        { name: 'message', type: getType('GLchar'), qualifiers: ['const', '*'] },
        { name: 'userParam', type: getType('void'), qualifiers: ['const', '*'] }
    ]
});

TYPES.push({
    name: 'GLDEBUGPROCKHR',
    type: 'function',
    returns: { name: 'GLDEBUGPROCKHR', type: getType('void'), qualifiers: ['*'] },
    params: [
        { name: 'source', type: getType('GLenum'), qualifiers: [] },
        { name: 'type', type: getType('GLenum'), qualifiers: [] },
        { name: 'id', type: getType('GLuint'), qualifiers: [] },
        { name: 'severity', type: getType('GLenum'), qualifiers: [] },
        { name: 'length', type: getType('GLsizei'), qualifiers: [] },
        { name: 'message', type: getType('GLchar'), qualifiers: ['const', '*'] },
        { name: 'userParam', type: getType('void'), qualifiers: ['const', '*'] }
    ]
});

TYPES.push({
    name: 'GLDEBUGPROCAMD',
    type: 'function',
    returns: { name: 'GLDEBUGPROCAMD', type: getType('void'), qualifiers: ['*'] },
    params: [
        { name: 'id', type: getType('GLuint'), qualifiers: [] },
        { name: 'category', type: getType('GLenum'), qualifiers: [] },
        { name: 'severity', type: getType('GLenum'), qualifiers: [] },
        { name: 'length', type: getType('GLsizei'), qualifiers: [] },
        { name: 'message', type: getType('GLchar'), qualifiers: ['const', '*'] },
        { name: 'userParam', type: getType('void'), qualifiers: ['const', '*'] }
    ]
});

TYPES.push({
    name: 'GLVULKANPROCNV',
    type: 'function',
    returns: { name: 'GLVULKANPROCNV', type: getType('void'), qualifiers: ['*'] },
    params: []
});

/**
 * @param {Document} spec
 * @returns {void}
 */
const parseSpec = spec => {
    /**
     * @param {ChildNode} node
     * @returns {node is Element}
     */
    const nodeIsElement = node => {
        if (node.nodeType === node.ELEMENT_NODE) {
            return true;
        } else {
            return false;
        }
    }

    /**
     * @param {Element} parent
     * @param {string} tagName
     * @returns {Element[]}
     */
    const getElementsByTagName = (parent, tagName) => {
        /** @type {Element[]} */
        const ret = [];
        for (let i = 0; i < parent.childNodes.length; i++) {
            const node = parent.childNodes.item(i);
            if (nodeIsElement(node) && node.tagName === tagName) {
                ret.push(node);
            }
        }
        return ret;
    }

    /**
     * @param {Element} element
     * @returns {Proto}
     */
    const parseProto = element => {
        /** @type {string} */
        let name = '';
        /** @type {Type} */
        let type = getType('void');
        /** @type {string[]} */
        let qualifiers = [];
        /** @type {string} */
        let qualifiersTest = '';
        for (let i = 0; i < element.childNodes.length; i++) {
            const node = element.childNodes.item(i);
            if (nodeIsElement(node)) {
                if (node.tagName === 'ptype') {
                    type = getType(node.textContent ?? '');
                } else if (node.tagName === 'name') {
                    name = (node.textContent ?? '');
                }
            } else {
                const tokens = (node.textContent ?? '').trim().toLowerCase().split(/(\*)|(\w+)/);
                for (const token of tokens) {
                    if ((token === 'const') || (token === '*')) {
                        qualifiers.push(token);
                        qualifiersTest += token;
                    }
                }
            }
        }
        if (qualifiers.join('') !== qualifiersTest) {
            throw new Error(`Qualifiers parsing is not correct, parsed: ${qualifiers.join('')}, should be: ${qualifiersTest}`);
        }
        return {
            name,
            type,
            qualifiers
        }
    }

    /**
     * @param {Element} element
     * @returns {Func}
     */
    const parseCommand = element => {
        const [ protoElement ] = getElementsByTagName(element, 'proto');
        const [ ...paramElements ] = getElementsByTagName(element, 'param');
        if (!protoElement) {
            throw new Error('<proto /> element not found');
        }
        const proto = parseProto(protoElement);
        const params = paramElements.map(p => parseProto(p));
        return {
            name: proto.name,
            params,
            returns: proto,
            versions: [],
            extensions: []
        }
    }

    /**
     * @param {Element} element
     * @returns {Define}
     */
    const parseDefine = element => {
        return {
            name: (element.getAttribute('name') ?? ''),
            value: (element.getAttribute('value') ?? ''),
            versions: [],
            extensions: []
        }
    }

    /** @type {Define[]} */
    const defines = [];

    /** @type {Func[]} */
    const funcs = [];

    const enumsElements = getElementsByTagName(spec.documentElement, 'enums');
    for (const enumsElement of enumsElements) {
        const enumElements = getElementsByTagName(enumsElement, 'enum');
        for (const enumElement of enumElements) {
            const define = parseDefine(enumElement);
            defines.push(define);
        }
    }

    const [ commandsElement ] = getElementsByTagName(spec.documentElement, 'commands');
    if (commandsElement) {
        const commandElements = getElementsByTagName(commandsElement, 'command');
        for (const commandElement of commandElements) {
            const func = parseCommand(commandElement);
            funcs.push(func);
        }
    }

    libfs.writeFileSync(__dirname + '/spec.json', JSON.stringify({ defines, funcs }, null, 4));
}

try {
    const data = libfs.readFileSync(__dirname + '/gl.xml').toString();
    const xmldoc = new libxmldom.DOMParser().parseFromString(data, 'text/xml');
    const parsed = parseSpec(xmldoc);
} catch (e) {
    console.error('ERROR: ' + e.message);
}