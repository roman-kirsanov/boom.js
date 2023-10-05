import { abort } from './utilities/abort'




const [ , command, subargs ] = process.argv;

if (command === 'init') {

} else if (command === '--help') {
    ;
} else {
    abort(`Wrong command "${command}"`);
}