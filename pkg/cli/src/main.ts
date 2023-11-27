import { abort } from './utilities/abort'
import { help } from './help/help'
import { run } from './run/run'

const [ , command, ...subargs ] = process.argv;

console.log(command, subargs);

if ((command === null)
|| (command === undefined)
|| (command === '--help')) {
    help();
} else if (command === 'run') {
    run(subargs);
} else if (command === 'init') {

} else {
    abort(`Wrong command "${command}"`);
}