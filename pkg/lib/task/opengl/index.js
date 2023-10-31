const { writeFileSync } = require('fs');
const { defs } = require(__dirname + '/defs.json');

/**
 * @param {string} value
 * @returns {string}
 */
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
    return 'OpenGL' + result;
}

for (const def of defs) {
    console.log(`auto constexpr ${convertName(def.name)} = ${def.value};`);
}