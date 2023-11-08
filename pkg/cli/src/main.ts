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
console.log('File class: ', JSON.stringify(File));
console.log('FileInfo: ', JSON.stringify(File.Info(process.execPath), null, 4));

const app = new App();
const win = new Window();

app.on('exit', () => app.exit());
win.on('close', () => app.exit());

win.title = "Window 101";
win.size = [640, 480];
win.visible = true;
win.center();