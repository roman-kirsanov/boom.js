import { abort } from './utilities/abort'
import { help } from './help/help'

const [ , command, ...subargs ] = process.argv;

console.log(command, subargs);

if ((command === null)
|| (command === undefined)
|| (command === '--help')) {
    help();
} else if (command === 'run') {

} else if (command === 'init') {

} else {
    abort(`Wrong command "${command}"`);
}