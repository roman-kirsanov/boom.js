import { abort } from '../utilities/abort'

export const run = (args: string[]) => {
    const [ path, ...subargs ] = args;
    if (File.Exists(path)) {
        // @ts-ignore
        globalThis.__run = path;
    } else {
        abort(`File not found "${path}"`);
    }
}