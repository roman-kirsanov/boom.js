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
 * }} Define
 *
 * @typedef {{
 *   name: string;
 *   type: string;
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
 *
 * @typedef {{
 *   defines: Define[];
 *   funcs: Func[];
 * }} Spec
 */

/** @type {{ glName: string; boomName: string; }[]} */
const TYPE_NAMES = [
    { glName: 'GLeglClientBufferEXT', boomName: 'boom::OpenGLEGLClientBufferEXT' },
    { glName: 'struct _cl_context', boomName: 'void*' },
    { glName: 'struct _cl_event', boomName: 'void*' },
    { glName: 'GLvdpauSurfaceNV', boomName: 'boom::OpenGLVdpauSurfaceNV' },
    { glName: 'GLDEBUGPROCAMD', boomName: 'boom::OpenGLDebugProcAMD' },
    { glName: 'GLDEBUGPROCARB', boomName: 'boom::OpenGLDebugProcARB' },
    { glName: 'GLDEBUGPROCKHR', boomName: 'boom::OpenGLDebugProcKHR' },
    { glName: 'GLVULKANPROCNV', boomName: 'boom::OpenGLVulkanProcNV' },
    { glName: 'GLeglImageOES', boomName: 'boom::OpenGLEGLImageOES' },
    { glName: 'GLsizeiptrARB', boomName: 'boom::OpenGLSizeiptrARB' },
    { glName: 'GLDEBUGPROC', boomName: 'boom::OpenGLDebugProc' },
    { glName: 'GLintptrARB', boomName: 'boom::OpenGLIntptrARB' },
    { glName: 'GLhandleARB', boomName: 'boom::OpenGLHandleARB' },
    { glName: 'GLuint64EXT', boomName: 'boom::OpenGLUInt64EXT' },
    { glName: 'GLbitfield', boomName: 'boom::OpenGLBitfield' },
    { glName: 'GLsizeiptr', boomName: 'boom::OpenGLSizeiptr' },
    { glName: 'GLint64EXT', boomName: 'boom::OpenGLInt64EXT' },
    { glName: 'GLboolean', boomName: 'boom::OpenGLBoolean' },
    { glName: 'GLcharARB', boomName: 'boom::OpenGLCharARB' },
    { glName: 'GLhalfARB', boomName: 'boom::OpenGLHalfARB' },
    { glName: 'GLhalfNV', boomName: 'boom::OpenGLHalfNV' },
    { glName: 'GLintptr', boomName: 'boom::OpenGLIntptr' },
    { glName: 'GLushort', boomName: 'boom::OpenGLUShort' },
    { glName: 'GLclampx', boomName: 'boom::OpenGLClampx' },
    { glName: 'GLclampf', boomName: 'boom::OpenGLClampf' },
    { glName: 'GLclampd', boomName: 'boom::OpenGLClampd' },
    { glName: 'GLdouble', boomName: 'boom::OpenGLDouble' },
    { glName: 'GLuint64', boomName: 'boom::OpenGLUInt64' },
    { glName: 'GLint64', boomName: 'boom::OpenGLInt64' },
    { glName: 'GLfixed', boomName: 'boom::OpenGLFixed' },
    { glName: 'GLubyte', boomName: 'boom::OpenGLUbyte' },
    { glName: 'GLshort', boomName: 'boom::OpenGLShort' },
    { glName: 'GLsizei', boomName: 'boom::OpenGLSizei' },
    { glName: 'GLfloat', boomName: 'boom::OpenGLFloat' },
    { glName: 'GLchar', boomName: 'boom::OpenGLChar' },
    { glName: 'GLhalf', boomName: 'boom::OpenGLHalf' },
    { glName: 'GLsync', boomName: 'boom::OpenGLSync' },
    { glName: 'GLvoid', boomName: 'boom::OpenGLVoid' },
    { glName: 'GLenum', boomName: 'boom::OpenGLEnum' },
    { glName: 'GLbyte', boomName: 'boom::OpenGLByte' },
    { glName: 'GLuint', boomName: 'boom::OpenGLUint' },
    { glName: 'GLint', boomName: 'boom::OpenGLInt' },
    { glName: 'void', boomName: 'void' }
]

/**
 * @param {Document} spec
 * @returns {Spec}
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
        /** @type {string} */
        let type = 'void';
        /** @type {string[]} */
        let qualifiers = [];
        /** @type {string} */
        let qualifiersTest = '';
        for (let i = 0; i < element.childNodes.length; i++) {
            const node = element.childNodes.item(i);
            if (nodeIsElement(node)) {
                if (node.tagName === 'ptype') {
                    type = (node.textContent ?? '');
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
            value: (element.getAttribute('value') ?? '')
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
    if (!commandsElement) {
        throw new Error('<commands /> element not found');
    }
    const commandElements = getElementsByTagName(commandsElement, 'command');
    for (const commandElement of commandElements) {
        const func = parseCommand(commandElement);
        funcs.push(func);
    }

    /** @type {Set<Func>} */
    const compatFuncs = new Set();
    /** @type {Set<Func>} */
    const coreFuncs = new Set();
    /** @type {Set<Func>} */
    const esFuncs = new Set();

    const featureElements = getElementsByTagName(spec.documentElement, 'feature');
    for (const featureElement of featureElements) {
        const api = (featureElement.getAttribute('api')?.toLowerCase() ?? '');
        const version = (featureElement.getAttribute('number')?.toLowerCase() ?? '').replace('.', '');

        if (api === 'gl') {
            const requireElements = getElementsByTagName(featureElement, 'require');
            for (const requireElement of requireElements) {
                const profile = requireElement.getAttribute('profile');
                const commandElements = getElementsByTagName(requireElement, 'command');
                for (const commandElement of commandElements) {
                    const func = funcs.find(f => f.name === commandElement.getAttribute('name'));
                    if (func) {
                        if (profile === 'compatibility') {
                            compatFuncs.add(func);
                        } else if (profile === 'core') {
                            coreFuncs.add(func);
                        } else {
                            compatFuncs.add(func);
                            coreFuncs.add(func);
                        }
                    } else {
                        throw new Error(`Function "${commandElement.getAttribute('name')}" not found`);
                    }
                }
            }

            const removeElements = getElementsByTagName(featureElement, 'remove');
            for (const removeElement of removeElements) {
                const profile = removeElement.getAttribute('profile');
                const commandElements = getElementsByTagName(removeElement, 'command');
                for (const commandElement of commandElements) {
                    const func = funcs.find(f => f.name === commandElement.getAttribute('name'));
                    if (func) {
                        if (profile === 'compatibility') {
                            compatFuncs.delete(func);
                        } else if (profile === 'core') {
                            coreFuncs.delete(func);
                        } else {
                            compatFuncs.delete(func);
                            coreFuncs.delete(func);
                        }
                    } else {
                        throw new Error(`Function "${commandElement.getAttribute('name')}" not found`);
                    }
                }
            }

            if (['10', '11', '12', '13', '14', '15', '20', '21', '30', '31'].includes(version) === false) {
                for (const func of compatFuncs) {
                    // @ts-ignore
                    func.versions.push(`CompatibilityProfile_${version}`);
                }
                for (const func of coreFuncs) {
                    // @ts-ignore
                    func.versions.push(`CoreProfile_${version}`);
                }
            }
        } else if ((api === 'gles1') || (api === 'gles2')) {
            const requireElements = getElementsByTagName(featureElement, 'require');
            for (const requireElement of requireElements) {
                const commandElements = getElementsByTagName(requireElement, 'command');
                for (const commandElement of commandElements) {
                    const func = funcs.find(f => f.name === commandElement.getAttribute('name'));
                    if (func) {
                        esFuncs.add(func);
                    } else {
                        throw new Error(`Function "${commandElement.getAttribute('name')}" not found`);
                    }
                }
            }

            const removeElements = getElementsByTagName(featureElement, 'remove');
            for (const removeElement of removeElements) {
                const commandElements = getElementsByTagName(removeElement, 'command');
                for (const commandElement of commandElements) {
                    const func = funcs.find(f => f.name === commandElement.getAttribute('name'));
                    if (func) {
                        esFuncs.delete(func);
                    } else {
                        throw new Error(`Function "${commandElement.getAttribute('name')}" not found`);
                    }
                }
            }

            for (const func of esFuncs) {
                // @ts-ignore
                func.versions.push(`ES_${version}`);
            }
        }
    }

    const [ extensionsElement ] = getElementsByTagName(spec.documentElement, 'extensions');
    if (!extensionsElement) {
        throw new Error('<extensions /> element not found');
    }
    const extensionElements = getElementsByTagName(extensionsElement, 'extension');
    for (const extensionElement of extensionElements) {
        const extension = (extensionElement.getAttribute('name') ?? '');
        const requireElements = getElementsByTagName(extensionElement, 'require');
        for (const requireElement of requireElements) {
            const commandElements = getElementsByTagName(requireElement, 'command');
            for (const commandElement of commandElements) {
                const name = (commandElement.getAttribute('name') ?? '');
                const func = funcs.find(f => f.name === name);
                if (func) {
                    func.extensions.push(extension);
                } else {
                    throw new Error(`Function "${name}" not found`);
                }
            }
        }
    }

    const dangling = funcs.filter(f => (f.extensions.length === 0) && (f.versions.length === 0));
    if (dangling.length > 0) {
        throw new Error(`Following functions have no version or extension: ${dangling.map(d => d.name).join(', ')}`);
    }

    /**
     * @param {{ name: string; }} a
     * @param {{ name: string; }} b
     * @requires {number}
     */
    const byName = (a, b) => {
        const nameA = a.name.toUpperCase();
        const nameB = b.name.toUpperCase();
        if (nameA < nameB) {
            return -1;
        } else if (nameA > nameB) {
            return 1;
        } else {
            return 0;
        }
    }

    defines.sort(byName);
    funcs.sort(byName);

    return { defines, funcs };
}

/**
 * @param {string} name
 * @returns {string}
 */
const toMethodName = name => {
    if (name.startsWith('gl')) {
        return (name.slice(2, 3).toLowerCase() + name.slice(3));
    } else {
        return name;
    }
}

/**
 * @param {string} name
 * @returns {string}
 */
const toTypeName = name => {
    const type = TYPE_NAMES.find(t => t.glName === name);
    if (type) {
        return type.boomName;
    } else {
        throw new Error(`Type name "${name}" not found`);
    }
}

/**
 * @param {Spec} spec
 * @returns {[string, string][]}
 */
const makeMethods = spec => {
    /** @type {[string, string][]} */
    const ret = [];
    for (const func of spec.funcs) {
        const name = toMethodName(func.name);
        const params = func.params.map(p => `${toTypeName(p.type)} ${p.name}`).join(', ');
        const calling = func.params.map(p => p.name).join(', ');
        const returns = toTypeName(func.returns.type);
        ret.push([
            `${returns} ${name}(${params});`,
            `${returns} OpenGL::${name}(${params}) {\n    if (_${name}Loaded == false) {\n        throw boom::Error("OpenGL function \\"${name}\\" is not available in \\"" + _versionName() + "\\"");\n    }\n    _makeCurrent();\n    ${returns !== 'void' ? `return ${returns}` : ''}_${name}(${calling});\n}`
        ]);
    }
    return ret;
}

try {
    const data = libfs.readFileSync(__dirname + '/gl.xml').toString();
    const xml = new libxmldom.DOMParser().parseFromString(data, 'text/xml');
    const spec = parseSpec(xml);
    if (process.argv.includes('methods-hpp')) {
        const methods = makeMethods(spec);
        const output = methods.map(([ hpp, cpp ]) => hpp).join('\n');
        console.log(output);
    }
} catch (e) {
    console.error('ERROR: ' + e.message);
}