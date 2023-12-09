// @ts-check

const libfs = require('fs');
const libxmldom = require('@xmldom/xmldom');

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
 * }} Type
 *
 * @typedef {{
 *   name: string;
 *   type: Type;
 * }} Param
 *
 * @typedef {{
 *   name: string;
 *   params: Param[];
 *   returns: Type;
 *   versions: Version[];
 *   extensions: string[];
 * }} Func
 */

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
        if (node.ELEMENT_NODE) {
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
     * @returns {Type}
     */
    const parseType = element => {
        return {
            name: (element.textContent ?? '')
        }
    }

    /**
     * @param {Element} element
     * @returns {Func}
     */
    const parseCommand = element => {
        const [ protoElement ] = getElementsByTagName(element, 'proto');
        const [ ...paramElements ] = getElementsByTagName(element, 'param');
        const [ typeElement ] = getElementsByTagName(protoElement, 'ptype');
        const [ nameElement ] = getElementsByTagName(protoElement, 'name');
        const returns = (typeElement ? parseType(typeElement) : { name: 'void' });
        const params = paramElements.map(paramElement => {
            const [ typeElement ] = getElementsByTagName(paramElement, 'ptype');
            const [ nameElement ] = getElementsByTagName(paramElement, 'name');
            return {
                name: (nameElement.textContent ?? ''),
                type: (typeElement ? parseType(typeElement) : { name: 'void' })
            }
        })
        return {
            name: (nameElement.textContent ?? ''),
            params,
            returns,
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