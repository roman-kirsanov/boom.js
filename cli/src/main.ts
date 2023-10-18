import { abort } from './utilities/abort'
import { help } from './help/help'

const [ , command, subargs ] = process.argv;

if ((command === null)
|| (command === undefined)
|| (command === '--help')) {
    help();
} else if (command === 'init') {

} else {
    abort(`Wrong command "${command}"`);
}

console.log('Date.now(): ', Date.now());
console.log('FileInfo: ', JSON.stringify(FileInfo(process.execPath), null, 4));