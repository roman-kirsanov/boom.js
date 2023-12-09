// @ts-check

const libfs = require('fs');
const libxmldom = require('@xmldom/xmldom');

/**
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
 *   versions: string[];
 * }} Func
 */

/**
 * @param {Document} spec
 * @returns {Func[]}
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
        if (protoElement) {
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
                versions: []
            }
        } else {
            throw new Error('<proto /> element not found');
        }
    }

    const [ commandsElement ] = getElementsByTagName(spec.documentElement, 'commands');
    if (commandsElement) {
        const commandElements = getElementsByTagName(commandsElement, 'command');
        for (const commandElement of commandElements) {
            const func = parseCommand(commandElement);
            console.dir(func, { depth: null });
        }
    }

    return [];
}

try {
    const data = libfs.readFileSync(__dirname + '/gl.xml').toString();
    const xmldoc = new libxmldom.DOMParser().parseFromString(data, 'text/xml');
    const parsed = parseSpec(xmldoc);
} catch (e) {
    console.error('ERROR: ' + e.message);
}